/********************************************************************
	����:	2016/12/14 11:06:05
	�ļ���:	CommonSocket.h
	����:	BrianYi
	
	��;:	TCP��UDP��Ĺ������࣬���ڷ�װsocket����
*********************************************************************/
#pragma once
#include "common.h"
#include "Address.h"

class CommonSocket
{
public:
    CommonSocket();
    CommonSocket(INT32 inSocketType, IOType inIOType = Blocking);
    ~CommonSocket();
    void open();
    void close();
	void setIOType(IOType inIOType);
protected:
    void bind_to_port(const USHORT& inPort);
protected:
    SOCKET m_socketID;
    INT32 m_socketType;
    BOOL m_opened;
    BOOL m_binded;
    IOType m_ioType;
private:
    static UINT32 s_num_sockets;
};

