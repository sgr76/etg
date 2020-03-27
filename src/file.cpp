/*! @file file.cpp
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
#include "file.hpp"

#include "scope.hpp"
#include "enum.hpp"


EtgFile::EtgFile (EtgFiletype         _type,
                  const std::string & _filename)
    : type(_type),
      filename(_filename)
{
}


EtgFile::EtgFile (EtgFiletype                 _type,
                  const std::string         & _filename,
                  std::shared_ptr<EtgScope> & _scope,
                  std::shared_ptr<EtgEnum>  & _enumDef)
    : type(_type),
      filename(_filename)
{
    addDef(_scope,
           _enumDef);
}


EtgFile::~EtgFile ()
{
}


/*! @brief
 *
 * @param _scope TODO
 * @param _enumDef TODO
 */
void EtgFile::addDef (std::shared_ptr<EtgScope> & _scope,
                      std::shared_ptr<EtgEnum>  & _enumDef)
{
    for (auto I = defs.begin(); I != defs.end(); I++)
    {
        if (_scope->getFullPath() < I->first->getFullPath())
        {
            defs.insert(I,
                        std::pair<std::shared_ptr<EtgScope>, std::shared_ptr<EtgEnum> >(_scope,
                                                                                        _enumDef));

            return;
        }
    }

    defs.push_back(std::pair<std::shared_ptr<EtgScope>, std::shared_ptr<EtgEnum> >(_scope,
                                                                                   _enumDef));
} // addDef


/*! @brief
 *
 * @param pF TODO
 */
void EtgFile::generateIncludes (std::ofstream & out)
{
}


/*! @brief
 *
 * @return TODO
 */
EtgFile::EtgFiletype EtgFile::getType ()
{
    return type;
}
