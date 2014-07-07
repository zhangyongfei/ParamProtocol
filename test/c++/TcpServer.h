#ifndef _SERVER_
#define _SERVER_
#include <stdint.h>
#include <WinSock.h>
#include <vector>

class SvrConnection;

typedef std::vector<SvrConnection*> ClientVector;

typedef void (*AcceptCB)(sockaddr_in addr, yeguang::ParamSocket* conn, void* context);

class TcpServer {
	friend class SvrConnection;
public:
	TcpServer();
	~TcpServer();

	void SetAcceptCB(AcceptCB acceptcb, void* context);

	int CreateServer(int port);
	int DestroyServer();

protected:
	static unsigned long  WINAPI AcceptThread(void* context);

private:
    ClientVector clients_;

	SOCKET sock_;
	bool bstatus_;

	AcceptCB acceptcb_;
	void* accept_context_;
};

#endif