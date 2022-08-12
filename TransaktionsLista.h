#ifndef TRANSAKTIONSLISTA_H_INCLUDED
#define TRANSAKTIONSLISTA_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

 class TransaktionsLista
 {
 private:
   int antal_transaktioner;

   vector<Transaktion> transaktionerr;

 public:
   TransaktionsLista();
   ~TransaktionsLista();
   void   lasIn(istream & is);
   void   skrivUt(ostream & os);
   void   laggTill(Transaktion & t);
   double totalKostnad();
   double liggerUteMed(const string &namnet);
   double arSkyldig(const string &namnet);
   PersonLista fixaPersoner(){
       string namn = "";

        double liggerUt = 0, skyldigAv = 0;
        PersonLista personlista;

        for(int i = 0;i < antal_transaktioner;i++){
            namn = transaktionerr[i].hamtaNamn();
            //cout << namn <<  endl;

            if(personlista.finnsPerson(namn)==false){
                //cout << "ligger ute med " << liggerUteMed(namn) << endl;
                //cout << "skyldig med " << arSkyldig(namn) << endl;

                liggerUt = liggerUteMed(namn);
                skyldigAv = arSkyldig(namn);

                Person person(namn,liggerUt,skyldigAv);

                personlista.laggTill(person);
            }
        }
        //Ska bara kolla att skyldig och betalat_andras ar samma summa.
        //personlista.skrivUtOchFixa(cout);
        return personlista;
   }
 };

TransaktionsLista::TransaktionsLista(){
    antal_transaktioner = 0;
    transaktionerr = {};
}

TransaktionsLista::~TransaktionsLista(){
     //cout << "Destroyed TransaktionsLista" << endl;
}

void TransaktionsLista::lasIn(istream & is){
    //seems like some of the stuff here should be moved to bool lasin() in the Transaktion class

    string input;
    string text;
    string text2;

    while (getline(is,input)){
        string datum = "";
        string typ = "";
        string namn = "";
        double belopp = 0.0;
        int antal_kompisar = 0;
        string kompis_namn = "";
        vector <string> kompisArr = {};

        int antalGangerLooped = 0;
        char x = ' ';
        int arrayPosition = 0;

        for(int i = 0;i < input.length();i++){
            x = input[i];
            if(x != ' '){
                text = text + x;
            }
            else{
                //continue;
            }

            if(x==' ' && text != ""){
                //cout << "space! String is: " << text << endl;

                if(antalGangerLooped == 0 && text!= " "){
                    //erases all whitespace from the thing (we dont want this)
                    text.erase(remove(text.begin(), text.end(), ' '), text.end());
                    //cout << text << " is datum" << endl;

                    datum = text;

                    antalGangerLooped++;
                    text = "";
                }
                    else if(antalGangerLooped == 1){
                        text.erase(remove(text.begin(), text.end(), ' '), text.end());
                        //cout << text << " is typ" << endl;

                        typ = text;

                        antalGangerLooped++;
                        text = "";
                        }
                        else if(antalGangerLooped == 2){
                            text.erase(remove(text.begin(), text.end(), ' '), text.end());
                            //cout << text << " is namn" << endl;

                            namn = text;

                            antalGangerLooped++;
                            text = "";
                        }
                            else if(antalGangerLooped == 3){
                                text.erase(remove(text.begin(), text.end(), ' '), text.end());
                                //cout << text << " is belopp" << endl;

                                belopp = stod(text);

                                antalGangerLooped++;
                                text = "";
                            }
                                    else if(antalGangerLooped == 4){
                                        text.erase(remove(text.begin(), text.end(), ' '), text.end());
                                        //cout << text << " is antal kompisar" << endl;

                                        antal_kompisar = stoi(text);

                                        antalGangerLooped++;
                                        text = "";
                                    }
                                        else if(antalGangerLooped <= 5){
                                            //cout << "Vann: " << text << endl;


                                            kompisArr.insert(kompisArr.end(),text);
                                            arrayPosition++;

                                            kompis_namn = kompis_namn + " " + text;

                                            text = "";
                                        }

                else{
                    //cout << "somethings wrong";
                }
            }

            if(i==input.length()-1){
                //cout << "END OF LINE! List of friends are: " << text << endl;

                kompis_namn = kompis_namn + " " + text;

                //kompisArr[arrayPosition] = text;
                kompisArr.insert(kompisArr.end(),text);
                text = "";




                transaktionerr.insert(transaktionerr.end(),Transaktion(datum,typ, namn,belopp,antal_kompisar,kompis_namn,kompisArr));

                antal_transaktioner++;

            }
        }
    }
}

void   TransaktionsLista::skrivUt(ostream & os){

    os << "Skriver ut alla transaktioner" << endl;
    os << "Antal transaktioner: " << antal_transaktioner << endl;
    for(int i = 0;i < antal_transaktioner;i++)
    {
        transaktionerr[i].skrivUt();
    }
}

void TransaktionsLista::laggTill(Transaktion & t){
    //cout << "lagger till en transaktion SIST  i arrayen transaktioner" << endl;

    transaktionerr[antal_transaktioner] = t;
    antal_transaktioner++;
}

double TransaktionsLista::totalKostnad(){
    //cout << "beraknar och returnerar summan pa hela resan" << endl;
    double totalaKostnad = 0.0,transaktionKostnad = 0.0;

    for(int i = 0;i < antal_transaktioner;i++){
        transaktionKostnad = transaktionerr[i].hamtaBelopp();
        totalaKostnad = totalaKostnad + transaktionKostnad;
    }

    return totalaKostnad;
}

double TransaktionsLista::liggerUteMed(const string &namnet){
    //cout << "raknar ut hur mycket nagon med inparametern namnet har betalat for resan - Ga genom alla transaktioner men SKA MINUS DET SOM DE HAR BETALAT" << endl;

    double summa = 0.;
   for (int i = 0; i < antal_transaktioner; i++)
     if (transaktionerr[i].hamtaNamn() == namnet)
       summa += transaktionerr[i].hamtaBelopp() *
                (1.0 - 1.0 / (transaktionerr[i].hamtaAntalKompisar() + 1));
   return summa;

}

double TransaktionsLista::arSkyldig(const string &namnet){
    //cout << "raknar ut hur mycket nagon med inparametern namnet ar skyldig for resan" << endl;
    string loopNamn = "";
    int antalKompisar = 0;
    double totalSumma = 0, relativSumma = 0;
    bool hittatNamnet = false;

    //cout << "Namnet ar: " << namnet << endl;

    for(int i = 0;i<antal_transaktioner;i++){
        antalKompisar = transaktionerr[i].hamtaAntalKompisar();
        //cout << "Antal kompisar ar: " << antalKompisar << endl;

        hittatNamnet = transaktionerr[i].finnsIarray(namnet);

        if(hittatNamnet == true){
            //cout << "namnet ar hittat i kompis listan" << endl;
            relativSumma = transaktionerr[i].hamtaBelopp();
            antalKompisar = antalKompisar+1;

            relativSumma = relativSumma/antalKompisar;
            totalSumma = relativSumma + totalSumma;
        }
        else{
            //cout << "inte i array" << endl;
        }
    }

    return totalSumma;

}

#endif // TRANSAKTIONSLISTA_H_INCLUDED
