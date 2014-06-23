#ifndef _BOOLEAN_VALUE_
#define _BOOLEAN_VALUE_

namespace yeguang
{
	class BooleanValue
	{
	public:
		BooleanValue();
		~BooleanValue();

		static bool ParseBoolean(const char * const data);

		static void PackageBoolean(bool value, char *const data, int &datalen);
	};
}

#endif 
