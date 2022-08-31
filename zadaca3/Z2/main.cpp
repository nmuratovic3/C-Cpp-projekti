//TP 2018/2019: Zadaća 3, Zadatak 2
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

bool NalaziSe(std::string s, std::string b)
{
    if(s.size()!=b.size()) return false;
    for(auto i=0; i<s.size(); i++) {
        if(s.at(i)==b.at(i)) continue;
        return false;
    }
    return true;
}
typedef std::map<std::string, std::vector<std::string>> Knjiga;
using namespace std;
map<string, set<tuple<string, int, int>>>KreirajIndeksPojmova(Knjiga book)
{
    map<string, set<tuple<string, int, int>>> mapa;
    for(auto it=book.begin(); it!=book.end(); it++) {
        for(int i=0; i<it->second.size(); i++) {
            auto pom=it->second.at(i).begin();
            tuple<string, int, int> NekiSet;
            while( pom!=it->second.at(i).end()) {
                while(pom!=it->second.at(i).end() && !(*pom>='A' && *pom<='Z') && !(*pom>='a' && *pom<='z') && !(*pom>='0' && *pom<='9') ) pom++;
                auto pamti=pom;
                string TrazenaRijec;
                while(pom!=it->second.at(i).end() && ((*pom>='A' && *pom<='Z') || (*pom>='a' && *pom<='z') || (*pom>='0' && *pom<='9'))) {
                    if(*pom>='A' && *pom<='Z') *pom+=32;
                    TrazenaRijec.push_back(*pom);
                    pom++;
                }
                string ime=it->first;
                mapa[TrazenaRijec].insert(make_tuple(ime, i+1, pamti-it->second.at(i).begin()));
            }

        }
    }
    return mapa;
}
set<tuple<string, int, int>> PretraziIndeksPojmova(string rijec, map<string, set<tuple<string, int, int>>> moja_mapa)
{
    auto it=moja_mapa.find(rijec);
    if(it==moja_mapa.end()) throw logic_error("Unesena rijec nije nadjena!\n");
    else {
        return it->second;
    }
}
void IspisiIndeksPojmova(map<string, set<tuple<string, int, int>>> mapa)
{
    auto it=mapa.begin();
    while (it!=mapa.end()) {
        std::cout << it->first << ": " ;
        auto pok=it->second.begin();
        while (pok!=it->second.end()) {
            std::cout <<get<0>(*pok) << "/" << get<1>(*pok) << "/" << get<2>(*pok) ;
            pok++;
            if(pok!=it->second.end()) std::cout<<", ";
        }
        cout << endl;
        it++;
    }
}

int main ()
{
    Knjiga book;

    do {
        cout << "Unesite naziv poglavlja: ";
        string pog;
        getline(cin, pog);
        if(pog==".") break;
        int i=1;
        std::vector<string>teka;
        string sadrzaj;
        do {
            cout<<"Unesite sadrzaj stranice " << i++ <<": ";
            getline(cin, sadrzaj);
            if(sadrzaj==".") break;
            teka.push_back(sadrzaj);
        } while(1);
        book.insert({pog, teka});
    } while(1);
    auto kreacija=KreirajIndeksPojmova(book);
    cout<<"\nKreirani indeks pojmova: \n";
    IspisiIndeksPojmova(kreacija);
    
    do {
        cout << "Unesite rijec: ";
        string trazena_rijec;
        getline(cin, trazena_rijec);
        if(trazena_rijec==".")  break;
        try{
        auto word=PretraziIndeksPojmova(trazena_rijec, kreacija);
        auto it=word.begin();
        while(it!=word.end()){
           cout << get<0>(*it) << "/" << get<1>(*it) << "/" <<get<2>(*it)<<" ";
           it++;
           
        }
        cout<<endl;
        }catch(logic_error e){
            cout<<e.what();
        }
    }while(1);

        return 0;
    }
