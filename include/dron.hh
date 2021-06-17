#ifndef DRON_HH
#define DRON_HH

#include "prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"
#include "ObiektSceny.hh"
#include <unistd.h>

/**
 * @file Dron.hh
 * @brief Plik zawiera definicję klasy Dron
 * 
 */

/**
 * @brief Klasa modeluje pojęcie drona
 * 
 */
class Dron : public uklad, public ObiektSceny
{
    /**
     * @brief Prostopadłościan, który ma posłużyć jako korpus drona
     * 
     */
    prostopadloscian _KorpusDrona;
    /**
     * @brief Tablica czteroelementowa graniastosłupów, zawierająca rotory drona
     * 
     */
    Graniastoslup _RotorDrona[4];
    /**
     * @brief Zmienna statyczna zawierająca ilość stworzonych Dronów
     * 
     */
    static int NrDrona;
    
    /**
     * @brief Zmienna typu int przechowująca numer danego drona
     * 
     */
    int _NrDrona;



    /**
     * @brief Metoda pozwala na transformacje bryly do Globalnego Ukladu Współrzędnych
     * 
     * Metoda ma na celu Pobranie z pliku bryły wzorcowej każdy wierzchołek,
     * a następnie po kolei odpowiednio go przeskalować, oraz przetransformować
     * jego współrzędne względem drona, oraz względem sceny. Zmodyfikowane
     * w ten sposób elementy zapisuje do pliku finalnego 
     * 
     * @param Plik_We - Plik, z którego ma zostać pobrana bryła wzorcowa
     * @param Plik_Wy - Plik, w którym mają zostać zapisane współrzędne bryły po konwersji
     * @param Br - Wskaźnik na bryłę, pozwala na użycie funkcji zarówno na prostopadłościanach
     * jak i graniastosłupach
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte
     */
    bool TransformujBryle(std::ifstream &Plik_We,
                          std::ofstream &Plik_Wy, const BrylaGeometryczna *Br) const;

    /**
     * @brief Metoda pozwala na transformację korpusu Drona do Globalnego Układu Współrzędnych
     * 
     * 
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte
     */
    bool Oblicz_i_Zapisz_WspGlbKorpusu() const;

    /**
     * @brief Metoda pozwala na transformację rotorów Drona do Globalnego Układu Współrzędnych 
     * 
     * @param Rotor - Rotor, który ma zostać przetransformowany
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte 
     */
    bool Oblicz_i_Zapisz_WspGlbRotora(const Graniastoslup &Rotor) const;

    /**
     * @brief Metoda która pozwala na obrót rotorów poprzez dodanie im kąta rotacji
     * 
     */
    void ObrocRotory();

public:
    /**
     * @brief Konstruktor Drona
     * 
     * Konstruktor ten przekazuje podane Położenie oraz Kąt Orientacji do Drona,
     * a także wywołuje konstruktory brył z odpowiednimi, zdefiniowanymi parametrami,
     * takimi jak skala, czy pozycja względem drona. Konstruktor także przypisuje każdej
     * bryle odpowiednią nazwę pliku, a także przyporządkowuje Dronowi jego numer
     * oraz zwiększa licznik dronów
     * 
     * @param Polozenie - Obiekt typu Wektor3D zawierająćy Położenie Drona względem sceny
     * @param KatOrientacji - Liczba typu double zawierająca kąt orientacji drona w stopniach
     */
    Dron(const Wektor3D &Polozenie, const double KatOrientacji);

    /**
     * @brief Metoda transformująca współrzędne Drona do Sceny
     * 
     * Metoda Otwiera pliki brył wzorcowych, transformuje każdą
     * bryłę zawartą w dronie do jego układu współrzędnych, a następnie do 
     * globalnego układu współrzędnych
     * 
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte 
     */
    bool Oblicz_i_Zapisz_WspGlbDrona() const;

    /**
     * @brief Metoda wyświetla aktualne położenie drona, tj. jego współrzędne X, Y
     * 
     */
    void WyswietlPol()
    {
        std::cout << _NrDrona << " - Polozenie (x,y): ";
        WyswietlWsp();
    }

    /**
     * @brief Metoda wyświetla komunikat, że dany dron jest aktywny
     * 
     */
    void WyswietlAkt()
    {
        std::cout << " <--Dron aktywny";
    }

