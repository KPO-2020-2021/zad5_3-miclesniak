#include "../include/uklad.hh"
#include "../include/Macierz3x3.hh"
#include "../include/Wektor3D.hh"
#include <cmath>

Wektor3D uklad::TransfdoUkladuRodzica(const Wektor3D &wierzcholek) const
{
    Macierz3x3 M1;
    M1.setZ(_Kat);
    Wektor3D WierzPoTrans = wierzcholek * M1 + _Polozenie;
    return WierzPoTrans;
}

void uklad::Przesun(const Wektor3D wsp, const double CalkDlugosc)
{
    _Polozenie[0] = _Polozenie[0] + wsp[0] / CalkDlugosc;
    _Polozenie[1] = _Polozenie[1] + wsp[1] / CalkDlugosc;
}

void uklad::WyswietlWsp()
{
    std::cout << _Polozenie[0] << " " << _Polozenie[1];
}

void uklad::DodajKat(const double alfa)
{
    _Kat += alfa;
}