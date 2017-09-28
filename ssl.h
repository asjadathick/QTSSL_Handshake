#ifndef SSL_H
#define SSL_H

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <exception>

#define FAIL    -1

int OpenConnection(const char *hostname, int port);
SSL_CTX* InitCTX(void);
std::string performHandshake(int count, char *strings[]);


#endif // SSL_H
