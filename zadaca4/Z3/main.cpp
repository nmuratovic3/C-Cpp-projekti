//TP 2018/2019: Zadaća 4, Zadatak 3
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include <cmath>
#include <initializer_list>
using namespace std;

struct VrijemePolijetanja {
    int sati, minute; 
};
class Let
{
    static const int vel1=30;
    static const int vel2=10;
    char naziv_odredista [vel1];
    char oznaka_leta[vel2];
    int izlazna_kapija;
    int sati, minute;
    int trajanje, kasnjenje;

public:
    friend class Letovi;
    Let(const char odrediste[], const char oznaka_leta[], int kapija,
        int sat_polaska, int minute_polaska, int trajanje_leta):izlazna_kapija(kapija),sati(sat_polaska), minute(minute_polaska),trajanje(trajanje_leta)
    {
        if(strlen(odrediste)>30 || strlen(oznaka_leta)>10) throw domain_error ("Neispravan naziv");
        if(sat_polaska<0 || sat_polaska>23 || minute_polaska<0 || minute_polaska>59) throw domain_error("Neispravno vrijeme");
        kasnjenje=0;
        strcpy(naziv_odredista,odrediste);
        strcpy(Let::oznaka_leta,oznaka_leta);
        if(strlen(odrediste)>20) naziv_odredista[19]='\0';
    }
    void PostaviKasnjenje(int kasnjenje);
    bool DaLiKasni() const;
    int DajTrajanjeLeta() const;
    std::pair<int, int> DajOcekivanoVrijemePolijetanja() const;
    std::pair<int, int> DajOcekivanoVrijemeSlijetanja() const;
    void Ispisi() const;
};
void Let::PostaviKasnjenje(int kasnjenje)
{
    Let::kasnjenje=kasnjenje;
}
bool Let::DaLiKasni()const
{
    if(kasnjenje>0) return true;
    return false;
}
int Let::DajTrajanjeLeta() const
{
    return trajanje;
}
std::pair<int, int> Let::DajOcekivanoVrijemePolijetanja() const
{
    std::pair<int, int> p;
    p.first=sati;
    p.second=minute+kasnjenje;
    if(p.second>59) {
        p.first+=(p.second/60);
        p.second%=60;
    }
    if(p.first>23) p.first%=24;
    return p;
}
std::pair<int, int> Let::DajOcekivanoVrijemeSlijetanja() const
{
    auto p=DajOcekivanoVrijemePolijetanja();
    p.second+=DajTrajanjeLeta();
    if(p.second>59) {
        p.first+=(p.second/60);
        p.second%=60;
    }
    if(p.first>23) p.first%=24;
    return p;
}
void Let::Ispisi()const
{
    if(!DaLiKasni()) {
        auto n=DajOcekivanoVrijemeSlijetanja();
        cout <<left << setw(10)<<setfill(' ') << oznaka_leta << setw(20)<<setfill(' ')<< naziv_odredista<<  "   "<< right<< setw(2)<< setfill('0')<<sati<<":"<< setw(2)<< setfill('0')<<
             minute<<"   "<<setw(2)<<n.first
             <<":"<<setw(2)<< n.second<<setfill(' ')<<setw(6)<< izlazna_kapija<<endl;
    } else {
        auto p=DajOcekivanoVrijemePolijetanja();
        p.second-=kasnjenje;
        if(p.second>59) {
            p.first+=(p.second/60);
            p.second%=60;
        }
        if(p.second<0) {
		p.first-=(std::abs(p.second/60)+1);
		p.second=60-std::abs(p.second)%60;
	}
	if(p.first<0) {
		p.first=24-std::abs(p.first)%24;
	}
        if(p.first>23) p.first%=24;
        cout <<left << setw(10) << oznaka_leta << setw(20)<< naziv_odredista << "   "<< right<< setw(2)<< setfill('0')<<DajOcekivanoVrijemePolijetanja().first<<":"<<setw(2)<<setfill('0')<< DajOcekivanoVrijemePolijetanja().second<<" (Planirano "<<
             setw(2)<< setfill('0')<<
             p.first <<":"<<setw(2)<< setfill('0')<<p.second<<", Kasni " << kasnjenje<< " min)"<<endl;
    }
}

