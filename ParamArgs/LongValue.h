#ifndef _LONG_VALUE_
#define _LONG_VALUE_
#include <stdint.h>

namespace yeguang
{
	class CLongValue
	{
	public:
		CLongValue();
		~CLongValue();

		static int64_t ParseLong(const char * const data);

		static void PackageLong(int64_t value, char *const data, int &datalen);
	};
}

#endif