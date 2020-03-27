/*! @file etg.hpp
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

#if defined ETG_SYMBOLS

#define ETG_TOKEN(A) __attribute__((annotate("etg_text " A)))
#define ETG_INVALID __attribute__((annotate("etg_invalid_value")))
// #define ETG_VALUE(A) __attribute__((annotate("etg_value " # A)))

#define ETG(A)             __attribute__((annotate("etg " A)))
// #define ETG_CLASS_INLINE(A) __attribute__((annotate("etg_class_inline " A)))

#else // if defined ETG_SYMBOLS

#define ETG_TOKEN(A)
#define ETG_INVALID
// #define ETG_VALUE(A) = A

#define ETG(A)
// #define ETG_CLASS_INLINE(A)

#endif // if defined ETG_SYMBOLS
