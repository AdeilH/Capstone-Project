#include "mockserver.hpp"

#include <string>
mockserver::mockserver() {}
mockserver::~mockserver() {}
// https://www.gnu.org/software/libc/manual/html_node/Server-Example.html

/**
 * @brief Construct a new streamingserver::streamingserver object
 *
 * @param address
 * @param port
 */

/*case EPROTONOSUPPORT:
      LOG("SOCKET NOT SUPPORTED");
      break;
    case EMFILE:
      LOG("TOO MANY PROCESS FILE DESCRIPTORS");
      break;
    case ENFILE:
      LOG("TOO MANY SYSTEM FILE DESCRIPTORS");
      break;
    case EACCES:
      LOG("THE PROCESS ISN'T ALLOWED TO CREATE SOCKET");
      break;
    case ENOBUFS:
      LOG("No BUFFER SPACE");
      break;*/
streamingserver::streamingserver(std::string_view address, const int port)
    : m_port(port) {
  m_socketfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt=1;
    socklen_t optlen=sizeof(opt);
  auto ss = setsockopt(m_socketfd, SOL_SOCKET, SO_REUSEADDR , &opt, optlen);
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
      LOG("FILE DESCRIPTOR OF NEW SOCKET: " + std::to_string(m_socketfd));
      break;
  }
  m_addrinfo.sin_port = htons(m_port);
  m_addrinfo.sin_addr.s_addr = htonl(INADDR_ANY);
  m_addrinfo.sin_family = AF_INET;
}

bool streamingserver::Bind() {
  if (bind(m_socketfd, reinterpret_cast<struct sockaddr *>(&m_addrinfo),
           sizeof(m_addrinfo)) < 0) {
    switch (errno) {
      case EADDRINUSE:
        LOG("ADDRESS ALREADY IN USE");
        break;
      case EINVAL:
        LOG("SOCKET ALREADY BOUND");
        break;
    }
    LOG("Binding Failed");
    return false;
  }
  LOG("Binding Successful");

  // LOG(m_addrinfo.sin_addr.s_addr);

  if (!Listen()) {
    return false;
  }
  struct sockaddr_in m_client;
  socklen_t addrlen = 0;
  addrlen = sizeof(m_client);
  int newSock = 0;
  newSock = accept(m_socketfd, reinterpret_cast<struct sockaddr *>(&m_client),
                   &addrlen);
  if (newSock < 0) {
    LOG("accept failed");
    // ADD ERROR DETAILS switch
    LOG("ERROR NO: " + std::to_string(errno));
    return false;
  } else {
    LOG("SUCCESSFULLY ACCEPTED");
    LOG("NEW SOCKET: " + std::to_string(newSock))
    recvData(newSock);
  }
  return true;
}

/**
 * @brief Start Listening
 *
 * @return true
 * @return false
 */

bool streamingserver::Listen() {
  int listenstatus = listen(m_socketfd, 100);
  switch (listenstatus) {
    case -1:
      LOG("Listening Failed");
      switch (errno) {
        case EBADF:
          LOG("The argument socket is not a valid file descriptor");
          break;
        case ENOTSOCK:
          LOG("The argument socket is not a socket. ");
          break;
        case EOPNOTSUPP:
          LOG("The socket socket does not support this operation. ");
          break;
      }
      break;
    case 0:
      LOG("LISTENING SUCCESS");

      return true;
  }
  return false;
}

void sendError(int sockfd) {
  LOG("Sending Error to " + std::to_string(sockfd));
  std::string_view buffer =
      "You are receiving this message because you are not authorized";
  while (true) {
    int sendStatus = write(sockfd, buffer.data(), buffer.size());
    LOG(sendStatus);
    if (sendStatus < 0) {
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
            LOG("    The size of the file would become larger than the "
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
        LOG("Send Successful" + std::to_string(sendStatus));
        break;
    }
  }
}

void streamingserver::parseData(char buffer[512], int sockfd) {
   LOG("Message Recieved: " + std::string(buffer));
  if (strcmp(buffer, "One"))
    sendData(sockfd);
  else {
    LOG("UNAUTHORIZED");
    sendError(sockfd);
    return;
  }
}

/**
 * @brief
 *
 */

void streamingserver::sendData(int sockfd) {
  while(true){
  char buffer[512] = "You are receiving this message because you sent One";
  int sendStatus = write(sockfd, buffer, sizeof(buffer));
  if (sendStatus < 0) {
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
          LOG("    The size of the file would become larger than the "
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
      LOG("Send Successful" + std::to_string(sendStatus));
  }
  }
}

void streamingserver::recvData(int newSock) {
  while (true) {
    LOG("Receiving Data");
    sockaddr_in m_client;
    char buffer[512];
    auto bytesrcvd = read(newSock, buffer, sizeof(buffer));
    if (bytesrcvd < 0) {
      LOG("Couldn't Read");
      LOG("ERROR NO: " + std::to_string(errno));
    } else if (bytesrcvd == 0)
      /* End-of-file. */
      return;
    else {
     
      parseData(buffer, newSock);
      return;
    }
  }
}

streamingserver::~streamingserver() { close(m_socketfd); }