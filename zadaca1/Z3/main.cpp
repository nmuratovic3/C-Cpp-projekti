//TP 2016/2017: Zadaća 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>  
#include <iomanip>
typedef std::vector<std::vector<double>>Matrica;
typedef std::vector<std::vector<std::vector<double>>>Trodimenzionalna;
bool MoguSeMnoziti(Matrica m1, Matrica m2)
{   
    if(m1.size()==0 || m2.size()==0) return false;
    return m1.at(0).size()==m2.size();
}
bool Potpuna(Matrica m)
{   
    for(int i=1; i<m.size(); i++)
        if(m.at(i).size()!=m.at(0).size()) return false;
    return true;
}
bool Kvadratna(Matrica m)
{   if(m.size()==0) return true;
    if(m.size()!=m.at(0).size()) return false;
    return true;
}
Matrica MnozenjeMatrica(Matrica m1, Matrica m2)
{   if(m1.size()==0 && m2.size()==0) return m2;
    if(!MoguSeMnoziti(m1,m2)) throw std::domain_error("Nije moguce mnozenje matrica!");
    if(!Potpuna(m1) || !Potpuna(m2)) throw std::domain_error("Neispravna matrica!");
    Matrica mat(m1.size(), std::vector<double>(m2.at(0).size()));
    for(int i=0; i<m1.size(); i++) {
        for(int j=0; j<m2.at(0).size(); j++) {
            double suma(0);
            for(int k=0; k<m2.size(); k++) suma+=m1.at(i).at(k)*m2.at(k).at(j);
            mat.at(i).at(j)=suma;
        }
    }
    return mat;
}
Trodimenzionalna DoolitleLU( Matrica H )
{   
    
    if(!Potpuna(H)) throw std::domain_error("Neispravna matrica!");
    if(!Kvadratna(H)) throw std::domain_error("Matrica mora biti kvadratnog oblika!");
    Trodimenzionalna D (2, Matrica(H.size(), std::vector<double>(H.size())));
    if(H.size()==0){
        D.resize(0);
        return D;
        }
    Matrica prva(H.size(), std::vector<double>(H.size(), 0));
    Matrica druga(H.size(), std::vector<double>(H.size(), 0));
    for(int i=0; i<H.size(); i++) {
        for(int j=0; j<H.size(); j++) {
            if(i==j) D.at(0).at(i).at(i)=1;
        }
    }


    for(int i=0; i<H.size(); i++) {
        for(int j=0; j<H.size(); j++) {
            if(i>j) {
                double element(0);
                for(int k=0; k<=j-1; k++) element+=prva.at(i).at(k)*druga.at(k).at(j);
                element=-(element-H.at(i).at(j));
                element*=(1/druga.at(j).at(j));
                prva.at(i).at(j)=element;
                D.at(0).at(i).at(j)=element;
            } else if(j>=i){
                
                double element(0);
                for(int k=0; k<=i-1; k++)
                    element+=prva.at(i).at(k)*druga.at(k).at(j);
                element=H.at(i).at(j)-element;      
                druga.at(i).at(j)=element;
                D.at(1).at(i).at(j)=element;
            }
        }
    }
    
    return D;
}
bool ProvjeriFaktorizaciju(Matrica mat, Trodimenzionalna pom)
{       
        if(mat.size()==0 && pom.size()==0) return true;
        if(pom.size()!=2) return false;
        if(!MoguSeMnoziti(pom.at(0), pom.at(1)) || !Kvadratna(pom.at(0)) || !Kvadratna(pom.at(1)) || !Potpuna(mat)) return false;
        if(pom.at(0).size()!=mat.size() || pom.at(1).size()!=mat.size()) return false;
        if(MnozenjeMatrica(pom.at(0), pom.at(1))!=mat) return false;
    return true;
}

int main ()
{
    try {
        std::cout<<"Unesite dimenziju kvadratne matrice H: ";
        int H;
        std::cin>>H;
        Matrica mat1(H, std::vector<double>(H));
        std::cout<<"Unesite elemente matrice H: \n";
        for(int i=0; i<H; i++) {
            for(int j=0; j<H; j++) {
                std::cin>>mat1.at(i).at(j);
            }
        }
        Trodimenzionalna lumat=DoolitleLU(mat1);
        for(int i=0; i<H; i++)
            std::cout<<"Elementi "<<i+1<<". reda: ";
        std::cout<<"Matrica L:\n";
        for(int i=0; i<H; i++) {
            for(int j=0; j<H; j++) {
                std::cout<<std::right<<std::setw(9)<<std::setprecision(4)<<std::fixed<<lumat.at(0).at(i).at(j);
            }
            std::cout<<std::endl;
        }
        std::cout<<"Matrica U:\n";
        for(int i=0; i<H; i++) {
            for(int j=0; j<H; j++) {
                std::cout<<std::right<<std::setw(9)<<std::setprecision(4)<<std::fixed<<lumat.at(1).at(i).at(j);
            }
            std::cout<<std::endl;
        }
    } catch(std::domain_error e) {
        std::cout<<e.what()<<std::endl;
    }


    return 0;
}
