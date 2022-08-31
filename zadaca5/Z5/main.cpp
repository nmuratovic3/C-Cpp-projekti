//TP 2018/2019: Zadaća 5, Zadatak 5
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <new>
using namespace std;
template <typename TipEl>
class Matrica
{
	int br_redova, br_kolona;
	TipEl **elementi;
	char ime_matrice;
	static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
	static void DealocirajMemoriju(TipEl **elementi, int br_redova);
	void KopirajElemente(TipEl **elementi);
public:
	Matrica(int br_redova, int br_kolona, char ime = 0);
	Matrica(const Matrica &m);
	Matrica(const char ime[], bool istina){
	    if(!istina){
	         ifstream ucitaj(ime);
   if(!ucitaj) throw logic_error("Trazena datoteka ne postoji");
   int kolone{}, redovi{};
   TipEl broj;
   char znak;
   while(ucitaj.get()!='\n' && !ucitaj.eof()){
       ucitaj>>broj>>znak; kolone++;}
   while(1) {
            if(ucitaj.get()=='\n') redovi++;
            if(ucitaj.eof())break;
        }
        br_kolona=kolone;
        br_redova=redovi;
        ucitaj.close();
        ifstream ucitaj1(ime);
        AlocirajMemoriju(br_redova,br_kolona);
    for(int i=0; i<redovi; i++){
        for(int j=0; j<kolone; j++){
            ucitaj1>>broj>>znak;
            if(!ucitaj1) throw logic_error("Datoteka sadrzi besmislene podatke");
            elementi[i][j]=broj;
        }
    }}}
	void SacuvajUBinarnuDatoteku(const char ime[]);
	void SacuvajUTekstualnuDatoteku(const char ime[]);
	void ObnoviIzBinarneDatoteke(const char ime[]);
	void ObnoviIzTekstualneDatoteke(const char ime[]);
	Matrica(Matrica &&m);
	~Matrica()
	{
		DealocirajMemoriju(elementi, br_redova);
	}
	Matrica &operator =(const Matrica &m);
	Matrica &operator =(Matrica &&m);
   
	TipEl* &operator[] (int indeks)
	{
		return elementi[indeks];
	}
	TipEl* operator[] (int indeks) const
	{
		return elementi[indeks];
	}
	TipEl &operator ()(int i, int j){
		if(i<=0 || i>br_redova || j<=0 || j>br_kolona) throw range_error("Neispravan indeks");
		return elementi[i-1][j-1];
	}
	TipEl operator ()(int i, int j)const{
		if(i<=0 || i>br_redova || j<=0 || j>br_kolona) throw range_error("Neispravan indeks");
		return elementi[i-1][j-1];
	}
	template <typename Tip>
	friend std::istream &operator >>(std::istream &tok, Matrica<Tip> & m)
	{
		for(int i = 0; i < m.br_redova; i++){
			for(int j = 0; j < m.br_kolona; j++) {
				std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
				tok >> m.elementi[i][j];
			}
		}
		return tok;
	}
	template <typename Tip>
	friend std::ostream &operator <<(std::ostream &tok, Matrica<Tip>& m)
	{
		auto rez(tok.width());
		for(int i = 0; i < m.br_redova; i++) {
			for(int j = 0; j < m.br_kolona; j++)
				tok <<setw(rez) << m.elementi[i][j];
			tok << std::endl;
		}
		return tok;
	}
		template <typename Tip>
	friend Matrica<Tip> operator *(const Matrica<Tip> &m1, const Matrica<Tip> &m2)
	{
		if(m1.br_kolona!=m2.br_redova) throw domain_error("Matrice nisu saglasne za mnozenje");
		Matrica<Tip> m3(m1.br_redova, m2.br_kolona);
		for(int i=0; i<m1.br_redova; i++) {
			for(int j=0; j<m2.br_kolona; j++) {
				m3.elementi[i][j]=0;
				for(int k=0; k<m1.br_redova; k++) m3.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
			//	m2.elementi[i][j]=suma;
			}
		}
		return m3;
	}
		template <typename Tip>
    friend Matrica<Tip> operator+(const Matrica<Tip> &m1, const Matrica<Tip> &m2)
{
	if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	Matrica<Tip> m3(m1.br_redova, m1.br_kolona);
	for(int i = 0; i < m1.br_redova; i++){
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];}
	return m3;
}
template <typename Tip>
friend Matrica<Tip> operator-(const Matrica<Tip> &m1, const Matrica<Tip> &m2)
{
	if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	Matrica<Tip> m3(m1.br_redova, m1.br_kolona);
	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
	return m3;
}
	
	
	
