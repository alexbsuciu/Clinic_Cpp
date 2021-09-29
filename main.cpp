#include <iostream>
#include <fstream>
#include "clinica.h"
#include <time.h>
#define clrscr() cout<<"\e[1;1H\e[2J"

// variabile globale

int nrMedic, nrProg, alegere, alegeredoc, alegerepr;
Medic ** vectorMedici;
Programare ** vectorProgramare;

// --------------- Parte de cod pt DB Medici ---------------

// citire medici

Medic ** citireMedici()
{
  ifstream f("medici.txt");
  f >> nrMedic;
  f.get();
  vectorMedici = new Medic*[500];
  char buff[256];
  for(int i = 0; i < nrMedic; i++)
  {
    f.getline(buff, 256);
    vectorMedici[i] = new Medic;
    vectorMedici[i] -> setN(strtok(buff, ","));
    vectorMedici[i] -> setF(strtok(NULL, ","));
    vectorMedici[i] -> setC(strtok(NULL, ","));
    vectorMedici[i] -> setS(strtok(NULL, ","));
  }
  f.close();
  return vectorMedici;
}

// afisare medici

void afisareMedici()
{
  cout<<"Nr.  Nume  Prenume  CNP  Specializare\n";
  for(int i = 0; i < nrMedic; i++)
    cout << "[" << i + 1 << "] " << *vectorMedici[i] << "\n";
}

// adaugare medic

void addMedic()
{
  nrMedic++;
  cout << "Introduceti datale noului medic:" << "\n";
  vectorMedici[nrMedic - 1] = new Medic;
  cin >> *vectorMedici[nrMedic - 1];
}

// salvare modificari DB medici

void saveMedici()
{
  ofstream fout("medici.txt");
  fout << nrMedic << "\n";
  for(int i=0;i < nrMedic; i++)
  {
    fout << *vectorMedici[i];
  }
  fout.close();
}

// sortare DB medici

void sortMedici()
{
  for(int i=0;i<nrMedic-1;i++)
  {
    for(int j=i+1;j<nrMedic;j++)
    {
      if(strcmp(vectorMedici[i]->getN(),vectorMedici[j]->getN())>0)
      {
        Medic *aux;
        aux = vectorMedici[i];
        vectorMedici[i] = vectorMedici[j];
        vectorMedici[j] = aux;
      }
      else
      {
        if(strcmp(vectorMedici[i]->getN(), vectorMedici[j]->getN())==0)
        {
          if(strcmp(vectorMedici[i]->getF(), vectorMedici[i]->getF())>0)
          {
           Medic *aux = vectorMedici[i];
           vectorMedici[i] = vectorMedici[j];
           vectorMedici[j] = aux;
          }
        }
      }
    }
  }
}

// cautare medic dupa CNP

int searchMedic(char *cnp)
{
  int index = -1;
  for(int i=0;i<nrMedic;i++)
  {
    if(strcmp(vectorMedici[i]->getC(),cnp)==0)
    {
      index = i;
      break;
    }
  }
  return index;
}

// stergere medic

void stergereMedic(int indice)
{
  if(indice != -1)
  {
    for(int i=indice+1;i<nrMedic;i++)
    {
      vectorMedici[i-1] = vectorMedici[i];
    }
    nrMedic--;    
  }
  else
  {
    cout<<"Doctorul cautat nu exista!\n";
  }
}

// modificare medic

void modificareMedic(int indice)
{
  if(indice == -1)
    cout<<"Doctorul cautat nu exista!\n";
  else
  {
    cout<<"Ce doriti sa modificati? \n";
    cout<<"1) Numele\n";
    cout<<"2) Prenumele\n";
    cout<<"3) CNP\n";
    cout<<"4) Specializarea\n";
    cout<<"Introduceti orice alt numar pentru a inchide comanda.\n";
    cout<<"Introduceti optiunea:\n";
    int opt;
    cin>>opt;
    cin.get();
    char modif[30];
    switch(opt)
    {
      case 1:
      {
        cout<<"Introduceti numele:\n";
        cin.getline(modif,30);
        vectorMedici[indice]->setN(modif);
        break;
      }
      case 2:
      {
        cout<<"Introduceti prenumele:\n";
        cin.getline(modif,30);
        vectorMedici[indice]->setF(modif);
        break;
      }
      case 3:
      {
        cout<<"Introduceti CNP-ul:\n";
        cin.getline(modif,30);
        vectorMedici[indice]->setC(modif);
        break;
      }
      case 4:
      {
        cout<<"Introduceti specializarea:\n";
        cin.getline(modif,30);
        vectorMedici[indice]->setS(modif);
        break;
      }
      default:
        break;
    }
  }
}

