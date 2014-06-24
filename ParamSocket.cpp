#define DLLEXPORT
#include "paramsocket.h"
#include <string.h>

namespace yeguang
{

#define PDUSIZE 4096
#define MAXPDU 20

#define MAKEINT(byte0, byte1, byte2, byte3) \
    ((byte0) | ((byte1) << 8) | ((byte2) << 16) | ((byte3) << 24))

#define MAKESHORT(byte0, byte1) ((byte0) | ((byte1) << 8))

#define HEADRTVALUE    0x00014556

#define GETHEADER(hdr) ((hdr) & 0xffffff)
#define GETDATATYPE(hdr) (((hdr) >> 24) & 0xff)

#define HEARTTYPE     0
#define DATATYPE      1

#pragma pack(push, 1)
typedef struct tagParamMessage
{
    int hdrflag;
    int msglen;
    int eventid;
    unsigned short checksum;
    char eventarg[0];

    tagParamMessage()
    {
        hdrflag  = HEADRTVALUE;
        msglen   = 0;
        eventid  = 0;
        checksum = 0;
    }
}TParamMessage;
#pragma pack(pop)

ParamSocket::ParamSocket()
{
    m_data_buffer = NULL;

    m_read_position = m_write_position = m_data_len = 0;
}

ParamSocket::~ParamSocket()
{
    if(m_data_buffer != NULL)
    {
        delete [] m_data_buffer;
        m_data_buffer = NULL;
    }
}

ParamSocket* ParamSocket::Create()
{
    ParamSocket* sock = new ParamSocket();
    sock->Init();
    return sock;
}

int ParamSocket::Init()
{
    send_callback_ = NULL;
    send_context_ = NULL;

    recv_callback_ = NULL;
    recv_context_ = NULL;

    check_callbak_ = NULL;
    check_context_ = NULL;

    if(m_data_buffer != NULL)
    {
        delete [] m_data_buffer;
        m_data_buffer = NULL;
    }

    m_data_buffer = new char[PDUSIZE * MAXPDU];
    m_buffer_size = PDUSIZE * MAXPDU;

    m_temp_data = new char[PDUSIZE];
    m_pdu_size  = PDUSIZE;

    return 0;
}

int ParamSocket::SetSendCB(Output2NetworkCB send_callback, void* context)
{
    send_callback_ = send_callback;
    send_context_ = context;
	return 0;
}

int ParamSocket::SetRecvCB(Output2InteriorCB recv_callback, void* context)
{
    recv_callback_ = recv_callback;
    recv_context_ = context;
	return 0;
}

int ParamSocket::SetCheckCB(CheckConnCB check_callback, void* context)
{
    check_callbak_ = check_callback;
    check_context_ = context;
	return 0;
}

extern uint32_t APHash(const char *str);

int ParamSocket::CallFunction(std::string funname, ParamArgs &args)
{
	char buffer[PDUSIZE] = {0};
	int data_len = sizeof(buffer) - sizeof(TParamMessage);

	TParamMessage *phead = (TParamMessage *)buffer;


	args.GetData(phead->eventarg, data_len);

	//printf("data_len:%d\n", data_len + sizeof(TParamMessage));

	phead->hdrflag = HEADRTVALUE | (DATATYPE << 24);
	phead->msglen  = data_len + sizeof(TParamMessage);
	phead->eventid = APHash(funname.c_str());
	phead->checksum = CheckSum(phead->hdrflag, phead->msglen, phead->eventid, 0);

    if(send_callback_)
	{
		send_callback_(buffer, data_len + sizeof(TParamMessage), send_context_);
	}

    return data_len + sizeof(TParamMessage);
}

int ParamSocket::CheckConn()
{
	char buffer[PDUSIZE] = {0};
	int data_len = sizeof(buffer) - sizeof(TParamMessage);

	TParamMessage *phead = (TParamMessage *)buffer;

	phead->hdrflag = HEADRTVALUE;
	phead->msglen  = sizeof(TParamMessage);
	phead->eventid = -1;
	phead->checksum = CheckSum(phead->hdrflag, phead->msglen, phead->eventid, 0);

	if(send_callback_)
	{
		send_callback_(buffer, sizeof(TParamMessage), send_context_);
	}

    return sizeof(TParamMessage);
}

int ParamSocket::InputData(const char * const data, int data_len)
{
    return ParseData(data, data_len);
}

int ParamSocket::ParseData(const char * const data, int data_len)
{
    if((m_buffer_size - m_data_len) < data_len|| data == NULL
        || data_len <= 0)
    {
        return -1;
    }

    if((m_buffer_size - m_write_position) >= data_len)
    {
        memcpy(&m_data_buffer[m_write_position], data, data_len);
        m_write_position = m_write_position + data_len;
    }
    else
    {
        memcpy(&m_data_buffer[m_write_position], data, (m_buffer_size - m_write_position));
        memcpy(&m_data_buffer[0], &data[m_buffer_size - m_write_position],
            data_len - (m_buffer_size - m_write_position));
        m_write_position = data_len - (m_buffer_size - m_write_position);
    }

    m_data_len += data_len;

    do
    {
        if(FindHeader() < 0)
        {
            return -1;
        }

		//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

        int msg_len = ReadInt(m_data_buffer, m_read_position + 4, m_buffer_size);

        if(msg_len > m_pdu_size)
        {
            m_read_position = (m_read_position + 1) % m_buffer_size;
            m_data_len += 1;
            continue;
        }

		//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

        if(msg_len > m_data_len)
        {
            return -1;
        }

		//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

        if((m_buffer_size - m_read_position) >= msg_len)
        {
            memcpy(m_temp_data, &m_data_buffer[m_read_position], msg_len);
            m_read_position = m_read_position + msg_len;
        }
        else
        {
            memcpy(m_temp_data, &m_data_buffer[m_read_position], (m_buffer_size - m_read_position));
            memcpy(m_temp_data + (m_buffer_size - m_read_position), &m_data_buffer[0],
                msg_len - (m_buffer_size - m_read_position));
            m_read_position = msg_len - (m_buffer_size - m_read_position);
        }

		TParamMessage *param_msg = (TParamMessage *)m_temp_data;
		//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

        if (GETDATATYPE(param_msg->hdrflag) == DATATYPE)
        {
            int eventid = ReadInt(m_temp_data, 8, m_buffer_size);

			//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);

            if(recv_callback_)
            {        
				//printf("%s:%s, %d\n", __FUNCTION__, __FILE__, __LINE__);
				//printf("param_msg->eventarg:%p param_msg->msglen:%d\n", param_msg->eventarg, param_msg->msglen); //
                recv_callback_(param_msg->eventid, ParamArgs(param_msg->eventarg, 
					param_msg->msglen - sizeof(TParamMessage)), recv_context_);
            }

        }
        else if ((param_msg->msglen - sizeof(TParamMessage)) == 0)
        {
            if(check_callbak_)
            {
                check_callbak_(check_context_);
            }
        }

        m_data_len -= msg_len;
    }while(m_data_len >= sizeof(TParamMessage));

    return 0;
}

int ParamSocket::ReadInt(const char* const buffer, int pos, int bufsize)
{
    unsigned char byte0 = buffer[pos % bufsize];
    unsigned char byte1 = buffer[(pos + 1) % bufsize];
    unsigned char byte2 = buffer[(pos + 2) % bufsize];
    unsigned char byte3 = buffer[(pos + 3) % bufsize];

    return MAKEINT(byte0, byte1, byte2, byte3);
}

unsigned short ParamSocket::ReadShort(const char* const buffer, int pos, int bufsize)
{
    unsigned char byte0 = buffer[pos % bufsize];
    unsigned char byte1 = buffer[(pos + 1) % bufsize];

    return MAKESHORT(byte0, byte1);
}

unsigned short ParamSocket::CheckSum(int hdrflag, int msglen,
    int eventid, unsigned short checksum)
{
    int tempsum = hdrflag + msglen + eventid;

    tempsum = (tempsum & 0xffff) + ((tempsum >> 16) & 0xffff);
    tempsum += checksum;

    return ~((unsigned short)tempsum);
}

int ParamSocket::FindHeader()
{
    int pos = 0;
    int data_len = m_data_len;

    do
    {
        int hdrflag = ReadInt(m_data_buffer, m_read_position + pos, m_buffer_size);

        while (GETHEADER(hdrflag) != HEADRTVALUE && data_len > 0)
        {
            pos++;
            data_len--;
            hdrflag = ReadInt(m_data_buffer, m_read_position + pos, m_buffer_size);
        }

        if(data_len < sizeof(TParamMessage))
        {
            m_read_position = (m_read_position + pos) % m_buffer_size;
            m_data_len = data_len;
            return -1;
        }

        int msglen = ReadInt(m_data_buffer, m_read_position + pos + 4, m_buffer_size);
        int eventid = ReadInt(m_data_buffer, m_read_position + pos + 8, m_buffer_size);
        unsigned short checksum = ReadShort(m_data_buffer, m_read_position + pos + 12, m_buffer_size);

        if(CheckSum(hdrflag, msglen, eventid, checksum) == 0)
        {
            break;
        }

        pos++;
        data_len--;
    }while(1);

    m_read_position = (m_read_position + pos) % m_buffer_size;
    m_data_len = data_len;
    return 0;
}

}
