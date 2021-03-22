#include "pripojenie.h"

Pripojenie::Pripojenie()
    { std::cout << "> Vytvaram server" ; }

Pripojenie::Pripojenie(int port, pthread_mutex_t mutex)
    {
    std::cout << "> Vytvaram server na porte " << port;
    setPort(port);
    }

bool Pripojenie::setPort(int port)
    {
    if((port > 65535) || (port < 2000))
        {
        std::cout << "\nEr: Nespravny port! (2000 - 65535)";
        return false;
        }
    else
        {
        m_port = port;
        return true;
        }
    }

void Pripojenie::vypisKlientov()
    {
    m_klienti->vypisZoznam();
    }

int Pripojenie::priprav()
    {
    int ret = 0;
    if (!setPort(m_port))
        {ret = 1;}
    if (ret == 0)
        {
        ready = true;
        std::cout << "\n> Server je pripravemy";
        }
    return ret;
    }

void *Pripojenie::spusti()
    {
    if (ready)
        {
        spustiServer();
        }
    else
        { std::cout << "\nEr: server nieje pripraveny"; }
    return 0;
    }

int Pripojenie::spustiServer()
    {
    std::cout << "> Spustam server" << std::endl;
    std::vector<pthread_t> vlakna;

    listenFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //create socket

    if(listenFd < 0)
        {
        std::cout << "\nEr: Socket nemozno vytvorit!";
        exit(0);
        }
    else { std::cout << "> Socket uspesne vytvoreny" << std::endl; }

    bzero((char*) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(m_port);

    while (bind(listenFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        { std::cout << "Er: Socket nemozno nabindovat" << std::endl; sleep(3); }
    std::cout << "> Socket uspesne nabindovany" << std::endl;

    listen(listenFd, 5);
    dlzka = sizeof(clientAddress);


    while(true)
        {
        std::cout << "> Cakam na nove pripojenie" << std::endl;

        //this is where client connects. svr will hang in this mode until client conn
        m_connFd = accept(listenFd, (struct sockaddr *)&clientAddress, &dlzka);

        if (m_connFd < 0)
            {
            std::cout << "\nEr: Nemozno prijat spojenie!\n";
            exit(0);
            }
        else
            { std::cout << "\n> Nove pripojenie upsesne nadviazane" << std::endl; }

        pthread_t vlakno;

        //pthread_create(&threadA[noThread++], NULL, &prijmacHlp, &*this);
        pthread_create(&vlakno, NULL, &prijmacHlp, &*this);
        vlakna.push_back(vlakno);
        }
    }

void *Pripojenie::prijmac()
    {
    //std::cout << "\n> Cislo vlakna: " << pthread_self();
    std::cout << "> Port: " << clientAddress.sin_port << std::endl;
    //int klient_id = m_klienti->pridaj(clientAddress);

    char test[300];
    int connFd = m_connFd, n = 1;
    bzero(test, 301);
    do
        {
        bzero(test, 301);
        n = read(connFd, test, 300);
        if ( (std::string) test != "")
            {
            //std::cout << "\nKlient[" << m_klienti->getKlient(klient_id)->getId() << "]: " << (std::string) test << std::endl;  //<< std::to_string(k->getId)
            if ( (std::string) test == "exit" ) { n = 0; }
            }
        else n = 0;
        }
    while(n > 0);

    if (n == 0)  { std::cout << "\n> Klient odpojeny" << std::endl; }
    else { std::cout << "\nEr: Chyba pri citani socket!" << std::endl; }

    close(connFd);
    return 0;
    }

void *Pripojenie::prijmacHlp(void *objekt)
    {return ((Pripojenie *)objekt)->prijmac(); }

void *Pripojenie::spustiHlp(void *objekt)
    { return ((Pripojenie *)objekt)->spusti(); }
