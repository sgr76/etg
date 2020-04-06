/*! @file enum.cpp
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
#include "enum.hpp"

#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/AST/AttrIterator.h>
#include <clang/AST/Decl.h>
#include <clang/Tooling/CommonOptionsParser.h>

#include <iostream>

extern llvm::cl::opt<bool> verbose;


EtgEnum::EtgEnum (const clang::EnumDecl * ed)
    : addDebug(NoDebug),
      addCast(false),
      addToken(false),
      addTranslation(false),
      addIterator(false),
      addFormat(false),
      useException(true),
      exceptionWithDefault(false),
      caseInsensitive(false),
      isClass(false)
{
    if (verbose)
    {
        ed->dump();
    }

    name    = ed->getNameAsString();
    isClass = ed->isScoped();

    if (verbose && isClass)
    {
        std::cerr << "  class enum!" << std::endl;
    }

    parseEnumAttr(ed);

    for (auto I = ed->enumerator_begin(); I != ed->enumerator_end(); I++)
    {
        parseItem(*I);
    }

    if (verbose)
    {
        std::cerr << "  enum: " << name;

        if (NoDebug != addDebug)
        {
            std::cerr << ((ShortDebug == addDebug) ? "  debug:short" : "  debug:long");
        }

        if (addCast)
        {
            std::cerr << "  cast";
        }

        if (addToken)
        {
            std::cerr << "  token";
        }

        if (addTranslation)
        {
            std::cerr << "  translation";
        }

        if (addIterator)
        {
            std::cerr << "  iterator";
        }

        if (addFormat)
        {
            std::cerr << "  format";
        }

        if (useException)
        {
            std::cerr << "  exception";
        }

        if (exceptionWithDefault)
        {
            std::cerr << "  expt_default";
        }

        if (0 < classInline.length())
        {
            std::cerr << "  inline(" << classInline << ")";
        }

        std::cerr << std::endl;

        for (auto & I : items)
        {
            std::cerr << "    item: " << (I->defaultValue ? "*" : "") << I->name << " -> ";

            if (0 < I->text.length())
            {
                std::cerr << I->text;
            }
            else
            {
                std::cerr << I->name;
            }

            std::cerr << std::endl;
        }
    }

    if ((0 == invalidValue.length()) && (!items.empty()))
    {
        invalidValue = items.front()->name;
    }
}


EtgEnum::~EtgEnum ()
{
}


/*! @brief
 *
 * @param ed TODO
 */
void EtgEnum::parseEnumAttr (const clang::EnumDecl * ed)
{
    for (auto A = ed->specific_attr_begin<clang::AnnotateAttr>(); A != ed->specific_attr_end<clang::AnnotateAttr>(); A++)
    {
        auto value = A->getAnnotation().str();

        if (0 == value.compare(0,
                               4,
                               "etg "))
        {
            int pos = 3;

            do
            {
                if ((pos = value.find_first_not_of(" ,",
                                                   pos)) != std::string::npos)
                {
                    auto end = value.find_first_of(" ,",
                                                   pos);

                    if (verbose)
                    {
                        std::cerr << "pos:" << pos << "   end:" << end << std::endl;
                    }

                    if (std::string::npos != end)
                    {
                        parseEnumAttrItem(value.substr(pos,
                                                       end - pos));
                    }
                    else
                    {
                        parseEnumAttrItem(value.substr(pos,
                                                       value.size() - pos));
                    }

                    pos = end;
                }
            }
            while (pos != std::string::npos);
        }
    }
} // parseEnumAttr


void EtgEnum::parseEnumAttrItem (const std::string & attr)
{
    if (verbose)
    {
        std::cerr << "EtgEnum::parseEnumAttrItem(" << attr << ")" << std::endl;
    }

    if ("debug" == attr)
    {
        addDebug = ShortDebug;
    }

    if ("long_debug" == attr)
    {
        addDebug = LongDebug;
    }

    if ("cast" == attr)
    {
        addCast = true;
    }

    if ("token" == attr)
    {
        addToken = true;
    }

    if ("translation" == attr)
    {
        addTranslation = true;
    }

    if ("iterator" == attr)
    {
        addIterator = true;
    }

    if ("format" == attr)
    {
        addFormat = true;
    }

    if ("exception_default" == attr)
    {
        exceptionWithDefault = true;
    }

    if ("case_insensitive" == attr)
    {
        caseInsensitive = true;
    }
}


/*! @brief
 *
 * @param ec TODO
 */
void EtgEnum::parseItem (const clang::EnumConstantDecl * ec)
{
    std::shared_ptr<Item> item(new Item);

    item->name         = ec->getNameAsString();
    item->defaultValue = false;

    bool missingToken = true;

    for (auto A = ec->specific_attr_begin<clang::AnnotateAttr>(); A != ec->specific_attr_end<clang::AnnotateAttr>(); A++)
    {
        auto value = A->getAnnotation().str();

        if (0 == value.compare(0,
                               9,
                               "etg_text "))
        {
            item->text = value.substr(9);

            missingToken = false;
        }

        if (0 == value.compare("etg_invalid_value"))
        {
            item->defaultValue = true;

            if (!useException)
            {
#warning duplicate default value
            }

            if (!exceptionWithDefault)
            {
#warning conflicting attributes
            }

            useException         = false;
            exceptionWithDefault = false;
        }
    }

    if (missingToken)
    {
        item->text = item->name;
    }

    items.push_back(item);
} // parseItem


/*! @brief
 *
 * @return TODO
 */
const std::string & EtgEnum::getClassInline ()
{
    return classInline;
}


/*! @brief
 *
 * @return TODO
 */
const std::string EtgEnum::getInvalidValue ()
{
    if (isClass)
    {
        return getScopePrefix() + invalidValue;
    }

    return invalidValue;
}


const std::string EtgEnum::getScopePrefix ()
{
    if (isClass)
    {
        return "::" + name + "::";
    }

    return "";
}


/*! @brief
 *
 * @return TODO
 */
const std::string & EtgEnum::getName ()
{
    return name;
}


bool EtgEnum::getUseDebug ()
{
    return NoDebug != addDebug;
}


bool EtgEnum::getUseLongDebug ()
{
    return LongDebug == addDebug;
}


EtgEnum::SetDatastructure EtgEnum::getSetDataSource ()
{
    if (addIterator)
    {
        return set;
    }

    if (addCast)
    {
        if (addToken)
        {
            return token;
        }

        if (addDebug)
        {
            return debug;
        }

        if (addTranslation)
        {
            return translation;
        }

        return set;
    }
    else
    {
        return none;
    }
}


bool EtgEnum::getUseCast ()
{
    return addCast;
}


bool EtgEnum::getNeedSet ()
{
    return (addCast || addIterator) && (!(addToken || addDebug || addTranslation));
}


bool EtgEnum::getUseIterator ()
{
    return addIterator;
}


bool EtgEnum::getUseToken ()
{
    return addToken;
}


/*! @brief
 *
 * @return TODO
 */
bool EtgEnum::getTranslate ()
{
    return addTranslation;
}


bool EtgEnum::getFormat ()
{
    return addFormat;
}


/*! @brief
 *
 * @return TODO
 */
bool EtgEnum::getUseException ()
{
    return useException;
}


bool EtgEnum::getUseExceptionWithDefault ()
{
    return exceptionWithDefault;
}


bool EtgEnum::getUseCaseInsensitive ()
{
    return caseInsensitive;
}
