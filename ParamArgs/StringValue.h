#ifndef _STRING_VALUE_
#define _STRING_VALUE_
#include <string>

namespace yeguang
{
	class CStringValue
	{
	public:
		CStringValue();
		~CStringValue();

		static std::string ParseString(const char* const data);

		static void PackageString(std::string value, char *const data, int &datalen);
	};

}

#endif