/*! @file file_pool.cpp
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
#include "file_pool.hpp"

#include "header.hpp"
#include "implementation.hpp"


EtgFilePool::EtgFilePool ()
{
}


EtgFilePool::~EtgFilePool ()
{
}


/*! @brief
 *
 * @return TODO
 */
EtgFilePool & EtgFilePool::get ()
{
    if (nullptr == pool)
    {
        pool = std::shared_ptr<EtgFilePool>(new EtgFilePool);
    }

    return *pool;
}


/*! @brief
 *
 * @param type TODO
 * @param file TODO
 */
void EtgFilePool::addFile (std::shared_ptr<EtgFile> file)
{
    switch (file->getType())
    {
    case EtgFile::MainHeader:
        mainHeader = file;
        break;
    case EtgFile::Implementation:
        implementation = file;
        break;
    default:
        break;
    }

    files.push_back(file);
} // addFile


/*! @brief
 */
void EtgFilePool::generate ()
{
    for (auto & F : files)
    {
        F->generate();
    }
}


/*! @brief
 *
 * @param pF TODO
 */
void EtgFilePool::generateIncludes (std::ofstream & out)
{
    for (auto & F : files)
    {
        if (EtgFile::Implementation != F->getType())
        {
            F->generateIncludes(out);
        }
    }
}


/*! @brief
 *
 * @return TODO
 */
std::shared_ptr<EtgFile> & EtgFilePool::getImplementation ()
{
    return implementation;
}


/*! @brief
 *
 * @return TODO
 */
std::shared_ptr<EtgFile> & EtgFilePool::getMainHeader ()
{
    return mainHeader;
}


std::shared_ptr<EtgFilePool> EtgFilePool::pool;
