#ifndef __MOCKSERVER__H__
#define __MOCKSERVER__H__



#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "logger.hpp"
#include <cstring>


class mockserver
{
private:
 /* data */

public:
    mockserver(/* args */);
    virtual bool Bind() = 0;
    virtual bool Listen() = 0;
    virtual void sendData(int sockfd) = 0;
    virtual void recvData(int newSock) = 0;
    virtual ~mockserver();
};


class streamingserver : public mockserver
{
    private:
    // socket FileDescriptor
     int m_socketfd = 0;
     // Socket Address Info Struct to store port and address details
     struct sockaddr_in m_addrinfo;
     int m_port;

    public:
    streamingserver(std::string_view address, int port = 8888);

    // Binding to a port
    bool Bind() override;

    // Listening on Socket
    bool Listen() override; 

    // Parsing Data
    void parseData(char buffer[512], int sockfd);

    // Sending Data
    void sendData(int sockfd) override; 

    // Receiving Data
    void recvData(int newSock) override;


    // Close Socket
    ~streamingserver();
};

#endif  //!__MOCKSERVER__H__