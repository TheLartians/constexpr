#pragma once

#include "cx_murmur3.h"

//----------------------------------------------------------------------------
// constexpr typeid

namespace cx {

  template <typename T> struct typeid_t {
    template <typename> friend constexpr uint32_t type_id();

  private:
    constexpr static const char* name() {
#ifdef _MSC_VER
      // this is untested: __FUNCDNAME__ or __FUNCSIG__ ?
      return __FUNCDNAME__;
#else
      return __PRETTY_FUNCTION__;
#endif
    }
    constexpr static uint32_t id = murmur3_32(name(), 0);
  };

  template <typename T> constexpr uint32_t type_id() { return typeid_t<T>::id; }
}  // namespace cx
