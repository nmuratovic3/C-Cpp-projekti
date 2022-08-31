//TP 2018/2019: Zadaća 5, Zadatak 1
#include <iostream>
#include<vector>
#include <stdexcept>
#include <iomanip>
#include <initializer_list>
#include <type_traits>
using namespace std;           
template <typename Tip>
class SimetricnaMatrica
{
    vector<vector<Tip>> matrica;
public:
    SimetricnaMatrica()=default;
    template <typename NekiTip>
    SimetricnaMatrica(const SimetricnaMatrica<NekiTip> &m)
    {
        matrica.resize(m.size());
        for(int i=0; i<m.size(); i++) {
            for(int j=0; j<m.at(i).size(); j++) {
                matrica.at(i).push_back(m.at(i).at(j));
            }
        }
    }
    template <typename NekiTip>
    friend bool operator!(SimetricnaMatrica<NekiTip> a);
    SimetricnaMatrica(vector<vector<Tip>> v);
    //SimetricnaMatrica(initializer_list<initializer_list<Tip>> v);
    SimetricnaMatrica(int n);
    template <typename TipEl>
    friend std::ostream &operator <<(ostream& tok, SimetricnaMatrica<TipEl>&m)
    {
        auto nesto=tok.width();
        for(int i=0; i<m.DajDimenziju(); i++) {
            for(int j=0; j<m.DajDimenziju(); j++)
            if(j>i) tok<<setw(nesto)<<m.matrica[j][i];
              else  tok<<setw(nesto)<<m.matrica[i][j];
            tok<<endl;
        }
        return tok;
    }
    template <typename TipEl> ///cou<<
    friend istream &operator >>(istream &tok, SimetricnaMatrica<TipEl> &m)
    {
        for(int i=0; i<m.DajDimenziju(); i++) {
            for(int j=i+1; j<m.DajDimenziju(); j++)
                tok>>m.matrica[i][j];
        }
        return tok;
    }
    int DajDimenziju() const
    {
        return matrica.size();
    }

    Tip &operator ()(int i, int j)
    {
        if(i<=0 || i>matrica.size() || j<=0 || j>matrica.size()) throw range_error("Neelegalni indeksi");
        if(j>i) {
            return matrica[j-1][i-1];
        }
        return matrica[i-1][j-1];
    }
    Tip operator ()(int i, int j)const
    {
        if(i<=0 || i>DajDimenziju() || j<=0 || j>DajDimenziju()) throw range_error("Nelegalni indeksi");
        if(j>i) {
            return matrica[j-1][i-1];
        }
        return matrica[i-1][j-1];
    }
    template <typename TipEl>
    friend SimetricnaMatrica<TipEl> operator +(SimetricnaMatrica<TipEl> &a, SimetricnaMatrica<TipEl> &b){
        for(int i=0; i<a.DajDimenziju(); i++){
            for(int j=i; j<a.DajDimenziju(); j++){
                a.matrica.at(i).at(j)=a.matrica.at(i).at(j)+b.matrica.at(i).at(j);
            }
        }
        return a;
    }};
    template <typename TipEl>
SimetricnaMatrica<TipEl> &SimetricnaMatrica<TipEl> :: operator +=(const SimetricnaMatrica<TipEl> &sm)
   /* template <typename NekiTip1, typename NekiTip2>
    friend  auto operator+= (SimetricnaMatrica<NekiTip1>&a, SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
            b.matrica[0][0])>::type**;
    template <typename NekiTip1, typename NekiTip2>
    friend auto operator-= (SimetricnaMatrica<NekiTip1> &a, SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
            b.matrica[0][0])>::type**;
            template <typename NekiTip1, typename NekiTip2>
    friend auto operator+ (const SimetricnaMatrica<NekiTip1> &a,const SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
            b.matrica[0][0])>::type**;
    template <typename NekiTip1, typename NekiTip2>
    friend  auto operator- (SimetricnaMatrica<NekiTip1>a,const SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
            b.matrica[0][0])>::type**;*/
   /* Tip operator[](int i, int j)
    {
        if(j>i) {
            return matrica[j][i];
        }
        return elementi[i][j];
    }*/
  /*  template <typename NekiTip1, typename NekiTip2>
    friend  auto operator+= (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
            b.matrica[0][0])>::type**;
    template <typename NekiTip1, typename NekiTip2>
    friend auto operator-= (SimetricnaMatrica<NekiTip1> &a, SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
            b.matrica[0][0])>::type**;*/
