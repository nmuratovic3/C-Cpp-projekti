//TP 2018/2019: Zadaća 3, Zadatak 1
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <functional>
using namespace std;
bool NalaziSe(std::vector<std::pair<double,double>> vek)
{
    for(int i=0; i<vek.size(); i++) {
        for(int j=i+1; j<vek.size(); j++) {
            if(abs(vek.at(i).first-vek.at(j).first)<0.001) return true;
        }
    }
    return false;
}
double Pomocna(double x, double xj,  double xi)
{
    return (x-xj)/(xi-xj);
}

std::function<double(double)>LagrangeovaInterpolacija(const std::vector<std::pair<double,double>> &vek)
{
   // if(vek.size()==0) return 0;
    if(NalaziSe(vek)) throw domain_error("Neispravni cvorovi");
    return [=](double x) {
       // if(vek.size()==0) return 0;
        double pomocna=0;
        for(int i=0; i<vek.size(); i++) {
            double pom=1;
            for(int j=0; j<vek.size(); j++) {
                if(i==j) continue;
                else
                    pom*=Pomocna(x, vek.at(j).first, vek.at(i).first);
            }
            pomocna+=pom*vek.at(i).second;
        }
        return pomocna;
    };
}
std::function<double(double)>LagrangeovaInterpolacija(double f(double), double xmin, double xmax, double delta)
{
    if(xmin>xmax) throw domain_error("Nekorektni parametri");
    if(delta<=0) throw domain_error("Nekorektni parametri");

    return [f,xmin,xmax,delta](double x) {
        auto pom=xmin;
        vector<pair<double,double>> vek;
        double nesto=0;
        while(xmax-pom>=delta) {
            nesto=f(pom);
            vek.push_back({pom, nesto});
            pom+=delta;
        }
        double pomocna=0;
        for(int i=0; i<vek.size(); i++) {
            double pom=1;
            for(int j=0; j<vek.size(); j++) {
               if(i==j) continue;
               else
                    pom*=Pomocna(x, vek.at(j).first, vek.at(i).first);
            }
            pomocna+=pom*vek.at(i).second;
        }
        return pomocna;
    };

}
double MojaF(double x)
{
    return x*x+sin(x)+log(x+1);
}
int main ()
{
    try {
        int broj;
        cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
        cin >> broj;
        if(broj==1) {
            int k;
            cout << "Unesite broj cvorova: ";
            cin >> k;
            if(k<=0) {
                cout<<"Broj cvorova mora biti pozitivan broj!";
                return 1;
            }
            std::vector<pair<double,double>> vek;
            double prvi, drugi;
            cout << "Unesite cvorove kao parove x y: ";
            cin >> prvi;
            cin >> drugi;
            auto min=prvi;
            auto max=prvi;vek.push_back({prvi, drugi});
            for(int i=0; i<k-1; i++) {
                cin >> prvi;
                cin >> drugi;
                if(prvi>max) max=prvi;
                if(prvi<min) min=prvi;
                vek.push_back({prvi, drugi});

            }
            double argument;
            auto ki=LagrangeovaInterpolacija(vek);
            cout << "Unesite argument (ili "<<'"'<<"kraj"<<'"'<<" za kraj): ";
            cin >> argument;

            while(cin) {
                cout << "f(" << argument <<") = "<< ki(argument);
                if(min>argument || max<argument) cout << " [ekstrapolacija]";
                cout <<endl;
                cout << "Unesite argument (ili "<<'"'<<"kraj"<<'"'<<" za kraj): ";
                cin >> argument;
            }
        } else if(broj==2) {
            cout << "Unesite krajeve intervala i korak: ";
            double x1, x2, delta;
            cin >> x1 >> x2 >> delta;
            auto  jos=x1;
            auto ti=LagrangeovaInterpolacija(MojaF, jos, x2, delta);
            std::vector<pair<double,double>>vek;
            while(x2-x1>=delta) {
                vek.push_back({x1,x1*x1+sin(x1)+log(x1+1)});
                x1+=delta;
            }
            double argument;
            auto ki=LagrangeovaInterpolacija(vek);
            cout << "Unesite argument (ili "<<'"'<<"kraj"<<'"'<<" za kraj): ";
            cin >> argument;
            while(cin) {
                cout << "f(" << argument << ") = " << ki(argument) << " P(" <<
                     argument << ") = " << ti(argument) << endl;
                cout << "Unesite argument (ili "<<'"'<<"kraj"<<'"'<<" za kraj): ";
                cin >> argument;

            }
        } else cout<<"Nepoznat slucaj!";
    } catch(std::domain_error e) {
        cout<< "IZUZETAK: " << e.what()<<"!";
    } catch(...) {
    }

    return 0;
}
