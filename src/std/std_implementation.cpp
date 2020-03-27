/*! @file std_implementation.cpp
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
#include "std_implementation.hpp"

#include <fstream>
#include <enum.hpp>
#include <scope.hpp>
#include <file_pool.hpp>
#include <scope_walker.hpp>

EtgImplementationStd::EtgImplementationStd (const std::string _filename)
    : EtgImplementation(_filename)
{
}


void EtgImplementationStd::generate ()
{
    std::ofstream out(filename);

    if (out.is_open())
    {
        EtgFilePool::get().generateIncludes(out);

        out << std::endl;

        out << "#include <algorithm>" << std::endl << std::endl;

        for (auto & D : defs)
        {
            std::string fqEnum(D.first->getPathImpDef() + D.second->getName());
            std::string scope(D.first->getPathImpEtg() + D.second->getName());

            generateMethods_Exception_InvalidValue(out,
                                                   D.second,
                                                   scope,
                                                   fqEnum);

            if (D.second->getUseExceptionWithDefault())
            {
                generateMethods_ExceptionDefault(out,
                                                 D.second,
                                                 scope,
                                                 fqEnum);
            }

            D.second->generateValues(out,
                                     fqEnum,
                                     scope,
                                     D.second->getTranslate());
        }

        out.close();
    }
} // generate


void EtgImplementationStd::generateMethods_Exception_InvalidValue (std::ofstream                  & out,
                                                                   const std::shared_ptr<EtgEnum> & _enum,
                                                                   const std::string &
                                                                   scope,
                                                                   const std::string & fqEnum)
{
    if (_enum->getUseToken())
    {
        if (_enum->getUseException())
        {
            out << fqEnum << " " << scope << "::getEnum(const std::string &v) {" << std::endl;
        }
        else
        {
            out << fqEnum << " " << scope << "::getEnum(const std::string &v, " << fqEnum << " d) {" << std::endl;
        }

        if (_enum->getUseCaseInsensitive())
        {
            out << "  auto tmp = v;" << std::endl;
            out << "  std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](unsigned char c){ return std::toupper(c); });";
            out << "  auto rval = token2enum.find(tmp);" << std::endl;
        }
        else
        {
            out << "  auto rval = token2enum.find(v);" << std::endl;
        }

        out << "  if (token2enum.end() != rval) {" << std::endl;
        out << "    return rval->second;" << std::endl;
        out << "  }" << std::endl << std::endl;

        if (_enum->getUseException())
        {
            out << "  throw std::exception();" << std::endl;
        }
        else
        {
            out << "  return d;" << std::endl;
        }

        out << "}" << std::endl << std::endl;

        out << "const std::string & " << scope << "::getToken(" << fqEnum << " v) {" << std::endl;
        out << "  auto rval = enum2token.find(v);" << std::endl;
        out << "  if (enum2token.end() != rval) {" << std::endl;
        out << "    return rval->second;" << std::endl;
        out << "  }" << std::endl << std::endl;

        if (_enum->getUseException())
        {
            out << "  throw std::exception();" << std::endl;
        }
        else
        {
            out << "  return enum2token.at(" << _enum->getInvalidValue() << ");" << std::endl;
        }

        out << "}" << std::endl << std::endl;
    }

    if (EtgEnum::none != _enum->getUseCast())
    {
        if (_enum->getUseException())
        {
            out << fqEnum << " " << scope << "::cast(int v) {" << std::endl;
        }
        else
        {
            out << fqEnum << " " << scope << "::cast(int v, " << fqEnum << " d) {" << std::endl;
        }

        std::string lookupTable;

        switch (_enum->getSetDataSource())
        {
        case EtgEnum::token:
            lookupTable = "enum2token";
            break;
        case EtgEnum::debug:
            lookupTable = "enum2symbol";
            break;
        case EtgEnum::translation:
            lookupTable = "enum2translation";
            break;
        case EtgEnum::set:
            lookupTable = "enumCast";
            break;
        case EtgEnum::none:
            break;
        }

        out << "  auto rval = " << lookupTable << ".find((" << fqEnum << ")v);" << std::endl;
        out << "  if (" << lookupTable << ".end() != rval) {" << std::endl;
        out << "    return (" << fqEnum << ")v;" << std::endl;
        out << "  }" << std::endl << std::endl;

        if (_enum->getUseException())
        {
            out << "  throw std::exception();" << std::endl;
        }
        else
        {
            out << "  return d;" << std::endl;
        }

        out << "}" << std::endl << std::endl;
    }

    if (_enum->getUseIterator())
    {
        out << "std::set<" << fqEnum << ">::const_iterator " << scope << "::begin() {" << std::endl;
        out << "  return enumCast.cbegin();" << std::endl;
        out << "}" << std::endl << std::endl;

        out << "std::set<" << fqEnum << ">::const_iterator " << scope << "::end() {" << std::endl;
        out << "  return enumCast.cend();" << std::endl;
        out << "}" << std::endl << std::endl;
    }

    if (_enum->getUseDebug())
    {
        out << "const std::string & " << scope << "::getDebugSymbol(" << fqEnum << " v) {" << std::endl;
        out << "  auto rval = enum2symbol.find(v);" << std::endl;
        out << "  if (enum2symbol.end() != rval) {" << std::endl;
        out << "    return rval->second;" << std::endl;
        out << "  }" << std::endl << std::endl;

        if (_enum->getUseException())
        {
            out << "  throw std::exception();" << std::endl;
        }
        else
        {
            out << "  return getDebugSymbol(" << _enum->getInvalidValue() << ");" << std::endl;
        }

        out << "}" << std::endl << std::endl;
    }
}


void EtgImplementationStd::generateMethods_ExceptionDefault (std::ofstream                  & out,
                                                             const std::shared_ptr<EtgEnum> & _enum,
                                                             const std::string              & scope,
                                                             const std::string              & fqEnum)
{
    if (EtgEnum::none != _enum->getUseCast())
    {
        out << fqEnum << " " << scope << "::cast(int v, " << fqEnum << " d) {" << std::endl;
        out << "  try {" << std::endl;
        out << "    return cast(v);" << std::endl;
        out << "  } catch (const std::exception &e) {" << std::endl;
        out << "    return d;" << std::endl;
        out << "  }" << std::endl;
        out << "}" << std::endl << std::endl;
    }

    if (_enum->getUseToken())
    {
        out << fqEnum << " " << scope << "::getEnum(const std::string &v, " << fqEnum << " d) {" << std::endl;
        out << "  try {" << std::endl;
        out << "    return getEnum(v);" << std::endl;
        out << "  } catch (const std::exception &e) {" << std::endl;
        out << "    return d;" << std::endl;
        out << "  }" << std::endl;
        out << "}" << std::endl << std::endl;
    }
}
