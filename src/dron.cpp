#include "dron.hh"

/**
 * @file Dron.cpp
 * @brief Plik zawierający rozwinięcie metod klasy Dron
 * 
 *  
 */

int Dron::NrDrona = 0;

Dron::Dron(const Wektor3D &Polozenie, const double KatOrientacji)
    : uklad(Polozenie, KatOrientacji),
      _KorpusDrona(Wektor3D{SKALA_KORPUSU},
                   Wektor3D{TRANSLACJA_KORPUS}),
      _RotorDrona{{Graniastoslup(Wektor3D{SKALA_ROTORA},
                                 Wektor3D{TRANSLACJA_ROTOR_LEWY_PRZEDNI})},
                  {Graniastoslup(Wektor3D{SKALA_ROTORA},
                                 Wektor3D{TRANSLACJA_ROTOR_PRAWY_PRZEDNI})},
                  {Graniastoslup(Wektor3D{SKALA_ROTORA},
                                 Wektor3D{TRANSLACJA_ROTOR_LEWY_TYLNY})},
                  {Graniastoslup(Wektor3D{SKALA_ROTORA},
                                 Wektor3D{TRANSLACJA_ROTOR_PRAWY_TYLNY})}}
{
    NrDrona++;
    _NrDrona = NrDrona;
    _KorpusDrona.UstalNazwePliku_BrylaFinalna(SCIEZKA_DO_PLIKU +
                                              std::to_string(NrDrona) +
                                              NAZWA_KORPUSU);
    for (int i = 0; i < 4; i++)
    {
        _RotorDrona[i].UstalNazwePliku_BrylaFinalna(SCIEZKA_DO_PLIKU +
                                                    std::to_string(NrDrona) +
                                                    NAZWA_ROTORA + std::to_string(i + 1) +
                                                    ".dat");
    }
}

bool Dron::TransformujBryle(std::ifstream &Plik_We,
                            std::ofstream &Plik_Wy, const BrylaGeometryczna *Br) const
{
    Wektor3D Wierz;
    assert(Plik_We.good());
    assert(Plik_Wy.good());

    Plik_We >> Wierz;
    while (!Plik_We.fail())
    {
        for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ;
             ++IloscWierzcholkow)
        {
            Wierz = Br->Skaluj(Wierz);
            Wierz = Br->TransfdoUkladuRodzica(Wierz);
            Wierz = TransfdoUkladuRodzica(Wierz);
            Plik_Wy << Wierz << std::endl;
            Plik_We >> Wierz;
            assert(IloscWierzcholkow == ILOSC_WIERZ_LINII_TWORZACEJ - 1 || !Plik_We.fail());
        }
        Plik_Wy << std::endl;
    }
    return !Plik_Wy.fail();
}

bool Dron::Oblicz_i_Zapisz_WspGlbKorpusu() const
{
    std::ifstream Plik_Wz(_KorpusDrona.WezNazwePliku_BrylaWzorcowa());
    std::ofstream Plik_Finalny(_KorpusDrona.WezNazwePliku_BrylaFinalna());
    if (!Plik_Wz.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << _KorpusDrona.WezNazwePliku_BrylaWzorcowa() << std::endl
                  << std::endl;
        return false;
    }
    if (!Plik_Finalny.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << _KorpusDrona.WezNazwePliku_BrylaFinalna() << std::endl
                  << std::endl;
        return false;
    }
    return TransformujBryle(Plik_Wz, Plik_Finalny, &_KorpusDrona);
}

bool Dron::Oblicz_i_Zapisz_WspGlbRotora(const Graniastoslup &Rotor) const
{
    std::ifstream Plik_Wz(Rotor.WezNazwePliku_BrylaWzorcowa());
    std::ofstream Plik_Finalny(Rotor.WezNazwePliku_BrylaFinalna());
    if (!Plik_Wz.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << Rotor.WezNazwePliku_BrylaWzorcowa() << std::endl
                  << std::endl;
        return false;
    }
    if (!Plik_Finalny.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << Rotor.WezNazwePliku_BrylaFinalna() << std::endl
                  << std::endl;
        return false;
    }
    return TransformujBryle(Plik_Wz, Plik_Finalny, &Rotor);
}

bool Dron::Oblicz_i_Zapisz_WspGlbDrona() const
{
    if (!Oblicz_i_Zapisz_WspGlbKorpusu())
        return false;
    for (int i = 0; i < 4; ++i)
        if (!Oblicz_i_Zapisz_WspGlbRotora(_RotorDrona[i]))
            return false;
    return true;
}

void Dron::ObrocRotory()
{
    _RotorDrona[0].DodajKat(-SKOK_OBROTU_ROTOROW_stopnie);
    _RotorDrona[1].DodajKat(SKOK_OBROTU_ROTOROW_stopnie);
    _RotorDrona[2].DodajKat(SKOK_OBROTU_ROTOROW_stopnie);
    _RotorDrona[3].DodajKat(-SKOK_OBROTU_ROTOROW_stopnie);
}

