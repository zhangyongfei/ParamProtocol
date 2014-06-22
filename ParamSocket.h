#ifndef PARAMSOCKET_H
#define PARAMSOCKET_H
#include "ParamArgs.h"
#include <stdint.h>
#include <string>

namespace yeguang
{

typedef int (* Output2NetworkCB)(const char * const data, int data_len, void* context);
typedef int (* Output2InteriorCB)(uint32_t function_id, ParamArgs& args, void* context);
typedef int (* CheckConnCB)(void* context);

class ParamSocket
{
    ParamSocket();
public:
    ~ParamSocket();

    static ParamSocket* Create();

    int CheckConn();

    int SetSendCB(Output2NetworkCB send_callback, void* context);

    int SetRecvCB(Output2InteriorCB recv_callback, void* context);

    int SetCheckCB(CheckConnCB check_callback, void* context);

    int InputData(const char * const data, int data_len);

    int SendArgs(std::string funname, ParamArgs& args);

protected:
    int Init();

    int ParseData(const char * const data, int data_len);

	int FindHeader();

    unsigned short CheckSum(int hdrflag, int msglen,
        int eventid, unsigned short checksum);

    int ReadInt(const char* const buffer, int pos, int bufsize);

    unsigned short ReadShort(const char* const buffer, int pos, int bufsize);

private:
    Output2NetworkCB send_callback_;
    void* send_context_;

    Output2InteriorCB recv_callback_;
    void* recv_context_;

    CheckConnCB check_callbak_;
    void* check_context_;

    // 解析缓存队列
    char *m_data_buffer;
    char *m_temp_data;
    int  m_read_position;
    int  m_write_position;
    int  m_data_len;
    int  m_buffer_size;
    int  m_pdu_size;
};
}

#endif // PARAMSOCKET_H
