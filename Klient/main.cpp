#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h> //sleep
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> //client


//              C L I E N T

bool report = true, runi = true, runo = true;
int sockfd, nr;
struct sockaddr_in serv_addr;
struct hostent *server;
char buffer[256];
pthread_t vlakno, mainv;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void hlaska(std::string sprava)
    {
    pthread_mutex_lock(&mutex);
    if (report)
        { std::cout << "> " << sprava << std::endl; }
    pthread_mutex_unlock(&mutex);
    }

void error(const char *msg)
    {
    perror(msg);
    runi = false;
    }

void* prijmac(void*)
    {
    int n;
    char buffer[256];
    do
        {
        bzero(buffer,256);
        n = read(sockfd,buffer,255);
        if ( (std::string) buffer != "") { std::cout << "\nServer: " << buffer; }
        }
    while (n > 0);

    if (n == 0)
        { std::cout << "\n> Chyba pri citani zo socketu\n> Pripojienie ukoncene\n"; runi = false; }
    else
        { error("Er: Chyba pri citani socketu!\n"); }
    pthread_cancel(mainv);
    return 0;
    }

void connect(const int portno,const char* host)
    {
    hlaska("Vytvaram pripojenie");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { error("Er: Nemozno otvorit socket!\n"); }
    else { hlaska("Socket upsesne vytvoreny"); }
    server = gethostbyname(host);
    if (server == NULL)
        {
        fprintf(stderr,"Er: Neplatna adresa!");
        exit(0);
        }
    else { hlaska("Adresa priradenaa"); }

    hlaska("Pripajam sa na server");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    while( connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0 )
        { sleep(3); }
    std::cout << "\n> Pripojeny";
    }

void *main2(void *)
    {
    std::cout << std::endl;
    do
        {
        std::cout << "# ";
        bzero(buffer,256);
        fgets(buffer,255,stdin);

        if ( (std::string) buffer != "" ) { nr = write(sockfd,buffer,strlen(buffer)); }
        }
    while (std::string (buffer) != "exit" && nr >= 0 && runi);
    return 0;
    }

int main(int argc, char *argv[])
    {
    while(runo)
        {
        connect(27015,"localhost");
        pthread_create( &vlakno , NULL ,  &prijmac , NULL );
        pthread_create( &mainv , NULL ,  &main2 , NULL );

        sleep(3);
        pthread_join(mainv, NULL);
        if (std::string(buffer) == "exit") { runo = false; std::cout << "\n> Spojenie ukoncene uzivatelom"; }
        else if ( nr == 0 ) { std::cout << "\n> Chyba pri zapise do socketu\n> Pripojenie ukoncene"; }
        else { std::cout << "\n> Chyba pri zapise do socketu"; }

        std::cout << "\n> Odpajam sa od servera\n ======\n";
        pthread_cancel(vlakno);
        close(sockfd);
        }
    return 0;
    }
