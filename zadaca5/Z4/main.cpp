//TP 2018/2019: Zadaća 5, Zadatak 4
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <initializer_list>
using namespace std;
class ApstraktnoVozilo{
    int tezina;
    public:
    ApstraktnoVozilo(int tezina):tezina(tezina){}
    virtual ~ApstraktnoVozilo() {}
    int DajTezinu() const{
        return tezina;
    }
    virtual int DajUkupnuTezinu() const=0;
    virtual ApstraktnoVozilo* DajKopiju() const=0;
    virtual void IspisiPodatke() const=0;
};
class Automobil:public ApstraktnoVozilo{
    std::vector<int>tezine_putnika;
    public:
    Automobil(int tezina, vector<int> tezine_putnika): ApstraktnoVozilo(tezina), tezine_putnika(tezine_putnika){
    }
    Automobil(int tezina, initializer_list<int> lista): ApstraktnoVozilo(tezina){
        auto it=lista.begin();
        while(it!=lista.end()) tezine_putnika.push_back(*it++);
    }
    int DajUkupnuTezinu() const{
        int ukupna{};
        for(int i=0; i<tezine_putnika.size(); i++) ukupna += tezine_putnika.at(i);
        ukupna+=DajTezinu();
        return ukupna;
    }
    ApstraktnoVozilo* DajKopiju() const{
        auto pom=new Automobil(DajTezinu(), tezine_putnika);
        return pom;
    }
    void IspisiPodatke() const{
        cout<<"Vrsta vozila: Automobil\n";
        cout<<"Vlastita tezina: "<<DajTezinu()<<endl;
        cout<<"Tezine putnika: "; for(int i=0; i<tezine_putnika.size()-1; i++) cout<<tezine_putnika.at(i)<<" kg, ";
        cout<<tezine_putnika.at(tezine_putnika.size()-1)<<endl;
        cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<endl;
    }
};
class Kamion:public ApstraktnoVozilo{
    int tezina_tereta;
    public:
    Kamion(int tezina, int tezina_tereta):ApstraktnoVozilo(tezina), tezina_tereta(tezina_tereta){}
    int DajUkupnuTezinu() const{
        return tezina_tereta+DajTezinu();
    }
    ApstraktnoVozilo* DajKopiju() const{
        return new Kamion(DajTezinu(), tezina_tereta);
    }
    void IspisiPodatke() const{
        cout<<"Vrsta vozila: Kamion"<<endl;
        cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<endl;
        cout<<"Tezina tereta: "<<tezina_tereta<<" kg"<<endl;
        cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<endl;
    }
};
class Autobus:public ApstraktnoVozilo{
    int broj_n, prosjek;
    public:
    Autobus(int tezina, int broj_n, int prosjek):ApstraktnoVozilo(tezina), broj_n(broj_n), prosjek(prosjek){}
    int DajUkupnuTezinu() const{
        return DajTezinu()+broj_n*prosjek;
    }
    ApstraktnoVozilo* DajKopiju() const{
        return new Autobus(DajTezinu(), broj_n, prosjek);
    }
    void IspisiPodatke() const{
        cout<<"Vrsta vozila: Autobus"<<endl;
        cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<endl;
        cout<<"Broj putnika: "<<broj_n<<endl;
        cout<<"Prosjecna tezina putnika: "<<prosjek<<" kg"<<endl;
        cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<endl;
    }
};
class Vozilo{
    ApstraktnoVozilo* vozilo;
    public:
    Vozilo():vozilo(nullptr){}
    ~Vozilo(){ delete vozilo;}
    Vozilo(const ApstraktnoVozilo &v):vozilo(v.DajKopiju()){}
    Vozilo(const Vozilo &v){
        if(!v.vozilo) vozilo=nullptr;
        else vozilo=v.vozilo->DajKopiju();
    }
    Vozilo(Vozilo &&v){
        vozilo=v.vozilo;
        v.vozilo=nullptr;
    }
    Vozilo &operator=(const Vozilo &v){
        ApstraktnoVozilo *pom=nullptr;
        if(v.vozilo!=nullptr) pom=v.vozilo->DajKopiju();
        delete vozilo;
        vozilo=pom;
        return *this;
    }
    Vozilo &operator =(Vozilo &&v){
        swap(vozilo, v.vozilo);
        return *this;
    }
    void IspisiPodatke() const{
        vozilo->IspisiPodatke();
    }
    ApstraktnoVozilo* DajKopiju(){
        return vozilo->DajKopiju();
    }
    int DajUkupnuTezinu()const{
        return vozilo->DajUkupnuTezinu();
    }
    int DajTezinu()const{
        return vozilo->DajTezinu();
    }
};
int main ()
{
    std::vector<Vozilo>v;
    try{
    ifstream ulazna("VOZILA.TXT");
    if(!ulazna) throw "Datoteka ne postoji";
    while(1){
        char slovo=ulazna.get();
        if(slovo=='A'){
            int tezina_auta, broj_n, x;
            std::vector<int>putnici;
            ulazna>>tezina_auta>>broj_n;
           // ulazna.ignore(1000, '\n');
            for(int i=0; i<broj_n; i++){
                ulazna>>x;
                putnici.push_back(x);
                }
                ulazna.ignore(1000, '\n');
              v.resize(v.size()+1);
            //  cout<<tezina_auta<<" "<<broj_n;
                v[v.size()-1]=Vozilo(Automobil(tezina_auta, putnici));
                }
        else if(slovo=='K'){
            int kamion, teret;
            ulazna>>kamion>>teret;
            ulazna.ignore(1000, '\n');
            v.resize(v.size()+1);
          //  cout<<kamion<<" "<<teret;
                v[v.size()-1]=Vozilo(Kamion(kamion, teret));
          //  v.push_back(new Kamion(kamion, teret));
        }
        else if(slovo=='B'){
            int broj_p, prosjek, tezina;
            ulazna>>tezina>>broj_p>>prosjek;
            ulazna.ignore(1000, '\n');
            v.resize(v.size()+1);
                v[v.size()-1]=Vozilo(Autobus(tezina, broj_p, prosjek));
          //  v.push_back(new Autobus(tezina, broj_p, prosjek));
        }
        else if(!ulazna.eof()) throw logic_error("Datoteka sadrzi besmislene podatke");
        if(ulazna.eof()) break;
        else if(ulazna.bad()) throw logic_error("Datoteka sadrzi besmislene podatke");
        if(!ulazna) throw logic_error("Problemi pri citanju datoteke");
    }
    sort(v.begin(), v.end(), [](Vozilo a, Vozilo b){ return a.DajUkupnuTezinu()<b.DajUkupnuTezinu();});
  for(int i=0; i<v.size(); i++) cout<<v.at(i).DajUkupnuTezinu()<<endl;
    }catch(logic_error e){
        cout<<"IZUZETAK: "<<e.what();
    }
    catch(...){
      
    }
    
            
            
    
	return 0;
}




















