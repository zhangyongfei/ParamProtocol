#ifndef _BOOLEAN_VALUE_
#define _BOOLEAN_VALUE_

namespace yeguang
{
	class CBooleanValue
	{
	public:
		CBooleanValue();
		~CBooleanValue();

		static bool ParseBoolean(const char * const data);

		static void PackageBoolean(bool value, char *const data, int &datalen);
	};
}

#endif 
