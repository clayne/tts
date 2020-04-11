//==================================================================================================
/*
  TTS - Tiny Test System
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#ifndef TTS_TESTS_BASIC_HPP_INCLUDED
#define TTS_TESTS_BASIC_HPP_INCLUDED

#include <tts/detail/decompose.hpp>
#include <tts/detail/rt_helpers.hpp>
#include <tts/tests/infos.hpp>

//==================================================================================================
#define TTS_EXPECT(Expr)                                                                           \
  do                                                                                               \
  {                                                                                                \
    ::tts::detail::result tts_var_d = TTS_DECOMPOSE(Expr);                                         \
    if(tts_var_d)                                                                                  \
    {                                                                                              \
      TTS_PASS("Expecting: "  << TTS_STRING(Expr) );                                               \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
      TTS_FAIL( "Expecting: " << TTS_STRING(Expr) << " but " << ::tts::detail::red                 \
                              << tts_var_d.lhs << " " << tts_var_d.op << " " << tts_var_d.rhs      \
                              << ::tts::detail::reset << " occured instead.");                     \
    }                                                                                              \
  } while(::tts::detail::is_false())
/**/

//==================================================================================================
#define TTS_EXPECT_NOT(Expr)                                                                       \
  do                                                                                               \
  {                                                                                                \
    ::tts::detail::result tts_var_d = TTS_DECOMPOSE(Expr);                                         \
    if(tts_var_d)                                                                                  \
    {                                                                                              \
      TTS_FAIL( "Not Expecting: " << TTS_STRING(Expr) << " but " << ::tts::detail::red             \
                                  << tts_var_d.lhs << " " << tts_var_d.op << " " << tts_var_d.rhs  \
                                  << ::tts::detail::reset << " occured anyway.");                  \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
      TTS_PASS("Not Expecting: "  << TTS_STRING(Expr) );                                           \
    }                                                                                              \
  } while(::tts::detail::is_false())
/**/

#endif

