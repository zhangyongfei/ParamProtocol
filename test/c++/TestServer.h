#ifndef _SERVER_
#define _SERVER_
#include <stdint.h>
#include <WinSock2.h>

class TestServer {
	TestServer();
	~TestServer();

	int CreateServer(int port);
	int DestroyServer();

protected:
	static uint32_t WINAPI AcceptThread(void* context);

private:
	SOCKET sock_;
};

#endif