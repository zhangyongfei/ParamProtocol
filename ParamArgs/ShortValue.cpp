#include "ShortValue.h"
#include "ValueCommon.h"
#include <stdexcept>

namespace yeguang
{
	CShortValue::CShortValue()
	{

	}

	CShortValue::~CShortValue()
	{

	}

	int16_t CShortValue::ParseShort(const char* const data)
	{
		if (data == NULL)
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		TValueStruct *pvalue = (TValueStruct *)data;

		if(pvalue->marklen != 1 || pvalue->totallen != 6
			|| pvalue->data[0] != 'S')
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		int16_t tmp = (pvalue->data[2] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[1] & 0xff);

		return tmp;
	}

	void CShortValue::PackageShort(int16_t value, char *const data, int &datalen)
	{
		if (datalen < (3 + sizeof(TValueStruct)))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		TValueStruct *pvalue = (TValueStruct *)data;

		pvalue->marklen = 1;
		datalen = pvalue->totallen = (3 + sizeof(TValueStruct));

		char *ptmp = (char *)&value;

		pvalue->data[0] = 'S';
		pvalue->data[1] = ptmp[0];
		pvalue->data[2] = ptmp[1];
	}

}