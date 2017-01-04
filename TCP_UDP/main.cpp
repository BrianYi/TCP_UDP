// main.cpp : 定义控制台应用程序的入口点。
//

#include "TCP.h"
#include "UDP.h"


int main()
{
//     TCP server;
//     server.listen_on_port(5566);
//     TCP client = server.accept_client();
//     char recvBuf[RECV_BUF_SIZE] = { 0 };
//     UINT32 receivedBytes = client.receive(recvBuf, RECV_BUF_SIZE);
//     printf("received[%u bytes]: %s\n", receivedBytes, recvBuf);
    const int recv_buf_size = 5;
    const int send_buf_size = 5;
    UDP server;
    server.set_socket_rcvbuf_size(recv_buf_size);
    server.listen_on_port(5566);
    int recvBytes = 0;
    while (true)
    {
        char recvBuf[1024] = { 0 };
        recvBytes = server.receive(recvBuf, recv_buf_size, IOType::Blocking);
        if (recvBytes != -1)
            printf("[recv %d bytes]:%s\n", recvBytes, recvBuf);
    }
//     UDP client;
//     client.set_socket_sndbuf_size(send_buf_size);
//     while (true)
//     {
//         char sendBuf[1024] = { 0 };
//         scanf_s("%s", sendBuf, 1024);
//         int sendSize = strlen(sendBuf);
//         client.send("192.168.0.185", 5566, sendBuf, sendSize);
//     }

    return 0;
}