// afisare medici cu o anumita specializare

void afspec(char *spec)
{
  cout<<"Nr.  Nume  Prenume  CNP  Specializare\n";
  for(int i = 0; i < nrMedic; i++)
    if(strcmp(vectorMedici[i]->getS(),spec)==0)
      cout << "[" << i + 1 << "] " << *vectorMedici[i] << "\n";
}

// --------------- Parte de cod pt DB Programari ---------------

// citire programari

Programare ** citireProgramare()
{
  ifstream f("programari.txt");
  f >> nrProg;
  f.ignore();
  vectorProgramare = new Programare*[500];
  char buff[256];
  for(int i = 0; i < nrProg; i++)
  {
    f.getline(buff, 256);
    vectorProgramare[i] = new Programare;
    vectorProgramare[i] -> setNume(strtok(buff, ","));
    vectorProgramare[i] -> setPrenume(strtok(NULL, ","));
    vectorProgramare[i] -> setCNP(strtok(NULL, ","));
    vectorProgramare[i] -> setDate(strtok(NULL, ","));
    vectorProgramare[i] -> setSpec(strtok(NULL, ","));
    vectorProgramare[i] -> setTrim(strtok(NULL, ","));
  }
  f.close();
  return vectorProgramare;
}

// afisare programari

void afisareProgramari()
{
  cout<<"Nr.  Nume   Prenume    CNP    Data    Clinica   Trimitere\n";
  for(int i = 0; i < nrProg; i++)
    cout << "[" << i + 1 << "] " << *vectorProgramare[i] << "\n";
}

// adaugare programare

void addProgramare()
{
  nrProg++;
  cout << "Introduceti datale noii programari:\n";
  vectorProgramare[nrProg - 1] = new Programare;
  cin >> *vectorProgramare[nrProg - 1];
}

// salvare modificari programari

void saveProgramare()
{
  ofstream fout("programari.txt");
  fout << nrProg<< "\n";
  for(int i = 0; i < nrProg; i++)
    fout << *vectorProgramare[i];
  fout.close();
}

// sortare programari

void sortProgramari()
{
  for(int i=0;i<nrProg-1;i++)
  {
    for(int j=i+1;j<nrProg;j++)
    {
      if(vectorProgramare[i]->getYear() > vectorProgramare[j]->getYear())
      {
        Programare *aux;
        aux = vectorProgramare[i];
        vectorProgramare[i] = vectorProgramare[j];
        vectorProgramare[j] = aux;
      }
      else
      {
        if(vectorProgramare[i]->getYear() == vectorProgramare[j]->getYear())
        {
          if(vectorProgramare[i]->getMonth() > vectorProgramare[j]->getMonth())
          {
            Programare *aux;
            aux = vectorProgramare[i];
            vectorProgramare[i] = vectorProgramare[j];
            vectorProgramare[j] = aux;
          }
          else
          {
            if(vectorProgramare[i]->getMonth() == vectorProgramare[j]->getMonth())
            {
              if(vectorProgramare[i]->getDay() > vectorProgramare[j]->getDay())
              {
                Programare *aux;
                aux = vectorProgramare[i];
                vectorProgramare[i] = vectorProgramare[j];
                vectorProgramare[j] = aux;
              }
            }
          }
        }
      }
    }
  }
}

// cautare prog dupa CNP

int searchProgramare(char *cnp)
{
  int index = -1;
  for(int i=0;i<nrProg;i++)
  {
    if(strcmp(vectorProgramare[i]->getCNP(),cnp)==0)
    {
      index = i;
      break;
    }
  }
  return index;
}

// stergere programare

void stergereProgramare(int indice)
{
  if(indice != -1)
  {
    for(int i=indice+1;i<nrProg;i++)
    {
      vectorProgramare[i-1] = vectorProgramare[i];
    }
    nrProg--;    
  }
  else
  {
    cout<<"Programarea cautata nu exista!\n";
  }
}

// modificare programare