class Letovi
{
    const int max_broj;
    int broj_letova;
    Let ** letovi;
public:
    explicit Letovi(int max_broj_letova):max_broj(max_broj_letova),broj_letova(0)
    {
        letovi=new Let*[max_broj] {};
    };


    Letovi(std::initializer_list<Let> lista_letova);
    ~Letovi()
    {
        for(int i=0; i<broj_letova; i++) delete letovi[i];
        delete[] letovi;
    }


    Letovi(const Letovi &pletovi);
    Letovi(Letovi &&l):max_broj(l.max_broj), broj_letova(l.broj_letova), letovi(l.letovi)
    {
        l.letovi=nullptr;
        l.broj_letova=0;
    }


    Letovi &operator =(const Letovi &l);
    Letovi &operator =(Letovi &&l);
    void RegistrirajLet(const char odrediste[], const char oznaka_leta[],
                        int kapija, int sat_polaska, int minute_polaska, int trajanje_leta);
    void RegistrirajLet(Let *l);
    int DajBrojLetova() const;
    int DajBrojLetovaKojiKasne() const;
    int DajProsjecnoTrajanjeLetova() const;
    Let &DajPrviLet() const;
    Let &DajPosljednjiLet() const;
    void IsprazniKolekciju();
    void Ispisi(int sati, int minute) const;
};
 Letovi::Letovi(std::initializer_list<Let> lista_letova):max_broj(lista_letova.size()), broj_letova(lista_letova.size())
    {
        letovi=new Let*[max_broj] {};
        auto it=lista_letova.begin();
        try {
            for(int i=0; i<broj_letova; i++)
                letovi[i]=new Let(*it++);
        } catch(...) {
            for(int i=0; i<broj_letova; i++) {
                delete letovi[i];
                letovi[i]=nullptr;
            }
        }
    }

 Letovi::Letovi(const Letovi &pletovi):broj_letova(pletovi.broj_letova), max_broj(pletovi.max_broj)
    {
        try {
            letovi=new Let*[max_broj] {};
            try {
                for(int i=0; i<broj_letova; i++) letovi[i]=new Let(*pletovi.letovi[i]); //pokusaj
            } catch(...) {
                for(int i=0; i<pletovi.broj_letova; i++) {
                    delete letovi[i];
                    letovi[i]=nullptr;
                }
                delete[] letovi;
            }
        } catch(...) {}
    }
Letovi &Letovi::operator =(const Letovi &l)
{
    //if(max_broj!=l.max_broj) throw logic_error("Nesaglasan maksimalan broj");
    if(l.broj_letova>broj_letova) {
        try {
            for(int i=broj_letova; i<l.broj_letova; i++)
                letovi[i]=new Let(*l.letovi[i]);
        } catch(...) {
            for(int i=broj_letova; i<l.broj_letova; i++) {
                delete letovi[i];
                letovi[i]=nullptr;
            }
            throw; 
        }
    } else {
        for(int i=l.broj_letova; i<broj_letova; i++) {
            delete letovi[i];
            letovi[i]=nullptr;
        }
    }
    broj_letova=l.broj_letova;
    for(int i=0; i<broj_letova; i++) *letovi[i]=*l.letovi[i];
    return *this;
}
Letovi &Letovi::operator = (Letovi &&l)
{
    //if(max_broj!=l.max_broj) throw logic_error("Nesaglasan maksimalan broj");
    swap(broj_letova, l.broj_letova);
    swap(letovi, l.letovi);
    return *this;
}
void Letovi::RegistrirajLet(const char odrediste[], const char oznaka_leta[], int kapija, int sat_polaska, int minute_polaska, int trajanje_leta)
{
    if(strlen(odrediste)>30) throw domain_error("Neispravan naziv");
    if(broj_letova>=max_broj) throw range_error("Dostignut maksimalni broj letova");
    letovi[broj_letova++]=new Let(odrediste,  oznaka_leta,  kapija,  sat_polaska,  minute_polaska,  trajanje_leta);
   // letovi[broj_letova++]->Ispisi();
}
void Letovi::RegistrirajLet(Let *l)
{
    if(strlen((*l).naziv_odredista)>30) throw domain_error("Neispravan naziv");
    if(broj_letova>=max_broj) throw range_error("Dostignut maksimalni broj letova");
    letovi[broj_letova++]=l;
    //letovi[broj_letova]->Ispisi();
   // *letovi[broj_letova++]=*l;
    
    
}
int Letovi::DajBrojLetova() const
{
    return broj_letova;
}

