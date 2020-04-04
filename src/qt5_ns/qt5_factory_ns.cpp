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
#include "qt5_factory_ns.hpp"

#include "qt5_enum_ns.hpp"
#include "qt5_header_ns.hpp"
#include "qt5_implementation_ns.hpp"


GeneratorFactoryQt5Ns::GeneratorFactoryQt5Ns ()
{
}


/*! @brief
 *
 * @return TODO
 */
const std::string & GeneratorFactoryQt5Ns::getName ()
{
    return name;
}


bool GeneratorFactoryQt5Ns::getUsesNamespaces ()
{
    return true;
}


/*! @brief
 *
 * @param ed TODO
 * @return TODO
 */
std::shared_ptr<EtgEnum> GeneratorFactoryQt5Ns::newEnum (const clang::EnumDecl * ed) const
{
    return std::shared_ptr<EtgEnum>(new EtgEnumQt5Ns(ed));
}


/*! @brief
 *
 * @param _type TODO
 * @param _filename TODO
 * @param _srcInc TODO
 * @return TODO
 */
std::shared_ptr<EtgHeader> GeneratorFactoryQt5Ns::newHeader (EtgFile::EtgFiletype _type,
                                                             const std::string    _filename,
                                                             const std::string  & _srcInc) const
{
    return std::shared_ptr<EtgHeader>(new EtgHeaderQt5Ns(_type,
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
std::shared_ptr<EtgHeader> GeneratorFactoryQt5Ns::newHeader (EtgFile::EtgFiletype      _type,
                                                             const std::string         _filename,
                                                             std::shared_ptr<EtgScope> _scope,
                                                             std::shared_ptr<EtgEnum>  _enumDef) const
{
    return std::shared_ptr<EtgHeader>(new EtgHeaderQt5Ns(_type,
                                                         _filename,
                                                         _scope,
                                                         _enumDef));
}


/*! @brief
 *
 * @param _filename TODO
 * @return TODO
 */
std::shared_ptr<EtgImplementation> GeneratorFactoryQt5Ns::newImplementation (const std::string _filename) const
{
    return std::shared_ptr<EtgImplementation>(new EtgImplementationQt5Ns(_filename));
}


const std::string GeneratorFactoryQt5Ns::name = "qt5";

GeneratorFactory::GeneratorRegistration<GeneratorFactoryQt5Ns> GeneratorFactoryQt5Ns::factory;
