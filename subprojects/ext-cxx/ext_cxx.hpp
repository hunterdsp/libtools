#pragma once
#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_EXT_CXX
    #define EXT_CXX_PUBLIC __declspec(dllexport)
  #else
    #define EXT_CXX_PUBLIC __declspec(dllimport)
  #endif
#else
  #ifdef BUILDING_EXT_CXX
      #define EXT_CXX_PUBLIC __attribute__ ((visibility ("default")))
  #else
      #define EXT_CXX_PUBLIC
  #endif
#endif

namespace ext_cxx {

class EXT_CXX_PUBLIC Ext_cxx {

public:
  Ext_cxx();
  int get_number() const;

private:

  int number;

};

}

