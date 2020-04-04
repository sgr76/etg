/*! @file std_factory.hpp
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

#include <factory.hpp>


class GeneratorFactoryStdNs : public GeneratorFactory
{
protected:
    GeneratorFactoryStdNs (const GeneratorFactoryStdNs &) = delete;

    GeneratorFactoryStdNs & operator = (const GeneratorFactoryStdNs &) = delete;

public:
    GeneratorFactoryStdNs ();

    std::shared_ptr<EtgEnum> newEnum (const clang::EnumDecl * ed) const override;

    std::shared_ptr<EtgHeader> newHeader (EtgFile::EtgFiletype _type,
                                          const std::string    _filename,
                                          const std::string  & _srcInc) const override;

    std::shared_ptr<EtgHeader> newHeader (EtgFile::EtgFiletype      _type,
                                          const std::string         _filename,
                                          std::shared_ptr<EtgScope> _scope,
                                          std::shared_ptr<EtgEnum>  _enumDef) const override;

    std::shared_ptr<EtgImplementation> newImplementation (const std::string _filename) const override;

protected:
    const std::string & getName () override;
bool getUsesNamespaces () override;

private:
    static const std::string                          name;

    static GeneratorRegistration<GeneratorFactoryStdNs> factory;
};
