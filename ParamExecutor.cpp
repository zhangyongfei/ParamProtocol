#include "ParamExecutor.h"
#include <string.h>

namespace yeguang
{

ParamExecutor::ParamExecutor()
{

}

ParamExecutor::~ParamExecutor()
{

}

ParamExecutor* ParamExecutor::Instance()
{
    static ParamExecutor exec;

    return &exec;
}

uint32_t APHash(const char *str)
{
	register uint32_t hash = 0;
	uint32_t ch;

	for (long i = 0; (ch = (uint32_t)*str++) != 0; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
		}
	}

	return hash;
}

int ParamExecutor::AddRecvCB(std::string function_name, Output2InteriorCB recvcb, void *context)
{
    uint32_t hash_value = APHash(function_name.c_str());

    RecvCBMap::iterator iter = recvcb_map_.find(hash_value);

    if(iter != recvcb_map_.end())
    {
        return -1;
    }

    recvcb_map_.insert(RecvCBMap::value_type(hash_value, TParamInfo(recvcb, context)));

    return 0;
}

int ParamExecutor::CallFunction(uint32_t function_id, ParamArgs& args)
{
    return 0;
}

}


