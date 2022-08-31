//TP 2016/2017: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <deque>
#define EPS 0.01

typedef std::deque<std::vector<double>> DekVektora;   
enum Smjer {Rastuci, Opadajuci};

void rastuci(std::vector<double> &v)
{
    for(int i=0; i<v.size()/2; i++) {
        for(int j=i+1; j<v.size()/2; j++) {
            if(v.at(j)<v.at(i)) {
                double temp=v.at(i);
                v.at(i)=v.at(j);
                v.at(j)=temp;
            }
        }
    }
    int brojac=0;
    if(v.size()%2!=0) brojac=1;
    for(int i=v.size()/2+brojac; i<v.size(); i++) {
        for(int j=i+1; j<v.size(); j++) {
            if(v.at(j)>v.at(i)) {
                double temp=v.at(i);
                v.at(i)=v.at(j);
                v.at(j)=temp;
            }
        }
    }
}
void opadajuci(std::vector<double> &v)
{
    for(int i=0; i<v.size()/2; i++) {
        for(int j=i+1; j<v.size()/2; j++) {
            if(v.at(j)>v.at(i)) {
                double temp=v.at(i);
                v.at(i)=v.at(j);
                v.at(j)=temp;
            }
        }
    }
    int brojac=0;
    if(v.size()%2!=0) brojac=1;
    for(int i=v.size()/2+brojac; i<v.size(); i++) {
        for(int j=i+1; j<v.size(); j++) {
            if(v.at(j)<v.at(i)) {
                double temp=v.at(i);
                v.at(i)=v.at(j);
                v.at(j)=temp;
            }
        }
    }
}
bool Balansirani(std::vector<double> v)
{   if(v.size()<2) return false;
    int brojac=0;
    if(v.size()%2!=0) brojac=1;
    double suma1=0, suma2=0;
    for(int i=0; i<v.size()/2; i++)  
        suma1+=v.at(i);
    for(int i=v.size()/2+brojac; i<v.size(); i++)
        suma2+=v.at(i);
    if(fabs(suma2-suma1)<EPS) return true;
    return false;
}
bool Provjera(DekVektora v, int n){
    for(int i=0; i<v.size(); i++)
    if(v.at(i).at(v.at(i).size()-1)>=n) return false;
    return true;
    }

DekVektora MaksimalniBalansiraniPodniz(std::vector<double>v)
{                  
    DekVektora vv;
   
       
    for(int i=0; i<v.size(); i++) {
        for(int j=v.size()-1; j>=i; j--){
            std::vector<double>pom;
            int k;
            for( k=i; k<j+1; k++)
              pom.push_back(v.at(k));
              if(Balansirani(pom)){ 
                  pom.push_back(k);
                   if(Provjera(vv, k)){ vv.push_back(pom) ;
                   j=0;
              }
                      
              
              }
            }
        }
        for(int i=0; i<vv.size(); i++)
            vv.at(i).resize(vv.at(i).size()-1);
    
    
    return vv;
}

DekVektora Transformacija( DekVektora v, Smjer n)
{
    for(int i=0; i<v.size(); i++)
      if( !Balansirani(v.at(i))) throw std::domain_error ("Dek vektora je neispravan.");
    if(n==0)
        for(int i=0; i<v.size(); i++)
            rastuci(v.at(i));
    else for(int i=0; i<v.size(); i++)
            opadajuci(v.at(i));
    return v;
}


int main ()
{
    try{
    int n;
    std::cout<<"Unesite broj elemenata niza: ";
    std::cin>>n;
    std::vector<double>v;

    double clan;
    std::cout<<"Unesite elemente niza: ";
    for(int i=0; i<n; i++){ 
        std::cin>>clan;
    v.push_back(clan);}
    int tip;
    std::cout<<"Unesite tip: (1 - rastuci, 0 - opadajuci): ";
    std::cin>>tip;
    std::cout<<"\nMaksimalni balansirani podnizovi: "<<std::endl;
    DekVektora neki_dek;
    
       neki_dek=MaksimalniBalansiraniPodniz(v);
    for(int j=0; j<neki_dek.size(); j++){
    for(int i=0; i<neki_dek.at(j).size(); i++)
       std::cout<<neki_dek.at(j).at(i)<<" ";
       std::cout<<std::endl;
    }
    std::cout<<"\nSavrseni balansirani podnizovi nakon transformacije: "<<std::endl;
    if(tip==1) neki_dek=Transformacija(neki_dek, Smjer::Rastuci );
    else neki_dek=Transformacija(neki_dek, Smjer::Opadajuci);
    for( int j=0; j<neki_dek.size(); j++){
    for(int i=0;i< neki_dek.at(j).size(); i++)
    std::cout<<neki_dek.at(j).at(i)<<" ";
    std::cout<<std::endl;
    }
    
    
}
catch(...){
}
    return 0;
}
