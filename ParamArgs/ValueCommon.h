#ifndef _VALUE_COMMON_
#define _VALUE_COMMON_
#include <stdint.h>
#include <string.h>
#include <string>
#include <stdexcept>

namespace yeguang
{
#pragma pack(push, 1)

	typedef struct tagValueStruct
	{
		uint16_t totallen;
		uint8_t  marklen;
		char     data[0];
	}TValueStruct;
#pragma pack(pop)
}

#endif