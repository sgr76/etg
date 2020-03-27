/*! @file header.cpp
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
#include "header.hpp"

#include "enum.hpp"
#include "scope.hpp"
#include "scope_walker.hpp"


EtgHeader::EtgHeader (EtgFile::EtgFiletype _type,
                      const std::string    _filename,
                      const std::string  & _srcInc)
    : EtgFile(_type, _filename),
      srcInc(_srcInc)
{
}


EtgHeader::EtgHeader (EtgFiletype               _type,
                      const std::string         _filename,
                      std::shared_ptr<EtgScope> _scope,
                      std::shared_ptr<EtgEnum>  _enumDef)
    : EtgFile(_type, _filename, _scope, _enumDef)
{
}


/*! @brief
 *
 * @param pF TODO
 */
void EtgHeader::generateIncludes (std::ofstream & out)
{
    if (0 < srcInc.length())
    {
        out << "#include \"" << filename << "\"" << std::endl;
    }
}
