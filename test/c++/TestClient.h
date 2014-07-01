#ifndef _TESTCLIENT_
#define _TESTCLIENT_
#include <stdint.h>
#include "ParamSocket.h"
#include "ParamExecutor.h"

class TestServer;

class TestClient{
public:
	TestClient(TestServer* server);
	~TestClient();

	void Init(SOCKET sock);
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

	TestServer* server_;

	bool bstatus;
};

#endif