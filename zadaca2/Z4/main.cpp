//TP 2018/2019: Zadaća 2, Zadatak 4
#include <iostream>
#include <algorithm>
#include <stdexcept>
bool ManjaVeca( std::string manji,std::string veci)
{
    if(manji.size()<veci.size()) return true;
    else if(manji.size()>veci.size()) return false;
    for(int i=0; i<manji.size(); i++){
        if(std::toupper(manji.at(i))<std::toupper(veci.at(i))) return true;
        else if(std::toupper(manji.at(i))>std::toupper(veci.at(i))) return false;
    }
    return false;
}

std::string* SortirajRecenice(std::string* prvi, std::string* iza_kraja)
{
    if(iza_kraja<prvi) throw std::domain_error("Nije moguce sortiranje");
    std::sort(prvi, iza_kraja, ManjaVeca);
    return prvi;
}
int main ()
{
    try {
        int n;
        std::cout<<"Unesite broj recenica: ";
        std::cin>>n;
        std::string *recenice=new std::string [n] {};
        std::cin.ignore(1000, '\n');
        std::cout<<"Unesite recenice: "<<std::endl;

        for(int i=0; i<n; i++) {

            std::getline(std::cin, recenice[i]);

        }

        recenice=SortirajRecenice(recenice, recenice+n);
        std::cout<<"Recenice nakon sortiranja: "<<std::endl;
        for(int i=0; i<n; i++) {
            std::cout<<recenice[i]<<std::endl;
        }
        std::cout<<std::endl;
        std::string pom;
        std::cout<<"Unesite recenicu za pretragu: ";
        std::getline(std::cin, pom);
        auto pomocni=std::lower_bound(recenice, recenice+n, pom, ManjaVeca);
        if( pomocni != recenice+n && *pomocni==pom) std::cout<<"Recenica se nalazi na poziciji: "<<pomocni-recenice<<std::endl;
        else std::cout<<"Trazena recenica se ne nalazi u nizu!";
        delete[] recenice;
    } catch(...) {

        std::cout<<"Problemi s memorijom!";
    }
    return 0;
}
