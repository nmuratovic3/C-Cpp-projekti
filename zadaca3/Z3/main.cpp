//TP 2018/2019: Zadaća 3, Zadatak 3
#include <iostream>
#include <iomanip>
//KOPIRANO SA PREDAVANJA
#include <stdexcept>
#include <new>
#include <vector>
template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!
    char ime_matrice;
};
template <typename TipElemenata>
void UnistiMatricu(const Matrica<TipElemenata> &mat)
{
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
   // mat.elementi = nullptr;
}
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona, char ime = 0)
{
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
    mat.ime_matrice = ime;
    mat.elementi = new TipElemenata*[br_redova] {};
    try {
        for(int i = 0; i < br_redova; i++)
            mat.elementi[i] = new TipElemenata[br_kolona];
    } catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}
template <typename TipElemenata>
void UnesiMatricu(Matrica<TipElemenata> &mat)
{
    for(int i = 0; i < mat.br_redova; i++)
        for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << mat.ime_matrice
                      << "(" << i + 1 << "," << j + 1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}
template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost=6, bool treba_brisati=false)
{
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++)
            std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost) << mat.elementi[i][j];
        std::cout << std::endl;
    }
    if(treba_brisati) UnistiMatricu(mat);
}
template <typename TipElemenata>
Matrica <TipElemenata>MnoziSaSkalarom(const Matrica<TipElemenata> &mat, double n){
    auto m=StvoriMatricu<TipElemenata>(mat.br_redova,mat.br_kolona);
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++){
            m.elementi[i][j]=n*mat.elementi[i][j];
        }
    }
   // UnistiMatricu(mat);
    return m;
}
    
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2)
{
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
}
template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2){
    if(m1.br_kolona !=m2.br_redova) throw std::domain_error ("Matrice nisu saglasne za mnozenje");
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona);
    for(int i=0; i<m1.br_redova; i++){
        for(int j=0; j<m2.br_kolona; j++){
            TipElemenata suma=0;
            for(int k=0; k<m2.br_redova; k++) suma+=m1.elementi[i][k]*m2.elementi[k][j];
            m3.elementi[i][j]=suma;
        }
    }
    return m3;
}using namespace std;
template <typename TipElemenata>
Matrica<TipElemenata>MatricniHarmonijskiPolinom(Matrica<TipElemenata> m1, int n){
    if(m1.br_redova!=m1.br_kolona) throw std::domain_error("Matrica nije kvadratna");
    if(n<0) throw std::domain_error("Pogresan parametar n");
    Matrica<TipElemenata>** stepeni=nullptr;
    Matrica<TipElemenata>** zbirovi=nullptr;
    Matrica<TipElemenata>** skalarne=nullptr;
    try {
        stepeni=new Matrica<TipElemenata>*[n]{};
    }
    catch (std::range_error) {
       cout<<"Problemi s memorijom";
    }
    try {
        zbirovi=new Matrica<TipElemenata>*[n]{};
    }
    catch (std::range_error) {
        delete[] stepeni;
        cout<<"Problemi s memorijom";
    }
    try{
        skalarne=new Matrica<TipElemenata>*[n]{};
    }
    catch(std::range_error){
        delete stepeni;
        delete zbirovi;
        cout<<"Problemi s memorijom";
    }
    
    *stepeni[0]=StvoriMatricu(m1.br_kolona, m1.br_kolona);
    *zbirovi[0]=StvoriMatricu(m1.br_kolona, m1.br_kolona);
    *skalarne[0]=StvoriMatricu(m1.br_kolona, m1.br_kolona);
    auto pocetna=m1;
      auto pom=m1;
    for(int i=2; i<=n; i++){
        *stepeni[i-1]=ProduktMatrica(*stepeni[i-2], m1);
        *skalarne[i-1]=MnoziSaSkalarom(*stepeni[i-1], 1./i);
        *zbirovi[i-1]=ZbirMatrica(*zbirovi[i-2], *skalarne[i-1]);
    
       // IspisiMatricu(pocetna,9,9);
    }
    auto pomocna=zbirovi[n-1];
    for(int i=0; i< n; i++){
        delete zbirovi[i];
        delete stepeni[i];
        delete skalarne[i];
    }
    delete[] stepeni; delete[] skalarne; 
    delete[] zbirovi;
        return *pomocna;
}
             
            
   /* 

template <typename TipElemenata>
Matrica <TipElemenata> Jedinicna (int n){
    StvoriMatricu(n,n);
    
template <typename TipElemenata>
Matrica<TipElemenata> MatricniHarmonijskiPolinom (const Matrica<TipElemenata> &m, int n){
    if(m.br_redova!=m.br_kolona) throw std::domain_error("Matrica nije kvadratna!");
    if(n<0) throw std::domain_error("Pogresan parametar n");
    auto pom=StvoriMatricu<TipElemenata>(m.br_kolona, m.br_kolona);
    std::vector<typename std::remove_reference<decltype(pom)>::type> pokazivaci(n);
    pokazivaci[0]=
    for(int i=0; i<n; i++){
        pokazivaci[i]=ProduktMatrica
        */
int main()
{
   /* Matrica<double> a, b, c; // AUTOMATSKA INICIJALIZACIJA!!!
    int m, n;
    std::cout << "Unesi broj redova i kolona za matrice:\n";
    std::cin >> m >> n;
    try {
        a = StvoriMatricu<double>(m, n, 'A');
        b = StvoriMatricu<double>(m, n, 'B');
        std::cout << "Unesi matricu A:\n";
        UnesiMatricu(a);
        std::cout << "Unesi matricu B:\n";
        UnesiMatricu(b);
        std::cout << "Zbir ove dvije matrice je:\n";
        IspisiMatricu(c = ZbirMatrica(a, b), 7);
    } catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije!\n";
    }*/
   
    return 0;
}




