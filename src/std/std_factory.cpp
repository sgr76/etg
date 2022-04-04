/*! @file std_factory.cpp
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
#include "std_factory.hpp"

#include "std_enum.hpp"
#include "std_header.hpp"
#include "std_implementation.hpp"


GeneratorFactoryStd::GeneratorFactoryStd ()
{
}


GeneratorType GeneratorFactoryStd::getType ()
{
    return standard;
}


bool GeneratorFactoryStd::getUsesNamespaces ()
{
    return false;
}


/*! @brief
 *
 * @param ed TODO
 * @return TODO
 */
std::shared_ptr<EtgEnum> GeneratorFactoryStd::newEnum (const clang::EnumDecl * ed) const
{
    return std::shared_ptr<EtgEnum>(new EtgEnumStd(ed));
}


/*! @brief
 *
 * @param _type TODO
 * @param _filename TODO
 * @param _srcInc TODO
 * @return TODO
 */
std::shared_ptr<EtgHeader> GeneratorFactoryStd::newHeader (EtgFile::EtgFiletype _type,
                                                           const std::string    _filename,
                                                           const std::string  & _srcInc) const
{
    return std::shared_ptr<EtgHeader>(new EtgHeaderStd(_type,
                                                       _filename,
                                                       _srcInc));
}


/*! @brief
 *
 * @param _type TODO
 * @param _filename TODO
 * @param _scope TODO
 * @param _enumDef TODO
 * @return TODO
 */
std::shared_ptr<EtgHeader> GeneratorFactoryStd::newHeader (EtgFile::EtgFiletype      _type,
                                                           const std::string         _filename,
                                                           std::shared_ptr<EtgScope> _scope,
                                                           std::shared_ptr<EtgEnum>  _enumDef) const
{
    return std::shared_ptr<EtgHeader>(new EtgHeaderStd(_type,
                                                       _filename,
                                                       _scope,
                                                       _enumDef));
}


/*! @brief
 *
 * @param _filename TODO
 * @return TODO
 */
std::shared_ptr<EtgImplementation> GeneratorFactoryStd::newImplementation (const std::string _filename) const
{
    return std::shared_ptr<EtgImplementation>(new EtgImplementationStd(_filename));
}


const std::string GeneratorFactoryStd::name = "std";

GeneratorFactory::GeneratorRegistration<GeneratorFactoryStd> GeneratorFactoryStd::factory;
