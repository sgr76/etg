/*! @file header.hpp
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

#include "file.hpp"


class EtgHeader : public EtgFile
{
public:
    EtgHeader (EtgFiletype         _type,
               const std::string   _filename,
               const std::string & _srcInc);
    EtgHeader (EtgFiletype               _type,
               const std::string         _filename,
               std::shared_ptr<EtgScope> _scope,
               std::shared_ptr<EtgEnum>  _enumDef);

    void generateIncludes (std::ofstream & out) override;

protected:
    std::string srcInc;
};
