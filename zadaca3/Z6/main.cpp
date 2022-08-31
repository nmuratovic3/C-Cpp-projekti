//TP 2018/2019: Zadaća 3, Zadatak 6
#include <iostream>
#include <new>
#include <set>
#include <memory>

struct Clan{
    int redni_broj;
    std::shared_ptr<Clan> sljedeci;
};
using namespace std;
int Poglavica(int n, int m, bool istina=false){
    if(n<=0 || m<=0) return 0;
    if(n==1) return 1;
    
    shared_ptr<Clan>pocetak=nullptr; shared_ptr<Clan>prethodni;
    int i=1;
    for(;;){
        std::shared_ptr<Clan> novi(new Clan{i, nullptr});
        if(!pocetak)pocetak=novi;
        else prethodni->sljedeci=novi;
        prethodni=novi;
        if(i==n) break;
        i++;
    }
    prethodni->sljedeci=pocetak;
   prethodni=nullptr;
    auto p=pocetak;
   // auto lol=pocetak;
    int redni{};
    shared_ptr<Clan> next;
    while (i>=1) {
        for(int brojac=1; brojac<m; p=p->sljedeci){
            if(brojac==m-2) pocetak=p->sljedeci;
            brojac++;
        }
        if(istina) std::cout<<p->redni_broj<<" ";
        next=p->sljedeci;
        if(i==1){ redni=next->redni_broj;
        next->sljedeci=nullptr;
        pocetak=nullptr;
        p=nullptr;
        }
        if(i!=1){
        pocetak->sljedeci=next;
        p=next;}
        i--;
    }
    return redni;

        
    }
   int SigurnoMjesto (int m, int n1, int n2)
{
    

    std::set<int>nesigurni;
    for(int i=n1; i<=n2; i++){
        nesigurni.insert(Poglavica(i, m));
       
    }
    if(nesigurni.size()==m) return 0;
    auto pom=nesigurni.begin();
   // auto trl=nesigurni.begin();
    //return *trl;
    for(int i=1; i<=m; i++) {
        if(*pom!=i) return i;
        pom++;
    }

    
    return 0;
}


int main ()
{
    cout<<"Unesi broj punoljetnih clanova (N): ";
    int n,m;
    cin>>n;
    cout<<"Unesi korak razbrajanja (M): ";
    cin>>m;
    int n1,n2;
    cout<<"Unesi raspon (N1-N2): ";
    cin>>n1>>n2;
    cout<<"Redni broj osobe koja postaje poglavica: "<<Poglavica(n,m)<<" ";
    int broj=SigurnoMjesto(m,n1,n2);
    if(broj==0) cout << "Sigurno mjesto ne postoji!";
    else cout << "Sigurno mjesto: "<<broj;
    
    return 0;
}
