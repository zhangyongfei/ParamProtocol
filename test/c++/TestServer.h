#ifndef _SERVER_
#define _SERVER_
#include <stdint.h>
#include <WinSock.h>
#include <vector>

class TestClient;

typedef std::vector<TestClient*> ClientVector;

class TestServer {
	friend class TestClient;
public:
	TestServer();
	~TestServer();

	int CreateServer(int port);
	int DestroyServer();

protected:
	static unsigned long  WINAPI AcceptThread(void* context);

private:
    ClientVector clients_;

	SOCKET sock_;
	bool bstatus_;
};

#endif