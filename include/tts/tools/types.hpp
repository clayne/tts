//======================================================================================================================
/**
  TTS - Tiny Test System
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//======================================================================================================================
#pragma once
#include <cstdint>

namespace tts
{
  //====================================================================================================================
  //! @brief Type list structure
  //!
  //! Encapsulates a variadic list of types to be processed by scenarios.
  //!
  //! @tparam Ts List of types to embed into a type list
  //====================================================================================================================
  template<typename... Ts>
  struct types
  {
    template<typename... Us> constexpr types<Ts...,Us...> operator+( types<Us...> const&) const;
  };

  // Concatenate types lists
  template<typename... Ls> struct concatenate { using type = decltype( (Ls{} + ...) ); };
  template<typename... Ls> using concatenate_t = typename concatenate<Ls...>::type;

  //====================================================================================================================
  //! @brief Type wrapper
  //!
  //! Encapsulates a type to be processed by scenarios.
  //!
  //! @tparam T Type to embed
  //====================================================================================================================
  template<typename T> struct type {};

  // Reusable pre-made types lists

  /// List of all standard floating point types.
  using real_types        = types < double,float>;
  /// List of all standard signed integer types.
  using int_types         = types < std::int64_t , std::int32_t , std::int16_t , std::int8_t>;
  /// List of all standard signed types.
  using signed_types      = concatenate_t<real_types,int_types>;
  /// List of all standard unsigned types.
  using uint_types        = types < std::uint64_t , std::uint32_t , std::uint16_t , std::uint8_t>;
  /// List of all standard integer types.
  using integral_types    = concatenate_t<int_types,uint_types>;
  /// List of all standard arithmetic types.
  using arithmetic_types  = concatenate_t<real_types,int_types,uint_types>;
}
