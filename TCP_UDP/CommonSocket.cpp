#include "CommonSocket.h"

UINT32 CommonSocket::s_num_sockets = 0;

CommonSocket::CommonSocket()
{
    this->s_num_sockets++;
    if (this->s_num_sockets == 1)
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            printf("WSAStartup error!\n");
    }

    this->m_socketType = SOCK_STREAM;
    this->m_opened = FALSE;
    this->m_binded = FALSE;
    this->m_ioType = Blocking;
    this->open();
    this->setIOType(this->m_ioType);
    ::setsockopt(this->m_socketID, SOL_SOCKET, SO_SNDBUF, (char*)&SEND_BUF_SIZE, sizeof(int));
    ::setsockopt(this->m_socketID, SOL_SOCKET, SO_RCVBUF, (char*)&RECV_BUF_SIZE, sizeof(int));
}


CommonSocket::CommonSocket(INT32 inSocketType, IOType inIOType)
{
    this->s_num_sockets++;
    if (this->s_num_sockets == 1)
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            printf("WSAStartup error!\n");
    }

    this->m_socketType = inSocketType;
    this->m_opened = FALSE;
    this->m_binded = FALSE;
    this->m_ioType = inIOType;
    this->open();
    this->setIOType(this->m_ioType);
    ::setsockopt(this->m_socketID, SOL_SOCKET, SO_SNDBUF, (char*)&SEND_BUF_SIZE, sizeof(int));
    ::setsockopt(this->m_socketID, SOL_SOCKET, SO_RCVBUF, (char*)&RECV_BUF_SIZE, sizeof(int));
}

CommonSocket::~CommonSocket()
{
    this->s_num_sockets--;
    if (this->s_num_sockets == 0)
    {
        WSACleanup();
        printf("clean up all sockets!\n");
    }
}

void CommonSocket::open()
{
    if (this->m_opened)
    {
        printf("Already opened!\n");
        return;
    }
    
    if ((this->m_socketID = ::socket(AF_INET, this->m_socketType, 0)) == -1)
    {
        printf("Create socket error!\n");
        return;
    }
    this->m_opened = TRUE;
}

void CommonSocket::close()
{
    if (this->m_opened)
    {
        ::closesocket(this->m_socketID);
        this->m_opened = FALSE;
        this->m_binded = FALSE;
    }
}

void CommonSocket::bind_to_port(const USHORT& inPort)
{
    if (!this->m_opened)
        this->open();
    else
    {
        if (this->m_binded)
        {
            printf("Socket %u already binded!\n", this->m_socketID);
            return;
        }

        Address address(inPort);
        if (bind(this->m_socketID, (const sockaddr*)&address, sizeof(struct sockaddr)) == -1)
        {
            printf("Binded socket error!\n");
            return;
        }
        this->m_binded = TRUE;
    }
}

void CommonSocket::setIOType(IOType inIOType)
{
    ULONG iMode = 0;
    switch (inIOType)
    {
    case Blocking:
        iMode = 0;
        if (::ioctlsocket(this->m_socketID, FIONBIO, &iMode) == SOCKET_ERROR)
        {
            printf("Blocking: ioctlsocket failed!\n");
        }
        break;
    case NonBlocking:
        iMode = 1;
        if (::ioctlsocket(this->m_socketID, FIONBIO, &iMode) == SOCKET_ERROR)
        {
            printf("Non-Blocking: ioctlsocket failed!\n");
        }
        break;
    default:
        printf("ERROR: No such IO type!\n");
        break;
    }
    this->m_ioType = inIOType;
}
