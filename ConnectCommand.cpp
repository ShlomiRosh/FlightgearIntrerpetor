#include "Commands.h"
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int ConnectCommand::sockfd = 0;

void ConnectCommand::doCommand(vector<string> parameters, string line) {
    char isConnected;
    string IP = parameters[1];
    int portno = stoi(parameters[2]);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    server = gethostbyname(IP.c_str());
    if (server == nullptr) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    cin >> isConnected;
    if (connect(this->sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
}

void ConnectCommand::deliverDateToServer(string thePath, double itsValue) {
    if (!sockfd) {
        throw("You are not connected to a server: try open the FlightGear and run again");
    }
    string thePathAndItsValue = "set " + thePath + ' ' + to_string(itsValue) + "\r\n";
    int returnValue = write(sockfd, thePathAndItsValue.c_str(), thePathAndItsValue.size());
    if (returnValue < 0) {
        perror("Failed to deliver data to server");
        exit(1);
    }
}

void ConnectCommand::stopToConnect() {
    close(ConnectCommand::sockfd);
}
