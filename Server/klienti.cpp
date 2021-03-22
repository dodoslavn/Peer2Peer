#include "klienti.h"

Klienti::Klienti()
    {
    m_zoznamKlientov.clear();
    m_id = 0;
    }

int Klienti::getPocet()
    { return m_zoznamKlientov.size(); }

void Klienti::vypisZoznam()
    {
    for(unsigned int i = 0; i<=m_zoznamKlientov.size(); i++)
      {
      (m_zoznamKlientov.at(i))->printInfo();
      }
    }

int Klienti::pridaj(struct sockaddr_in address)
  {
  m_zoznamKlientov.push_back(new Klient(address, ++m_id));
  return m_id;
  }

Klient* Klienti::getKlient(int p_id)
  {
  int unsigned c = 0;
  bool naslosa = false;

  while(c < m_zoznamKlientov.size() or naslosa)
    {
    c++;
    if ((m_zoznamKlientov.at(c))->getId() == p_id ) return m_zoznamKlientov.at(c);
    }
  return nullptr;
  }
