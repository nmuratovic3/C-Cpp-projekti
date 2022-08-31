//TP 2018/2019: Zadaća 2, Zadatak 1
#include <iostream>
#include <vector>
#include <stdexcept>
typedef std::vector<std::vector<char>>Matrica ;
std::vector<std::vector<std::vector<char>>> KreirajMatrice(int m, int n)
{
    if(m<1 || n<1) throw std::domain_error("Dimenzije matrica moraju biti pozitivne");
    if(m>99 || n>99) throw std::domain_error("Prevelike dimenzije");
    if(m!=n) throw std::domain_error("Matrice moraju biti kvadratne");
    std::vector<std::vector<std::vector<char>>> matrica(2, Matrica(m, std::vector<char>(n)));
    for(int k=0; k<2; k++) {
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                matrica.at(k).at(i).at(j)='-';
            }
        }
    }
    return matrica;
}
void Nacrtaj(const std::vector<std::vector<std::vector<char>>> &mat, int n)
{
    if(n==0) {
        for(int i=0; i<mat.at(0).size(); i++) {
            for(int j=0; j<mat.at(0).at(0).size(); j++) {
                std::cout << mat.at(0).at(i).at(j) << " ";
            }
            std::cout << std::endl;
        }
    } else if(n==1) {
        for(int i=0; i<mat.at(1).size(); i++) {
            for(int j=0; j<mat.at(1).at(0).size(); j++) {
                std::cout << mat.at(1).at(i).at(j) << " ";
            }
            std::cout << std::endl;
        }
    }

}
bool DaLiJeGrbava(Matrica m)
{
    for(int i=1; i<m.size(); i++)
        if(m.at(i).size()!=m.at(0).size()) return true;
    return false;
}
void Unos(std::vector<std::vector<std::vector<char>>> &matrica, int broj_robota)
{
    if(matrica.size()==0) throw std::domain_error("Matrica ne postoji");
    if(matrica.size()!=2) throw std::range_error("3D matrica ima pogrešne dimenzije");
    if(matrica.at(0).size()==0 || matrica.at(1).size()==0) throw std::domain_error( "Neka od dvije matrice je prazna");
    if(DaLiJeGrbava(matrica.at(0)) || DaLiJeGrbava(matrica.at(1))) throw std::domain_error("Neka matrica je grbava");
    if(matrica.at(0).size()!=matrica.at(0).at(0).size() || matrica.at(1).size()!=matrica.at(1).at(0).size()) throw std::domain_error("Neka od matrica nije kvadratna" );
    if(matrica.at(0).size()!=matrica.at(1).size()) throw std::domain_error("Matrice nemaju iste dimenzije");
    if(broj_robota*(broj_robota+1)/2>matrica.at(0).size()*matrica.at(0).size()) throw std::overflow_error("Zelite igrati sa previse robota.");
    if(broj_robota>15) throw std::range_error("Zelite igrati sa previse robota.");
    if(broj_robota<1) throw std::domain_error("Ne mozete igrati bez robota.");
    std::vector<std::vector<int>>koordinate(broj_robota, std::vector<int>(4));
    std::vector<std::vector<int>>koordinate2(broj_robota, std::vector<int>(4));
    int broj;
    for(int i=0; i<broj_robota; i++) {
        bool istina;
        do {
            istina=false;
            bool nova_istina;
            koordinate.at(i).at(0)=0;
            koordinate.at(i).at(1)=0;
            std::cout << "Naida unesi pocetne i krajnje koordinate " << i+1 << ". robota: ";
            for( int j=0; j<4; j++ ) {
                std::cin >> broj;
                nova_istina=false;
                if(!std::cin || broj>=matrica.at(0).size() || broj<0) {
                    std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                    nova_istina=true;
                    break;
                }

                koordinate.at(i).at(j)=broj;
                if(koordinate.at(i).at(0)==-1 && koordinate.at(i).at(1)==-1 || koordinate.at(i).at(2)==-1 && koordinate.at(i).at(3)==-1) return;
            }
            if(nova_istina) continue;
            int j;
            // for(j=0; j<4; j++) {
            //   if(koordinate.at(i).at(j)==-2) continue;
            // break;
            //}
            if(koordinate.at(i).at(0)==-2 && koordinate.at(i).at(1)==-2 || koordinate.at(i).at(3)==-2 && koordinate.at(i).at(4)==-2) j=4;

            if(j==4) {
                Nacrtaj(matrica,0);
                istina=true;
            }
            std::cout << std::endl;

            if(koordinate.at(i).at(0)>koordinate.at(i).at(3)) {
                for(int k=koordinate.at(i).at(3); k<=koordinate.at(i).at(0); k++) {
                    if(matrica.at(0).at(i).at(k)=='-')
                        matrica.at(0).at(i).at(k)=i+65;
                    else {
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                        istina=true;
                        break;
                    }
                }
            } else if(koordinate.at(i).at(0)<koordinate.at(i).at(2)) {
                for(int k=koordinate.at(i).at(0); k<=koordinate.at(i).at(3); k++){
                    if(matrica.at(0).at(i).at(k)=='-')
                    matrica.at(0).at(i).at(k)=i+65;
                    else {
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                        istina=true;
                        break;
                    }
                }
            } else if(koordinate.at(i).at(1)>koordinate.at(i).at(3)) {
                for(int k=koordinate.at(i).at(3); k<=koordinate.at(i).at(1); k++)
                    if(matrica.at(0).at(k).at(koordinate.at(i).at(3))=='-') matrica.at(0).at(k).at(koordinate.at(i).at(3))=i+65;
                    else{
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                        istina=true;
                        break;}
            } else if(koordinate.at(i).at(3)>koordinate.at(i).at(1)) {
                for(int k=koordinate.at(i).at(1); k<=koordinate.at(i).at(3); k++)
                    if(matrica.at(0).at(k).at(koordinate.at(i).at(3))=='-') matrica.at(0).at(k).at(koordinate.at(i).at(3))=i+65;
                    else {
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                        istina=true;
                        break;}
            } else matrica.at(0).at(i).at(koordinate.at(i).at(0))=i+65;
        } while(istina);
        do {
            int j;
            istina=false;
            bool nova_istina;
            koordinate2.at(i).at(0)=0;
            koordinate2.at(i).at(1)=0;
            std::cout << "Alina unesi pocetne i krajnje koordinate " << i+1 << ". robota: ";
            for(j=0; j<4; j++ ) {
                std::cin >> broj;
                koordinate2.at(i).at(j)=broj;
                if(!std::cin || broj>matrica.at(1).at(0).size() || broj<0) {
                    std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                    nova_istina=true;
                    break;
                }

                if( koordinate2.at(i).at(0)==-1 && koordinate2.at(i).at(1)==-1 ||  koordinate2.at(i).at(2)==-1 && koordinate2.at(i).at(3)==-1) return;
            }
            if(nova_istina) continue;
            j=0;
            if(koordinate2.at(i).at(0)==-2 && koordinate2.at(i).at(1)==-2 || koordinate2.at(i).at(3)==-2 && koordinate2.at(i).at(4)==-2) j=4;
            if(j==4) {
                Nacrtaj(matrica,1);
                istina=true;
            }
        
        if(koordinate2.at(i).at(0)>koordinate2.at(i).at(3)) {
            for(int k=koordinate2.at(i).at(3); k<=koordinate2.at(i).at(0); k++)
         {if(matrica.at(1).at(i).at(k)=='-')
                        matrica.at(1).at(i).at(k)=i+65;
                    else {
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                        istina=true;
                        break;
                    }
                }
            }
         else if(koordinate2.at(i).at(0)<koordinate2.at(i).at(2)) {
            for(int k=koordinate2.at(i).at(0); k<=koordinate2.at(i).at(3); k++)
               {
                    if(matrica.at(1).at(i).at(k)=='-')
                    matrica.at(1).at(i).at(k)=i+65;
                    else {
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                        istina=true;
                        break;
                    }
                }
            
        } else if(koordinate2.at(i).at(1)>koordinate2.at(i).at(3)) {
            for(int k=koordinate2.at(i).at(3); k<=koordinate2.at(i).at(1); k++)
            if(matrica.at(1).at(k).at(koordinate.at(i).at(3))=='-') matrica.at(1).at(k).at(koordinate.at(i).at(3))=i+65;
                    else{
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                        istina=true;
                        break;}
            }
            else if(koordinate2.at(i).at(3)>koordinate2.at(i).at(1)) {
            for(int k=koordinate2.at(i).at(1); k<=koordinate2.at(i).at(3); k++)
                if(matrica.at(1).at(k).at(koordinate.at(i).at(3))=='-') matrica.at(1).at(k).at(koordinate.at(i).at(3))=i+65;
                    else {
                        std::cout<<"Pogresne koordinate gdje zelite smjestiti robota";
                        istina=true;
                        break;}
        } else matrica.at(1).at(i).at(koordinate2.at(i).at(0))=i+65;
    }} while(istina);
}
int main ()
{
    auto mat=KreirajMatrice(3,3);
    Nacrtaj(mat,1);
    Unos(mat,3);
    Nacrtaj(mat,1);
    return 0;
}
