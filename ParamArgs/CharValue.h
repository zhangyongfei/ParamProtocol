#ifndef _CHAR_VALUE_
#define _CHAR_VALUE_
#include <stdint.h>

namespace yeguang
{
	class CharValue
	{
	public:
		CharValue();
		~CharValue();

		static int8_t ParseChar(const char * const data);

		static void PackageChar(char value, char *const data, int &datalen);
	};
}

#endif
