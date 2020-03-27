/*! @file scope.hpp
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
#pragma once

#include <list>
#include <string>
#include <memory>


namespace clang
{
class DeclContext;
};


class EtgScope
{
public:
    EtgScope (const clang::DeclContext * ctx);
    virtual ~EtgScope ();

    void setIsClassLocal ();

    const std::string & getFullPath ();
    const std::string & getPathImpEtg ();
    const std::string & getPathImpDef ();

    std::shared_ptr<std::list<std::string> > getPathListHeader ();

protected:
    enum EtgScopeType
    {
        ScopeNamespace,
        ScopeClass
    };


    std::list<std::pair<EtgScopeType, std::string> > path;

    unsigned                                         namespaceCount;
    unsigned                                         classCount;
    bool                                             classLocal;

    std::string                                      pathFull;
    std::string                                      pathImpEtg;
    std::string                                      pathImpDef;
};
