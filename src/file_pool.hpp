/*! @file file_pool.hpp
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

#include <fstream>
#include <memory>
#include <list>

class EtgHeader;
class EtgImplementation;


class EtgFilePool
{
protected:
    EtgFilePool ();

public:
    virtual ~EtgFilePool ();

    static EtgFilePool & get ();

    void addFile (std::shared_ptr<EtgFile> file);

    std::shared_ptr<EtgFile> & getMainHeader ();

    std::shared_ptr<EtgFile> & getImplementation ();

    void generate ();
    void generateIncludes (std::ofstream & out);

protected:
    std::list<std::shared_ptr<EtgFile> > files;

    std::shared_ptr<EtgFile>             mainHeader;
    std::shared_ptr<EtgFile>             implementation;

    static std::shared_ptr<EtgFilePool>  pool;
};
