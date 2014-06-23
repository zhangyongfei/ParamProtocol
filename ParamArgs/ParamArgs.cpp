#include "ParamArgs.h"
#include <string.h>
#include "ValueCommon.h"
#include <stdio.h>

namespace yeguang
{
#pragma pack(push, 1)
	typedef struct tagEventAgs
	{
		int8_t argscnt;
		char   data[0];
	}TEventAgs;
#pragma pack(pop)

	ParamArgs::ParamArgs()
	{
		m_argslist.clear();
	}

	ParamArgs::ParamArgs(ParamArgs& args)
	{
		m_argslist.clear();

		std::copy(args.m_argslist.begin(), args.m_argslist.end(), m_argslist.begin());
	}

	ParamArgs::ParamArgs(const char * const data, int datalen)
	{
		if (datalen < sizeof(TEventAgs))
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		m_argslist.clear();

		TEventAgs *pargs = (TEventAgs *)data;

		int count = pargs->argscnt;
		int i = 0;

		TValueStruct *pvalue = (TValueStruct *)pargs->data;

		while (i < count)
		{
			m_argslist.push_back(ValueObject((char *)pvalue, pvalue->totallen));
			pvalue = (TValueStruct *)(((char *)pvalue) + pvalue->totallen);
			i++;
		}
	}

	ParamArgs::~ParamArgs()
	{

	}

	int ParamArgs::GetData(char* const data, int& datalen)
	{
		int count = m_argslist.size();
		int pos = 0;
		int tmplen = datalen;
		char *tmpdata = (char *)data;

		int i = 0;

		tmpdata[0] = count;
		pos++;

		for (i = 0; i < count && tmplen != 0; i++)
		{
			m_argslist[i].GetData(tmpdata + pos, tmplen);

			pos = pos + tmplen;
			tmplen = datalen - pos;
		}

		datalen = pos;

		return 0;
	}

	void ParamArgs::AddArg(ValueObject value)
	{
		m_argslist.push_back(value);
	}

    void ParamArgs::InsertArg(int index, ValueObject value)
    {
        if (index < 0 || index >= m_argslist.size())
        {
#ifdef _WIN32
            throw std::exception("input param is errror.");
#else

            throw std::invalid_argument("input param is errror!");
#endif
        }

        m_argslist.insert(m_argslist.begin() + index, value);
    }

    void ParamArgs::RemoveArg(int index)
    {
        if (index < 0 || index >= m_argslist.size())
        {
#ifdef _WIN32
            throw std::exception("input param is errror.");
#else

            throw std::invalid_argument("input param is errror!");
#endif
        }

        ArgsVector::iterator iter = m_argslist.begin() + index;

        m_argslist.erase(iter);
    }

	ValueObject& ParamArgs::GetArg(int index)
	{
		if (index < 0 || index >= m_argslist.size())
		{
#ifdef _WIN32
			throw std::exception("input param is errror.");
#else

			throw std::invalid_argument("input param is errror!");
#endif
		}

		return m_argslist[index];
	}

	int ParamArgs::GetArgCount()
	{
		return (int)m_argslist.size();
	}

	void ParamArgs::Reset()
	{
		m_argslist.clear();
	}
}