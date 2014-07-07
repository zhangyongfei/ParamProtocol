#ifndef _TESTCLIENT_
#define _TESTCLIENT_
#include <stdint.h>
#include "ParamSocket.h"
#include "ParamExecutor.h"

class TcpServer;

class SvrConnection{
public:
	SvrConnection(TcpServer* server);
	~SvrConnection();

	yeguang::ParamSocket* Init(SOCKET sock);
    void Exit();

protected:
	static unsigned long WINAPI RecvThread(void* context);
	int SendData(const char* const data, int len);

	static int SendCallback(const char * const data, int data_len, void* context);
	static int Recvallback(uint32_t function_id, yeguang::ParamArgs& args, void* context);
	static int CheckCallback(void* context);

private:
	SOCKET sock_;

	yeguang::ParamSocket *param_;

	TcpServer* server_;

	bool bstatus;
};

#endif