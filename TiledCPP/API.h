#pragma once

#include "Macros.h"

#ifdef ENGINE_DLL
#ifdef _WIN32
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __attribute__((visibility("default")))
#endif
#else
#ifdef _WIN32
#define ENGINE_API
#else
#define ENGINE_API
#endif
#endif

#define FORWARD_DECLARE(T) class ENGINE_API T

#ifdef _MSC_VER
#define FORCEINLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define FORCEINLINE __attribute__((always_inline)) inline
#else
#define FORCEINLINE inline
#endif