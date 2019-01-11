#include "Commands.h"
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include "ReadBufferServer.cpp"

bool OpenDateServerCommand::toConnect = false;

struct params {
    int Hz;
    int port;
};

void *ReadDataFromServer(void *args) {
    int portno = ((params *) args)->port;
    int Hz = ((params *) args)->Hz;
    int sockfd, newsockfd, clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    int option = 1;
    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    /* Now start listening for the clients, here process will */
    cout << "open the simulator" << endl;
    listen(sockfd, Hz);
    clilen = sizeof(cli_addr);
    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    cout << "connected to the server. when its gui is open enter character" << endl;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    while (!OpenDateServerCommand::toConnect) {
        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        /* If connection is established then start communicating */
        bzero(buffer, 1024);
        n = read(newsockfd, buffer, 1023);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        pthread_mutex_lock(&mutex);
        ReadBufferServer::updatMaps(buffer);
        pthread_mutex_unlock(&mutex);
        /* Write a response to the client */
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        };
        this_thread::sleep_for(0.2s);
    }
    close(sockfd);
}

void OpenDateServerCommand::doCommand(vector<string> parameters, string line) {
    params *p = new params();
    p->port = stoi(parameters[1]);
    p->Hz = stoi(parameters[2]);
    pthread_t pthread;
    pthread_create(&pthread, nullptr, ReadDataFromServer, p);
}

