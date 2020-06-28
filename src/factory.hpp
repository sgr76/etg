/*! @file factory.hpp
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

#include <file.hpp>

#include <list>
#include <string>
#include <memory>


namespace clang
{
class EnumDecl;
class EnumConstantDecl;
}

class EtgEnum;
class EtgScope;
class EtgHeader;
class EtgImplementation;

enum GeneratorType{
    standard,qt5
};


class GeneratorFactory
{
protected:
    GeneratorFactory ();
    GeneratorFactory (const GeneratorFactory &) = delete;

    GeneratorFactory & operator = (const GeneratorFactory &) = delete;

public:
    static const GeneratorFactory * get ();
    static bool select (GeneratorType _type,
                        bool                _useNamespaces);

    virtual std::shared_ptr<EtgEnum> newEnum (const clang::EnumDecl * ed) const = 0;

    virtual std::shared_ptr<EtgHeader> newHeader (EtgFile::EtgFiletype _type,
                                                  const std::string    _filename,
                                                  const std::string  & _srcInc) const = 0;

    virtual std::shared_ptr<EtgHeader> newHeader (EtgFile::EtgFiletype      _type,
                                                  const std::string         _filename,
                                                  std::shared_ptr<EtgScope> _scope,
                                                  std::shared_ptr<EtgEnum>  _enumDef) const = 0;

    virtual std::shared_ptr<EtgImplementation> newImplementation (const std::string _filename) const = 0;

protected:
    virtual GeneratorType getType () = 0;
    virtual bool getUsesNamespaces ()      = 0;
    static void registerGenerator (std::shared_ptr<GeneratorFactory> generator);

    template<class T>
    class GeneratorRegistration
    {
    public:
        GeneratorRegistration ()
        {
            GeneratorFactory::registerGenerator(std::shared_ptr<GeneratorFactory>(new T));
        }
    };


private:
    static std::shared_ptr<GeneratorFactory>             selected;

    static std::list<std::shared_ptr<GeneratorFactory> > generators;
};
