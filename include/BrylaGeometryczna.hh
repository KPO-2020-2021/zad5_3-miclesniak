#ifndef BRYLA_HH
#define BRYLA_HH

#include "uklad.hh"
/**
 * @file Bryla.hh 
 * 
 *
 * @brief Plik zawiera definicję klasy Bryla
 * 
 */

/**
 * @brief Klasa modeluje pojęcie bryły
 * 
 */
class BrylaGeometryczna : public uklad
{
    /**
     * @brief Obiekt typu string zawierajacy ścieżkę do pliku zawierającego bryłę wzorcową
     * 
     */
    std::string _NazwaPliku_BrylaWzorcowa;
    /**
     * @brief Obiekt typu string zawierajacy ścieżkę do pliku zawierającego bryłę finalną
     * 
     */
    std::string _NazwaPliku_BrylaFinalna;
    /**
     * @brief Obiekt typu Wektor3D zawierający skalę bryły
     * 
     */
    Wektor3D _skala;

protected:
    /**
     * @brief Konstruktor Bryły
     * 
     * @param NazwaPlikuBrylaWzorcowa - Nazwa Pliku zawierającego bryłę wzorcową
     * @param Skala - Obiekt typu Wektor3D zawierający skalę bryły
     * @param Polozenie - Obiekt typu Wektor3D zawierający położenie bryły
     */
    BrylaGeometryczna(const std::string &NazwaPlikuBrylaWzorcowa,
          const Wektor3D &Skala,
          const Wektor3D &Polozenie)
        : uklad(Polozenie),
          _NazwaPliku_BrylaWzorcowa(NazwaPlikuBrylaWzorcowa),
          _skala(Skala){};


     BrylaGeometryczna(const std::string &NazwaPlikuBrylaWzorcowa,
          const Wektor3D &Skala,
          const Wektor3D &Polozenie,const std::string &NazwaPlikuBrylaFinalna)
        : uklad(Polozenie),
          _NazwaPliku_BrylaWzorcowa(NazwaPlikuBrylaWzorcowa),
          _NazwaPliku_BrylaFinalna(NazwaPlikuBrylaFinalna),
          _skala(Skala){};
                            

public:
    /**
     * @brief Metoda zwracająca nazwę pliku zawierającego bryłę finalną
     * 
     * @return const std::string& - nazwa pliku zawierającego bryłę finalną
     */
    const std::string &WezNazwePliku_BrylaFinalna() const
    {
        return _NazwaPliku_BrylaFinalna;
    };

    /**
     * @brief Metoda, która służy do skalowania wierzchołków bryły
     * 
     * @param Wierz - Obiekt typu Wektor3D zawierający wierzchołek bryły
     * @return Wektor3D - Obiekt typu Wektor3D zawierający wierzchołek po skalowaniu
     */
    Wektor3D Skaluj(const Wektor3D &Wierz) const
    {
        Wektor3D Wynik;
        for (int i = 0; i < 3; ++i)
            Wynik[i] = Wierz[i] * _skala[i];
        return Wynik;
    };

    /**
     * @brief Metoda zwracająca nazwę pliku zawierającego bryłę wzorcową
     * 
     * @return const std::string& - nazwa pliku zawierającego bryłę wzorcową
     */
    const std::string &WezNazwePliku_BrylaWzorcowa() const
    {
        return _NazwaPliku_BrylaWzorcowa;
    };

    

    /**
     * @brief Metoda ustalająca nazwę pliku zawierającego bryłę finalną
     * 
     * @param Nazwa - Nazwa pliku zawierającego bryłę finalną
     */
    void UstalNazwePliku_BrylaFinalna(const std::string &Nazwa)
    {
        _NazwaPliku_BrylaFinalna = Nazwa;
    }

    const Wektor3D &WezSkale()const {return _skala;}
};

#endif