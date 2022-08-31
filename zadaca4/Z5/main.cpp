//TP 2018/2019: Zadaća 4, Zadatak 5
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <map>
using namespace std;
struct Korisnik {
    string ime, prezime, adresa, telefon;
};
class Knjiga
{
    string  naslov,ime_pisca, zanr;
    int godina_izdavanja;
    Korisnik* zaduzenik;
public:
friend class Biblioteka;
    Knjiga(string nasl, string ime_pis, string zan, int god):naslov(nasl),ime_pisca(ime_pis), zanr(zan), godina_izdavanja(god)
    {
        zaduzenik=nullptr;
    }
    string DajNaslov()const
    {
        return naslov;
    }
    string DajAutora()const
    {
        return ime_pisca;
    }
    string DajZanr()const
    {
        return zanr;
    }
    int DajGodinuIzdavanja()const
    {
        return godina_izdavanja;
    }
    Korisnik* DajKodKogaJe() const
    {
        return zaduzenik;
    }
    void ZaduziKnjigu(Korisnik& citac)
    {
        zaduzenik=&citac;
    } void RazduziKnjigu()
    {
        zaduzenik=nullptr;
    }
    bool DaLiJeZaduzena()
    {
        if(zaduzenik) return true;
        return false;
    }
};

class Biblioteka
{
    map<int, Korisnik*> korisnik;
    map<int, Knjiga*> knjiga;
public:
    Biblioteka()=default;
    Biblioteka(const Biblioteka &bibl)
    {
        try {
            for(auto it=bibl.korisnik.begin(); it!=bibl.korisnik.end(); it++)
                korisnik[it->first]=new Korisnik(*it->second) ;
            try {

                for(auto it=bibl.knjiga.begin(); it!=bibl.knjiga.end(); it++)
                    knjiga[it->first]=new Knjiga(*it->second) ;
            } catch(...) {
                for(auto it=knjiga.begin(); it!=knjiga.end(); it++){
                    delete it->second;
                it->second=nullptr;}
                // throw;
            }
        } catch(...) {
            for(auto it=korisnik.begin(); it!=korisnik.end(); it++) {
                delete it->second;
                it->second=nullptr;
            }
        }
    }
    ~Biblioteka(){
        for(auto it=knjiga.begin(); it!=knjiga.end(); it++){
                    delete it->second;
                it->second=nullptr;}
        for(auto it=korisnik.begin(); it!=korisnik.end(); it++) {
                delete it->second;
                it->second=nullptr;
            }
    }        
        
