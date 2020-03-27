/*! @file scope.cpp
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
#include "scope.hpp"

#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <iostream>

extern llvm::cl::opt<bool> verbose;


EtgScope::EtgScope (const clang::DeclContext * ctx)
    : namespaceCount(0),
      classCount(0),
      classLocal(false)
{
    while (ctx->isNamespace() || ctx->isRecord())
    {
        if (ctx->isNamespace())
        {
            auto ns = clang::NamespaceDecl::castFromDeclContext(ctx);

            if (verbose)
            {
                std::cerr << "namespace: " << ns->getNameAsString() << std::endl;
            }

            path.push_front(std::pair<EtgScopeType, std::string>(ScopeNamespace,
                                                                 ns->getNameAsString()));

            if (0 != classCount)
            {
                pathImpEtg = "etg::" + pathImpEtg;
            }

            pathImpDef = ns->getNameAsString() + "::" + pathImpDef;
            pathImpEtg = ns->getNameAsString() + "::" + pathImpEtg;

            namespaceCount++;
        }

        if (ctx->isRecord())
        {
            auto rec = clang::RecordDecl::castFromDeclContext(ctx);

            if (verbose)
            {
                std::cerr << "object: " << rec->getNameAsString() << std::endl;
            }

            path.push_front(std::pair<EtgScopeType, std::string>(ScopeClass,
                                                                 rec->getNameAsString()));

            pathImpDef = rec->getNameAsString() + "::" + pathImpDef;
            pathImpEtg = rec->getNameAsString() + "::" + pathImpEtg;

            classCount++;
        }

        ctx = ctx->getParent();
    }

    pathImpDef = "::" + pathImpDef;

    if (0 == classCount)
    {
        pathImpEtg += "etg::";
    }
    else
    {
        if ((0 < classCount) && (0 == namespaceCount))
        {
            pathImpEtg = "etg::" + pathImpEtg;
        }
    }

    for (auto & P : path)
    {
        pathFull += P.second;
    }
};


EtgScope::~EtgScope ()
{
}


/*! @brief
 *
 * @return TODO
 */
std::shared_ptr<std::list<std::string> > EtgScope::getPathListHeader ()
{
    std::shared_ptr<std::list<std::string> > res(new std::list<std::string>);

    bool etgNsDone = false;
    auto cc        = classCount;

    if (classLocal)
    {
        res->push_back("struct etg");
    }
    else
    {
        for (auto & S : path)
        {
            switch (S.first)
            {
            case ScopeClass:
                cc--;

                if (0 == cc)
                {
                    res->push_back("namespace etg");

                    etgNsDone = true;
                }

                res->push_back("namespace " + S.second);
                break;
            case ScopeNamespace:
                res->push_back("namespace " + S.second);
                break;
            default:
                break;
            } // switch
        }

        if (!etgNsDone)
        {
            res->push_back("namespace etg");
        }
    }

    return res;
} // getPathListHeader


/*! @brief
 */
void EtgScope::setIsClassLocal ()
{
    classLocal = true;
}


const std::string & EtgScope::getFullPath ()
{
    return pathFull;
}


const std::string & EtgScope::getPathImpEtg ()
{
    return pathImpEtg;
}


const std::string & EtgScope::getPathImpDef ()
{
    return pathImpDef;
}
