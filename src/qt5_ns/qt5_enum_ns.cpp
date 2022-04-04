/*! @file qt5_enum.cpp
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
#include "qt5_enum_ns.hpp"

#include <algorithm>


EtgEnumQt5Ns::EtgEnumQt5Ns (const clang::EnumDecl * ed)
    : EtgEnum(ed)
{
}


/*! @brief
 *
 * @param pF TODO
 * @return TODO
 */
void EtgEnumQt5Ns::generateNames (std::ofstream & out)
{
    bool first = true;

    for (auto & I : items)
    {
        out << (first ? "" : ",") << " \"" << name << "::" << I->name << "\"";

        first = false;
    }
}


/*! @brief
 *
 * @param pF TODO
 * @return TODO
 */
void EtgEnumQt5Ns::generateTexts (std::ofstream & out)
{
    bool first = true;

    for (auto & I : items)
    {
        out << (first ? "" : ",") << " \"" << I->text << "\"";

        first = false;
    }
}


/*! @brief
 *
 * @param pF TODO
 * @param fqEnum TODO
 * @param scope TODO
 * @param withTranslation TODO
 * @return TODO
 */
void EtgEnumQt5Ns::generateValues (std::ofstream     & out,
                                   const std::string & fqEnum,
                                   const std::string & scope,
                                   bool                withTranslation)
{
    bool first = true;

    if (NoDebug != addDebug)
    {
        out << "const QMap<" << fqEnum << ", QString> " << scope << "::enum2symbol = {";

        for (auto & I : items)
        {
            if (LongDebug == addDebug)
            {
                out << (first ? "" : ",") << " { " << fqEnum << "::" << I->name << ", \"" << name << "::" << I->name << "\" }";
            }
            else
            {
                out << (first ? "" : ",") << " { " << fqEnum << "::" << I->name << ", \"" << I->name << "\" }";
            }

            first = false;
        }

        out << " };" << std::endl << std::endl;
    }

    if (addToken)
    {
        first = true;

        out << "const QMap<" << fqEnum << ", QString> " << scope << "::enum2token = {";

        for (auto & I : items)
        {
            out << (first ? "" : ",") << " { " << fqEnum << "::" << I->name << ", \"" << I->text << "\" }";

            first = false;
        }

        out << " };" << std::endl << std::endl;

        first = true;

        out << "const QHash<QString, " << fqEnum << "> " << scope << "::token2enum = {";

        for (auto & I : items)
        {
            if (getUseCaseInsensitive())
            {
                auto tmp = I->text;

                std::transform(tmp.begin(),
                               tmp.end(),
                               tmp.begin(),
                               [](unsigned char c) {
                    return std::toupper(c);
                });

                out << (first ? "" : ",") << " { \"" << tmp << "\", " << fqEnum << "::" << I->name << " }";

                for (auto & J:I->aliases)
                {
                    tmp = J;

                    std::transform(tmp.begin(),
                                   tmp.end(),
                                   tmp.begin(),
                                   [](unsigned char c) {
                        return std::toupper(c);
                    });

                    out << ", { \"" << tmp << "\", " << fqEnum << "::" << I->name << " }";
                }
            }
            else
            {
                out << (first ? "" : ",") << " { \"" << I->text << "\", " << fqEnum << "::" << I->name << " }";

                for (auto & J:I->aliases)
                {
                    out << ", { \"" << J << "\", " << fqEnum << "::" << I->name << " }";
                }
            }

            first = false;
        }

        out << " };" << std::endl << std::endl;
    }

    if (withTranslation)
    {
        first = true;

        out << "const QMap<" << fqEnum << ", std::function<QString()>> " << scope << "::enum2translation = {";

        for (auto & I : items)
        {
            out << (first ? "" : ",") << " { " << fqEnum << "::" << I->name << ", [](){ return QObject::tr(\"" << I->text << "\", \"" << name << "\"); } }" << std::endl;

            first = false;
        }

        out << " };" << std::endl << std::endl;
    }

    if (set == getSetDataSource())
    {
        first = true;

        out << "const std::set<" << fqEnum << "> " << scope << "::enumCast = {";

        for (auto & I : items)
        {
            out << (first ? "" : ", ") << fqEnum << "::" << I->name;

            first = false;
        }

        out << " };" << std::endl << std::endl;
    }
} // generateValues


/*! @brief
 *
 * @param pF TODO
 * @return TODO
 */
void EtgEnumQt5Ns::generateTranslates (std::ofstream & out)
{
}
