//TP 2018/2019: Zadaća 4, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <utility>

typedef std::pair<double, double> Tacka;
enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno};
enum Smjer {Nalijevo, Nadesno};
using namespace std;

class Pravougaonik
{
    Tacka t1, t2;
   
public:
    Pravougaonik(const Tacka &t1, const Tacka &t2);
    void Postavi(const Tacka &t1, const Tacka &t2);
    void Postavi(Pozicija p, const Tacka &t);
    void Centriraj(const Tacka &t);
    Tacka DajTjeme(Pozicija p) const;
    Tacka DajCentar() const;
    double DajHorizontalnu() const;
    double DajVertikalnu() const;
    double DajObim() const;
    double DajPovrsinu() const;
    static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2);
    void Transliraj(double delta_x, double delta_y);
    void Rotiraj(const Tacka &t, Smjer s);
    void Ispisi() const;
    friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
   

};
Pravougaonik::Pravougaonik(const Tacka &t1, const Tacka &t2): t1(t1), t2(t2) {}

void Pravougaonik::Postavi(const Tacka &t1, const Tacka &t2)
{
    Pravougaonik::t1=t1;
    Pravougaonik::t2=t2;
}


void Pravougaonik::Postavi(Pozicija p, const Tacka &t)
{
    if(p==GoreDesno) {
        if(t1.first>t2.first) t1.first=t.first;
        else t2.first=t.first;
        if(t1.second>t2.second) t1.second=t.second;
        else t2.second=t.second;
    } else if(p==GoreLijevo) {
        if(t1.first<t2.first) t1.first=t.first;
        else t2.first=t.first;
        if(t1.second>t2.second) t1.second=t.second;
        else t2.second=t.second;
    } else if(p==DoljeLijevo) {
        if(t1.first<t2.first) t1.first=t.first;
        else t2.first=t.first;
        if(t1.second<t2.second) t1.second=t.second;
        else t2.second=t.second;
    } else if(p==DoljeDesno) {
        if(t1.first>t2.first) t1.first=t.first;
        else t2.first=t.first;
        if(t1.second<t2.second) t1.second=t.second;
        else t2.second=t.second;
    }
}


Tacka Pravougaonik::DajTjeme(Pozicija p) const
{
    Tacka pom;
    if(p==GoreDesno || p==GoreLijevo) {
        if(t1.second>t2.second) pom.second=t1.second;
        else pom.second=t2.second;
        if(p==GoreDesno) {
            if(t1.first>t2.first) pom.first=t1.first;
            else pom.first=t2.first;
        } else {
            if(t1.first<t2.first) pom.first=t1.first;
            else pom.first=t2.first;
        }
    }
    if(p==DoljeDesno || p==DoljeLijevo) {
        if(t1.second<t2.second) pom.second=t1.second;
        else pom.second=t2.second;
        if(p==DoljeDesno) {
            if(t1.first>t2.first) pom.first=t1.first;
            else pom.first=t2.first;
        } else {
            if(t1.first<t2.first) pom.first=t1.first;
            else pom.first=t2.first;
        }
    }
    return pom;
}
Tacka Pravougaonik::DajCentar() const
{
    Tacka centar;
    double delta_x(abs(t1.first-t2.first));
    if(t1.first<t2.first) centar.first=t1.first+delta_x/2;
    else centar.first=t2.first+delta_x/2;
    delta_x=abs(t1.second-t2.second);
    if(t1.second<t2.second) centar.second=t1.second+delta_x/2;
    else centar.second=(t2.second+delta_x/2);
    return centar;
}
void Pravougaonik::Centriraj(const Tacka &t)
{
    double x1=DajCentar().first-t1.first;
    double y1=DajCentar().second-t1.second;
    double x2=DajCentar().first-t2.first;
    double y2=DajCentar().second-t2.second;
    t1.first=t.first+x1;
    t1.second=t.second+y1;
    t2.first=t.first+x2;
    t2.second=t.second+y2;/*
    double x = (*this).DajCentar().first-t.first;
    double y = (*this).DajCentar().second-t.second;
    t1.first+=x;
    t1.second+=y;
    t2.first+=x;
    t2.second+=y;*/
}

