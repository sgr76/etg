/*! @file file.hpp
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
#include <list>
#include <memory>
#include <string>

class EtgScope;
class EtgEnum;


class EtgFile
{
public:
    enum EtgFiletype
    {
        MainHeader,
        Implementation,
        ClassHeader
    };


    EtgFile (EtgFiletype         _type,
             const std::string & _filename);
    EtgFile (EtgFiletype                 _type,
             const std::string         & _filename,
             std::shared_ptr<EtgScope> & _scope,
             std::shared_ptr<EtgEnum>  & _enumDef);

    virtual ~EtgFile ();

    void addDef (std::shared_ptr<EtgScope> & _scope,
                 std::shared_ptr<EtgEnum>  & _enumDef);
    EtgFiletype getType ();

    virtual void generate () = 0;
    virtual void generateIncludes (std::ofstream & out);

protected:
    EtgFiletype                                                                 type;

    std::string                                                                 filename;

    std::list<std::pair<std::shared_ptr<EtgScope>, std::shared_ptr<EtgEnum> > > defs;
};
