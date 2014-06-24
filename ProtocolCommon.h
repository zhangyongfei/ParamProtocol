#ifndef PROTOCOL_COMMON
#define PROTOCOL_COMMON

#ifdef WIN32
#ifdef DLLEXPORT
#define PARAMPROTOCOL_API  __declspec(dllexport)
#else
#define PARAMPROTOCOL_API __declspec(dllimport)
#endif
#else
#define PARAMPROTOCOL_API
#endif

#endif