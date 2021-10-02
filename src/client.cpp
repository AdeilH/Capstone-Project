#include "client.hpp"

client::client(/* args */) {}

client::~client() {}

streamingclient::streamingclient(std::string_view address, const int port) {
  m_socketfd = socket(AF_INET, SOCK_STREAM, 0);
  switch (m_socketfd) {
    case -1:
      LOG("SOCKET NOT CREATED");
      switch (errno) {
        case EPROTONOSUPPORT:
          LOG("NOT SUPPORTED");
          break;
        case EMFILE:
          LOG("The process already has too many file descriptors open.");
          break;
        default:
          LOG("THE ERROR NO IS" + std::to_string(errno));
          break;
      }
      break;

    default:
      LOG("SOCKET CREATED");
      LOG("FILE DESCRIPTOR OF NEW SOCKET: " + std::to_string(m_socketfd));
      break;
  }
  m_addrinfo.sin_family = AF_INET;
  m_addrinfo.sin_addr.s_addr = inet_addr(address.data());
  m_addrinfo.sin_port = htons(port);
}

bool streamingclient::Connect() {
  if (connect(m_socketfd, reinterpret_cast<struct sockaddr *>(&m_addrinfo),
              sizeof(m_addrinfo)) < 0) {
    switch (errno) {
      case EINVAL:
        LOG("SOCKET ALREADY Connected");
        break;
      case ECONNREFUSED:
        LOG("FAILED TO ESTABLISH CONNECTION")
        break;
      default:
        LOG("ERROR NO: " + std::to_string(errno));
        break;
    }
    LOG(m_addrinfo.sin_family);
    LOG(m_addrinfo.sin_port);
    LOG(m_addrinfo.sin_addr.s_addr);
    LOG("SOCKET NOT CONNECTED");
    return false;
  }
  LOG("SOCKET CONNECTED");
  return true;
}

void streamingclient::parseData(char buffer[512]) {
  std::cout << std::string(buffer) << std::endl;
}

void streamingclient::recvData() {
  while (true) {
    char buffer[512];
    auto bytesrcvd = read(m_socketfd, buffer, 512);
    if (bytesrcvd < 0) {
      LOG("Couldn't Read");
    } else if (bytesrcvd == 0)
      /* End-of-file. */
      return;
    else {
      LOG("Message Recieved: " + std::string(buffer));
      parseData(buffer);
      return;
    }
  }
}

void streamingclient::sendData(const std::string &buffer) {
 LOG("SENDING DATA");
 int sendStatus = write(m_socketfd, buffer.c_str(), buffer.size());
 if (sendStatus < 0){
      LOG("Send Failed");
      switch (errno) {
        case EAGAIN:
          LOG("EAGAIN");
          break;
        case EBADF:
          LOG(" The filedes argument is not a valid file descriptor, or is "
              "not "
              "open for writing.");
          break;
        case EFBIG:
          LOG("The size of the file would become larger than the "
              "implementation can support.");
          break;
        case EINTR:
          LOG("The write operation was interrupted by a signal while it was "
              "blocked waiting for completion");
          break;
        case EIO:
          LOG("HARDWARE ERROR");
          break;
        case ENOSPC:
          LOG("The device containing the file is full.")
          break;
        case EPIPE:
          LOG("Isn't open for reading");
          break;
        case EINVAL:
          LOG("Offsets not aligned");
          break;
      }
 }
 else{
      LOG("Send Successful");
      recvData();
  }
}

streamingclient::~streamingclient() { close(m_socketfd); }