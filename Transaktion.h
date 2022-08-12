class Transaktion
{
    private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int antal_kompisar;
    string kompis_namn;

    //this is dynamic
    vector <string>kompisar;

    public:
    Transaktion();
    Transaktion(const string &inDatum, string inTyp, string inNamn, double inBelopp, int inAntal_Kompisar, string kompis_namn,vector <string> inKompisar);
    ~Transaktion();
    string hamtaNamn();
    double hamtaBelopp();
    int    hamtaAntalKompisar();
    bool   finnsKompis(const string &namnet);
    bool   lasIn(istream &is); //istream stands for IN STREAM (information going to you) and ostream stands for information going OUT
    void   skrivUt();
    void   skrivTitel(ostream &os);

    string hamtaArr(){
        return kompisar[0];
    }

    void printVannLista(){
        cout << "Antal kompisar: " << antal_kompisar << endl;
        for(int i = 0;i < antal_kompisar;i++){
            cout << i << ": " << kompisar[i] << endl;
        }
    }

    void hamtaFirstIArray(){

        cout << "PRINTAR KOMPIS: " << endl;

        for(int i = 0;i < antal_kompisar;i++){
            cout << "Kompis: " << kompisar[i] << endl;
        }
    }

    bool finnsIarray(string namnet){
        for(int i = 0;i < antal_kompisar;i++){
            if(namnet == kompisar[i]){
                return true;
            }
        }
        return false;
    }

};

Transaktion::Transaktion(){
    string datum = "";
    string typ = "";
    string namn = "";
    double belopp = 0;
    int antal_kompisar = 0;
    string kompis_namn = "";
    vector <string>kompisar = {};
}

Transaktion::Transaktion(const string &inDatum, string inTyp, string inNamn, double inBelopp, int inAntal_Kompisar, string inKompis_namn,vector <string> inKompisar){
    datum = inDatum;
    typ = inTyp;
    namn = inNamn;
    belopp = inBelopp;
    antal_kompisar = inAntal_Kompisar;
    kompis_namn = inKompis_namn;

    //cout << "NAMN AR: " << namn << endl;
    for(int i = 0;i < antal_kompisar;i++){
        //cout << "Added a friend " << antal_kompisar << " Name: " << inKompisar[i] << endl;
        kompisar.insert(kompisar.end(),inKompisar[i]);
        //kompisar[i] = inKompisar[i];
        //cout << inKompisar[i] << endl;
    }

}

Transaktion::~Transaktion(){
    //cout << "Destroyed Transaktion" << endl;
}

string Transaktion::hamtaNamn(){
    return namn;
}

double Transaktion::hamtaBelopp(){
    return belopp;
}

int Transaktion::hamtaAntalKompisar(){
    return antal_kompisar;
}

bool Transaktion::finnsKompis(const string &namnet){
    cout << "kollar genom kompisar array och returnerar true/false" << endl;
}

bool Transaktion::lasIn(istream &is){
    //cout << "laser in en transaktion fran tagentbordet, bool for att den anropas fran Klass TransaktionsLista" << endl;

    char x = ' ';
    string totalString = "";
    bool reachedLetters = false;
    int arrayPos = 0;

    is >> datum >> typ >> namn >> belopp >> antal_kompisar;
    getline(cin,kompis_namn);

    //cout << "\n  Hela kompis namn: " << kompis_namn << endl;

    for(int i = 0;i < kompis_namn.length()+1;i++){
        x = kompis_namn[i];

        if(x != ' '){
            reachedLetters = true;
        }

        if(reachedLetters == true){
            if(x == ' '){
                //cout << "space detected! Resetting string!" << endl;
                //cout << "Total string was (remove strings pls): " << totalString << endl;

                totalString.erase(remove(totalString.begin(), totalString.end(), ' '), totalString.end());
                kompisar.insert(kompisar.end(),totalString);
                arrayPos++;

                totalString = "";
                x = ' ';
            }
            else if(i == kompis_namn.length()-1){
                //cout << "Length is: " << kompis_namn.length() << " Last letter is: " << kompis_namn[kompis_namn.length()-1] << endl;
                totalString = totalString + kompis_namn[kompis_namn.length()-1];
                //cout << "Reached end of string! Current string is: " << totalString << endl;
                totalString.erase(remove(totalString.begin(), totalString.end(), ' '), totalString.end());

                //had to change this
                kompisar.insert(kompisar.end(),totalString);




            }
            else{
                totalString = totalString + x;
            }
        }
    }
}

void Transaktion::skrivUt(){
    //cout << "skriver ut om transaktionen bade på skarm och fil" << endl;
    cout << datum << " " << typ << " " << namn << " " << belopp << " " << antal_kompisar << " " << kompis_namn << endl;
}

void Transaktion::skrivTitel(ostream &os){
    os << "Ange i foljande format\nDatum Typ Namn Belopp Antal_Kompisar Kompis_Namn" << endl;
}
