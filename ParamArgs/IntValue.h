#ifndef _INT_VALUE_
#define _INT_VALUE_
#include <stdint.h>

namespace yeguang
{
	class CIntValue
	{
	public:
		CIntValue();
		~CIntValue();

		static int32_t ParseInt(const char* const data);

		static void PackageInt(int32_t value, char *const data, int &datalen);
	};
}

#endif