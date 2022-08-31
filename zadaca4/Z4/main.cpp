#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include <memory>
#include <initializer_list>
#include <vector>
using namespace std;

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
    vector<shared_ptr<Let>>letovi;
public:
    Letovi()=default;
    explicit Letovi(std::initializer_list<Let> lista_letova);
    Letovi(const Letovi &pletovi);
    Letovi(Letovi &&l);
    Letovi &operator =(const Letovi &l);
    Letovi &operator =(Letovi &&l);
    void RegistrirajLet(const char odrediste[], const char oznaka_leta[],
                        int kapija, int sat_polaska, int minute_polaska, int trajanje_leta);
    void RegistrirajLet(shared_ptr<Let>l);
    int DajBrojLetova() const;
    int DajBrojLetovaKojiKasne() const;
    int DajProsjecnoTrajanjeLetova() const;
    Let &DajPrviLet() const;
    Let &DajPosljednjiLet() const;
    void IsprazniKolekciju();
    void Ispisi(int sati, int minute) const;
};
 Letovi::Letovi(std::initializer_list<Let> lista_letova)
    {
        letovi.resize(lista_letova.size());
        auto it(lista_letova.begin());
        
            for(int i=0; i<lista_letova.size(); i++)
                letovi[i]=make_shared<Let>(*it++);
        
    }
Letovi::Letovi(Letovi &&l)=default;
 Letovi::Letovi(const Letovi &pletovi){
     letovi.resize(pletovi.letovi.size());
     for(int i=0; i<pletovi.letovi.size(); i++)
         letovi[i]=make_shared<Let>(*pletovi.letovi[i]);
     }
Letovi &Letovi::operator =(const Letovi &l)
{
    letovi=l.letovi;
}
Letovi &Letovi::operator =(Letovi &&l)=default;

void Letovi::RegistrirajLet(const char odrediste[], const char oznaka_leta[], int kapija, int sat_polaska, int minute_polaska, int trajanje_leta)
{
    if(strlen(odrediste)>30) throw domain_error("Neispravan naziv");
    
    letovi.push_back(make_shared<Let>(Let(odrediste,  oznaka_leta,  kapija,  sat_polaska,  minute_polaska,  trajanje_leta)));
}
void Letovi::RegistrirajLet(shared_ptr<Let> l)
{
    if(strlen(l->naziv_odredista)>30) throw domain_error("Neispravan naziv");
    
    letovi.push_back(l);
   // l=nullptr;

    
}
int Letovi::DajBrojLetova() const
{
    return letovi.size();
}

int Letovi::DajBrojLetovaKojiKasne() const
{
    int i=count_if(letovi.begin(), letovi.end(), [](shared_ptr<Let> l) {
        return l->DaLiKasni();
    });
    return i;
}
static int pom=0;
int Letovi::DajProsjecnoTrajanjeLetova() const
{
    pom=0;
    for(int i=0; i<letovi.size(); i++)
        pom+=letovi[i]->DajTrajanjeLeta();
    pom=pom/letovi.size();
    return pom;
}
Let &Letovi::DajPrviLet() const
{
    if(letovi.size()==0) throw domain_error("Nema registriranih letova");
    auto p= min_element(letovi.begin(), letovi.end(), [](shared_ptr<Let> l, shared_ptr<Let> p) {
        if(l->DajOcekivanoVrijemePolijetanja().first<p->DajOcekivanoVrijemePolijetanja().first) return true;
        else if(l->DajOcekivanoVrijemePolijetanja().first>p->DajOcekivanoVrijemePolijetanja().first) return false;
        if(l->DajOcekivanoVrijemePolijetanja().second<p->DajOcekivanoVrijemePolijetanja().second) return true;
        return false;
    });
    return **p;
}
Let &Letovi::DajPosljednjiLet() const
{
    if(letovi.size()==0) throw domain_error("Nema registriranih letova");
    auto p= max_element(letovi.begin(), letovi.end(), [](shared_ptr<Let> l, shared_ptr<Let> p) {
        if(l->DajOcekivanoVrijemePolijetanja().first>p->DajOcekivanoVrijemePolijetanja().first) return true;
        else if(l->DajOcekivanoVrijemePolijetanja().first<p->DajOcekivanoVrijemePolijetanja().first) return false;
        if(l->DajOcekivanoVrijemePolijetanja().second>p->DajOcekivanoVrijemePolijetanja().second) return true;
        return false;
    });
    return **p;
}
void Letovi::IsprazniKolekciju()
{
    letovi.resize(0);
    
} 
void Letovi::Ispisi(int sati, int minute) const
{
  // shared_ptr<Let> l=letovi.begin(); 
//cout<<(*l)->DajOcekivanoVrijemePolijetanja().first<<endl;
   // cout<<letovi[0]->DajOcekivanoVrijemePolijetanja().first<<endl;
  /* sort(letovi.begin(), letovi.end(), [](const shared_ptr<Let> l, const shared_ptr<Let> p) {
    if(*(l->DajOcekivanoVrijemePolijetanja()).first<*(p->DajOcekivanoVrijemePolijetanja()).first) return true;
        else if(*(l->DajOcekivanoVrijemePolijetanja()).first>*(p->DajOcekivanoVrijemePolijetanja()).first) return false;
        if(*(l->DajOcekivanoVrijemePolijetanja()).second<*(p->DajOcekivanoVrijemePolijetanja()).second) return true;
        return false;
    });*/
   
 /* sort(timovi.begin(), timovi.end(), [](shared_ptr<Tim> p_tim1, shared_ptr<Tim> p_tim2) {
		if(p_tim1->DajBrojPoena()!=p_tim2->DajBrojPoena())
			return p_tim1->DajBrojPoena()>p_tim2->DajBrojPoena();
			else if(p_tim1->DajBrojPoena()==p_tim2->DajBrojPoena() && p_tim1->DajGolRazliku()!=p_tim2->DajGolRazliku())
				return p_tim1->DajGolRazliku()>p_tim2->DajGolRazliku();
				else if(p_tim1->DajBrojPoena()==p_tim2->DajBrojPoena() && p_tim1->DajGolRazliku()==p_tim2->DajGolRazliku())
					return strcmp(p_tim1->DajImeTima(), p_tim2->DajImeTima())<0;
				});*/
    
    int indeks(-1);
    for(int i=0; i<letovi.size(); i++) {
        if(sati>(letovi[i])->sati) continue;
        if(sati<=(letovi[i])->sati) {
            if(minute>(letovi[i])->minute) continue;
            else {
                indeks=i;
                break;
            }
        }
    }
   // cout <<indeks;
    if(indeks!=-1) {
        for(int i=indeks; i<letovi.size(); i++)
            (letovi[i])->Ispisi();
    }
}




int main ()
{
   
    Letovi letovi;
    letovi.RegistrirajLet("A", "B", 1, 0, 0, 100);
    letovi.IsprazniKolekciju();

    letovi.RegistrirajLet("Odrediste2", "Oznaka2", 20, 12, 12, 250);
    std::shared_ptr<Let> let(std::make_shared<Let>("Odrediste", "Oznaka", 10, 10, 10, 300));
    let->PostaviKasnjenje(100);
    letovi.RegistrirajLet(let);
    letovi.RegistrirajLet("A", "B", 1, 0, 55, 100);
    letovi.Ispisi(5,5);
    return 0;
}