    /**
     * @brief Metoda wykonująca rotację Drona
     * 
     * Metoda ma na celu animację obrotu Drona, w tym celu posłuży się metodą UkladWsp::UstalKat,
     * która pozwala zmienić kąt rotacji układu
     * 
     * @param Kat - Kat obrotu drona
     * @param Lacze - Łącze, które posłuży do ukazania rotacji
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte  
     */
    bool WykonajObrot(const double Kat, PzG::LaczeDoGNUPlota &Lacze);

    /**
     * @brief Metoda wykonująca pionowy lot Drona
     * 
     * Metoda ma na celu wykonanie pionowego lotu Drona o zadaną, zdefiniowaną
     * długość lotu. w tym celu posłuży się metodą UkladWsp::Wznies, która
     * pozwala zmienić współrzędną 'Z' Układu
     * 
     * @param DlugoscLotu - Liczba typu double przechowująca wartość długości lotu
     * @param Lacze - Łącze, które posłuży do ukazania lotu
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte
     */
    bool WykonajPionowyLot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze);

    /**
     * @brief Metoda wykonująca poziomy lot Drona
     * 
     * Metoda ma na celu animację poziomego lotu Drona o zadaną długość,
     * pod zadanym kątem. 
     * W tym celu posłuży się metodą UkladWsp::Przesun która pozwala na przesunięcie
     * Drona o dane współrzędne X i Y.
     * 
     * @param DlXY - Wektor przesuniecia drona
     * @param Dl - Dlugosc lotu
     * @param Lacze - Łącze, które posłuży do ukazania lotu
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte 
     */
    bool WykonajPoziomyLot(const double Dl,const Wektor3D DlXY, PzG::LaczeDoGNUPlota &Lacze);

    /**
     * @brief Metoda planująca ścieżkę Drona
     * 
     * Metoda ma na celu pobranie od użytkownika kąta rotacji ścieżki oraz jej
     * długość, a następnie zaplanowac sciezke 
     * 
     * @param Kat - Kat obrotu drona 
     * @param Dl - Dlugosc lotu drona
     * @param DlXY - Wektor przesuniecia drona
     * @param Lacze - Łącze, które posłuży do ukazania ścieżki
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte 
     */
    void PlanujPoczatkowaSciezke(double &Kat,double &Dl,Wektor3D &DlXY,vector<Wektor3D>&sciezka);
    /**
     * @brief Metoda rysujaca sciezke Drona 
     * 
     * Metoda ma na celu na podstawie podanych parametrow narysowac sciezki 
     * w programie GNUPlot przy pomocy lacza
     * 
     * @param Kat - Kat obrotu drona 
     * @param Dl - Dlugosc lotu drona
     * @param DlXY - Wektor przesuniecia drona
     * @param sciezka - zaplanowana sciezka do narysowania
     * @param Lacze - Łącze, które posłuży do ukazania ścieżki
     * @return true - Jeżeli operacja się powiedzie
     * @return false - Jeżeli pliki nie zostały poprawnie otwarte 
    **/
    bool NarysujSciezke(double &Kat, double &Dl, Wektor3D &DlXY,vector<Wektor3D>&sciezka, PzG::LaczeDoGNUPlota &Lacze);

    /**
     * @brief Metoda usuwająca ścieżkę
     * 
     * Metoda ma na celu usunięcie pliku zawierającego ścieżkę drona z łącza,
     * oraz wyczyszczenie szablonu vector<Wektor3D> zawierającego punkty ścieżki,
     * aby było możliwe ponowne jego zapełnienie
     * 
     * @param Wektor3D - zaplanowana sciezka 
     * @param Lacze - Łącze, które posłużyło do ukazania ścieżki
     */

    void UsunSciezke(vector<Wektor3D>&sciezka, PzG::LaczeDoGNUPlota &Lacze)
    {
        Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
        Lacze.Rysuj();
        sciezka.clear();
    }

    bool CzyMoznaLadowwac(const int Promien, const Wektor3D& Srodek, void* WskNaDrona = nullptr) const override final{
        if (this==WskNaDrona) return true;
        int Odleglosc = sqrt(pow(Srodek[0]- WezPolozenie()[0],2) + pow(Srodek[1] - WezPolozenie()[1],2));
        return !(Odleglosc <= 2*Promien);
    };

    std::string WezTypObiektu() const override final{ return "Dron"; };

   bool WykonajKrotkiPoziomyLot(const double Kat, PzG::LaczeDoGNUPlota &Lacze);
};

#endif