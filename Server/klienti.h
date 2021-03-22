#ifndef KLIENTI_H
#define KLIENTI_H

#include <netdb.h>
#include <iostream>
#include <string>
#include <vector>

#include "klient.h"

class Klienti
    {
    private:
        std::vector<Klient*> m_zoznamKlientov;
        int m_id;
    public:
        Klienti();
        int getPocet();
        void vypisZoznam();
        int pridaj(struct sockaddr_in address);
        Klient* getKlient(int id);
    };

#endif // KLIENTI_H