/*    template <typename NekiTip1, typename NekiTip2>
    friend auto operator* (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
            b.matrica[0][0])>::type**;
    template <typename NekiTip1, typename NekiTip2>
    friend auto operator*= (SimetricnaMatrica<NekiTip1> &a, NekiTip2 b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+b)>::type**;
    template <typename NekiTip1, typename NekiTip2>
    friend auto operator* (SimetricnaMatrica<NekiTip1>a, NekiTip2 b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+b)>::type**;
    template <typename NekiTip1, typename NekiTip2>
    friend auto operator* (NekiTip1 b, SimetricnaMatrica<NekiTip2>a)->typename SimetricnaMatrica<decltype(b+a.matrica[0][0])>::type**;
   *//* template <typename NekiTip1, typename NekiTip2>
    friend auto operator+ (const SimetricnaMatrica<NekiTip1>a,const SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
            b.matrica[0][0])>::type**;
    template <typename NekiTip1, typename NekiTip2>
    friend  auto operator- (SimetricnaMatrica<NekiTip1>a,const SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
            b.matrica[0][0])>::type**;*/
/*    template <typename NekiTip1, typename NekiTip2>
    friend bool operator== (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b);
    template <typename NekiTip1, typename NekiTip2>
    friend bool operator!= (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b);

};*/
template <typename Tip>
SimetricnaMatrica<Tip>::SimetricnaMatrica(vector<vector<Tip>> v)
{
    //
    for(int i=0; i<v.size(); i++)
        if(v.at(i).size()!=i+1) throw logic_error("Nekorektna forma simetricne matrice");
    matrica.resize(v.size());
    for(int i=0; i<v.size(); i++) {
        for(int j=0; j<v.at(i).size(); j++) {
            matrica.at(i).push_back(v.at(i).at(j));
        }
    }
}/*
template <typename Tip>
SimetricnaMatrica<Tip>::SimetricnaMatrica(initializer_list<initializer_list<Tip>> v)//
{
    int i=1;
    for(auto it=v.begin(); it!=v.end(); it++, i++)
        if((*it).size()!=i) throw logic_error("Nekorektna forma simetricne matrice");
    matrica.resize(v.size());
    auto it=v.begin();
    for(int i=0; i<v.size(); i++) {
        for(int j=0; j<i+1; j++) {
            matrica.at(i).at(j)=(**it);
            //myb popraviti
        }
       // it++;
    }
}*/
template <typename Tip>
SimetricnaMatrica<Tip>::SimetricnaMatrica(int n)//
{
    if(n<0) throw domain_error("Neispravna dimenzija");
    matrica.resize(n);
    for(int i=0; i<n; i++) matrica.at(i).resize(i+1);
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            matrica.at(i).at(j)=0;
}
template <typename Tip>
bool operator !(SimetricnaMatrica<Tip> a) //
{
    for(int i=0; i<a.DajDimenziju(); i++) {
        for(int j=0; j<a.matrica.at(i).size(); j++) {
            if(a.matrica.at(i).at(j)!=0) return false;
        }
    }
    return true;
}
/*  template <typename NekiTip>
  friend SimetricnaMatrica<NekiTip> operator+ (SimetricnaMatrica<NekiTip>a, SimetricnaMatrica<NekiTip>b);
  template <typename NekiTip>
  friend SimetricnaMatrica<NekiTip> operator- (SimetricnaMatrica<NekiTip>a, SimetricnaMatrica<NekiTip>b);
  template <typename NekiTip1, typename NekiTip2>
  SimetricnaMatrica<NekiTip> auto:: operator+= (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
          b.matrica[0][0])>::type**
*/
template <typename NekiTip1, typename NekiTip2>//
 auto operator+= (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
        b.matrica[0][0])>::type**
{
    if(a.DajDimenziju()!=b.DajDimenziju()) throw logic_error("Matrice nisu saglasne za trazenu operaciju");
    //SimetricnaMatrica <decltype<a.matrica[0][0]+b.matrica[0][0]>> m;
    //m.matrica.resize(a.DajDimenziju());
    for(int i=0; i<a.DajDimenziju(); i++) {
        for(int j=0; j<a.at(i).size(); j++) {
            a.matrica.at(i).at(j)+=b.matrica.at(i).at(j);
            //m.matrica.at(i).push_back(a.matrica.at(i).at(j)+b.matrica.at(i).at(j));
        }
    }
    return a;
}template <typename TipEl>
SimetricnaMatrica<TipEl> &SimetricnaMatrica<TipEl> :: operator +=(const SimetricnaMatrica<TipEl> &sm)

