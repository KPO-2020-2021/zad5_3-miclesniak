#include "Scena.hh"
#include <algorithm>

int Scena::_AktDron = 0;

Scena::Scena(const Wektor3D &Polozenie1,
             const double KatObrotu1,
             const Wektor3D &Polozenie2,
             const double KatObrotu2)
    : _TabDronow{{Dron(Polozenie1, KatObrotu1)},
                 {Dron(Polozenie2, KatObrotu2)}} {
                     for (Dron& Dr:_TabDronow){ListaObiektow.emplace_back(&Dr);}
                 }

void Scena::WyswietlPolozenie()
{
    for (int i = 0; i < 2; ++i)
    {
        _TabDronow[i].WyswietlPol();
        if (_AktDron == i)
            _TabDronow[i].WyswietlAkt();
        std::cout << std::endl;
    }
}

void Scena::WyswietlAktPolozenie()
{
    std::cout << "Polozenie Drona aktywnego (x,y): ";
    _TabDronow[_AktDron].WyswietlWsp();
    std::cout << std::endl;
}

bool Scena::InicjalizujScene()
{
    for (int i = 0; i < 2; ++i)
        if (!_TabDronow[i].Oblicz_i_Zapisz_WspGlbDrona())
            return false;
    return true;
}

void Scena::InicjalizujLacze()
{
    _Lacze.ZmienTrybRys(PzG::TR_3D);
    _Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.
    _Lacze.UstawZakresX(0, 200);
    _Lacze.UstawZakresY(0, 200);
    _Lacze.UstawZakresZ(0, 120);
    _Lacze.UstawRotacjeXZ(64, 65); // Tutaj ustawiany jest widok
    _Lacze.DodajNazwePliku("PlikFinalny_Dron1_Korpus.dat");
    _Lacze.DodajNazwePliku("PlikFinalny_Dron1_Rotor1.dat");
    _Lacze.DodajNazwePliku("PlikFinalny_Dron1_Rotor2.dat");
    _Lacze.DodajNazwePliku("PlikFinalny_Dron1_Rotor3.dat");
    _Lacze.DodajNazwePliku("PlikFinalny_Dron1_Rotor4.dat");
    _Lacze.DodajNazwePliku("PlikFinalny_Dron2_Korpus.dat");
    _Lacze.DodajNazwePliku("PlikFinalny_Dron2_Rotor1.dat");
    _Lacze.DodajNazwePliku("PlikFinalny_Dron2_Rotor2.dat");
    _Lacze.DodajNazwePliku("PlikFinalny_Dron2_Rotor3.dat");
    _Lacze.DodajNazwePliku("PlikFinalny_Dron2_Rotor4.dat");
    _Lacze.DodajNazwePliku(PLIK_PLASZCZYZNY);
    DodajGoraZGrania(Wektor3D{120, 90, 0}, Wektor3D{SKALA_GORA_GRAN});
    DodajGoraOstr(Wektor3D{60, 120, 0}, Wektor3D{SKALA_GORA_OSTR1});
    DodajGoraOstr(Wektor3D{100, 20, 0}, Wektor3D{SKALA_GORA_OSTR2});
    DodajPlaskowyz(Wektor3D{160, 105, 0}, Wektor3D{SKALA_PLASKOWYZU});
    _Lacze.Rysuj();
}

bool Scena::LotDrona(double &Kat, double &Dl, Wektor3D &DlXY, vector<Wektor3D> &sciezka)
{
    if (!UzyjAktywnegoDrona().NarysujSciezke(Kat, Dl, DlXY, sciezka, _Lacze))
        return false;
    if (!UzyjAktywnegoDrona().WykonajPionowyLot(LOT_PIONOWY, _Lacze))
        return false;
    if (!UzyjAktywnegoDrona().WykonajObrot(Kat, _Lacze))
        return false;
    if (!UzyjAktywnegoDrona().WykonajPoziomyLot(Dl, DlXY, _Lacze))
        return false;
    bool Kolizja;
    do {
        Kolizja = false;
        for (std::shared_ptr<ObiektSceny> ObiektPtr : ListaObiektow) {
            if(!ObiektPtr->CzyMoznaLadowwac(20,UzyjAktywnegoDrona().WezPolozenie(),&UzyjAktywnegoDrona()))
                Kolizja=true;
        }
        if (Kolizja) {
            std::cout << "Nie moge ladowac!" << std::endl;
            if (!UzyjAktywnegoDrona().WykonajKrotkiPoziomyLot(Kat,_Lacze))
                return false;
        }
    } while (Kolizja);

    if (!UzyjAktywnegoDrona().WykonajPionowyLot(-LOT_PIONOWY, _Lacze))
        return false;
    std::cout << "\nDron wyladowal ...\n";
    UzyjAktywnegoDrona().UsunSciezke(sciezka, _Lacze);
    return true;
}

