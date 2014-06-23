#include "StringValue.h"
#include "ValueCommon.h"

namespace yeguang
{
	StringValue::StringValue()
	{

	}

	StringValue::~StringValue()
	{

	}

	std::string StringValue::ParseString(const char* const data)
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

		if(pvalue->marklen != 8 || ((int)pvalue->totallen - 65535) > 0
			|| memcmp(pvalue->data, "LString;", 8))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		std::string tmp;

		char buffer[65535];

		memset(buffer, 0, sizeof(buffer));

        memcpy(buffer, pvalue->data + 8, pvalue->totallen - sizeof(TValueStruct) - 8);

		tmp = buffer;

		return tmp;
	}

	void StringValue::PackageString(std::string value, char *const data, int &datalen)
	{
		if (datalen < (int)(8 + value.length() + 1 + sizeof(TValueStruct)))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		TValueStruct *pvalue = (TValueStruct *)data;

		pvalue->marklen = 8;
		datalen = pvalue->totallen = (8 + value.length() + 1 + sizeof(TValueStruct));

		memcpy(pvalue->data, "LString;", 8);
		memcpy(&pvalue->data[8], value.c_str(), value.length());
		pvalue->data[8 + value.length()] = 0;
	}

}