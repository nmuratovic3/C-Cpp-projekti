//TP 2018/2019: Zadaća 3, Zadatak 5
#include <iostream>
#include <set>
#include <new>
struct Clan {
    int redni_broj;
    Clan* sljedeci;
};
using namespace std;
int Poglavica(int n, int m, bool istina=false)
{
    if(n<=0 || m<=0) return 0;
    
    Clan *pocetak=nullptr, *prethodni;
    int i=1;
    for(;;){
        Clan *novi=new Clan{i,nullptr};
        if(!pocetak) pocetak=novi;
        else prethodni->sljedeci=novi;
       // cout<< novi->redni_broj<<endl;
        prethodni=novi;
        if(i==n) break;
        i++;
    }
    prethodni->sljedeci=pocetak;
    auto p=pocetak;
    auto jedan_prije=pocetak;
    int nesto{};
    Clan* next;
    while(i>=1){
        for(int brojac=1; brojac<m; p=p->sljedeci){
            if(brojac==m-2) jedan_prije= p->sljedeci;
            brojac++;}
        next=p->sljedeci;
        if(i==1) nesto=next->redni_broj;
       jedan_prije->sljedeci=next;
       if(istina) std::cout<<p->redni_broj;
        delete p;
    
        p=next;
        i--;
    }
   
    return nesto; 
}
          
    int SigurnoMjesto (int m, int n1, int n2)
{
    

    std::set<int>nesigurni;
    for(int i=n1; i<=n2; i++){
        nesigurni.insert(Poglavica(i, m));
       
    }
    if(nesigurni.size()==m) return 0;
    auto pom=nesigurni.begin();
  //  auto trl=nesigurni.begin();
   // return *trl;
    for(int i=1; i<=n1; i++) {
        if(*pom!=i) return i;
        pom++;
    }

    
    return 0;
}
using namespace std;

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