void Scena::WybierzDrona()
{
    int idx;
    std::cout << "Wybor aktywnego drona\n\n";
    WyswietlPolozenie();
    std::cout << "\nWprowadz numer aktywnego drona> ";
    std::cin >> idx;
    while (!(idx == 1 || idx == 2) || cin.fail())
    {
        std::cerr << "\nWprowadzono niepoprawny numer!\n";
        std::cout << "\nWprowadz numer aktywnego drona> ";
        cin.clear();
        cin.ignore(999999, '\n');
        std::cin >> idx;
    }        
    _AktDron = idx - 1;
    WyswietlAktPolozenie();
    Wektor3D::WyswietlIlosc();
}

void Scena::DodajPrzeszkode()
{
    double SX, SY, SZ, WX, WY;
    int przeszkoda;
    Wektor3D Polozenie, Skala;
    cout << "Wybierz rodzaj przeszkody:\n";
    cout << "1 - Gora z ostrym szczytem\n";
    cout << "2 - Gora z grania\n";
    cout << "3 - Plaskowyz\n";

    cin >> przeszkoda;
    switch (przeszkoda)
    {
    case 1:
        cout << "Podaj skale wzdluz kolejnych osi 0X 0Y 0Z\n";
        cout << "Podaj wspolrzedne środka podstawy x,y\n";
        cin >> SX >> SY >> SZ;
        Skala = Wektor3D{SX, SY, SZ};
        cin >> WX >> WY;
        Polozenie = Wektor3D{WX, WY, 0};
        DodajGoraOstr(Polozenie, Skala);
        break;
    case 2:
        cout << "Podaj skale wzdluz kolejnych osi 0X 0Y 0Z\n";
        cout << "Podaj wspolrzedne środka podstawy x,y\n";
        cin >> SX >> SY >> SZ;
        Skala = Wektor3D{SX, SY, SZ};
        cin >> WX >> WY;
        Polozenie = Wektor3D{WX, WY, 0};
        DodajGoraZGrania(Polozenie, Skala);
        break;

    case 3:
        cout << "Podaj skale wzdluz kolejnych osi 0X 0Y 0Z\n";
        cout << "Podaj wspolrzedne środka podstawy x,y\n";
        cin >> SX >> SY >> SZ;
        Skala = Wektor3D{SX, SY, SZ};
        cin >> WX >> WY;
        Polozenie = Wektor3D{WX, WY, 0};
        DodajPlaskowyz(Polozenie, Skala);
        break;

    default:
    
        break;
    }
}


void Scena::UsunPrzeszkode()
{
    if (ListaPrzeszkod.size() > 0)
    {
        int nr=1;
        for(const std::shared_ptr<przeszkoda> &Prz: ListaPrzeszkod)
        {
            std:: cout << nr << " - ";
            Prz->Wyswietl();
            std::cout <<endl;
            nr++;
        }
        unsigned int licz;
        std::list<shared_ptr<przeszkoda>>::iterator it;
        std::cout << "Wybierz numer przeszkody do usuniecia:\n";
        std::cin >> licz;
        while (std::cin.fail() || licz > ListaPrzeszkod.size())
        {
            std::cerr << "Niepoprawny numer przeszkody\n";
            std::cin.clear();
            std::cin.ignore(9999, '\n');
            std::cin >> licz;
        }
        it = ListaPrzeszkod.begin();
        advance(it, (licz-1));
        _Lacze.UsunNazwePliku((*it)->WezNazwePlikuFinal().c_str());
        std::list<shared_ptr<ObiektSceny>>::iterator itobiekt = std::find(ListaObiektow.begin(), ListaObiektow.end(), std::static_pointer_cast<ObiektSceny>(*it));
        if(itobiekt!=ListaObiektow.end()) {
            ListaObiektow.erase(itobiekt);
        }
        it = ListaPrzeszkod.erase(it);
        _Lacze.Rysuj();
        cout<< "Element zostal usuniety.\n";
    }
    else
        std::cerr << "Brak elementow\n";
}