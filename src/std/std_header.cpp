/*! @file std_header.cpp
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
#include "std_header.hpp"

#include <fstream>
#include <enum.hpp>
#include <scope.hpp>
#include <scope_walker.hpp>


EtgHeaderStd::EtgHeaderStd (EtgFile::EtgFiletype _type,
                            const std::string    _filename,
                            const std::string  & _srcInc)
    : EtgHeader(_type, _filename, _srcInc)
{
}


EtgHeaderStd::EtgHeaderStd (EtgFile::EtgFiletype      _type,
                            const std::string         _filename,
                            std::shared_ptr<EtgScope> _scope,
                            std::shared_ptr<EtgEnum>  _enumDef)
    : EtgHeader(_type, _filename, _scope, _enumDef)
{
}


/*! @brief
 *
 * @return TODO
 */
void EtgHeaderStd::generate ()
{
    std::ofstream out(filename);

    if (out.is_open())
    {
        out << "#pragma once" << std::endl << std::endl;

        if (0 < srcInc.length())
        {
            out << "#include <" << srcInc << ">" << std::endl << std::endl;
        }

        out << "#include <etg_std.hpp>" << std::endl;
        out << "#include <string>" << std::endl;
        out << "#include <set>" << std::endl;
        out << "#include <map>" << std::endl << std::endl;

        for (auto & D : defs)
        {
            std::string fqEnum(D.first->getPathImpDef() + D.second->getName());

            out << "template<>" << std::endl;
            out << "struct etg<" << fqEnum << ">" << std::endl;
            out << "{" << std::endl;

            if (D.second->getUseException())
            {
                generateMethods_Exception(out,
                                          D.second,
                                          fqEnum);
            }
            else
            {
                generateMethods_InvalidValue(out,
                                             D.second,
                                             fqEnum);
            }

            if (D.second->getUseExceptionWithDefault())
            {
                generateMethods_ExceptionDefault(out,
                                                 D.second,
                                                 fqEnum);
            }

            if (D.second->getUseIterator())
            {
                out << "  static std::set<" << fqEnum << ">::const_iterator begin();" << std::endl;
                out << "  static std::set<" << fqEnum << ">::const_iterator end();" << std::endl;
            }

            out << "protected:" << std::endl;

            if (D.second->getUseDebug())
            {
                out << "  static const std::map<" << fqEnum << ", std::string> enum2symbol;" << std::endl;
            }

            if (D.second->getUseToken())
            {
                out << "  static const std::map<" << fqEnum << ", std::string> enum2token;" << std::endl;
                out << "  static const std::map<std::string, " << fqEnum << "> token2enum;" << std::endl;
            }

            if (D.second->getUseCast())
            {
                out << "  static const std::set<" << fqEnum << "> enumCast;" << std::endl;
            }

            if (D.second->getTranslate())
            {
                out << "  static std::map<" << fqEnum << ", std::string> enum2translation;" << std::endl;
            }

            out << "};" << std::endl << std::endl;
        }

        out.close();
    }
} // generate


void EtgHeaderStd::generateMethods_Exception (std::ofstream                  & out,
                                              const std::shared_ptr<EtgEnum> & _enum,
                                              const std::string              & fqEnum)
{
    if (_enum->getUseDebug())
    {
        out << "  static const std::string& debugSymbol(" << fqEnum << " v);" << std::endl;
    }

    if (EtgEnum::none != _enum->getUseCast())
    {
        out << "  static " << fqEnum << " cast(int v);" << std::endl;
    }

    if (_enum->getUseToken())
    {
        out << "  static const std::string& token(" << fqEnum << " v);" << std::endl;
        out << "  static " << fqEnum << " cast(const std::string &v);" << std::endl;
    }
}


void EtgHeaderStd::generateMethods_ExceptionDefault (std::ofstream                  & out,
                                                     const std::shared_ptr<EtgEnum> & _enum,
                                                     const std::string              & fqEnum)
{
    if (EtgEnum::none != _enum->getUseCast())
    {
        out << "  static " << fqEnum << " cast(int v, " << fqEnum << " d);" << std::endl;
    }

    if (_enum->getUseToken())
    {
        out << "  static " << fqEnum << " cast(const std::string &v, " << fqEnum << " d);" << std::endl;
    }
}


void EtgHeaderStd::generateMethods_InvalidValue (std::ofstream                  & out,
                                                 const std::shared_ptr<EtgEnum> & _enum,
                                                 const std::string              & fqEnum)
{
    if (_enum->getUseDebug())
    {
        out << "  static const std::string& debugSymbol(" << fqEnum << " v);" << std::endl;
    }

    if (EtgEnum::none != _enum->getUseCast())
    {
        out << "  static " << fqEnum << " cast(int v, " << fqEnum << " d=" << _enum->getInvalidValue() << ");" << std::endl;
    }

    if (_enum->getUseToken())
    {
        out << "  static const std::string& token(" << fqEnum << " v);" << std::endl;
        out << "  static " << fqEnum << " cast(const std::string &v, " << fqEnum << " d=" << _enum->getInvalidValue() << ");" << std::endl;
    }
}
