// main.cpp : 定义控制台应用程序的入口点。
//

#include "TCP.h"
#include "UDP.h"


int main()
{
    TCP server;
    server.listen_on_port(5566);
    TCP client = server.accept_client();
    char recvBuf[RECV_BUF_SIZE] = { 0 };
    UINT32 receivedBytes = client.receive(recvBuf, RECV_BUF_SIZE);
    printf("received[%u bytes]: %s\n", receivedBytes, recvBuf);
    return 0;
}

