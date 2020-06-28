/*! @file qt5_factory.cpp
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
#include "qt5_factory.hpp"

#include "qt5_enum.hpp"
#include "qt5_header.hpp"
#include "qt5_implementation.hpp"


GeneratorFactoryQt5::GeneratorFactoryQt5 ()
{
}

GeneratorType GeneratorFactoryQt5::getType()
{
    return qt5;
}


bool GeneratorFactoryQt5::getUsesNamespaces ()
{
    return false;
}


/*! @brief
 *
 * @param ed TODO
 * @return TODO
 */
std::shared_ptr<EtgEnum> GeneratorFactoryQt5::newEnum (const clang::EnumDecl * ed) const
{
    return std::shared_ptr<EtgEnum>(new EtgEnumQt5(ed));
}


/*! @brief
 *
 * @param _type TODO
 * @param _filename TODO
 * @param _srcInc TODO
 * @return TODO
 */
std::shared_ptr<EtgHeader> GeneratorFactoryQt5::newHeader (EtgFile::EtgFiletype _type,
                                                           const std::string    _filename,
                                                           const std::string  & _srcInc) const
{
    return std::shared_ptr<EtgHeader>(new EtgHeaderQt5(_type,
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
std::shared_ptr<EtgHeader> GeneratorFactoryQt5::newHeader (EtgFile::EtgFiletype      _type,
                                                           const std::string         _filename,
                                                           std::shared_ptr<EtgScope> _scope,
                                                           std::shared_ptr<EtgEnum>  _enumDef) const
{
    return std::shared_ptr<EtgHeader>(new EtgHeaderQt5(_type,
                                                       _filename,
                                                       _scope,
                                                       _enumDef));
}


/*! @brief
 *
 * @param _filename TODO
 * @return TODO
 */
std::shared_ptr<EtgImplementation> GeneratorFactoryQt5::newImplementation (const std::string _filename) const
{
    return std::shared_ptr<EtgImplementation>(new EtgImplementationQt5(_filename));
}


const std::string GeneratorFactoryQt5::name = "qt5";

GeneratorFactory::GeneratorRegistration<GeneratorFactoryQt5> GeneratorFactoryQt5::factory;