template <typename Tip>
friend Matrica<Tip> operator +=( Matrica<Tip> &m1, const Matrica<Tip> &m2)
{
	m1=m1+m2;
	return m1;
}
template <typename Tip>
friend Matrica<Tip> operator -=( Matrica<Tip> &m1, const Matrica<Tip> &m2)
{
	m1=m1-m2;
	return m1;
}
template <typename Tip>
friend Matrica<Tip> operator *=( Matrica<Tip> &m1, const Matrica<Tip> &m2)
{
	m1=m1*m2;
	return m1;
}
template <typename Tip>
	friend Matrica<Tip> operator*(int faktor,const Matrica<Tip> &m)
    {
	Matrica<Tip> krajnja(m.br_redova, m.br_kolona);
	for(int i=0; i<m.br_redova; i++)
		for(int j=0; j<m.br_kolona; j++) {
			krajnja.elementi[i][j]=m.elementi[i][j]*faktor;
		}
	return krajnja;
}


	template <typename Tip>
	friend Matrica<Tip> operator*(const Matrica<Tip> &m, int faktor){
	Matrica<Tip> krajnja(m.br_redova, m.br_kolona);
	for(int i=0; i<m.br_redova; i++)
		for(int j=0; j<m.br_kolona; j++) {
			krajnja.elementi[i][j]=m.elementi[i][j]*faktor;
		}
	return krajnja;
}
    

template <typename Tip>
friend Matrica<Tip> operator *=(Matrica<Tip> &m, int f){
	for(int i=0; i<m.br_redova; i++) {
			for(int j=0; j<m.br_kolona; j++) 
			   m.elementi[i][j]*=f;
	}
	return m;
}
operator string() const{
	string s("{");
	for(int i=0; i<br_redova; i++){
		s+="{";
		for(int j=0; j<br_kolona; j++){
			s+=to_string(int(elementi[i][j]));
			if(j!=br_kolona-1) s+=",";
		}
		if(i!=br_redova-1) s+="},";
		else s+="}";
	}
	s+="}";
	return s;
}

};
template<typename Tip>
void Matrica<Tip>::SacuvajUTekstualnuDatoteku(const char ime[]){
    ofstream upisi(ime);
    if(!upisi) throw logic_error ("Trazena datoteka ne postoji");
    Tip broj;
    for(int i=0; i<br_redova; i++){
        for(int j=0; j<br_kolona-1; j++){
            upisi << elementi[i][j] << ",";
            if(!upisi) throw logic_error("Problemi sa upisom u datoteku");
        }
        upisi << elementi[i][br_kolona-1] << endl;
        if(!upisi) throw logic_error("Problemi sa upisom u datoteku");
    }
}
template<typename Tip>
void Matrica<Tip>::SacuvajUBinarnuDatoteku(const char ime[]){
    ofstream upisi(ime, ios::binary);
        if(!upisi) throw logic_error ("Trazena datoteka ne postoji");

    upisi.write(reinterpret_cast<const char*>(this), sizeof *this);
    for(int i=0; i<br_redova; i++)
       for(int j=0; j<br_kolona; j++)
           upisi.write(reinterpret_cast<char*>(elementi[i][j]), sizeof(Tip));
    if(!upisi) throw logic_error("Problemi sa upisom u datoteku");
}
template<typename Tip>
void Matrica<Tip>::ObnoviIzTekstualneDatoteke(const char ime[]){
   ifstream ucitaj(ime); 
   if(!ucitaj) throw logic_error("Trazena datoteka ne postoji");
   for(int i=0; i<br_redova; i++) delete[] elementi[i];
   delete[] elementi;
   int kolone{}, redovi{1};
   Tip broj;
   char znak;
   while(ucitaj.get()!='\n' && !ucitaj.eof()){
       ucitaj>>broj>>znak; kolone++;}
   while(1) {
            if(ucitaj.get()=='\n') redovi++;
            if(ucitaj.eof())break;
        }
        br_kolona=kolone;
        br_redova=redovi;
        ucitaj.close();
        ifstream ucitaj1(ime);
        AlocirajMemoriju(br_redova,br_kolona);
    for(int i=0; i<redovi; i++){
        for(int j=0; j<kolone; j++){
            ucitaj1>>broj>>znak;
            if(!ucitaj1) throw logic_error("Datoteka sadrzi besmislene podatke");
            elementi[i][j]=broj;
        }
    }
          
}
template<typename Tip>
void ObnoviIzBinarneDatoteke(const char ime[]){}
template <typename TipEl>
TipEl ** Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona)
{
	TipEl **elementi = new TipEl*[br_redova] {};
	try {
		for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
	} catch(...) {
		DealocirajMemoriju(elementi, br_redova);
		throw;
	}
	return elementi;
}
template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova)
{
	for(int i = 0; i < br_redova; i++) delete[] elementi[i];
	delete[] elementi;
}
template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :
	br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
	elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi)
{
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			Matrica::elementi[i][j] = elementi[i][j];
}
template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), ime_matrice(m.ime_matrice),
	elementi(AlocirajMemoriju(m.br_redova, m.br_kolona))
{
	KopirajElemente(m.elementi);
}
template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice)
{
	m.br_redova = 0;
	m.elementi = nullptr;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m)
{
	if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
		TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
		DealocirajMemoriju(elementi, br_redova);
		elementi = novi_prostor;
	} else if(br_redova > m.br_redova)
		for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
	br_redova = m.br_redova;
	br_kolona = m.br_kolona;
	ime_matrice = m.ime_matrice;
	KopirajElemente(m.elementi);
	return *this;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m)
{
	std::swap(br_redova, m.br_redova);
	std::swap(br_kolona, m.br_kolona);
	std::swap(ime_matrice, m.ime_matrice);
	std::swap(elementi, m.elementi);
	return *this;
}


int main ()
{
	return 0;
}