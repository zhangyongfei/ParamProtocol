#ifndef _BYTE_VALUE_
#define _BYTE_VALUE_
#include <stdint.h>
#include <memory.h>
#include <string.h>
#ifdef WIN32
#include <memory.h>
#else
#include <tr1/memory>
#endif
#include "ValueObject.h"

namespace yeguang
{
	class ByteArray
	{			
	public:
		ByteArray();
		~ByteArray();

		static TByteArray ParseByteArray(const char * const data);

		static void PackageByteArray(TByteArray value, char *const data, int &datalen);
	};
}

#endif
