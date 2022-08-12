#include <iostream>

using namespace std;

 class Person
 {
 private:
   string namn;
   double betalat_andras;
   double skyldig;

 public:
   Person();
   Person(const string &inNamn, double inBetalat_andras, double inSkyldig);
   string hamtaNamn();
   double hamtaBetalat();
   double hamtaSkyldig();
   void   skrivUt(ostream &os);
};

Person::Person(){
    namn = "";
    betalat_andras = 0;
    skyldig = 0;
}

Person::Person(const string &inNamn, double inBetalat_andras, double inSkyldig){
    namn = inNamn;
    betalat_andras = inBetalat_andras;
    skyldig = inSkyldig;
}

string Person::hamtaNamn(){
    return namn;
}

double Person::hamtaBetalat(){
    return betalat_andras;
}

double Person::hamtaSkyldig(){
    return skyldig;
}

void Person::skrivUt(ostream &os){
    //os << "skriver ut namn och hur mycket hen har BETALAT och ar SKYLDIG" << endl;

    string taEllerLagga = "",franEllerTill = "";
    double summa = 50000000000000000000;

    if(betalat_andras < skyldig){
        taEllerLagga = "Skall lagga ";
        franEllerTill = " till potten!";

        summa = skyldig - betalat_andras;
    }
    else
    {
        taEllerLagga = "Skall ha ";
        franEllerTill = " fran potten!";

        summa = betalat_andras - skyldig;
    }

    os << namn << " ligger ute med " << betalat_andras << " och ar skyldig " << skyldig << ". " << taEllerLagga << summa << franEllerTill << endl;
}