    Biblioteka(Biblioteka && b):korisnik(b.korisnik), knjiga(b.knjiga)
    {
        for(auto it=b.korisnik.begin(); it!=b.korisnik.end(); it++)
            it->second=nullptr;
        for(auto it=b.knjiga.begin(); it!=b.knjiga.end(); it++)
            it->second=nullptr;
    }
    Biblioteka &operator=(const Biblioteka& b)
    {
        //if(b.korisnik.size()>korisnik.size()){
        /* try{
             for(auto it=b.korisnik.begin(); it<b.korisnik.end(); it++){
                 if(korisnik.find(it->first)==korisnik.end()){
                     korisnik[it->first]=new Korisnik*(it->second);
                 }
                 catch(...){*/
        for(auto it=korisnik.begin(); it!=korisnik.end(); it++) {
            delete it->second;
            it->second=nullptr;
            korisnik.erase(it);
        }
        for(auto it=knjiga.begin(); it!=knjiga.end(); it++) {
            delete it->second;
            it->second=nullptr;
            knjiga.erase(it);
        }
        try {
            for(auto it=b.korisnik.begin(); it!=b.korisnik.end(); it++)
                korisnik[it->first]=new Korisnik(*it->second) ;
            try {

                for(auto it=b.knjiga.begin(); it!=b.knjiga.end(); it++)
                    knjiga[it->first]=new Knjiga(*it->second) ;
            } catch(...) {
                for(auto it=knjiga.begin(); it!=knjiga.end(); it++){
                    delete it->second;
                it->second=nullptr;}
                // throw;
            }
        } catch(...) {
            for(auto it=korisnik.begin(); it!=korisnik.end(); it++) {
                delete it->second;
                it->second=nullptr;
            }
        }
        return *this;
    }
    Biblioteka &operator =(Biblioteka && b)
    {
        swap(knjiga, b.knjiga);
        swap(korisnik, b.korisnik);
        return *this;
    }
    void RegistrirajNovogKorisnika(int karta, string ime, string prezime, string adresa, string telefon)
    {
        if(korisnik.find(karta)!=korisnik.end()) throw logic_error("Korisnik vec postoji");
        else {
            Korisnik k;
            k.ime=ime;
            k.prezime=prezime;
            k.adresa=adresa;
            k.telefon=telefon;
            korisnik[karta]=new Korisnik(k);
        }
    }
    void RegistrirajNovuKnjigu(int broj, string naslov, string pisac, string tip, int god){
        if(knjiga.find(broj)!=knjiga.end()) throw logic_error("Knjiga vec postoji");
        else knjiga[broj]=new Knjiga(Knjiga(naslov, pisac, tip, god));
    }
    Korisnik& NadjiKorisnika(int broj){
        if(korisnik.find(broj)==korisnik.end()) throw logic_error("Korisnik nije nadjen");
        return *korisnik[broj];
    }
    Knjiga& NadjiKnjigu(int broj){
        if(knjiga.find(broj)==knjiga.end()) throw logic_error("Knjiga nije nadjena");
        return *knjiga[broj];
    }
    void IzlistajKorisnike()const{
        for(auto it=korisnik.begin(); it!=korisnik.end(); it++){
            cout<<"Clanski broj: "<<it->first<<endl;
            cout<<"Ime i prezime: "<< (*it->second).ime <<" "<< (*it->second).prezime<<endl;
            cout<<"Adresa: "<< (*it->second).adresa<<endl;
            cout<<"Broj telefona: "<< (*it->second).telefon<<"\n"<<endl;
        }
    }
    void IzlistajKnjige()const{
        for(auto it=knjiga.begin(); it!=knjiga.end(); it++){
            cout<<"Evidencijski broj: "<< it->first<<endl;
            cout<<"Naslov: "<<(*it->second).DajNaslov()<<endl;
            cout<<"Pisac: "<<(*it->second).DajAutora()<<endl;
            cout<<"Zanr: "<<(*it->second).DajZanr()<<endl;
            cout<<"Godina izdavanja: "<<(*it->second).DajGodinuIzdavanja()<<endl;
            if((*it->second).DaLiJeZaduzena()) 
                cout<<"Zaduzena kod korisnika: "<<(*(*it->second).DajKodKogaJe()).ime << " "<<(*(*it->second).DajKodKogaJe()).prezime<<endl;
            cout<<endl;
        }
    }
    void ZaduziKnjigu(int broj_knjige, int korisnicki_broj){
        if(knjiga.find(broj_knjige)==knjiga.end()) throw logic_error("Knjiga nije nadjena");
         if(korisnik.find(korisnicki_broj)==korisnik.end()) throw logic_error("Korisnik nije nadjen");
         if((*knjiga[broj_knjige]).DaLiJeZaduzena()) throw logic_error ("Knjiga vec zaduzena");
         (*knjiga[broj_knjige]).ZaduziKnjigu(*korisnik[korisnicki_broj]);
    }
    void RazduziKnjigu(int broj_knjige){
        if(knjiga.find(broj_knjige)==knjiga.end()) throw logic_error("Knjiga nije nadjena");
        if(!(*knjiga[broj_knjige]).DaLiJeZaduzena()) throw logic_error ("Knjiga nije zaduzena");
    }
    void PrikaziZaduzenja(int broj){
        auto pok=korisnik.find(broj);
        if(pok==korisnik.end())throw logic_error("Korisnik nije nadjen");
        auto it=knjiga.begin();
         for(; it!=knjiga.end(); it++)
            if((*(it->second)).DajKodKogaJe()==korisnik[broj]){
            cout<<"Evidencijski broj: "<< it->first<<endl;
            cout<<"Naslov: "<<(*(it->second)).DajNaslov()<<endl;
            cout<<"Pisac: "<<(*(it->second)).DajAutora()<<endl;
            cout<<"Zanr: "<<(*(it->second)).DajZanr()<<endl;
            cout<<"Godina izdavanja: "<<(*(it->second)).DajGodinuIzdavanja()<<endl;
            break;
            }
        if(it==knjiga.end()) cout<<("Nema zaduzenja za datog korisnika");
    }
};
                
    int main ()
    {
        Biblioteka b;
        int n;
        cout<<"Zelite li dodati knjigu(1) ili novog korisnika(2)";
        cin>>n;
        int brojac1=0,brojac2=0;
        int p=8;
        if(n==1){
            while (p) {
            cout<<"Unesite podatke za knjigu: ";
            string  naslov,ime_pisca, zanr;
            int godina_izdavanja; 
            b.RegistrirajNovuKnjigu(brojac1, naslov, ime_pisca, zanr, godina_izdavanja);
            brojac1++;
            cout<<"Ako ste zavrsili unos knjiga unesite 0, a ako niste 1!";
            cin>>p;
            if(p==0) break;
            }
            b.IzlistajKnjige();
        }
        if(n==2){
            while (p) {
            cout<<"Unesite podatke za korisnika: ";
            string  ime,prezime,adresa,telefon; 
            b.RegistrirajNovogKorisnika(brojac2,ime,prezime,adresa,telefon);
            brojac2++;
            cout<<"Ako ste zavrsili unos knjiga unesite 0, a ako niste 1!";
            cin>>p;
            if(p==0) break;
            }
            b.IzlistajKorisnike();
        }
        return 0;
    }
