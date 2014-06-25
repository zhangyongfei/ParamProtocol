#ifndef PARAMEXECUTOR_H
#define PARAMPEXECUTOR_H
#include "ParamArgs.h"
#include "ParamSocket.h"
#include <stdint.h>
#include <string>
#ifdef WIN32
#include <hash_map>
#elif LINUX
#include <ext/hash_map>
#endif
namespace yeguang
{
typedef struct tagParamInfo
{
    Output2InteriorCB recv_callback_;
    void* context_;

    tagParamInfo(Output2InteriorCB recv_callback, void* context)
    {
        this->context_ = context;
        this->recv_callback_ = recv_callback;
    }
}TParamInfo;

#ifdef WIN32
typedef stdext::hash_map<uint32_t, TParamInfo> RecvCBMap;
#elif LINUX
typedef __gnu_cxx::hash_map<uint32_t, TParamInfo> RecvCBMap;
#endif

class PARAMPROTOCOL_API ParamExecutor
{
    ParamExecutor();
    ~ParamExecutor();
public:
    static ParamExecutor* Instance();

    int AddRecvCB(std::string function_name, Output2InteriorCB recvcb, void *context);

    const TParamInfo* GetParamInfo(int function_id);
private:
    RecvCBMap recvcb_map_;
};
}



#endif // PARAMPEXECUTOR_H
