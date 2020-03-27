enum attributes
===============

ETG                            short for: ETG_SHORT_DEBUG, ETG_EXCPT

ETG_SHORT_DEBUG                generate symbols for debug output (only constant names)
ETG_LONG_DEBUG                 generate symbols for debug output (constant names with enum name prefix)
ETG_NO_DEBUG                   don't generate symbols for debug output

ETG_NO_TOKEN                   don't generate token tables
ETG_NO_CAST                    don't generate a cast from int method

ETG_EXCPT                      throw exceptions on invalid values
ETG_INVALID(value)             use value as invalid value

ETG_TRANSLATION                add a translation table
ETG_REVERSE_TRANSLATION        implement string to enum lookup on translated texts

ETG_CLASS_INLINE(header_file)  generate a declaration into header_file to be included within a class declaration


value attributes
================

ETG_TOKEN(token)               use token for the token table entry instead of the constant name
ETG_VALUE(value)               integer value of the constant (replaces into constant_name = value)
