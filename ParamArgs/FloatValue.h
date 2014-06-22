#ifndef _FLOAT_VALUE_
#define _FLOAT_VALUE_

namespace yeguang
{
	class CFloatValue
	{
	public:
		CFloatValue();
		~CFloatValue();

		static float ParseFloat(const char* const data);

		static void PackageFloat(float value, char *const data, int &datalen);
	};
}

#endif