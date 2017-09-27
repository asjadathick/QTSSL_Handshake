#include "ssl.h"

 int OpenConnection(const char *hostname, int port){
     int sd;
     struct hostent *host;
     struct sockaddr_in addr;

     if ((host = gethostbyname(hostname)) == NULL){
         perror(hostname);
         abort();
     }
     sd = socket(PF_INET, SOCK_STREAM, 0);
     bzero(&addr, sizeof(addr));
     addr.sin_family = AF_INET;
     addr.sin_port = htons(port);
     addr.sin_addr.s_addr = *(long*)(host->h_addr);
     if (connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0){
         close(sd);
         perror(hostname);
         abort();
     }
     return sd;
 }

 SSL_CTX* InitCTX(void) {
     SSL_CTX *ctx;

     OpenSSL_add_all_algorithms();
     SSL_load_error_strings();
     const SSL_METHOD *method = TLSv1_2_client_method();
     ctx = SSL_CTX_new(method);
     if (ctx == NULL){
         ERR_print_errors_fp(stderr);
         abort();
     }
     return ctx;
 }

 void ShowCerts(SSL* ssl){

 }

 std::string performHandshake(int count, char *strings[])
 {
     std::string output = "";
     char buffer[20000]; //max buffer size
     buffer[0]='\0';
     SSL_CTX *ctx;
     int server;
     SSL *ssl;
     char buf[1024];
     int bytes;
     char *hostname, *portnum;

     if (count != 3) {
         sprintf(buffer, "usage: %s <hostname> <portnum>\n", strings[0]);
         exit(0);
     }
     SSL_library_init();
     hostname=strings[1];
     portnum=strings[2];

     ctx = InitCTX();
     server = OpenConnection(hostname, atoi(portnum));
     ssl = SSL_new(ctx);
     SSL_set_fd(ssl, server);

     if ( SSL_connect(ssl) == FAIL ){
         ERR_print_errors_fp(stderr);
     }
     else {
         sprintf(buffer + strlen(buffer), "Cipher suite: %s\n", SSL_get_cipher(ssl));
         sprintf(buffer + strlen(buffer), "Master Secret: ");
         for (int i = 0; i < 48; ++i) {
             sprintf(buffer + strlen(buffer), "%02X", SSL_get_session(ssl)->master_key[i]);
         }
         sprintf(buffer + strlen(buffer), "\n");

         sprintf(buffer + strlen(buffer), "Session ID: ");
         for (int i = 0; i < 32; ++i) {
             sprintf(buffer + strlen(buffer), "%02X", SSL_get_session(ssl)->session_id[i]);
         }
         sprintf(buffer + strlen(buffer), "\n");


         X509 *cert;
         char *line;

         cert = SSL_get_peer_certificate(ssl);
         if ( cert != NULL ) {
             sprintf(buffer + strlen(buffer), "Server certificates:\n");
             line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
             sprintf(buffer + strlen(buffer), "Subject: %s\n", line);
             free(line);
             line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
             sprintf(buffer + strlen(buffer), "Issuer: %s\n", line);
             free(line);
             X509_free(cert);
         } else{
             sprintf(buffer + strlen(buffer), "Info: No client certificates configured.\n");
         }

         SSL_free(ssl);
     }
     close(server);
     SSL_CTX_free(ctx);
     output = buffer;
     return output;
 }
