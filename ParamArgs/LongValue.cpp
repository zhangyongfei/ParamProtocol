#include "LongValue.h"
#include "ValueCommon.h"

namespace yeguang
{
	LongValue::LongValue()
	{

	}

	LongValue::~LongValue()
	{

	}

	int64_t LongValue::ParseLong(const char * const data)
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

		if(pvalue->marklen != 1 || pvalue->totallen != 12
			|| pvalue->data[0] != 'J')
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		int64_t tmp = (pvalue->data[8] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[7] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[6] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[5] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[4] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[3] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[2] & 0xff);
		tmp = (tmp << 8) | (pvalue->data[1] & 0xff);

	    return tmp;
	}

	void LongValue::PackageLong(int64_t value, char *const data, int &datalen)
	{
		if (datalen < (9 + sizeof(TValueStruct)))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		TValueStruct *pvalue = (TValueStruct *)data;

		pvalue->marklen = 1;
		datalen = pvalue->totallen = (9 + sizeof(TValueStruct));

		char *ptmp = (char *)&value;

		pvalue->data[0] = 'J';
		pvalue->data[1] = ptmp[0];
		pvalue->data[2] = ptmp[1];
		pvalue->data[3] = ptmp[2];
		pvalue->data[4] = ptmp[3];
		pvalue->data[5] = ptmp[4];
		pvalue->data[6] = ptmp[5];
		pvalue->data[7] = ptmp[6];
		pvalue->data[8] = ptmp[7];
	}

}