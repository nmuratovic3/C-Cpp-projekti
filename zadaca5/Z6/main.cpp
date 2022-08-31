//TP 2018/2019: Zadaća 5, Zadatak 6
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <string>
#include <functional>
using namespace std;
template <typename TipElemenata>
void SortirajBinarnuDatoteku(const char ime_datoteke[],std::function<bool(TipElemenata, TipElemenata)> kriterij= std::less<TipElemenata>())
{
    fstream ulazni_tok (ime_datoteke, ios::in | ios::out | ios::binary);
    if(!ulazni_tok) throw logic_error("Datoteka ne postoji");
    ulazni_tok.seekg(0, ios::end);
    int duzina=ulazni_tok.tellg();
    int broj_el=duzina/sizeof(TipElemenata);
    TipElemenata veci, manji;
    for (int i=0; i<broj_el-1; i ++) {
        for(int j=i+1; j<broj_el; j++) {
            ulazni_tok.seekg(i*int(sizeof(TipElemenata)));
            ulazni_tok.read(reinterpret_cast<char*>(&veci), sizeof veci);
            ulazni_tok.seekg(j*int(sizeof(TipElemenata)));
            ulazni_tok.read(reinterpret_cast<char*>(&manji), sizeof manji);
            if(!ulazni_tok)throw logic_error ("Problemi u pristupu datoteci");
            if(!kriterij(veci, manji)) {
                ulazni_tok.seekp(j*int(sizeof(TipElemenata)));
                ulazni_tok.write(reinterpret_cast<char*>(&veci), sizeof (manji));
                ulazni_tok.seekp(i*int(sizeof(TipElemenata)));
                ulazni_tok.write(reinterpret_cast<char*>(&manji), sizeof veci);
            }
        }
    }
}
int main ()
{
    

    ofstream ulazni_tok("BROJEVI.DAT", std::ios::binary);
   ulazni_tok.close();
    SortirajBinarnuDatoteku<int>("BROJEVI.DAT",  [](int x, int y) { return x > y; });
    return 0;
}
