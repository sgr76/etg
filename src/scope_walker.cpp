/*! @file scope_walker.cpp
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
#include "scope_walker.hpp"

#include "scope.hpp"


EtgScopeWalker::EtgScopeWalker ()
{
}


EtgScopeWalker::~EtgScopeWalker ()
{
}


/*! @brief
 *
 * @param target TODO
 */
void EtgScopeWalker::walkHeader (std::ofstream             & out,
                                 std::shared_ptr<EtgScope> & target)
{
    walk(out,
         target->getPathListHeader());
}


/*! @brief
 *
 * @param targetPath TODO
 */
void EtgScopeWalker::walk (std::ofstream                          & out,
                           std::shared_ptr<std::list<std::string> > targetPath)
{
    unsigned matching = 0;

    for (auto I1 = currentPath.begin(), I2 = targetPath->begin(); (I1 != currentPath.end()) && (I2 != targetPath->end()) && (0 == I1->compare(*I2)); ++I1, ++I2)
    {
        matching++;
    }

    for (auto i = currentPath.size() - matching; i > 0; i--)
    {
        out << "};" << std::endl;

        currentPath.pop_back();
    }

    for (auto i = 0; i < matching; i++)
    {
        targetPath->pop_front();
    }

    for (auto & I : *targetPath)
    {
        out << I << " {" << std::endl;

        currentPath.push_back(I);
    }
} // walk


/*! @brief
 */
void EtgScopeWalker::finish (std::ofstream & out)
{
    for (auto & I : currentPath)
    {
        out << "};" << std::endl;
    }

    currentPath.clear();
}