void modificareProgramare(int indice)
{
  if(indice == -1)
    cout<<"Programarea cautata nu exista!\n";
  else
  {
    cout<<"Ce doriti sa modificati? \n";
    cout<<"1) Numele\n";
    cout<<"2) Prenumele\n";
    cout<<"3) CNP\n";
    cout<<"4) Data\n";
    cout<<"5) Clinica\n";
    cout<<"6) Trimiterea\n";
    cout<<"Introduceti orice alt numar pentru a inchide comanda.\n";
    cout<<"Introduceti optiunea:\n";
    int opt;
    cin>>opt;
    cin.get();
    char modif[30];
    switch(opt)
    {
      case 1:
      {
        cout<<"Introduceti numele:\n";
        cin.getline(modif,30);
        vectorProgramare[indice]->setNume(modif);
        break;
      }
      case 2:
      {
        cout<<"Introduceti prenumele:\n";
        cin.getline(modif,30);
        vectorProgramare[indice]->setPrenume(modif);
        break;
      }
      case 3:
      {
        cout<<"Introduceti CNP-ul:\n";
        cin.getline(modif,30);
        vectorProgramare[indice]->setCNP(modif);
        break;
      }
      case 4:
      {
        cout<<"Introduceti data:\n";
        cin.getline(modif,30);
        vectorProgramare[indice]->setDate(modif);
        break;
      }
      case 5:
      {
        cout<<"Introduceti clinica:\n";
        cin.getline(modif,30);
        vectorProgramare[indice]->setSpec(modif);
        break;
      }
      case 6:
      {
        cout << "Introduceti 0 daca nu are trimitere sau 1 daca are:\n";
        cin.getline(modif, 30);
        vectorProgramare[indice] -> setTrim(modif);
      }
      default:
        break;
    }
  }
}

// afisare programari de la o anumita clinica

void afSpecProg(char *clin)
{
  cout<<"Nr.  Nume   Prenume    CNP    Data    Clinica   Trimitere\n";
  for(int i = 0; i < nrProg; i++)
    if(strcmp(vectorProgramare[i]->getSpec(),clin)==0)
      cout << "[" << i + 1 << "] " << *vectorProgramare[i] << "\n";
}

char *getDate();

// afisare programari din data de azi
void afisareProgramariAzi()
{
  clrscr();
  char *todayDate = getDate();
  for(int i = 0; i < nrProg; i++)
  {
    if(!strcmp(vectorProgramare[i] -> getDate(), todayDate))
    {
      cout << *vectorProgramare[i] << "\n";
    }
  }
}

void afisareProgramariData()
{
  cin.ignore();
  cout << "Introduceti data: ";
  char date[13];
  cin.getline(date, 13);
  clrscr();
  for(int i = 0; i < nrProg; i++)
  {
    if(!strcmp(vectorProgramare[i] -> getDate(), date))
    {
      cout << *vectorProgramare[i] << "\n";
    }
  }
}
// --------------- Main si alte comenzi ajutatoare ---------------

// create current date

char *getDate()
{ 
  char *date = new char[12];
  time_t now;
  time(&now);
  struct tm *local = localtime(&now);
  int day = local->tm_mday;
  int month = local->tm_mon + 1;
  int year = local->tm_year + 1900;
  char buff[10];
  sprintf(buff, "%d", day);
  strcpy(date, buff);
  strcat(date, "/");
  if(month < 10)
    strcat(date, "0");
  sprintf(buff, "%d", month);
  strcat(date, buff);
  strcat(date, "/");
  sprintf(buff, "%d", year);
  strcat(date, buff);
  return date;
}

// text pt finalizare comanda

void endTask()
{ 
  cout<<"\n";
  cout<<"\n";
  cout<<"Comanda finalizata!\n";
  cout<<"1) Inapoi la meniu\n";
  cout<<"Apasati orice alt numar pentru inchiderea programului!\n";
}

