//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include <vector>
#include <set>
#include <list>
int Poglavica(int n, int m, bool istina=false)  
{
    if(n<=0 || m<=0) return 0;
    if(n==1) return 1;
    std::list<int>lista;
    for(int i=0; i<n; i++)
        lista.push_back(i+1);
       // std::vector<int>red;
auto it=lista.begin();
    for(; ; ) {
        if(it==lista.end()) it=lista.begin();
        int brojac=1;
        while(brojac!=m) {
            it++;  
            if(it==lista.end()){
                it=lista.begin();
            }
            brojac++;
        }
       if(istina) std::cout<<*it<<" ";
        it=lista.erase(it);
        n--;
        if(it==lista.end()) it=lista.begin();
        if(n==1) break;
    }
   // if(istina) for(int i=0; i<red.size(); i++) std::cout << red.at(i) << std::endl;
    return *it;
}
int SigurnoMjesto (int m, int n1, int n2)
{
    

    std::set<int>nesigurni;
    for(int i=n1; i<=n2; i++){
        nesigurni.insert(Poglavica(i, m));
     
    }
    if(nesigurni.size()==m) return 0;
    auto pom=nesigurni.begin();

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
    int pom=Poglavica(n,m);
    cout<<"Redni broj osobe koja postaje poglavica: "<<pom<<" ";
    int broj=SigurnoMjesto(m,n1,n2);
    if(broj==0) cout << "Sigurno mjesto ne postoji!";
    else cout << "Sigurno mjesto: "<<broj;
    
    return 0;
}
