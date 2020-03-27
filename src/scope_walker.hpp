/*! @file scope_walker.hpp
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

#include <fstream>
#include <memory>
#include <string>
#include <list>


class EtgScope;


class EtgScopeWalker
{
public:
    EtgScopeWalker ();
    virtual ~EtgScopeWalker ();

    void walkHeader (std::ofstream             & out,
                     std::shared_ptr<EtgScope> & target);
    void finish (std::ofstream & out);

protected:
    void walk (std::ofstream                          & out,
               std::shared_ptr<std::list<std::string> > targetPath);

protected:
    std::list<std::string> currentPath;
};
