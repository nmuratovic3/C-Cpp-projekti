//TP 2018/2019: Zadaća 2, Zadatak 3
#include <iostream>
#include <new>
#include <stdexcept>
#include <cmath>
#include <iomanip>
long long int rekurzija(int i, int j){
    if(j>i) return 0;
    if(i==0 && j==0) return 1;
    if(j==0) return 0;
    int k=j;
    int n=i;
    return rekurzija(i-1, j-1)+k*rekurzija(n-1, k);
}

long long int** StirlingoviBrojeviF(int n){
    if(n<0) throw std::domain_error("Parametar ne smije biti negativan");
    long long int** matrica=nullptr;
    try{
        matrica=new long long int *[n+1]{};
        try{
            for(int i=0; i<n+1; i++)
            matrica[i]=new long long int[i+1];
            
            for(int i=0; i<n+1; i++){
                for(int j=0; j<i+1; j++){
                    matrica[i][j]=rekurzija(i, j);
                }
            }
            return matrica;
        } catch(std::range_error){
            for(int i=0; i<n+1; i++) delete[] matrica[i];
            delete[] matrica;
            throw ;}
    }catch(...){
        
       throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
}
long long int** StirlingoviBrojeviK(int n){
    if(n<0) throw std::domain_error("Parametar ne smije biti negativan");
    long long int** matrica=nullptr;
    try{
        matrica=new long long int* [n+1]{};
        try{
            matrica[0]=new long long int[(n+1)*(n+2)/2];
            for(int i=1; i<n+1; i++)
              matrica[i]=matrica[i-1]+i;
            for(int i=0; i<n+1; i++){
                for( int j=0; j<i+1; j++){
                    matrica[i][j]=rekurzija(i, j);
                }
            }
            return matrica;
        } catch(std::range_error e){
            
            delete[] matrica;
            throw;
        }
    }catch(...){
       throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    } 
}
int BrojCifara(long long int broj){
    if(broj<=9) return 1;
    int brojac{};
    while(broj!=0){
        broj/=10;
        brojac++;}
    return brojac;
}
 
int NajsiriBroj(long long int** matrica, int n){
    if(n<0) throw std::domain_error("Parametar ne smije biti negativan");
    int max=0;
    for(int i=0; i<n+1; i++){
        for(int j=0; j<i+1; j++){
            if(BrojCifara(matrica[i][j])>max) max=BrojCifara(matrica[i][j]);
        }
    }max++;
    
    return max;
}      
        
int main ()
{
    
    try{
        int n;
        std::cout << "Unesite broj n: " ;
        std::cin >> n;
        
        auto mat1=StirlingoviBrojeviF(n);
        auto mat2=StirlingoviBrojeviK(n);
       // std::cout<<"Najsiri broj: "<<NajsiriBroj(mat1,15);

        int naj=NajsiriBroj(mat1, n);
        std::cout << "\nStirlingovi brojevi - fragmentirana alokacija: " << std::endl;
        for( int i=0; i<n+1; i++){
            for(int j=0; j<i+1; j++){
                std::cout<<std::setw(naj)<<mat1[i][j];
            }
            std::cout << std::endl;
        }
        std::cout  << std::endl;
        std::cout << "Stirlingovi brojevi - kontinualna alokacija: " << std::endl;
        for( int i=0; i<n+1; i++){
            for(int j=0; j<i+1; j++){
                std::cout<<std::setw(NajsiriBroj(mat1, n))<<mat2[i][j];
            }
            std::cout << std::endl;
        }
        for(int i=0; i<n+1; i++) delete[] mat1[i];
        delete[] mat1;
        delete[] mat2[0];
        delete[] mat2;
        return 0;
    }
    catch(std::domain_error e){
        std::cout << "Izuzetak: " << e.what() << "!";
    }
    catch(std::range_error ee){
        std::cout << "Izuzetak: " << ee.what() << "!" << std::endl;
    }
	return 0;
}