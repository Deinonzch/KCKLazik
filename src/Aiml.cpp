#include "Aiml.h"
Aiml::Aiml()
{
/*    void AIML(TaskManager *);
inline std::string trim(std::string& str)
{
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
    return str;
}
using namespace std;

struct category
{
    string pattern1;
    string template1;

};

string JakiPoziom(string tekst)
{
    string    poziom="";
    if (tekst[0]=='<')
    {
        tekst.erase(0,1);
        while (tekst[0]!='>')
        {
            poziom=poziom+tekst[0];
            tekst.erase(0,1);

        }


    }
//    else
//    {
//        while (tekst[0]!='<')
//        {
//            poziom=poziom+tekst[0];
//            tekst.erase(0,1);
//
//        }
//        JakiPoziom(tekst);
//
//
//    }

    return poziom;
}


string PomiedzyTagami(string tekst,string poziom)
{
//   bool zm=true;
//    if (tekst[0]!='<')
//    {
//        for(int i=0; i<poziom.size(); i++)
//        {
//            if (tekst[i]!=poziom[i])zm=false;
//        }
//
//        tekst.erase(0,poziom.size());
//        //return poziom;
//
//    }

    string slowo="";
    if(tekst.find("<"+poziom+">")==0 )
    {
        tekst.erase(0,poziom.size()+2);
        for(int i=0; i<tekst.find(poziom)-2; i++)
        {
            slowo=slowo+tekst[i];
        }
        tekst.erase(tekst.find(poziom)-2,poziom.size()+3);
    }
    return slowo;


}
string pobierzxml()
{
    fstream plik;
    string tekst="";


    plik.open( "aiml.xml", ios::in );
    if( plik.good() )
    {
        string napis;
        getline( plik, napis );

        while( !plik.eof() )
        {
            getline( plik, napis );
     if(DEBUG)       cout<<napis<<endl;
            trim(napis);

//            if(napis=="<aiml>" ||  napis=="</aiml>");
//            else if(napis.find("<category>")==0 )
//            {
//                getline( plik, napis );
//                getline( plik, napis );
//
//
//            }
//            else
//            {
//
//
//                cout<<napis.size()<<" "<<napis.find("</category>");
//                cout << napis << endl;
//            }
            tekst=tekst+napis;

        }

        plik.close();
    }
    else cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
    // cout<<JakiPoziom(tekst);


    return tekst;
}




vector<category> wstawxml()
{

    string tekst=pobierzxml();
    //  cout<<tekst<<endl;
    vector<category> kategorie;
    category kategoria;

    string kat="";
    int dlugosc=0;
    for(int i=0; i<100; i++)
    {
        if(tekst.size()==0)break;

        // cout<<PomiedzyTagami(tekst,"category")<<endl<<endl;

        if(JakiPoziom(tekst)=="aiml")
            tekst=PomiedzyTagami(tekst,JakiPoziom(tekst));
        if (JakiPoziom(tekst)=="category")
        {
            kat=tekst;
            tekst=PomiedzyTagami(tekst,JakiPoziom(tekst));
//           cout<<endl<<tekst<<endl;
            dlugosc=(tekst.size()+JakiPoziom("category").size()*2+5+16);//niewiem czemu +16 ale musi tak byc

        }

        if( JakiPoziom(tekst)=="pattern")
        {

            kategoria.pattern1=PomiedzyTagami(tekst,"pattern");
            tekst.erase(0,PomiedzyTagami(tekst,"pattern").size()+JakiPoziom(tekst).size()*2+5); //usuwa caly tag pattern



        }
        if( JakiPoziom(tekst)=="template")
        {

            kategoria.template1=PomiedzyTagami(tekst,"template");
            tekst.erase(0,PomiedzyTagami(tekst,"template").size()+JakiPoziom(tekst).size()*2+5);

//cout<<endl<<"usuwam"<<dlugosc<<kat;
            kat.erase(0,dlugosc);


            //          cout<<endl<<endl<<"usunienty"<<kat<<endl<<endl;
            tekst=kat;
            // kategorie.push_back(kategoria);
        }
        kategorie.push_back(kategoria);
    }

    return kategorie;
}
string znajdowanie(string a)
{
     vector<category> kategorie;

    map<string, string> znajdz;
    kategorie=wstawxml();

    for(int i=0; i<kategorie.size(); i++)
    {
     if(DEBUG)   cout<<kategorie.at(i).pattern1<<endl;
       if(DEBUG)   cout<<kategorie.at(i).template1<<endl<<endl;
        if(JakiPoziom(kategorie.at(i).template1)=="srai")  znajdz[kategorie.at(i).pattern1] =znajdz[ PomiedzyTagami(kategorie.at(i).template1,"srai")];
        else
            znajdz[kategorie.at(i).pattern1]=kategorie.at(i).template1;
    }





if(znajdz[a]=="") return ("nie rozpoznano komendy");
else return znajdz[a];
}*/


}

Aiml::~Aiml()
{
    //dtor
}
