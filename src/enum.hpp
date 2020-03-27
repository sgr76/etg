/*! @file enum.hpp
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

#include <fstream>
#include <string>
#include <memory>
#include <list>


namespace clang
{
class EnumDecl;
class EnumConstantDecl;
}


class EtgEnum
{
public:
    enum SetDatastructure
    {
        none,
        token,
        debug,
        translation,
        set
    };


    EtgEnum (const clang::EnumDecl * ed);

    virtual ~EtgEnum ();

    const std::string & getName ();
    const std::string & getClassInline ();
    const std::string getInvalidValue ();
    const std::string getScopePrefix ();

    bool getUseDebug ();
    bool getUseLongDebug ();
    bool getUseCast ();
    SetDatastructure getSetDataSource ();

    virtual bool getNeedSet ();

    bool getUseToken ();
    bool getUseIterator ();
    bool getTranslate ();
    bool getUseException ();
    bool getUseExceptionWithDefault ();
    bool getUseCaseInsensitive ();

    virtual void generateNames (std::ofstream & out) = 0;
    virtual void generateTexts (std::ofstream & out) = 0;
    virtual void generateValues (std::ofstream     & out,
                                 const std::string & fqEnum,
                                 const std::string & scope,
                                 bool                withTranslation) = 0;
    virtual void generateTranslates (std::ofstream & out)             = 0;

protected:
    void parseEnumAttr (const clang::EnumDecl * ed);
    void parseEnumAttrItem (const std::string & attr);
    void parseItem (const clang::EnumConstantDecl * ec);

protected:
    struct Item
    {
        std::string name;
        std::string text;

        bool defaultValue;
    };


    enum DebugType
    {
        NoDebug,
        ShortDebug,
        LongDebug
    };


    std::string                       name;

    DebugType                         addDebug;
    bool                              addCast;
    bool                              addToken;
    bool                              addTranslation;
    bool                              addIterator;

    bool                              useException;
    bool                              exceptionWithDefault;
    bool                              caseInsensitive;

    bool                              isClass;

    std::string                       classInline;
    std::string                       invalidValue;
    std::list<std::shared_ptr<Item> > items;
};