int Letovi::DajBrojLetovaKojiKasne() const
{
    int i=count_if(letovi, letovi+broj_letova, [](Let *l) {
        return l->DaLiKasni();
    });
    return i;
}
static int pom=0;
int Letovi::DajProsjecnoTrajanjeLetova() const
{
    pom=0;
    for(int i=0; i<broj_letova; i++)
        pom+=letovi[i]->DajTrajanjeLeta();
    pom=pom/broj_letova;
    return pom;
}
Let &Letovi::DajPrviLet() const
{
    if(broj_letova==0) throw domain_error("Nema registriranih letova");
    auto p= min_element(letovi, letovi+broj_letova, [](Let* l, Let* p) {
        if(l->DajOcekivanoVrijemePolijetanja().first<p->DajOcekivanoVrijemePolijetanja().first) return true;
        else if(l->DajOcekivanoVrijemePolijetanja().first>p->DajOcekivanoVrijemePolijetanja().first) return false;
        if(l->DajOcekivanoVrijemePolijetanja().second<p->DajOcekivanoVrijemePolijetanja().second) return true;
        return false;
    });
    return **p;
}
Let &Letovi::DajPosljednjiLet() const
{
    if(broj_letova==0) throw domain_error("Nema registriranih letova");
    auto p= max_element(letovi, letovi+broj_letova, [](Let* l, Let* p) {
        if(l->DajOcekivanoVrijemePolijetanja().first>p->DajOcekivanoVrijemePolijetanja().first) return true;
        else if(l->DajOcekivanoVrijemePolijetanja().first<p->DajOcekivanoVrijemePolijetanja().first) return false;
        if(l->DajOcekivanoVrijemePolijetanja().second>p->DajOcekivanoVrijemePolijetanja().second) return true;
        return false;
    });
    return **p;
}
void Letovi::IsprazniKolekciju()
{
    for(int i=0; i< broj_letova; i++){ delete letovi[i]; letovi[i]=nullptr; broj_letova=0;}
    //delete[] letovi;
} 
void Letovi::Ispisi(int sati, int minute) const
{
  //  auto j=letovi;
   // cout<<(letovi[0]->DajOcekivanoVrijemePolijetanja()).first;
    sort(letovi, letovi+broj_letova, [](Let *l, Let *p) {
        if((l->DajOcekivanoVrijemePolijetanja()).first<(p->DajOcekivanoVrijemePolijetanja()).first) return true;
        else if((l->DajOcekivanoVrijemePolijetanja()).first>(p->DajOcekivanoVrijemePolijetanja()).first) return false;
        if((l->DajOcekivanoVrijemePolijetanja()).second<(p->DajOcekivanoVrijemePolijetanja()).second) return true;
        return false;
    });
  
    
    int indeks(-1);
    for(int i=0; i<broj_letova; i++) {
        if(sati>(letovi[i])->sati) continue;
        if(sati<=(letovi[i])->sati) {
            if(minute>(letovi[i])->minute) continue;
            else {
                indeks=i;
                break;
            }
        }
    }
  //  cout <<indeks;
    if(indeks!=-1) {
        for(int i=indeks; i<broj_letova; i++)
            (letovi[i])->Ispisi();
    }
}




int main ()
{
   Let let("Odrediste", "Oznaka", 1, 1, 15, 400);
    int h, m;
    auto pomocna = let.DajOcekivanoVrijemePolijetanja();
    h = pomocna.first;
    m = pomocna.second;
    std::cout << h << ", " << m << ", ";
    pomocna = let.DajOcekivanoVrijemeSlijetanja();
    h = pomocna.first;
    m = pomocna.second;
    std::cout << h << ", " << m << std::endl;
  
    return 0;
}
