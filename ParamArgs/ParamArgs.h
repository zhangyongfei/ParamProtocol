#ifndef _EVENT_ARGS_
#define _EVENT_ARGS_
#include <vector>
#include "ValueObject.h"

namespace yeguang
{
	typedef std::vector<ValueObject> ArgsVector;

    class PARAMPROTOCOL_API ParamArgs
	{
	public:
        ParamArgs();
        ParamArgs(ParamArgs& args);
        ParamArgs(const char * const data, int datalen);
        ~ParamArgs();

		int GetData(char* const data, int& datalen);

		void Reset();

		void AddArg(ValueObject value);

        void InsertArg(int index, ValueObject value);

        void RemoveArg(int index);

		ValueObject& GetArg(int index);

		ValueObject& operator[](int index)
		{
			return GetArg(index);
		}

		int GetArgCount();

	private:
		ArgsVector m_argslist;
	};
}

#endif
