#ifndef TYPES_HPP
#define TYPES_HPP

#include <memory>
  
typedef unsigned char        byte;
typedef long long int        size;

typedef const char*          Str; 
  
typedef signed char          I8;
typedef signed short int     I16;
typedef signed int           I32;
typedef signed long long     I64;
 
typedef unsigned char        U8;
typedef unsigned short int   U16;
typedef unsigned int         U32;
typedef unsigned long long   U64;
 
typedef float                F32;
typedef double               F64;
typedef long double          F128;

template<typename T>
using UniquePtr = std::unique_ptr<T>;

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;

#endif