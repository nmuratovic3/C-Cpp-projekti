//TP 2016/2017: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
bool samoglasnik(char s)
{
    if(s=='A' || s=='a' || s=='E' || s=='e' || s=='I' || s=='i' || s=='O' || s=='o' || s=='U' || s=='u') return true;
    return false;
}

bool jesu(std::string s)
{
    if(samoglasnik(s.at(0))) {
        int i;
        for(i=1; i<s.size(); i++) {
            if(i%2!=0 ) {
                if(!samoglasnik(s.at(i))) continue;
                else break;
            } else {
                if(samoglasnik(s.at(i))) continue;
                else break;
            }
        }
  
        if(i==s.size()) return true;
    } else if(!samoglasnik(s.at(0))) {
        int i;
        for(i=1; i<s.size(); i++) {
            if( i%2!=0 ) {
                if(samoglasnik(s.at(i))) continue;
                else break;
            } else {
                if(!samoglasnik(s.at(i))) continue;
                else break;
            }
        }
 
        if(i==s.size()) return true;
    }
    return false;
}

std::string IstakniSavrsenoRitmicneRijeci(std::string s)
{
    bool neslovo=true;
    for(int i=0; i<s.size(); i++) {
        if ( s.at(i) == ' ' ) neslovo = true;
        else if(neslovo) {
            neslovo=false;
            int pamti_indeks_prvog=i;

            while(i<s.size() && ((s.at(i)>='A' && s.at(i)<='Z') || (s.at(i)>='a' && s.at(i)<='z'))) {
                i++;
            }
         
            if(jesu(s.substr(pamti_indeks_prvog, i-pamti_indeks_prvog)) && i-pamti_indeks_prvog>1) {
                s.insert(s.begin()+pamti_indeks_prvog, '(');
                s.insert(s.begin()+i+1,')');
            
            } i--;
        }
    
    }

    return s;
}
int main ()
{
    std::string recenica;
    std::cout << "Unesite recenicu (ENTER za kraj): ";
    std::getline(std::cin, recenica);
    std::cout << "Recenica sa istaknutim savrseno ritmicnim rijecima glasi: \n";
    recenica=IstakniSavrsenoRitmicneRijeci(recenica);
    for ( int i=0; i<recenica.size(); i++ )
        std::cout << recenica.at(i);
    std::cout <<std::endl;
    
    return 0;
}
