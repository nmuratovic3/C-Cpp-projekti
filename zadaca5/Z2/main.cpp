//TP 2018/2019: Zadaća 5, Zadatak 2
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <iterator>
using namespace std;
class Padavine
{
    std::vector<int>padavine;
    int max_broj;
    
    public:
    explicit Padavine(int x)
    {
        if(x<0) throw range_error("Ilegalna maksimalna kolicina");
        max_broj=x;
    }
    void RegistrirajPadavine(int x)
    {
        if(x<0 || x>max_broj) throw range_error("Ilegalna kolicina padavina");
        padavine.push_back(x);
    }
    int DajBrojRegistriranihPadavina() const
    {
        return padavine.size();
    }
    void BrisiSve()
    {
        padavine.resize(0);
    }
    int DajMaksimalnuKolicinuPadavina() const
    {
        if(padavine.size()==0) throw range_error("Nema registriranih padavina");
        return *max_element(padavine.begin(), padavine.end(), [](int a, int b) {
            return a<b;
        });
    }
    int DajMinimalnuKolicinuPadavina() const
    {
        if(padavine.size()==0) throw range_error("Nema registriranih padavina");
        return *min_element(padavine.begin(), padavine.end(), [](int a, int b) {
            return a<b;
        });
    }
    int DajBrojDanaSaPadavinamaVecimOd(int x) const
    {
        int pom=count_if(padavine.begin(), padavine.end(), bind(greater<int>(), placeholders::_1,x));
        if(padavine.size()==0) throw range_error("Nema registriranih padavina");
        return pom;
    }
    void Ispisi() const
    {
        std::vector<int>pom(padavine) ;
        sort(pom.begin(), pom.end(), bind(greater<int>(), placeholders::_1, placeholders::_2));
     copy(pom.begin(), pom.end(), std::ostream_iterator<int>(std::cout<<endl, "\n"));
      
    }
    int operator[](int x)
    {
        if(x>padavine.size()) throw range_error("Neispravan indeks");
        return padavine.at(x-1);
    }
    friend Padavine &operator++(Padavine &s);
    friend Padavine operator ++(Padavine &s, int);
    friend Padavine operator +(Padavine &s, int x);
        friend Padavine operator +(int x,Padavine &s);
        friend Padavine operator -(Padavine &s, int x);
        friend Padavine operator -(int x, Padavine &s);
        friend Padavine operator -(const Padavine &a,const Padavine &b);
        friend Padavine operator +(Padavine &a, Padavine &b);
        friend Padavine operator +=(Padavine &a, Padavine &b);
        friend Padavine operator +=(Padavine &a, int b);
        friend Padavine operator -=(Padavine &a,const Padavine &b);
        friend Padavine operator -=(Padavine &a, int b);
        friend  Padavine operator -(const Padavine &s);
        friend bool operator ==(const Padavine &a, const Padavine &b);
        friend bool operator !=(const Padavine &a, const Padavine &b);
};
     Padavine &operator++(Padavine &s)
    {
        if(s.padavine.size()==0) throw range_error("Nema registriranih padavina");
        s.max_broj++;
        transform(s.padavine.begin(), s.padavine.end(), s.padavine.begin(), bind(plus<int>(), 1, placeholders::_1));
        return s;
    }
     Padavine operator ++(Padavine &s, int)
    {
        Padavine pom(s.max_broj);
        pom.padavine.resize(s.padavine.size());
        copy(s.padavine.begin(), s.padavine.end(), pom.padavine.begin());
        s.max_broj++;
        transform(s.padavine.begin(), s.padavine.end(), s.padavine.begin(), bind(plus<int>(), 1, placeholders::_1));
        return pom;
    }
     Padavine operator +(Padavine &s, int x)
    {
        Padavine pom(s.max_broj);
        pom.max_broj+=x;
        transform(s.padavine.begin(), s.padavine.end(), pom.padavine.begin(), bind(plus<int>(), x, placeholders::_1));
        if(*min_element(pom.padavine.begin(), pom.padavine.end())<0) throw domain_error("Nekorektan rezultat operacije");
        return pom;
    }
    Padavine operator +(int x,Padavine &s)
    {
        Padavine pom(s.max_broj);
        pom.max_broj+=x;
        transform(s.padavine.begin(), s.padavine.end(), pom.padavine.begin(), bind(plus<int>(), x, placeholders::_1));
        if(*min_element(pom.padavine.begin(), pom.padavine.end())<0) throw domain_error("Nekorektan rezultat operacije");
        return pom;
    }
     Padavine operator -(Padavine &s, int x)
    {
        Padavine pom(s.max_broj-x);
        pom.padavine.resize(s.padavine.size());
        transform(s.padavine.begin(), s.padavine.end(), pom.padavine.begin(), bind(minus<int>(), placeholders::_1,x));
        if(*min_element(pom.padavine.begin(), pom.padavine.end())<0){
           // cout<<*min_element(pom.padavine.begin(), pom.padavine.end());
            throw domain_error("Nekorektan rezultat operacije");}
        return pom;
    }
    Padavine operator -(int x, Padavine &s)
    {
        Padavine pom(x);
        pom.padavine.resize(s.padavine.size());
        transform(s.padavine.begin(), s.padavine.end(), pom.padavine.begin(), negate<int>());
        transform(pom.padavine.begin(), pom.padavine.end(), pom.padavine.begin(), bind(plus<int>(), x, placeholders::_1));
        if(*min_element(pom.padavine.begin(), pom.padavine.end())<0) throw domain_error("Nekorektan rezultat operacije");
            return pom;
        }
    Padavine operator -(const Padavine &a,const Padavine &b)
    {
        if(a.padavine.size()!=b.padavine.size()) throw domain_error("Nesaglasni operandi");
        std::vector<bool>istina(a.padavine.size());
        transform(a.padavine.begin(), a.padavine.end(), b.padavine.begin(), istina.begin(), bind(less<int>(), placeholders::_1, placeholders::_2));
        auto p=find(istina.begin(), istina.end(), true);
        if(p!=istina.end()) throw domain_error("Nesaglasni operandi");
        Padavine pom(a.max_broj);
        pom.padavine.resize(a.padavine.size());
        transform(a.padavine.begin(), a.padavine.end(), b.padavine.begin(), pom.padavine.begin(), bind(minus<int>(), placeholders::_1, placeholders::_2));
        return pom;
    }
     Padavine operator +(Padavine &a, Padavine &b)
    {
        if(a.padavine.size()!=b.padavine.size()) throw domain_error("Nesaglasni operandi");
        Padavine pom(a.max_broj);
        transform(a.padavine.begin(), a.padavine.end(), b.padavine.begin(), pom.padavine.begin(), bind(plus<int>(), placeholders::_1, placeholders::_2));
        if(*max_element(pom.padavine.begin(), pom.padavine.end())>a.max_broj) throw domain_error("Nesaglasni operandi");
        return pom;
    }
    Padavine operator +=(Padavine &a, Padavine &b)
    {
        a=a+b;
        return a;
    }
     Padavine operator +=(Padavine &a, int b)
    {
        a.max_broj+=b;
        transform(a.padavine.begin(), a.padavine.end(), a.padavine.begin(), bind(plus<int>(), b, placeholders::_1));
        if(*min_element(a.padavine.begin(), a.padavine.end())<0) throw domain_error("Nekorektan rezultat operacije");
        
        return a;
    }
    Padavine operator -=(Padavine &a,const Padavine &b)
    {
       if(a.padavine.size()!=b.padavine.size()) throw domain_error("Nesaglasni operandi");
        std::vector<bool>istina(a.padavine.size());
        transform(a.padavine.begin(), a.padavine.end(), b.padavine.begin(), istina.begin(), bind(less<int>(), placeholders::_1, placeholders::_2));
        auto p=find(istina.begin(), istina.end(), true);
        if(p!=istina.end()) throw domain_error("Nesaglasni operandi");
        transform(a.padavine.begin(), a.padavine.end(), b.padavine.begin(), a.padavine.begin(), bind(minus<int>(), placeholders::_1, placeholders::_2));
        return a;
    }
     Padavine operator -=(Padavine &a, int b)
    {
        a=a-b;
        return a;
    }
   Padavine operator -(const Padavine &s)
    {
        Padavine p(s.max_broj);
        p.padavine.resize(s.padavine.size());
        transform(s.padavine.begin(), s.padavine.end(), p.padavine.begin(), bind(minus<int>(), s.max_broj, placeholders::_1));
        return p;
    }
    bool operator ==(const Padavine &a, const Padavine &b){
        if(a.padavine.size()!=b.padavine.size()) return false;
        std::vector<bool>istina(a.padavine.size());
        transform(a.padavine.begin(), a.padavine.end(), b.padavine.begin(), istina.begin(), bind(less<int>(), placeholders::_1, placeholders::_2));
        auto p=find(istina.begin(), istina.end(), true);
        if(p!=istina.end()) return false;
        transform(a.padavine.begin(), a.padavine.end(), b.padavine.begin(), istina.begin(), bind(greater<int>(), placeholders::_1, placeholders::_2));
         p=find(istina.begin(), istina.end(), true);
        if(p!=istina.end()) return false;
        return true;
    }
    bool operator !=(const Padavine &a, const Padavine &b){
         return (!(a==b));
    }

   
    int main ()
    { 
Padavine t(10);
Padavine t1(20);
  for(int i= 5;i<=10;i++)
    {
      t.RegistrirajPadavine(i);
      t1.RegistrirajPadavine(i);
    }
  for(int i= 4;i>=1;i--)
    {
      t.RegistrirajPadavine(i);
      t1.RegistrirajPadavine(i);
    }
if(t == t1) std::cout<<"DA";
else std::cout<<"NE";
if(t != t1) std::cout<<"DA";
else std::cout<<"NE";
t1.RegistrirajPadavine(1);
if(t == t1) std::cout<<"DA";
else std::cout<<"NE";
if(t != t1) std::cout<<"DA";
else std::cout<<"NE";
        return 0;
    }