int main() 
{
  citireMedici();
  citireProgramare();
  clrscr();
  cout<<"Selectati cifra corenspunzatoare optiunii dorite:\n";
  optiuni1: 
  cout<<"1) Baza de date pentru doctori\n";
  cout<<"2) Baza de date pentru programari\n";
  cout<<"0) Inchidere\n";
  cin>>alegere;
  switch(alegere)
  {
    case 1:
    {
      clrscr();
      cout<<"Alegeti actiunea dorita:\n";
      optiunidoctori:
      cout<<"1) Afisare lista doctori\n";
      cout<<"2) Adaugarea unui doctor nou\n";
      cout<<"3) Stergerea unui doctor din lista\n";
      cout<<"4) Modificarea datelor unui doctor\n";
      cout<<"5) Afisarea doctorilor cu o anumita specialitate\n";
      cout<<"0) Inapoi\n";
      cin>>alegeredoc;
      switch(alegeredoc)
      {
        case 1:
        {
          // afisare medici
          clrscr();
          sortMedici();
          saveMedici();
          afisareMedici();
          endTask();
          int choice;
          cin>>choice;
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 2:
        {

          // adaugare medic
          cin.get();
          clrscr();
          addMedic();
          sortMedici();
          saveMedici();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;          
        }
        case 3:
        {
          // stergere medic
          clrscr();
          cin.get();
          afisareMedici();
          cout<<"Introduceti CNP-ul medicului pe care doriti sa il stergeti:\n";
          char cnp[15];
          cin.getline(cnp,15);
          stergereMedic(searchMedic(cnp));
          sortMedici();
          saveMedici();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 4:
        {
          // modificare medic
          clrscr();
          cin.get();
          afisareMedici();
          cout<<"Introduceti CNP-ul medicului ale carui date doriti sa le modificati:\n";
          char cnp[15];
          cin.getline(cnp,15);
          modificareMedic(searchMedic(cnp));
          sortMedici();
          saveMedici();
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 5:
        {
          // afisare doctori cu o anumita specializare
          clrscr();
          sortMedici();
          saveMedici();
          cin.get();
          char spec[30];
          cout<<"Introduceti specializarea pentru care vor fi afisati medicii:\n";
          cin.getline(spec,30);
          afspec(spec);
          endTask();
          int choice;
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiunidoctori;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 0:
        {
          clrscr();
          cout<<"Alegeti o optiune:\n";
          goto optiuni1;
          break;
        }
        default:
        {
          clrscr();
          cout<<"Alegere invalida, va rugam incercati din nou!\n";
          goto optiunidoctori;
        }
      }
      break;
    }
    case 2:
    {
      clrscr();
      cout<<"Alegeti actiunea dorita:\n";
			optiuniprogramari:
      cout<<"1) Afisare lista programari\n";
      cout<<"2) Adaugarea unei programari noi\n";
      cout<<"3) Stergerea unei programari din lista\n";
      cout<<"4) Modificarea datelor unei programari\n";
      cout<<"5) Afisarea programarilor de azi\n";
      cout<<"6) Afisarea programarilor dintr-o anumita data\n";
      cout<<"7) Afisarea programarilor de la o anumita clinica\n";
      cout<<"0) Inapoi\n";
      cin>>alegerepr;
      switch(alegerepr)
      {
        case 1:
        {
          // afisare programari
          clrscr();
          cin.get();
          sortProgramari();
          saveProgramare();
          afisareProgramari();
          endTask();
          int choice;
          cin>>choice;
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 2:
        {
          // adaugare programare
          clrscr();
          cin.get();
          addProgramare();
          sortProgramari();
          saveProgramare();
          endTask();
          int choice;
          cin>>choice;
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 3:
        {
          // stergere programare
          clrscr();
          cin.get();
          afisareProgramari();
          cout<<"Introduceti CNP-ul persoanei a carei programare doriti sa o stergeti:\n";
          char cnp[15];
          cin.getline(cnp,15);
          stergereProgramare(searchProgramare(cnp));
          sortProgramari();
          saveProgramare();
          endTask();
          int choice;
          cin>>choice;
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 4:
        {
          // modificare programare
          clrscr();
          cin.get();
          afisareProgramari();
          cout<<"Introduceti CNP-ul persoanei a carei programare doriti sa o modificati:\n";
          char cnp[15];
          cin.getline(cnp,15);
          modificareProgramare(searchProgramare(cnp));
          sortProgramari();
          saveProgramare();
          endTask();
          int choice;
          cin>>choice;
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 5:
        {
          clrscr();
          cout<<"Afisare programari de azi:\n";
          afisareProgramariAzi();
          endTask();
          int choice;
          cin>>choice;
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 6:
        {
          clrscr();
          cout<<"Afisare programari anumita data:\n";
          afisareProgramariData();
          endTask();
          int choice;
          cin>>choice;
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 7:
        {
          // afisare programari de la o anumita clinica
          clrscr();
          cin.get();
          cout<<"Introduceti clinica de unde vor fi afisate programarile:\n";
          char clin[20];
          cin.getline(clin,20);
          sortProgramari();
          saveProgramare();
          afSpecProg(clin);
          endTask();
          int choice;
          cin>>choice;
          switch(choice)
          {
            case 1:
            clrscr();
            goto optiuniprogramari;
            break;

            default:
            return 0;
            break;
          }
          break;
        }
        case 0:
        {
          clrscr();
          cout<<"Alegeti o optiune:\n";
          goto optiuni1;
          break;
        }
        default:
        {
          clrscr();
          cout<<"Alegere invalida, va rugam incercati din nou!\n";
          goto optiuniprogramari;
        }
      }
      break;
    }
    case 0:
    {
      return 0;
    }
    default:
    {
      clrscr();
      cout<<"Alegere invalida, va rugam incercati din nou!\n";
      goto optiuni1;
    }
  }
  return 0;
}