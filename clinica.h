#include <iostream>
#include <cstring>
#include "persoana.h"

// clasa pentru medici ---------------------------

class Medic : public Persoana
{
private:
  char * specializare;
public:
  Medic(char *firstname = nullptr, char *name = nullptr, char *cnp = nullptr, char *spec = nullptr) : Persoana(firstname, name, cnp)
  {
    if(spec)
    {
      specializare = new char[strlen(spec) + 1];
      strcpy(specializare, spec);
    } else
      specializare = nullptr;
  }
  Medic(Medic &m)
  {
    if(specializare)
      delete[] specializare;
    specializare = new char[strlen(m.specializare) + 1];
    strcpy(specializare, m.specializare);
  }
  ~Medic()
  {
    delete[] specializare;
  }
//
  char *getS() const
  {
    return specializare;
  }
//
  void setS(char *spec)
  {
    if(specializare)
      delete[] specializare;
    specializare = new char[strlen(spec) + 1];
    strcpy(specializare, spec);
  }
//
Medic & operator = (Medic &);
//
virtual ostream & afisare(ostream &);
virtual istream & citire(istream &);
//
friend ostream & operator << (ostream &, Medic &);
friend istream & operator >> (istream &, Medic &);
};

// supraincarcare '='

Medic & Medic :: operator = (Medic &m)
{
  if(&m != this)
  {
    if(specializare)
      delete[] specializare;
    specializare = new char[strlen(m.specializare) + 1];
    strcpy(specializare, m.specializare); 
  }
  return *this;
}

// supraincarcare "<<" si fct de afisare

ostream & Medic :: afisare(ostream &os)
{
  if(&os == &cout)
  {
    os << Name << " " << Firstname << " " << CNP << " " << specializare;
  }
  else
  {
    os << Name << "," << Firstname << "," << CNP << "," << specializare<<"\n";
  }
  return os;  
}
ostream & operator << (ostream & os, Medic & m)
{
  return m.afisare(os);
}

// supraincarcare ">>" si fct de citire

istream & Medic :: citire(istream &is)
{
  char buff[256];
  cout<<"Nume:\n";
  is.getline(buff, 256);
  setN(buff);
  cout<<"Prenume:\n";
  is.getline(buff, 256);
  setF(buff);
  cout<<"CNP:\n";
  is.getline(buff, 256);
  setC(buff);
  cout<<"Specializare:\n";
  is.getline(buff, 256);
  setS(buff);
  return is;
}
istream & operator >> (istream & is, Medic & m)
{
  return m.citire(is);
}


// clasa pentru programari ---------------------------

class Programare
{
private:
  Persoana *persoane;
  bool trimitere;
  char *date = nullptr;
  char *clinica = nullptr;
public:
  Programare(char * clin = nullptr, char *data = nullptr, bool trim = 0)
  {
    trimitere = trim;
    persoane = new Persoana;
    if(data)
    {
      date = new char[strlen(data) + 1];
      strcpy(date, data);
    }
    if(clin != nullptr)
    {
      clinica = new char[strlen(clinica) + 1];
      strcpy(clinica, clin);
    }
  }
  Programare(Programare &p)
  {
    trimitere = p.trimitere;
    persoane = p.persoane;
    date = p.date;
    if(clinica)
      delete[] clinica;
    clinica = new char[strlen(p.clinica) + 1];
    strcpy(clinica, p.clinica);
  }
  ~Programare()
  {
    delete persoane;
    delete date;
    delete[] clinica;
  }
  //
  friend ostream & operator << (ostream &, Programare &);
  friend istream & operator >> (istream & , Programare &);
  //
  void setTrim(char *t)
  {
    if(!strcmp(t, "1"))
      trimitere = true;
    else
      trimitere = false;
  }
  void setNume(char *buff)
  {
    persoane -> setN(buff);
  }
  void setPrenume(char *buff)
  {
    persoane -> setF(buff);
  }
  void setCNP(char *buff)
  {
    persoane -> setC(buff);
  }
  void setDate(char *buff)
  {
    if(date)
      delete[] date;
    date = new char[strlen(buff) + 1];
    strcpy(date, buff);
  }
  void setSpec(char *buff)
  {
    if(clinica)
      delete[] clinica;
    clinica = new char[strlen(buff) + 1];
    strcpy(clinica, buff);
  }
  //
  bool getTrim()
  {
    return trimitere;
  }
  char *getName()
  {
    return persoane -> getN();
  }
  char *getFirstname()
  {
    return persoane -> getF();
  }
  char *getCNP()
  {
    return persoane -> getC();
  }
  char *getDate()
  {
    return date;
  }
  char *getSpec()
  {
    return clinica;
  }
  int getDay()
  {
    int zi;
    char data[10];
    strcpy(data,this->date);
    char *s=strtok(data,"/");
    zi = atoi(s);
    return zi;
  }
  int getMonth()
  {
    int luna;
    char data[10];
    strcpy(data,this->date);
    char *s=strtok(data,"/");
    s = strtok(NULL,"/");
    luna = atoi(s);
    return luna;
  }
  int getYear()
  {
    int an;
    char data[10];
    strcpy(data,this->date);
    char *s=strtok(data,"/");
    s = strtok(NULL,"/");
    s = strtok(NULL,"/");
    an = atoi(s);
    return an;
  }
};

// supraincarcare "<<"

ostream & operator << (ostream & os, Programare & p)
{
  if(&os == &cout)
  {
    os << p.persoane -> getN() << " " << p.persoane -> getF() << " " << p.persoane -> getC() << " " << p.date << " " << p.clinica << " " << (p.trimitere == 1 ? "are trimitere" : "nu are trimitere");
  }
  else
  {
    os << p.persoane -> getN() << "," << p.persoane -> getF() << "," << p.persoane -> getC() << "," << p.date << "," << p.clinica << "," << p.trimitere << "\n";
  }
  return os;
}

// supraincarcare ">>"

istream & operator >> (istream & is, Programare & p)
{
  char buff[256];
  cout<<"\nNume:";
  is.getline(buff, 256);
  p.setNume(buff);
  cout<<"\nPrenume:";
  is.getline(buff, 256);
  p.setPrenume(buff);
  cout<<"\nCNP:";
  is.getline(buff, 256);
  p.setCNP(buff);
  cout<<"\nData:";
  is.getline(buff, 256);
  p.setDate(buff);
  cout<<"\nClinica:";
  is.getline(buff, 256);
  p.setSpec(buff);
  cout<< "\nTrimitere: ";
  is >> p.trimitere;
  return is;
}