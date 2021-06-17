#ifndef UKLAD_HH
#define UKLAD_HH

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "definicje.hh"

using namespace std;

/**
 * @file uklad.hh
 * 
 * @brief plik zawierajacy definicje klasy uklad 
 */

/** 
 * @brief Klasa modelujaca pojecie ukladu
 */

class uklad
{
    /**
    * @brief Wektor w ktorym zawiera sie polozenie danego ukladu
    */
    Wektor3D _Polozenie;
    /**
     * @brief double w ktorym zawiera sie kat aktualnego obrotu ukladu
     */
    double _Kat;

public:
    /**
     * @brief konstruktor bezparametryczny
     */
    uklad()
    {
        _Polozenie = Wektor3D();
        _Kat = 0;
    }

    /**
     * @brief konstruktor parametryczny 
     */
    uklad(const Wektor3D pol,const double kat)
    {
        _Kat = kat;
        _Polozenie = pol;
    }

    uklad(const Wektor3D &Polozenie) : _Polozenie(Polozenie), _Kat(0){}

    void Przesun(const Wektor3D wsp, const double CalkDlugosc);
    void Wznies(const double wysokosc){_Polozenie[2] = wysokosc;}
    void UstawPolozenie(const Wektor3D polozenie){_Polozenie = polozenie;}
    const Wektor3D &WezPolozenie()const {return _Polozenie;}
    void UstawKat(const double kat){_Kat = kat;}
    const double &WezKat()const {return _Kat;}
    Wektor3D TransfdoUkladuRodzica(const Wektor3D &wierzcholek) const;
    void WyswietlWsp();
    void DodajKat(const double alfa);

};
#endif