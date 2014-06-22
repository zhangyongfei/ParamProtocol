#ifndef _EVENT_ARGS_
#define _EVENT_ARGS_
#include <vector>
#include "ValueObject.h"

namespace yeguang
{
	typedef std::vector<CValueObject> ArgsVector;

    class ParamArgs
	{
	public:
        ParamArgs();
        ParamArgs(ParamArgs& args);
        ParamArgs(const char * const data, int datalen);
        ~ParamArgs();

		int GetData(char* const data, int& datalen);

		void Reset();

		void AddArg(CValueObject value);

        void InsertArg(int index, CValueObject value);

        void RemoveArg(int index);

		CValueObject& GetArg(int index);

		CValueObject& operator[](int index)
		{
			return GetArg(index);
		}

		int GetArgCount();

	private:
		ArgsVector m_argslist;
	};
}

#endif
