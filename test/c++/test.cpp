#include <stdio.h>
#include "ParamSocket.h"
#include "ParamExecutor.h"
#include "TestServer.h"

using namespace yeguang;

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
	ParamExecutor::Instance()->AddRecvCB("Test", Execute, NULL);

	TestServer server;

	server.CreateServer(5000);

    getchar();

	server.DestroyServer();
	return 0;
}