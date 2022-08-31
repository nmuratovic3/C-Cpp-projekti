//TP 2016/2017: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>

bool naopak( int n )
{
    int pomocni=n;
    bool istina=true;
    if(n<0) 
        istina=false;
    int simetrican=0;
    while(n!=0) {
        int i = abs(n % 10);
        simetrican = simetrican*10 + i;
        n/=10;
    }
    if(!istina) simetrican*=-1;
    if(pomocni==simetrican) return true;
    return false;
}
int Ternarni(int x)
{

    int ter=0;
    int brojac=1;
    while(x!=0) {
        int ostatak=abs(x%3);
        ter+=ostatak*brojac;
        brojac*=10;
        x/=3;
    }
    return ter;
}

std::vector<int> IzdvojiSimetricneTernarne (std::vector<int>vek, bool da=true)
{
    std::vector<int>krajnji;

    for(int i=0; i<vek.size(); i++) {
        if(naopak(vek.at(i))==da  && naopak(Ternarni(vek.at(i)))) {
            int j;
            for(j=0; j<krajnji.size(); j++)
                if(vek.at(i)==krajnji.at(j))
                    break;
            if(j==krajnji.size())
                krajnji.push_back(vek.at(i));
        }
    }

    return krajnji;
}

int main ()
{
    int n1;

    std::cout<<"Unesite broj elemenata niza: ";
    std::cin>>n1;

    std::vector<int> veki;
    std::cout<<"Unesite elemente niza: ";
    int broj;
    for(int i=0; i<n1; i++) {
        std::cin>>broj;
        veki.push_back(broj);
    }
    bool parametar;
    std::cout<<"Unesite parametar (1 ili 0): ";
    std::cin>>parametar;
    std::vector<int>v=IzdvojiSimetricneTernarne(veki,parametar);
    std::cout<<"Izdvojeni elementi su: ";
    for(int i=0; i<v.size(); i++)
        if(i!=v.size()-1) std::cout<<v.at(i)<<", ";
        else std::cout<<v.at(i);
    return 0;
}
