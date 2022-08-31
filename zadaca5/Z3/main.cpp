//TP 2018/2019: Zadaća 5, Zadatak 3
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;
class Narudzba
{
    char obrok[30], ime[50];
protected:
    double cijena;
public:
    Narudzba(const char hrana[], double cijena_p, const char ime_h[]):cijena(cijena_p)
    {
        strcpy(obrok, hrana);
        strcpy(ime,ime_h);
    }
    virtual string DajNazivObroka() const
    {
        string naziv=obrok;

        return naziv;
    }
    virtual double DajCijenuObroka() const
    {
        return cijena;
    }
    virtual string DajNarucioca() const
    {
        string ime_n=ime;


        return ime;
    }
    virtual double DajUkupnuCijenu() const
    {
        return cijena;
    }
    virtual Narudzba* DajKopiju()const
    {
        return new Narudzba(obrok, cijena, ime);
    }
    virtual void Ispisi() const
    {
        cout<<"Obrok: "<<DajNazivObroka()<<endl;
        cout<<"Cijena: "<<DajCijenuObroka()<<" KM"<<endl;
        cout<<"Narucilac: "<<DajNarucioca()<<endl;
    }
};
class NarudzbaSaPicem:public Narudzba
{
    char sok[20];
    double cijena_s;
public:
    NarudzbaSaPicem(const char hrana[], double cijena, const char ime_h[], const char tecnost[], double cijena_soka):Narudzba(hrana, cijena, ime_h), cijena_s(cijena_soka)
    {
        strcpy(sok, tecnost);
    }
    double DajUkupnuCijenu() const
    {
        return DajCijenuObroka()+cijena_s;
    }
    string DajNazivPica() const
    {
        string pice(sok);

        return pice;
    }
    double DajCijenuPica() const
    {
        return cijena_s;
    }
    void Ispisi() const
    {
        cout<<"Obrok: "<<DajNazivObroka()<<endl;
        cout<<"Pice: "<<DajNazivPica()<<endl;
        cout<<"Cijena: "<<DajCijenuObroka()<<" KM"<<endl;
        cout<<"Cijena pica: "<<DajCijenuPica()<<" KM"<<endl;
        cout<<"Ukupna cijena: "<<DajUkupnuCijenu()<<" KM"<<endl;
        cout<<"Narucilac: "<<DajNarucioca()<<endl;
    }
    NarudzbaSaPicem* DajKopiju()const
    {
        return new NarudzbaSaPicem(DajNazivObroka().c_str(), DajCijenuObroka(), DajNarucioca().c_str(), sok, cijena_s);
    }
};
class Narudzbe
{
    std::vector<Narudzba*>zahtjevi;
public:
    Narudzbe()=default;
    ~Narudzbe()
    {
        for(int i=0; i<zahtjevi.size(); i++)
            delete zahtjevi.at(i);
        zahtjevi.resize(0);
    }
    Narudzbe(const Narudzbe& n)
    {
        try {
            zahtjevi.resize(n.zahtjevi.size());
            for(int i=0; i<n.zahtjevi.size(); i++)
                zahtjevi.at(i)=n.zahtjevi.at(i)->DajKopiju();
        } catch(...) {
            for(int i=0; i<n.zahtjevi.size(); i++) delete zahtjevi[i];
            throw;
        }
    }
    Narudzbe(Narudzbe &&n)
    {
        zahtjevi=n.zahtjevi;
        n.zahtjevi.resize(0);
    }
    Narudzbe& operator=(Narudzbe &&n)
    {
        for(int i=0; i<zahtjevi.size(); i++) delete zahtjevi[i];
        zahtjevi.resize(0);
        swap(zahtjevi, n.zahtjevi);
        return *this;
    }
    Narudzbe &operator=(const Narudzbe&n)
    {
        for(int i=0; i<zahtjevi.size(); i++) delete zahtjevi.at(i);
        zahtjevi.resize(n.zahtjevi.size());
        for(int i=0; i<n.zahtjevi.size(); i++)
            zahtjevi.at(i)=n.zahtjevi.at(i)->DajKopiju();
    }
    void NaruciObrok(const char hrana[], double cijena, const char ime_h[])
    {
        Narudzba n(hrana,cijena, ime_h);
        zahtjevi.push_back(n.DajKopiju());
    }
    void NaruciObrokSaPicem(const char hrana[], double cijena, const char ime_h[], const char pice[], double cijena_s)
    {
        NarudzbaSaPicem n(hrana, cijena, ime_h, pice, cijena_s);
        zahtjevi.push_back(n.DajKopiju());
    }
    void ObradiNarudzbu()
    {
        if(zahtjevi.size()<1) throw range_error("Nema vise narudzbi");
        zahtjevi.at(0)->Ispisi();
        delete zahtjevi[0];
        auto pom=zahtjevi.begin();
        pom++;
        copy(pom, zahtjevi.end(), zahtjevi.begin());
        zahtjevi.resize(zahtjevi.size()-1);
    }
    bool DaLiImaNarudzbi()const
    {
        if(zahtjevi.size()>0) return true;
        return false;
    }
    double operator[](string narucioc)const
    {
        double suma{};
        for(int i=0; i<zahtjevi.size(); i++) {
            if(zahtjevi.at(i)->DajNarucioca()==narucioc)
                suma+=zahtjevi.at(i)->DajUkupnuCijenu();
        }
       // cout<<suma<<endl;
        return suma;
    }
    void UcitajIzDatoteka(string prva, string druga)
    {
        ifstream narudzbe(prva.c_str());
        if(!narudzbe) throw logic_error("Trazena datoteka ne postoji");
        while(1) {
            string ime_narucioca, hrana, pice;
            getline(narudzbe, ime_narucioca);
            getline(narudzbe, hrana);
            getline(narudzbe, pice);
           // if(!narudzbe) throw logic_error("Problemi pri citanju");
            bool istina_za_hranu=false, istina_za_pice=false;
            double vlastita, tecnost;

            ifstream ulazni_tok(druga.c_str());
            if(!ulazni_tok) throw logic_error("Trazena datoteka ne postoji");
            while(1) {
                string sifra;

                double price{};
                
                getline(ulazni_tok, sifra);
                if(!ulazni_tok)throw logic_error("Problemi pri citanju");
            // cout<<   ulazni_tok.get();
                ulazni_tok>>price;
                
                if(!ulazni_tok)throw logic_error("Problemi pri citanju");
                 ulazni_tok.ignore(10000, '\n');
                if(sifra==hrana) {
                    istina_za_hranu=true;
                    vlastita=price;
                } else if(sifra==pice) {
                    istina_za_pice=true;
                    tecnost=price;
                }
  
                if(istina_za_hranu && istina_za_pice) {
                    break;
                    ulazni_tok.close();
                }
                if(ulazni_tok.eof()) break;
               
            }
            if(istina_za_hranu) {
                if(pice.size()>0) {
                    if(istina_za_pice) {
                        NarudzbaSaPicem n(hrana.c_str(), vlastita, ime_narucioca.c_str(), pice.c_str(), tecnost);
                        //cout<<pice<<" "<<tecnost<<endl;
                        zahtjevi.push_back(n.DajKopiju());
                    } else if(!istina_za_pice) throw logic_error("Nema odgovarajuce cijene");
                } else if(pice.size()==0) {
                    Narudzba n(hrana.c_str(), vlastita, ime_narucioca.c_str());
                    zahtjevi.push_back(n.DajKopiju());
                }
            } else {
                throw logic_error("Nema odgovarajuce cijene");
            }

            if(narudzbe.eof()) break;
            
            if(!narudzbe || narudzbe.bad())throw logic_error("Problemi pri citanju");
        }
    }

};


int main ()
{
    try{
    Narudzbe n;
   
    n.NaruciObrok("Grah", 3, "Enis Beslagic");
    n.NaruciObrokSaPicem("Sladoled", 2, "Halid Muslimovic", "mlijeko", 1);
    n.UcitajIzDatoteka("narudzbe.txt","cijene.txt");
    n.ObradiNarudzbu();
   // n.ObradiNarudzbu();
   cout<<n["Rambo Sulejmanovic"];
    }
    catch(logic_error e){
        cout<<e.what();
    }
    catch(range_error e){
        cout<<e.what();}
    return 0;
}
