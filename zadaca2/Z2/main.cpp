//TP 2018/2019: Zadaća 2, Zadatak 2
#include <iostream>
#include <new>
#include <algorithm>
#include <type_traits>
#include <vector>
#include <cmath>
template <typename tip>
bool potpunK(tip broj)
{
    //broj=abs(broj);
    int pom=sqrt(broj);
    if(pom*pom==broj) return true;
    return false;
}
template <typename tip>
bool DjeljivKvadratom(tip broj)
{

    broj=abs(broj);

    bool istina=false;
    for(int i=2; i<=broj/2; i++) {
        if(broj%i==0 && potpunK(i)) {
            istina=true;
            break;
        }
    }
    if(potpunK(broj) && broj!=1) return true;
    return istina;
}
template <typename tip>
bool Prost(tip broj)
{
    broj=abs(broj);
    for(int i=2; i<broj/2; i++)
        if(broj%i==0) return false;
    return true;
}
template <typename tip>
int SumaProstihFaktora(tip broj)
{

    broj=abs(broj);
    int brojac{};
    int prosloi=-1;
    for(int i=2; i<=broj; i++) {
        if(broj%i==0 && Prost(i)) {
            if(prosloi!=i)
                brojac+=i;
            broj/=i;
            prosloi=i;
            i--;

        }
    }
    return brojac;
}
template <typename tip>
bool Jednaki(tip a, tip b)
{
    if(SumaProstihFaktora(a)==SumaProstihFaktora(b)) return true;
    return false;
}
template <typename tip>
int ProizvodCifara(tip a)
{
    int proizvod=1;
    while(a!=0) {
        proizvod*=a%10;
        a/=10;
    }
    return proizvod;
}

template <typename Tip>
auto Izdvajanje(Tip p1, Tip &p2, int& broj_slobodnih)->typename std::remove_reference<decltype(*p1)>::type *
{

    auto pom=p1;
    int brojac{};
    while(pom!=p2) {
        auto ponavljanje=std::find(p1, p2, *pom);   //funkcija find ce vratiti pokazivac na prvi element u bloku koji je jednak trecem parametru
        if(!DjeljivKvadratom(*pom) && ponavljanje==pom) brojac++; //pa ako je ovaj npr drugi nece imati istu adresu
        pom++;
    }
    broj_slobodnih=brojac;
    //std::cout<<"Jesam li ja kriv";
    
    typename std::remove_reference<decltype(*p1)>::type * niz=nullptr;
    try {
        niz=new typename std::remove_reference<decltype(*p1)>::type [brojac] {};
        pom=p1;
        auto p11=p1;
        auto za_niz=niz;
        while(pom!=p2) {
            auto ponavljanje=std::find(p11,p2,*pom);
            if(!DjeljivKvadratom(*pom) && ponavljanje==pom) *za_niz++=*pom;
            pom++;
        }
      
        auto jos_pokazivaca=p1;
        pom=p1;
        pom++;
        
        while(jos_pokazivaca!=p2) {
            
            bool istina=false;
            while(pom<p2) {
                if(Jednaki(*jos_pokazivaca, *pom)) {
                    p2=std::remove(jos_pokazivaca+1, p2, *pom);
                    istina=true;
                    pom--;
                }
                pom++;
            }
        
            if(istina) {
                p2=std::remove(p1, p2, *jos_pokazivaca);
            
                jos_pokazivaca--;
               
            }
           jos_pokazivaca++;
            pom=jos_pokazivaca;

            pom++;
            
            
        }
        if(brojac==0) return nullptr;

        return niz;
    } catch(std::range_error e) {
        delete[] niz;
        throw std::range_error("Nedovoljno memorije!");
    }
}



int main ()
{
    try {
        std::vector<int> veki;
        int x;
        std::cout << "Unesite brojeve: " ;
        std::cin >> x;
        while( x != -1 ) {
            veki.push_back(x);
            std::cin >> x;
        }
        std::cout << "Izdvojeni brojevi: " ;
        int broj=0;
        auto nesto=veki.end();
        auto ccc=veki.begin();
        auto niz= Izdvajanje(ccc, nesto, broj);
        auto pom=niz;
        if(niz!=nullptr) {
            while(niz != pom+broj-1)
                std::cout << *niz++ << ", ";
            std::cout << *niz;
        }
        std::cout<<std::endl;
        std::cout << "Modificirani kontejner (prije sortiranja): ";
        auto pom1=veki.begin();
        if(pom1!=nesto) {
            while(pom1<nesto-1)
                std::cout << *pom1++ << ", ";
            std::cout << *pom1 ;
        }
        std::cout << std::endl;
        pom1=veki.begin();
        std::sort(pom1, nesto, [](int a, int b) {
            if(ProizvodCifara(a)==ProizvodCifara(b)) return a<b;
            return (ProizvodCifara(a)<ProizvodCifara(b));
        });
        std::cout << "Modificirani kontejner (nakon sortiranja): ";
        if(pom1!=nesto) {
            while(pom1<nesto-1) {
                std::cout<<*pom1++<<", ";
            }
            std::cout<<*pom1;
        }

        delete[] pom;
    } catch(std::range_error e) {
        std::cout << "Izuzetak: " << e.what() << "!" << std::endl;
    }
    return 0;
}
