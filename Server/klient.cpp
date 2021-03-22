#include "klient.h"

Klient::Klient(struct sockaddr_in address, int id)
    {
    this->m_address = address;
    this->m_id = id;
    }

void Klient::printInfo()
    {
    std::cout << "\nID: " << m_id << " asi port: "  << this->m_address.sin_port << std::endl;
    }

int Klient::getId()
    { return m_id; }
