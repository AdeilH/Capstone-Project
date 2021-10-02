#ifndef __CLIENT__H__
#define __CLIENT__H__



#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "logger.hpp"

class client
{
private:
    /* data */
public:
    client(/* args */);
    virtual bool Connect() = 0;
    virtual void parseData(char buffer[512]) = 0;
    virtual void sendData(const std::string &buffer) = 0;
    virtual void recvData() = 0;
    virtual ~client();
};


class streamingclient : public client
{
    private:
    // socket FileDescriptor
     int m_socketfd = 0;
     // Socket Address Info Struct to store port and address details
     struct sockaddr_in m_addrinfo;

    public:
    streamingclient(std::string_view address, const int port);

    // Connecting to a port
    bool Connect() override;

    // Parsing Data
    void parseData(char buffer[512]) override;

    // Sending Data
    void sendData(const std::string &buffer) override; 

    // Receiving Data
    void recvData() override;

    ~streamingclient();
};

#endif  //!__CLIENT__H__