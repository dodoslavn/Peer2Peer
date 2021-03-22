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

#include "pripojenie.h"
#include "klienti.h"



pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char* argv[])
    {
    pthread_t vlakno;
    std::string vstup;

    Pripojenie *serverik = new Pripojenie(27015, mutex);
    serverik->priprav();

    pthread_create(&vlakno, NULL, &serverik->spustiHlp, &*serverik);
    sleep(1);

    do
        {
        std::cout << "# ";
        std::cin >> vstup;
        if (vstup == "zoznam")
            { serverik->vypisKlientov(); }
        }
    while(vstup != "exit");

    std::cout << "> Vypinam server\n";
    pthread_detach(vlakno);

    delete serverik;
    }
