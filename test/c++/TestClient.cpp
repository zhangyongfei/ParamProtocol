#include "TestClient.h"
#include "TestServer.h"


TestClient::TestClient(TestServer* server){
    server_ = server;
	param_ = NULL;
}

TestClient::~TestClient(){
    if (param_ != NULL)
    {
		delete param_;
		param_ = NULL;
    }
}

void TestClient::Init(SOCKET sock){
    sock_ = sock;

	param_ = yeguang::ParamSocket::Create();

	param_->SetCheckCB(CheckCallback, this);
	param_->SetRecvCB(Recvallback, this);
	param_->SetSendCB(SendCallback, this);

	bstatus = true;
	CreateThread(NULL, 0, RecvThread, this, 0, NULL);
}

void TestClient::Exit(){
    if (sock_ != INVALID_SOCKET){
		::closesocket(sock_);
		sock_ = INVALID_SOCKET;
    }
}

int TestClient::SendData(const char* const data, int len){
	if(sock_ == INVALID_SOCKET){
        return -1;
	}

	return ::send(sock_, data, len, 0);
}

unsigned long WINAPI TestClient::RecvThread(void* context){
    TestClient *pthis = (TestClient *)context;
    int len = 0;
	char buffer[4096] = {0};

	while(pthis->bstatus){
		len = ::recv(pthis->sock_, buffer, 4096, 0);

		if (len <= 0){
			::closesocket(pthis->sock_);
			pthis->sock_ = INVALID_SOCKET;
			ClientVector::iterator iter = pthis->server_->clients_.begin();
			while (iter != pthis->server_->clients_.end()){
				if (*iter == pthis){
					delete pthis;
                    pthis->server_->clients_.erase(iter);
					break;
				}
				iter++;
			}
			break;
		}

		// 接收的数据
		pthis->param_->InputData(buffer, len);
	}

	return 0;
}

int TestClient::SendCallback(const char * const data, int data_len, void* context)
{
	TestClient *pthis = (TestClient *)context;

	pthis->SendData(data, data_len);

	return 0;
}

int TestClient::Recvallback(uint32_t function_id, yeguang::ParamArgs& args, void* context)
{
	const yeguang::TParamInfo* info = yeguang::ParamExecutor::Instance()->GetParamInfo(function_id);

	if (info != NULL)
	{
		info->recv_callback_(function_id, args, info->context_);
	}

	return 0;
}

int TestClient::CheckCallback(void* context)
{
	TestClient *pthis = (TestClient *)context;

	pthis->param_->CheckConn();

	return 0;
}
