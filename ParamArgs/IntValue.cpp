#include "IntValue.h"
#include "ValueCommon.h"

namespace yeguang
{
	IntValue::IntValue()
	{

	}

	IntValue::~IntValue()
	{

	}

	int32_t IntValue::ParseInt(const char* const data)
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

		if(pvalue->marklen != 1 || pvalue->totallen != 8
			|| pvalue->data[0] != 'I')
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		int32_t tmp = (pvalue->data[4] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[3] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[2] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[1] & 0xff);

		return tmp;
	}

	void IntValue::PackageInt(int32_t value, char *const data, int &datalen)
	{
		if (datalen < (5 + sizeof(TValueStruct)))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		TValueStruct *pvalue = (TValueStruct *)data;

		pvalue->marklen = 1;
		datalen = pvalue->totallen = (5 + sizeof(TValueStruct));

		char *ptmp = (char *)&value;

		pvalue->data[0] = 'I';
		pvalue->data[1] = ptmp[0];
		pvalue->data[2] = ptmp[1];
		pvalue->data[3] = ptmp[2];
		pvalue->data[4] = ptmp[3];
	}

}