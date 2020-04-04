#pragma once

#include <etg.hpp>

#include <string>
#include <set>


template<typename T>
struct etg
{
  static T cast(int) = delete;
  static T cast(const std::string &) = delete;
  static const std::string& debugSymbol(T) = delete;
  static const std::string& token(T) = delete;
    static const std::string translation(T) = delete;
  static typename std::set<T>::const_iterator begin() = delete;
  static typename std::set<T>::const_iterator end() = delete;
};
