#include "ByteArray.h"
#include "ValueCommon.h"


namespace yeguang
{
	CByteArray::CByteArray()
	{

	}

	CByteArray::~CByteArray()
	{

	}

	TByteArray CByteArray::ParseByteArray(const char * const data)
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

		if(pvalue->marklen != 2 || ((int)pvalue->totallen - 65535) > 0
			|| memcmp(pvalue->data, "[B", 2))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		TByteArray res;

        int count = pvalue->totallen - 2 - sizeof(TValueStruct);

        res.datasize = count;
		res.data = std::tr1::shared_ptr<uint8_t>(new uint8_t[count]);
        memcpy(res.data.get(), data + 2 + sizeof(TValueStruct), count);

		return res;
	}

	void CByteArray::PackageByteArray(TByteArray value, char *const data, int &datalen)
	{
		if (datalen < (int)(2 + value.datasize + sizeof(TValueStruct)))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		TValueStruct *pvalue = (TValueStruct *)data;

		pvalue->marklen = 2;
        datalen = pvalue->totallen = (2 + value.datasize + sizeof(TValueStruct));

		memcpy(pvalue->data, "[B", 2);

	    memcpy(pvalue->data + 2, value.data.get(), value.datasize);
	}

}
