#include "TcpServer.h"
#include "SvrConnection.h"

TcpServer::TcpServer(){
    WSADATA wsadata;
	::WSAStartup(0x0002, &wsadata);

	sock_ = INVALID_SOCKET;

	acceptcb_ = NULL;
	accept_context_ = NULL;
}

TcpServer::~TcpServer(){
	::WSACleanup();
}

int TcpServer::CreateServer(int port){
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

int TcpServer::DestroyServer(){

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


unsigned long WINAPI TcpServer::AcceptThread(void* context){
    TcpServer *pthis = (TcpServer *)context;

	while(pthis->bstatus_){
		sockaddr_in addr;
		int len = sizeof(addr);
		SOCKET tmpsock = ::accept(pthis->sock_, (sockaddr*)&addr, &len);

		if (tmpsock != INVALID_SOCKET){
             SvrConnection *client = new SvrConnection(pthis);
			 
			 yeguang::ParamSocket *param = client->Init(tmpsock);

			 pthis->clients_.push_back(client);

			 if (pthis->acceptcb_)
			 {
				 pthis->acceptcb_(addr, param, pthis->accept_context_);
			 }
		}
	}

	return 0;
}

void TcpServer::SetAcceptCB(AcceptCB acceptcb, void* context)
{
	acceptcb_ = acceptcb;
	accept_context_ = context;
}


