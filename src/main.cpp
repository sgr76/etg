/*! @file main.cpp
 *
 *  @brief
 *
 *  Copyright 2018 Sebastian Groth
 *
 * This file is part of etg.
 *
 * etg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * etg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <llvm/Support/CommandLine.h>
#include <iostream>
#include <memory>

#include "scope.hpp"
#include "enum.hpp"
#include "file_pool.hpp"
#include "header.hpp"
#include "implementation.hpp"
#include "factory.hpp"


using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace clang;
using namespace llvm;

enum GeneratorStyle
{
    namespaces,
    templates
};


static cl::OptionCategory     MyToolCategory("my options");
static cl::opt<std::string>   outHeader("H", cl::desc("specify the name of the generated header file"), cl::value_desc("filename"), cl::cat(MyToolCategory));
static cl::opt<std::string>   outImpl("o", cl::desc("specify the name of the generated implementation file"), cl::value_desc("filename"), cl::cat(MyToolCategory));
static cl::opt<std::string>   srcInclude("i", cl::desc("specify include for source file"), cl::value_desc("filename"), cl::cat(MyToolCategory));
static cl::opt<GeneratorType> generator("generator", cl::desc("Select the generator (default: standard):"), cl::init(standard), cl::cat(MyToolCategory),
                                        cl::values(
                                            clEnumValN(standard, "std", "standard c++ library"),
                                            clEnumVal(qt5, "Qt5 support")));
static cl::opt<bool>           parseIncluded("parse-included", cl::desc("parse included files"), cl::cat(MyToolCategory));
static cl::opt<GeneratorStyle> generatorStyle("generator-style", cl::desc("Select the generator style (default: namespaces):"), cl::init(namespaces), cl::cat(MyToolCategory),
                                              cl::values(
                                                  clEnumVal(namespaces, "move code for different enums into namespaces"),
                                                  clEnumVal(templates, "use template specialization to apply code to specific enums")));
cl::opt<bool> verbose("v", cl::desc("verbose"), cl::cat(MyToolCategory));


DeclarationMatcher EnumMatcher = enumDecl(hasAttr(clang::attr::Annotate)).bind("etgEnum");

class EtgEnumParser : public MatchFinder::MatchCallback
{
public:
    /*! @brief
     *
     * @param Result TODO
     */
    virtual void run (const MatchFinder::MatchResult & Result)
    {
        if (const EnumDecl * ED = Result.Nodes.getNodeAs<clang::EnumDecl>("etgEnum"))
        {
            if (parseIncluded || Result.Context->getSourceManager().isInMainFile(ED->getLocation()))
            {
                bool isEtg = false;

                for (auto A = ED->specific_attr_begin<clang::AnnotateAttr>(); A != ED->specific_attr_end<clang::AnnotateAttr>(); A++)
                {
                    if (0 == A->getAnnotation().str().compare(0,
                                                              3,
                                                              "etg"))
                    {
                        isEtg = true;
                    }
                }

                if (isEtg)
                {
                    std::shared_ptr<EtgScope> scope(new EtgScope(ED->getParent()));
                    std::shared_ptr<EtgEnum>  enumDef(GeneratorFactory::get()->newEnum(ED));

                    auto classInline = enumDef->getClassInline();

                    if (0 < classInline.length())
                    {
                        scope->setIsClassLocal();

                        EtgFilePool::get().addFile(GeneratorFactory::get()->newHeader(EtgFile::ClassHeader,
                                                                                      classInline,
                                                                                      scope,
                                                                                      enumDef));
                    }
                    else
                    {
                        EtgFilePool::get().getMainHeader()->addDef(scope,
                                                                   enumDef);
                    }

                    EtgFilePool::get().getImplementation()->addDef(scope,
                                                                   enumDef);
                }
                else
                {
                    if (verbose)
                    {
                        std::cerr << "not etg enum with attr" << std::endl;
                    }
                }
            }
        }
    } // run
};


/*! @brief
 *
 * @param argc TODO
 * @param argv TODO
 * @return TODO
 */
int main (int           argc,
          const char ** argv)
{
    char const ** ARGV(new char const *[argc + 3]);
    bool          haveDoubleDash = false;

    for (auto i = 0; i < argc; i++)
    {
        if (0 == strcmp("--",
                        argv[i]))
        {
            haveDoubleDash = true;
        }

        ARGV[i] = argv[i];
    }

    if (!haveDoubleDash)
    {
        ARGV[argc++] = "--";
    }

    ARGV[argc++] = "-DETG_SYMBOLS";
    ARGV[argc++] = "-Wno-pragma-once-outside-header";

    auto OptionsParser = CommonOptionsParser::create(argc, ARGV, MyToolCategory);

    if (!GeneratorFactory::select(generator,
                                  namespaces == generatorStyle))
    {
        std::cerr << "generator '" << generator << "' not found" << std::endl;

        exit(1);
    }
    else
    {
        if (verbose)
        {
            std::cout << "using generator '" << generator << "'" << std::endl;
        }
    }

    ClangTool Tool(OptionsParser->getCompilations(), OptionsParser->getSourcePathList());

    delete[] ARGV;

    EtgFilePool::get().addFile(std::shared_ptr<EtgFile>(GeneratorFactory::get()->newHeader(EtgFile::MainHeader,
                                                                                           outHeader,
                                                                                           srcInclude)));
    EtgFilePool::get().addFile(std::shared_ptr<EtgFile>(GeneratorFactory::get()->newImplementation(outImpl)));

    EtgEnumParser enumParser;
    MatchFinder   Finder;

    Finder.addMatcher(EnumMatcher,
                      &enumParser);

    auto rval = Tool.run(newFrontendActionFactory(&Finder).get());

    EtgFilePool::get().generate();

    return rval;
} // main
