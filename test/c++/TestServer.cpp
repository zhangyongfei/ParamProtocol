#include "TestServer.h"
#include "TestClient.h"

TestServer::TestServer(){
    WSADATA wsadata;
	::WSAStartup(0x0002, &wsadata);

	sock_ = INVALID_SOCKET;
}

TestServer::~TestServer(){
	::WSACleanup();
}

int TestServer::CreateServer(int port){
    if (sock_ != INVALID_SOCKET){
		::closesocket(sock_);
		sock_ = INVALID_SOCKET;
    }

	sock_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock_ == INVALID_SOCKET){
		return -1;
	}

	sockaddr_in addr;
    addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (::bind(sock_, (struct sockaddr *)&addr, sizeof(sockaddr)) == SOCKET_ERROR){
		return -1;
    }

	listen(sock_, 5);

	bstatus_ = true;
	CreateThread(NULL, 0, AcceptThread, this, 0, NULL);

	return 0;
}

int TestServer::DestroyServer(){

	ClientVector::iterator iter = clients_.begin();
	while (iter != clients_.end()){
		if (*iter != NULL){
           (*iter)->Exit();
           delete (*iter);

		   *iter = NULL;
		}	
		iter++;
	}

	if (sock_ != INVALID_SOCKET){
		::closesocket(sock_);
		sock_ = INVALID_SOCKET;
	}

	return 0;
}


unsigned long WINAPI TestServer::AcceptThread(void* context){
    TestServer *pthis = (TestServer *)context;

	while(pthis->bstatus_){
		SOCKET tmpsock = ::accept(pthis->sock_, NULL, NULL);

		if (tmpsock != INVALID_SOCKET){
             TestClient *client = new TestClient(pthis);

			 client->Init(tmpsock);

			 pthis->clients_.push_back(client);
		}
	}

	return 0;
}


