/*! @file factory.cpp
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
#include "factory.hpp"


GeneratorFactory::GeneratorFactory ()
{
}


/*! @brief
 *
 * @return TODO
 */
const GeneratorFactory * GeneratorFactory::get ()
{
    return selected.get();
}


/*! @brief
 *
 * @param name TODO
 * @return TODO
 */
bool GeneratorFactory::select (GeneratorType _type,
                               bool          _useNamespaces)
{
    for (auto & I : generators)
    {
        if ((I->getUsesNamespaces() == _useNamespaces) && (I->getType() == _type))
        {
            selected = I;

            return true;
        }
    }

    return false;
} // select


/*! @brief
 *
 * @param generator TODO
 * @return TODO
 */
void GeneratorFactory::registerGenerator (std::shared_ptr<GeneratorFactory> generator)
{
    generators.push_back(generator);
}


std::shared_ptr<GeneratorFactory> GeneratorFactory::selected;

std::list<std::shared_ptr<GeneratorFactory> > GeneratorFactory::generators;
