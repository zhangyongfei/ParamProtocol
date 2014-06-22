#include "FloatValue.h"
#include "ValueCommon.h"

namespace yeguang
{
	CFloatValue::CFloatValue()
	{

	}

	CFloatValue::~CFloatValue()
	{

	}

	float CFloatValue::ParseFloat(const char* const data)
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
			|| pvalue->data[0] != 'F')
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		float tmp;

		char *ptmp = (char *)&tmp;

		ptmp[0] = pvalue->data[1];
		ptmp[1] = pvalue->data[2];
		ptmp[2] = pvalue->data[3];
		ptmp[3] = pvalue->data[4];

		return tmp;
	}

	void CFloatValue::PackageFloat(float value, char *const data, int &datalen)
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

		pvalue->data[0] = 'F';
		pvalue->data[1] = ptmp[0];
		pvalue->data[2] = ptmp[1];
		pvalue->data[3] = ptmp[2];
		pvalue->data[4] = ptmp[3];
	}
}