bool Dron::WykonajPionowyLot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze)
{
    if (DlugoscLotu >= 0)
    {
        std::cout << std::endl
                  << "Wznoszenie ... " << std::endl;
        for (double wys = 0; wys <= DlugoscLotu; wys += 2)
        {
            if (!Oblicz_i_Zapisz_WspGlbDrona())
                return false;
            Wznies(wys);
            ObrocRotory();
            usleep(40000); // 0.1 ms
            Lacze.Rysuj();
        }
        return true;
    }
    else
    {
        std::cout << std::endl
                  << "Opadanie ... " << std::endl;
        for (double wys = -DlugoscLotu; wys >= -2; wys -= 2)
        {
            if (!Oblicz_i_Zapisz_WspGlbDrona())
                return false;
            Wznies(wys);
            ObrocRotory();
            usleep(40000); // 0.1 ms
            Lacze.Rysuj();
        }
        return true;
    }
    return false;
}

bool Dron::WykonajPoziomyLot(const double Dl,const Wektor3D DlXY, PzG::LaczeDoGNUPlota &Lacze)
{
    std::cout << "Lot do przodu ... " << std::endl;
    for (double dl = 0; dl <= Dl; ++dl)
    {
        if (!Oblicz_i_Zapisz_WspGlbDrona())
            return false;
        Przesun(DlXY, Dl);
        ObrocRotory();
        usleep(30000);
        Lacze.Rysuj();
    }
    return true;
}


bool Dron::WykonajKrotkiPoziomyLot(const double Kat, PzG::LaczeDoGNUPlota &Lacze)
{
    double Dl = 10;
    Macierz3x3 Rotacja;
    Wektor3D LotPoziomy{Dl,0,0};
    Rotacja.setZ(Kat);
    Wektor3D DlXY = LotPoziomy * Rotacja;
    std::cout << "Krotki przelot do przodu ... " << std::endl;
    for (double dl = 0; dl <= Dl; ++dl)
    {
        if (!Oblicz_i_Zapisz_WspGlbDrona())
            return false;
        Przesun(DlXY, Dl);
        ObrocRotory();
        usleep(30000);
        Lacze.Rysuj();
    }
    return true;
}

void Dron::PlanujPoczatkowaSciezke(double &Kat, double &Dl, Wektor3D &DlXY,vector<Wektor3D>&sciezka)
{
    std::cout << "Podaj kierunek lotu (kat w stopniach)> ";
    std::cin >> Kat;
    while (std::cin.fail())
    {
        std::cerr << "\nWprowadzono niepoprawna wartosc kata!\n";
        std::cout << "\nPodaj kierunek lotu (kat w stopniach)> ";
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        std::cin >> Kat;
    }
    Kat = Kat + WezKat();

    std::cout << "Podaj dlugosc lotu> ";
    std::cin >> Dl;
    while (std::cin.fail())
    {
        std::cerr << "\nWprowadzono niepoprawna wartosc dlugosci lotu!\n";
        std::cout << "\nPodaj dlugosc lotu> ";
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        std::cin >> Dl;
    }
    Wektor3D LotPoziomy = Wektor3D{Dl,0,0};

    Wektor3D W1 = WezPolozenie();
    sciezka.push_back(W1);

    Wektor3D W2,W3,W5;
    W2 = W1;
    W2[2] = W1[2] + LOT_PIONOWY;
    sciezka.push_back(W2);

    Macierz3x3 Rotacja;
    Rotacja.setZ(Kat);
    W3 = W2;
    W3[2] = W2[2];
    Wektor3D W4 = LotPoziomy * Rotacja;
    DlXY = W4;
    W3 = W3 + W4;
    sciezka.push_back(W3);

    W5 = W3;
    W5[2] = W3[2] - LOT_PIONOWY;
    sciezka.push_back(W5);
}

bool Dron::NarysujSciezke(double &Kat, double &Dl, Wektor3D &DlXY,vector<Wektor3D>&sciezka, PzG::LaczeDoGNUPlota &Lacze){
    std::ofstream StrmWy(PLIK_TRASY_PRZELOTU);
    PlanujPoczatkowaSciezke(Kat,Dl, DlXY,sciezka);
    if (!StrmWy.is_open())
    {
        std::cerr << std::endl
                  << " Nie mozna otworzyc do zapisu pliku: "
                  << PLIK_TRASY_PRZELOTU << std::endl
                  << std::endl;
        return false;
    }
    for (size_t i = 0; i < sciezka.size(); ++i)
    {
        StrmWy << sciezka[i] << std::endl;
    }

    Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
    Lacze.Rysuj();
    return !StrmWy.fail();
}

bool Dron::WykonajObrot(const double Kat, PzG::LaczeDoGNUPlota &Lacze)
{
    std::cout << "Zmiana orientacji ... " << std::endl;
    if (WezKat() <= Kat)
    {
        for (double KatOb = WezKat(); KatOb <= Kat; KatOb += 5)
        {
            UstawKat(KatOb);
            if (!Oblicz_i_Zapisz_WspGlbDrona())
                return false;
            ObrocRotory();
            usleep(60000);
            Lacze.Rysuj();
        }
        return true;
    }
    if (WezKat() > Kat)
    {
        for (double KatOb = WezKat(); KatOb >= Kat; KatOb -= 5)
        {
            UstawKat(KatOb);
            if (!Oblicz_i_Zapisz_WspGlbDrona())
                return false;
            ObrocRotory();
            usleep(60000);
            Lacze.Rysuj();
        }
        return true;
    }
    return false;
}
