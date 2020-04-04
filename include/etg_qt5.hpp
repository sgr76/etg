#pragma once

#include <etg.hpp>

#include <QtCore/QString>
#include <set>


template<typename T>

struct etg
{
    static T cast (int)             = delete;
    static T cast (const QString &) = delete;

    static const QString debugSymbol(T) = delete;
    static const QString token(T)       = delete;
    static const QString translation(T) = delete;

    static typename std::set<T>::const_iterator begin () = delete;

    static typename std::set<T>::const_iterator end () = delete;
};