double Pravougaonik::DajHorizontalnu() const
{
    return abs(t1.first-t2.first);
}
double Pravougaonik::DajVertikalnu() const
{
    // cout<<t1.second;
    return abs(t1.second-t2.second);
}
double Pravougaonik::DajObim() const
{
    return 2*DajHorizontalnu()+2*DajVertikalnu();
}
double Pravougaonik::DajPovrsinu() const
{
    return DajHorizontalnu()*DajVertikalnu();
}
Pravougaonik Pravougaonik::Presjek(const Pravougaonik &p1, const Pravougaonik &p2)
{
    if(DaLiSePoklapaju(p1,p2)) return p1;
    if(p1.DajTjeme(GoreDesno).first < p2.DajTjeme(GoreLijevo).first || p1.DajTjeme(DoljeDesno).second > p2.DajTjeme(GoreDesno).second
            || p1.DajTjeme(GoreLijevo).first>p2.DajTjeme(GoreDesno).first || p1.DajTjeme(GoreDesno).second< p2.DajTjeme(DoljeDesno).second
            || (p1.DajTjeme(GoreDesno).first < p2.DajTjeme(GoreDesno).first && p1.DajTjeme(GoreDesno).second < p2.DajTjeme(GoreDesno).second &&
                p1.DajTjeme(DoljeLijevo).first>p2.DajTjeme(DoljeLijevo).first && p1.DajTjeme(DoljeLijevo).second>p2.DajTjeme(DoljeLijevo).second) ||
            (p2.DajTjeme(GoreDesno).first < p1.DajTjeme(GoreDesno).first && p2.DajTjeme(GoreDesno).second < p1.DajTjeme(GoreDesno).second &&
             p2.DajTjeme(DoljeLijevo).first>p1.DajTjeme(DoljeLijevo).first && p2.DajTjeme(DoljeLijevo).second>p1.DajTjeme(DoljeLijevo).second)) throw domain_error("Pravougaonici se ne presjecaju");
    Tacka prva, druga;
    if(p1.DajTjeme(GoreDesno).second>=p2.DajTjeme(GoreDesno).second && p1.DajTjeme(DoljeLijevo).first<=p2.DajTjeme(GoreLijevo).first &&
            p1.DajTjeme(DoljeDesno).first>=p2.DajTjeme(GoreDesno).first) {
        prva=p2.DajTjeme(GoreDesno);
        druga.first=p2.DajTjeme(DoljeLijevo).first;
        druga.second=p1.DajTjeme(DoljeDesno).second;
    } else if(p1.DajTjeme(GoreDesno).second>=p2.DajTjeme(GoreDesno).second && p1.DajTjeme(DoljeLijevo).first>=p2.DajTjeme(GoreLijevo).first &&
              p1.DajTjeme(DoljeDesno).first<=p2.DajTjeme(GoreDesno).first) {
        prva.first=p1.DajTjeme(DoljeDesno).first;
        prva.second=p2.DajTjeme(GoreDesno).second;
        druga=p1.DajTjeme(DoljeLijevo);
        
        
    }else if(p2.DajTjeme(GoreDesno).second>=p1.DajTjeme(GoreDesno).second && p2.DajTjeme(DoljeLijevo).first<=p1.DajTjeme(GoreLijevo).first &&
            p2.DajTjeme(DoljeDesno).first>=p1.DajTjeme(GoreDesno).first) {
        prva=p1.DajTjeme(GoreDesno);
        druga.first=p1.DajTjeme(DoljeLijevo).first;
        druga.second=p2.DajTjeme(DoljeDesno).second;
    } else if(p2.DajTjeme(GoreDesno).second>=p1.DajTjeme(GoreDesno).second && p2.DajTjeme(DoljeLijevo).first>=p1.DajTjeme(GoreLijevo).first &&
              p2.DajTjeme(DoljeDesno).first<=p1.DajTjeme(GoreDesno).first) {
        prva.first=p2.DajTjeme(DoljeDesno).first;
        prva.second=p1.DajTjeme(GoreDesno).second;
        druga=p2.DajTjeme(DoljeLijevo);
    }
    

    else if(p1.DajTjeme(GoreDesno).first<=p2.DajTjeme(GoreDesno).first && p1.DajTjeme(GoreLijevo).first<=p2.DajTjeme(GoreLijevo).first) {

        if(p1.DajTjeme(GoreLijevo).second>=p2.DajTjeme(GoreLijevo).second && p1.DajTjeme(DoljeLijevo).second<=p2.DajTjeme(DoljeLijevo).second) {
            prva.first=p1.DajTjeme(DoljeDesno).first;
            prva.second=p2.DajTjeme(GoreDesno).second;
            druga=p2.DajTjeme(DoljeLijevo);
        } else if(p1.DajTjeme(GoreLijevo).second<=p2.DajTjeme(GoreLijevo).second && p1.DajTjeme(DoljeLijevo).second>=p2.DajTjeme(DoljeLijevo).second) {
            prva=p1.DajTjeme(GoreDesno);
            druga.first=p2.DajTjeme(GoreLijevo).first;
            druga.second=p1.DajTjeme(DoljeDesno).second;
        } else if(p1.DajTjeme(GoreLijevo).second>=p2.DajTjeme(GoreLijevo).second) {
            prva.first=p1.DajTjeme(GoreDesno).first;
            prva.second=p2.DajTjeme(GoreDesno).second;
            druga.first=p2.DajTjeme(DoljeLijevo).first;
            druga.second=p1.DajTjeme(DoljeLijevo).second;
        } else
            //(p1.DajTjeme(GoreLijevo).second<p2.DajTjeme(GoreLijevo).second)
        {
            prva=p1.DajTjeme(GoreDesno);
            druga=p2.DajTjeme(DoljeLijevo);

        }

    } else if(p1.DajTjeme(GoreDesno).first>=p2.DajTjeme(GoreDesno).first && p1.DajTjeme(GoreLijevo).first>=p2.DajTjeme(GoreLijevo).first) {

        if(p2.DajTjeme(GoreLijevo).second>=p1.DajTjeme(GoreLijevo).second && p2.DajTjeme(DoljeLijevo).second<=p1.DajTjeme(DoljeLijevo).second) {
            prva.first=p2.DajTjeme(DoljeDesno).first;
            prva.second=p1.DajTjeme(GoreDesno).second;
            druga=p1.DajTjeme(DoljeLijevo);
        } else if(p2.DajTjeme(GoreLijevo).second<=p1.DajTjeme(GoreLijevo).second && p2.DajTjeme(DoljeLijevo).second>=p1.DajTjeme(DoljeLijevo).second) {
            prva=p2.DajTjeme(GoreDesno);
            druga.first=p1.DajTjeme(GoreLijevo).first;
            druga.second=p2.DajTjeme(DoljeDesno).second;
        } else if(p2.DajTjeme(GoreLijevo).second>=p1.DajTjeme(GoreLijevo).second) {
            prva.first=p2.DajTjeme(GoreDesno).first;
            prva.second=p1.DajTjeme(GoreDesno).second;
            druga.first=p1.DajTjeme(DoljeLijevo).first;
            druga.second=p2.DajTjeme(DoljeLijevo).second;
        } else
            //(p1.DajTjeme(GoreLijevo).second<p2.DajTjeme(GoreLijevo).second)
        {
            prva=p2.DajTjeme(GoreDesno);
            druga=p1.DajTjeme(DoljeLijevo);

        }

    }
    return Pravougaonik(prva, druga);
}
void Pravougaonik::Transliraj(double delta_x, double delta_y)
{
    t1.first+=delta_x;
    t1.second+=delta_y;
    t2.first+=delta_x;
    t2.second+=delta_y;
}
void Pravougaonik::Rotiraj(const Tacka &t, Smjer s)
{
}
void Pravougaonik::Ispisi() const
{
    
    cout << "{{"<< DajTjeme(GoreLijevo).first<<"," << DajTjeme(GoreLijevo).second << "},{" << DajTjeme(DoljeDesno).first << ","<<DajTjeme(DoljeDesno).second<<"}}";
    // cout<< "{{" << t1.first << ", " << t1.second << "}," << "{" << t2.first << ", " << t2.second << "}}"<<endl;
}
bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2)
{
    //if(p1.DajGoreLijevo()==p2.DajGoreLijevo() && p1.DajDoljeDesno()==p2.DajDoljeDesno()) return true;
    if(p1.DajCentar()==p2.DajCentar() && p1.DajVertikalnu()==p2.DajVertikalnu() && p1.DajHorizontalnu()==p2.DajHorizontalnu()) return true;
    return false;
}
bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2)
{
    // cout<<Razmak(p1.t1,p1.t2);
    //cout<<p1.DajVertikalnu()<<" "<<p2.DajVertikalnu() <<" "<<p1.DajHorizontalnu() << " "<<p2.DajHorizontalnu();
    if((p1.DajVertikalnu()==p2.DajVertikalnu() && p1.DajHorizontalnu()==p2.DajHorizontalnu()) || (p1.DajHorizontalnu()==p2.DajVertikalnu() && p1.DajVertikalnu()==p2.DajHorizontalnu())) return true;
    return false;
}
bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2)
{
    //cout<<p1.DajVertikalnu()<<" "<<p2.DajVertikalnu() <<" "<<p1.DajHorizontalnu() << " "<<p2.DajHorizontalnu();
    if(p1.DajVertikalnu()==0 && p2.DajVertikalnu()==0 || p1.DajHorizontalnu()==0 && p2.DajHorizontalnu()==0 ) return true;
    if(DaLiSuPodudarni(p1,p2)) return true;
    if(p1.DajHorizontalnu()/p2.DajHorizontalnu() == p1.DajVertikalnu()/p2.DajVertikalnu() || p1.DajVertikalnu()/p2.DajHorizontalnu() == p1.DajHorizontalnu()/p2.DajVertikalnu()) return true;
    return false;
}
int main ()
{
    int n;
    cout<< "Unesite n: ";
    cin >> n;
    double prvo, drugo;
    std::pair<double, double> tjeme1, tjeme2;
    std::vector<Pravougaonik> p ;
    for(int i=0; i<n; i++) {
        cout<<"Unesite 1. tjeme pravougaonika "<<i+1 <<": ";
        cin >> prvo >> drugo;
        tjeme1.first=prvo;
        tjeme1.second=drugo;
        cout<<"Unesite 2. tjeme pravougaonika "<<i+1 <<": ";
        cin >> prvo >> drugo;
        tjeme2.first=prvo;
        tjeme2.second=drugo;
        p.push_back(Pravougaonik(tjeme1, tjeme2));
    }
    cout<<"Unesite podatke za transliranje (dx  dy): ";
    double dx,dy;
    cin>>dx>>dy;
    cout<<"Pravougaonici, nakon transformcija: \n";
    for(int i=0; i<n; i++) {
        p.at(i).Transliraj(dx,dy);
        p.at(i).Ispisi();
    }
}
