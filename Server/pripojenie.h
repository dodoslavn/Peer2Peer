#ifndef PRIPOJENIE_H
#define PRIPOJENIE_H

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>

#include <vector>
#include "klienti.h"

class Pripojenie
    {
    private:
        bool ready;
        int m_port, listenFd, pId, m_connFd;
        socklen_t dlzka;
        struct sockaddr_in serverAddress, clientAddress;
        int spustiServer();
        static void *prijmacHlp(void *objekt);
        void *spusti();
        Klienti* m_klienti;
    public:
        Pripojenie(int port, pthread_mutex_t mutex);
        Pripojenie();
        static void *spustiHlp(void *objekt);
        bool setPort(int port);
        bool setKlienti(std::vector<Klienti*> *zoznam);
        int priprav();
        void *prijmac();
        void vypisKlientov();
    };

#endif // PRIPOJENIE_H
