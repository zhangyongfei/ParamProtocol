#include "DoubleValue.h"
#include "ValueCommon.h"
#include <stdio.h>

namespace yeguang
{
	CDoubleValue::CDoubleValue()
	{
	}

	CDoubleValue::~CDoubleValue()
	{
	}

	double CDoubleValue::ParseDouble(const char* const data)
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
			|| pvalue->data[0] != 'D')
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		double tmp;

		char *ptmp = (char *)&tmp;

		ptmp[0] = pvalue->data[1];
		ptmp[1] = pvalue->data[2];
		ptmp[2] = pvalue->data[3];
		ptmp[3] = pvalue->data[4];
		ptmp[4] = pvalue->data[5];
		ptmp[5] = pvalue->data[6];
		ptmp[6] = pvalue->data[7];
		ptmp[7] = pvalue->data[8];

		printf("%lf\n", tmp);

		return tmp;
	}

	void CDoubleValue::PackageDouble(double value, char *const data, int &datalen)
	{
		if (datalen < (int)(9 + sizeof(TValueStruct)))
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

		pvalue->data[0] = 'D';
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