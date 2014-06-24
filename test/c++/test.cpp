#include <stdio.h>
#include "ParamSocket.h"
#include "ParamExecutor.h"

using namespace yeguang;

int SendCallback(const char * const data, int data_len, void* context)
{
	ParamSocket *sock = (ParamSocket *)context;

	sock->InputData(data, data_len);

	return 0;
}

int Recvallback(uint32_t function_id, ParamArgs& args, void* context)
{
	const TParamInfo* info = ParamExecutor::Instance()->GetParamInfo(function_id);

	if (info != NULL)
	{
		info->recv_callback_(function_id, args, info->context_);
	}

	return 0;
}

int CheckCallback(void* context)
{
	printf("CheckCallback\n");
	return 0;
}

int Execute(uint32_t function_id, ParamArgs& args, void* context)
{
	int i = 0;

	for (i = 0; i < args.GetArgCount(); i++)
	{
		ValueObject vobj = args.GetArg(i);

		switch (vobj.GetType())
		{
		case yeguang::BOOLVALUE:
			{
				printf("boolean:%d\n", vobj.GetBoolean());
			}break;
		case yeguang::CHARVALUE:
			{
				printf("char:%d\n", vobj.GetChar());
			}break;
		case yeguang::SHORTVALUE:
			{
				printf("short:%d\n", vobj.GetShort());
			}break;
		case yeguang::INTVALUE:
			{
				printf("int:%d\n", vobj.GetInt());
			}break;
		case yeguang::LONGVALUE:
			{
				printf("long:%ld\n", vobj.GetLong());
			}break;
		case yeguang::FLOATVALUE:
			{
				printf("float:%f\n", vobj.GetFloat());
			}break;
		case yeguang::DOUBLEVALUE:
			{
				printf("double:%f\n", vobj.GetDouble());
			}break;
		case yeguang::STRINGVALUE:
			{
				printf("string:%s\n", vobj.GetString().c_str());
			}break;
		case yeguang::BYTEARRAY:
			{
				int cnt = vobj.GetByteLength();
				for (int i = 0; i < cnt; i++)
				{
					printf("bytearray:%d\n", vobj.GetByteArray().get()[i]);
				}
			}break;
		default:
			break;
		}
	}

	return 0;
}

int main()
{
	ParamSocket *sock = ParamSocket::Create();

	sock->SetCheckCB(CheckCallback, sock);
	sock->SetRecvCB(Recvallback, sock);
	sock->SetSendCB(SendCallback, sock);

	ParamExecutor::Instance()->AddRecvCB("Test", Execute, sock);

	ParamArgs args;

	args.AddArg(ValueObject(false));
	args.AddArg(ValueObject((char)1));
	args.AddArg(ValueObject((short)2));
	args.AddArg(ValueObject(3));
	args.AddArg(ValueObject((int64_t)4));
	args.AddArg(ValueObject(5.0f));
	args.AddArg(ValueObject(6.0));
	uint8_t buf[1] = {7};
	args.AddArg(ValueObject(buf, sizeof(buf)));
	args.AddArg(ValueObject("Hello World!"));

	sock->CallFunction("Test", args);

	sock->CheckConn();

    getchar();
	return 0;
}