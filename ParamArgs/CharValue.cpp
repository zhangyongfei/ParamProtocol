#include "CharValue.h"
#include "ValueCommon.h"
#include <string.h>
#include <stdexcept>

namespace yeguang
{
	CCharValue::CCharValue()
	{

	}

	CCharValue::~CCharValue()
	{

	}

	int8_t CCharValue::ParseChar(const char * const data)
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

		if(pvalue->marklen != 1 || ((int)pvalue->totallen) != 5
			|| pvalue->data[0] != 'C')
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else
			throw std::invalid_argument("input param is errror!");
#endif
		}

		return (int8_t)pvalue->data[1];
	}

	void CCharValue::PackageChar(char value, char *const data, int &datalen)
	{
		if (datalen < (2 + sizeof(TValueStruct)))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		TValueStruct *pvalue = (TValueStruct *)data;

		pvalue->marklen = 1;
		datalen = pvalue->totallen = (2 + sizeof(TValueStruct));

		pvalue->data[0] = 'C';
		pvalue->data[1] = value;
	}
}