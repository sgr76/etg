/*! @file qt5_implementation.cpp
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
#include "qt5_implementation_ns.hpp"

#include <fstream>
#include <enum.hpp>
#include <scope.hpp>
#include <file_pool.hpp>
#include <scope_walker.hpp>


EtgImplementationQt5Ns::EtgImplementationQt5Ns (const std::string _filename)
    : EtgImplementation(_filename)
{
}


void EtgImplementationQt5Ns::generate ()
{
    std::ofstream out(filename);

    if (out.is_open())
    {
        EtgFilePool::get().generateIncludes(out);

        out << std::endl;
        out << "#include <QtCore/QObject>" << std::endl << std::endl;

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


void EtgImplementationQt5Ns::generateMethods_Exception_InvalidValue (std::ofstream                  & out,
                                                                   const std::shared_ptr<EtgEnum> & _enum,
                                                                   const std::string              & scope,
                                                                   const std::string              & fqEnum)
{
    if (_enum->getUseToken())
    {
        out << "const QString " << scope << "::getToken(" << fqEnum << " v) {" << std::endl;
        out << "  if (enum2token.contains(v)) {" << std::endl;
        out << "    return enum2token.value(v);" << std::endl;
        out << "  }" << std::endl << std::endl;

        if (_enum->getUseException())
        {
            out << "  throw std::exception();" << std::endl;
        }
        else
        {
            out << "  return enum2token.value(" << _enum->getInvalidValue() << ");" << std::endl;
        }

        out << "}" << std::endl << std::endl;

        if (_enum->getUseException())
        {
            out << fqEnum << " " << scope << "::getEnum(const QString &v) {" << std::endl;
        }
        else
        {
            out << fqEnum << " " << scope << "::getEnum(const QString &v, " << fqEnum << " d) {" << std::endl;
        }

        if (_enum->getUseCaseInsensitive())
        {
            out << "  auto rval = token2enum.find(v.toUpper());" << std::endl;
        }
        else
        {
            out << "  auto rval = token2enum.find(v);" << std::endl;
        }

        out << "  if (token2enum.end()!=rval) {" << std::endl;
        out << "    return rval.value();" << std::endl;
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

        out << "  if (" << lookupTable << ".end() != " << lookupTable << ".find((" << fqEnum << ")v)) {" << std::endl;
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
        out << "const QString " << scope << "::getDebugSymbol(" << fqEnum << " v) {" << std::endl;
        out << "  if (enum2symbol.contains(v)) {" << std::endl;
        out << "    return enum2symbol.value(v);" << std::endl;
        out << "  }" << std::endl << std::endl;

        if (_enum->getUseException())
        {
            out << "  throw std::exception();" << std::endl;
        }
        else
        {
            out << "  return enum2symbol.value(" << _enum->getInvalidValue() << ");" << std::endl;
        }

        out << "}" << std::endl << std::endl;
    }

    if (_enum->getTranslate())
    {
        out << "const QString " << scope << "::getTranslation(" << fqEnum << " v) {" << std::endl;
        out << "  if (enum2translation.contains(v)) {" << std::endl;
        out << "    return enum2translation.value(v)();" << std::endl;
        out << "  }" << std::endl << std::endl;

        if (_enum->getUseException())
        {
            out << "  throw std::exception();" << std::endl;
        }
        else
        {
            out << "  return enum2translation.value(" << _enum->getInvalidValue() << ");" << std::endl;
        }

        out << "}" << std::endl << std::endl;
    }
}


void EtgImplementationQt5Ns::generateMethods_ExceptionDefault (std::ofstream                  & out,
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
        out << fqEnum << " " << scope << "::getEnum(const QString &v, " << fqEnum << " d) {" << std::endl;
        out << "  try {" << std::endl;
        out << "    return getEnum(v);" << std::endl;
        out << "  } catch (const std::exception &e) {" << std::endl;
        out << "    return d;" << std::endl;
        out << "  }" << std::endl;
        out << "}" << std::endl << std::endl;
    }
}