template <typename NekiTip1, typename NekiTip2>
auto operator-= (SimetricnaMatrica<NekiTip1> &a, SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
        b.matrica[0][0])>::type** //
{
    if(a.DajDimenziju()!=b.DajDimenziju()) throw logic_error("Matrice nisu saglasne za trazenu operaciju");
   // SimetricnaMatrica <decltype<a.matrica[0][0]+b.matrica[0][0]>> m();
   // m.resize(a.DajDimenziju());
    for(int i=0; i<a.DajDimenziju(); i++) {
        for(int j=0; j<a.at(i).size(); j++) {
            (a.matrica.at(i).at(j)-=b.matrica.at(i).at(j));
        }
    }
    return a;
}
/*template <typename NekiTip1, typename NekiTip2>
auto operator* (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
        b.matrica[0][0])>::type**
{
    if(a.DajDimenziju()!=b.DajDimenziju()) throw logic_error("Matrice nisu saglasne za trazenu operaciju");
    SimetricnaMatrica <decltype<a.matrica[0][0]+b.matrica[0][0]>> m();
    m.resize(a.DajDimenziju());
    for(int i=0; i<m.DajDimenziju(); i++) m.at(i).resize(a.DajDimenziju());
    for(int i=0; i<m.DajDimenziju(); i++) {
        a.at(i).resize(a.DajDimenziju());
        b.at(i).resize(a.DajDimenziju());
    }
    for(int i=0; i<m.DajDimenziju(); i++)
        for(int j=i+1; j<m.DajDimenziju()-i-1; j++) {
            a.at(i).at(j)=a.at(j).at(i);
            b.at(i).at(j)=b.at(j).at(i);
        }
    for(int i=0; i<a.DajDimenziju(); i++) {
        for(int j=0; j<a.DajDimenziju(); j++) {
            decltype(a.matrica[0][0]+b.matrica[0][0]) suma{};
            for(int k=0; k<a.DajDimenziju(); k++)
                suma+=a.at(i).at(j)*b.at(i).at(j);
            m.at(i).at(j)=suma;
        }
    }
    vector<decltype<a.matrica[0][0]+b.matrica[0][0]>> v(a.DajDimenziju());
    for(int i=0; i<a.DajDimenziju(); i++) {
        for(int j=0; j<a.DajDimenziju(); j++) {
            v.at(j)=m.at(j).at(i);
        }
        if(m.at(i)!=v) throw logic_error("Rezultat nije simetricna matrica");
    }
    for(int i=0; i<a.DajDimenziju(); i++)
        m.resize(i+1);
    return m;
}*//*
template <typename NekiTip1, typename NekiTip2>
auto operator*= (SimetricnaMatrica<NekiTip1> &a, NekiTip2 b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+b)>::type** //
{*/
    //
 /*   SimetricnaMatrica <decltype<a.matrica[0][0]+b>> m(0);
    SimetricnaMatrica <decltype<a.matrica[0][0]+b>> m(0);
    m.resize(a.DajDimenziju());*/
 /*   for(int i=0; i<a.DajDimenziju(); i++) {
        for(int j=i+1; j<a.DajDimenziju(); j++) {
            a.at(i).at(j)=(a.at(i).at(j)*b);
        }
    }
    return a;
}
template <typename NekiTip1, typename NekiTip2>
auto operator* (SimetricnaMatrica<NekiTip1>a, NekiTip2 b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+b)>::type**
{
    //
    return a*=b;
}

template <typename NekiTip1, typename NekiTip2>
auto operator* (NekiTip1 b, SimetricnaMatrica<NekiTip2>a)->typename SimetricnaMatrica<decltype(b+a.matrica[0][0])>::type** //
{
    return a*=b;
}*/ 
template <typename NekiTip1, typename NekiTip2>
auto operator+ (SimetricnaMatrica<NekiTip1>a,const SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
        b.matrica[0][0])>::type** //
{
    a+=b;
    return a;
}
template <typename NekiTip1, typename NekiTip2>
auto operator- (SimetricnaMatrica<NekiTip1>a,const SimetricnaMatrica<NekiTip2>&b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
        b.matrica[0][0])>::type**
{
    a-=b;
    return a;
} /*
template <typename NekiTip1, typename NekiTip2>
auto operator* (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b)->typename SimetricnaMatrica<decltype(a.matrica[0][0]+
        b.matrica[0][0])>::type**
{
    //
    if(a.DajDimenziju()!=b.DajDimenziju()) throw logic_error("Matrice nisu saglasne za trazenu operaciju");
    SimetricnaMatrica <decltype<a.matrica[0][0]+b.matrica[0][0]>> m();
    m.resize(a.DajDimenziju());
    for(int i=0; i<m.DajDimenziju(); i++) m.at(i).resize(a.DajDimenziju());
    for(int i=0; i<m.DajDimenziju(); i++) {
        a.at(i).resize(a.DajDimenziju());
        b.at(i).resize(a.DajDimenziju());
    }
    for(int i=0; i<a.DajDimenziju(); i++)
        for(int j=i+1; j<a.DajDimenziju()-i-1; j++) {
            a.at(i).at(j)=a.at(j).at(i);
            b.at(i).at(j)=b.at(j).at(i);
        }
    for(int i=0; i<a.DajDimenziju(); i++) {
        for(int j=0; j<a.DajDimenziju(); j++) {
            decltype(a.matrica[0][0]+b.matrica[0][0]) suma{};
            for(int k=0; k<a.DajDimenziju(); k++)
                suma+=a.at(i).at(j)*b.at(i).at(j);
            m.at(i).at(j)=suma;
        }
    }
    vector<decltype<a.matrica[0][0]+b.matrica[0][0]>> v(a.DajDimenziju());
    for(int i=0; i<a.DajDimenziju(); i++) {
        for(int j=0; j<a.DajDimenziju(); j++) {
            v.at(j)=m.at(j).at(i);
        }
        if(m.at(i)!=v) throw logic_error("Rezultat nije simetricna matrica");
    }
    for(int i=0; i<a.DajDimenziju(); i++) {
        a.at(i)=m.at(i);
        a.at(i).resize(i+1);
    }
    return a;
}*/ /*
template <typename NekiTip1, typename NekiTip2>
bool operator== (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b)
{
    if(a.DajDimenziju()!=b.DajDimenziju())return false;
    for(int i=0; i<a.DajDimenziju(); i++) {
        for(int j=0; j<a.at(i).size(); j++) {
            if(a.matrica.at(i).at(j)!=b.matrica.at(i).at(j)) return false;
        }
    }
    return true;
}
template <typename NekiTip1, typename NekiTip2>
bool operator!= (SimetricnaMatrica<NekiTip1>a, SimetricnaMatrica<NekiTip2>b)
{
    return !(a==b);
}
*/
int main ()
{
 SimetricnaMatrica<int> sm({{4}, {1, 4}});
    std::cout << std::setw(3) << sm;
    return 0;
}
   