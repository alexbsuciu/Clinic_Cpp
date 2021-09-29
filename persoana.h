#include <iostream>
#include <cstring>

using namespace std;


// clasa cu datele de baza ale unei persoane

class Persoana
{
protected:
  char *CNP;
  char *Name;
  char *Firstname;
public:

  // constructor

  Persoana(char *firstname = nullptr, char *name = nullptr, char *cnp = nullptr)
  {
    if(cnp != nullptr)
    {
      CNP = new char[strlen(cnp) + 1];
      strcpy(CNP, cnp);
    } else
      CNP = nullptr;
    if(name != nullptr)
    {
      Name = new char[strlen(name) + 1];
      strcpy(Name, name);
    } else
      Name = nullptr;
    if(firstname != nullptr)
    {
      Firstname = new char[strlen(firstname) + 1];
      strcpy(Firstname, firstname);
    } else
      Firstname = nullptr;
  }

  // constructor de copiere

  Persoana(Persoana &p)
  {
    if(CNP != nullptr)
      delete[] CNP;
    if(Name != nullptr)
      delete[] Name;
    if(Firstname != nullptr)
      delete[] Firstname;
    CNP = new char[strlen(p.CNP) + 1];
    Name = new char[strlen(p.Name) + 1];
    Firstname = new char[strlen(p.Firstname) + 1];
    strcpy(CNP, p.CNP);
    strcpy(Name, p.Name);
    strcpy(Firstname, p.Firstname);
  }

  //destructor

  ~Persoana()
  {
    delete[] CNP;
    delete[] Name;
    delete[] Firstname;
  }

  // functii de get, name says it all

  char *getC() const
  {
    return CNP;
  }
  char *getF() const
  {
    return Firstname;
  }
  char *getN() const
  {
    return Name;

  }

  // functii pentru setat fiecare detaliu

  void setC(char *cnp)
  {
    if(CNP != nullptr)
      delete[] CNP;
    CNP = new char[strlen(cnp) + 1];
    strcpy(CNP, cnp);
  }
  void setF(char *firstname)
  {
    if(Firstname != nullptr)
      delete[] Firstname;
    Firstname = new char[strlen(firstname) + 1];
    strcpy(Firstname, firstname);
  }
  void setN(char *name)
  {
    if(Name != nullptr)
      delete[] Name;
    Name = new char[strlen(name) + 1];
    strcpy(Name, name);
  }

  //

  Persoana & operator = (Persoana &);
  //
  virtual ostream & afisare(ostream &);
  virtual istream & citire(istream &);
  //
  friend ostream & operator << (ostream &, Persoana &);
  friend istream & operator >> (istream &, Persoana &);
};

// supraincarcare '='

Persoana & Persoana :: operator = (Persoana &p)
{
  if(&p != this)
  {
    if(CNP != nullptr)
      delete[] CNP;
    if(Name != nullptr)
      delete[] Name;
    if(Firstname != nullptr)
      delete[] Firstname;
    CNP = new char[strlen(p.CNP) + 1];
    Name = new char[strlen(p.Name) + 1];
    Firstname = new char[strlen(p.Firstname) + 1];
    strcpy(CNP, p.CNP);
    strcpy(Name, p.Name);
    strcpy(Firstname, p.Firstname);
  }
  return *this;
}

// supraincarcare '<<' si functie de afisare

ostream & Persoana :: afisare(ostream & os)
{
  os << Firstname << " " << Name << " " << CNP;
  return os;
}
ostream & operator << (ostream & os, Persoana & p)
{
  return p.afisare(os);
}

// supraincarcare '>>' si functie de citire

istream & Persoana :: citire(istream & is)
{
  char buff[256];
  is.getline(buff, 256);
  setF(buff);
  is.getline(buff, 256);
  setN(buff);
  is.getline(buff, 256);
  setC(buff);
  return is;
}
istream & operator >> (istream & is, Persoana & p)
{
  return p.citire(is);
}