#ifndef PROTOCOL_COMMON
#define PROTOCOL_COMMON
#include <stdint.h>

#ifdef WIN32
#ifdef DLLEXPORT
#define PARAMPROTOCOL_API  __declspec(dllexport)
#else
#define PARAMPROTOCOL_API __declspec(dllimport)
#endif
#else
#define PARAMPROTOCOL_API
#endif

#ifdef WIN32
#include <windows.h>
#elif defined ANDROID
#include <android/log.h>
#include <pthread.h>
#else
#include <pthread.h>
#endif

#ifdef DEBUG
#ifdef ANDROID
#define dprint(format, ...) __android_log_print(ANDROID_LOG_ERROR, "TestJni", \
	               "[%s(%d)]\t"format, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define dprint(format, ...)  printf("[%s(%d)]\t"format, __FILE__, __LINE__, ##__VA_ARGS__);
#endif
#else
#define dprint(...)
#endif

#endif