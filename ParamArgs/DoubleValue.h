#ifndef _DOUBLE_VALUE_
#define _DOUBLE_VALUE_

namespace yeguang
{
	class CDoubleValue
	{
	public:
		CDoubleValue();
		~CDoubleValue();

		static double ParseDouble(const char* const data);

		static void PackageDouble(double value, char *const data, int &datalen);
	};
}

#endif