//==================================================================================================
/**
  TTS - Tiny Test System
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TTS_DETAIL_RT_HELPERS_HPP_INCLUDED
#define TTS_DETAIL_RT_HELPERS_HPP_INCLUDED

#include <tts/detail/ct_helpers.hpp>
#include <tts/detail/type_id.hpp>
#include <sstream>
#include <cstddef>
#include <iomanip>
#include <string>

namespace tts { namespace detail
{
  // warning-free FALSE generator
  inline bool is_false()  { return false; }

  // Container-aware size function
  template<typename C> inline auto size(C const& c)
  {
    if constexpr( detail::is_container_v<C> )
      return c.size();
    else
      return 1ull;
  }

  // Container-aware begin function
  template<typename C> inline auto begin(C const& c)
  {
    if constexpr( detail::is_container_v<C> )
      return c.begin();
    else
      return &c;
  }

  // Container-aware end function
  template<typename C> inline auto end(C const& c)
  {
    if constexpr( detail::is_container_v<C> )
      return c.end();
    else
      return (&c)+1;
  }

  // Externally extensible to_string converter
  inline std::string to_string( std::nullptr_t )       { return "nullptr";             }
  inline std::string to_string( bool v )               { return v ? "true" : "false";  }
  inline std::string to_string( std::string const& v ) { return v;                     }
  inline std::string to_string( char const* v )        { return std::string(v);        }
  inline std::string to_string( char v )               { return std::string(1, v);     }

  template<typename T> inline std::string to_string( T const& v )
  {
    std::ostringstream os;

    if constexpr ( detail::is_streamable_v<T> )
    {
      os << std::setprecision(20) << v;
      return os.str();
    }
    else
    {
      if constexpr ( detail::is_container_v<T> )
      {
        auto b = v.begin();
        auto e = v.end();

        os << "{ ";
        if(b!=e)      os << to_string(*b++);
        while(b != e) os << ", " << to_string(*b++);
        os << " }";

        return os.str();
      }
      else
      {
        os << "[ " << type_id<T>() << " ] @" << (void*)(&v);
        return os.str();
      }
    }
  }

  // Split line if huge container is to be printed
  template<typename LHS, typename RHS>
  inline std::string split_line(LHS const&, RHS const&, std::string const& op)
  {
    return (detail::is_container_v<LHS>?"\n":"") + op + (detail::is_container_v<RHS>?"\n":"");
  }

  // Make an iostream that just do nothing
  struct null_buffer_t : std::streambuf
  {
    int overflow(int c) { return c; }
  };

  inline null_buffer_t null_buffer = {};
  inline std::ostream null_stream(&null_buffer);

  // Simple wrapper for __FILE__/__LINE__
  struct location
  {
    std::string file;
    std::size_t line;
  };

  std::ostream& operator<<(std::ostream& os, location const& l)
  {
    return os << l.file << ":" << l.line;
  }

  inline location at(std::string const& f, std::size_t l) { return {f,l}; }

  // Represent a test result and its displayable representation
  struct result
  {
    bool        status;
    std::string lhs;
    std::string op;
    std::string rhs;

    explicit operator bool() { return status; }
  };

  // Setup/section environment guard
  struct section_guard
  {
    int & id;
    int const & section;

    section_guard( int & id_, int const & section_, int & count ) : id( id_), section( section_)
    {
      if ( section == 0 ) id = count++ - 1;
    }

    template<typename Env> bool check(std::string const& desc, Env& e)
    {
      if(id == section)
        e.output()  << std::endl << "... " << desc << std::endl;
      return id == section;
    }
  };
} }

#endif
