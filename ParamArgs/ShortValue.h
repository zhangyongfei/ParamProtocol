#ifndef _SHORT_VALUE_
#define _SHORT_VALUE_
#include <stdint.h>

namespace yeguang
{
	class CShortValue
	{
	public:
		CShortValue();
		~CShortValue();

		static int16_t ParseShort(const char* const data);

		static void PackageShort(int16_t value, char *const data, int &datalen);
	};
}

#endif