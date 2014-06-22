#include "BooleanValue.h"
#include <stdint.h>
#include <stdexcept>
#include "ValueCommon.h"

namespace yeguang
{
	CBooleanValue::CBooleanValue()
	{

	}

	CBooleanValue::~CBooleanValue()
	{

	}

	bool CBooleanValue::ParseBoolean(const char * const data)
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

		if(pvalue->marklen != 1 || pvalue->totallen != 5
			|| pvalue->data[0] != 'Z' || 
			(pvalue->data[1] != 1 && pvalue->data[1] != 0))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		if (pvalue->data[1] == 0)
		{
			return false;
		}

		return true;
	}

	void CBooleanValue::PackageBoolean(bool value, char *const data, int &datalen)
	{
		if (datalen < (int)(2 + sizeof(TValueStruct)))
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

		pvalue->data[0] = 'Z';

		if (value)
		{
			pvalue->data[1] = 1;
		}
		else
		{
			pvalue->data[1] = 0;
		}
	}

}