#ifndef PRZESZKODA_HH
#define PRZESZKODA_HH

#include "Wektor3D.hh"
#include "BrylaGeometryczna.hh"
#include "ObiektSceny.hh"
#include <string>
class przeszkoda : public ObiektSceny
{
private:
    std::string _NazwaPrzeszkody;
    int _NumerPrzeszkody;

    Wektor3D Skala;
    Wektor3D Polozenie;

protected:
    virtual bool TransformujBryle(std::ifstream &Plik_We,
                                  std::ofstream &Plik_Wy, const BrylaGeometryczna *Br) const = 0;


public:
    std::string StworzNazwePlikuPrzeszkody() const;
    virtual bool ObliczIZapiszWsplGlobalnePrzeszkody() const = 0;
    virtual std::string WezNazwePlikuFinal() const = 0;
    virtual void Wyswietl() = 0;
    std::string WezNazwePrzeszkody() const
    {
        return _NazwaPrzeszkody;
    }
    int WezNumerPrzeszkody() const
    {
        return _NumerPrzeszkody;
    }

    bool CzyMoznaLadowwac(const int Promien, const Wektor3D& Srodek, void* WskNaDrona = nullptr) const override final{
        (void)WskNaDrona; //zeby nie bylo warninga
        double DX = abs(Srodek[0] - Polozenie[0]);
        double DY = abs(Srodek[1] - Polozenie[1]); // Sprawdzenie czy srodek okregu jest zbyt daleko
        if (DX > (Skala[0] / 2 + Promien) || DY > (Skala[1] / 2 + Promien))
            return true;
        // Sprawdzenie czy srodek okregu w prostokacie lub obok bokow
        if (DX <= (Skala[0] / 2) || DY <= (Skala[1] / 2))
            return false;

        double D = pow(DX - Skala[0] / 2, 2) + pow(DY - Skala[1] / 2, 2);
        // Sprawdzenie czy srodek okregu lezy w obszarze wierzcholka
        return !(D <= pow(Promien, 2));
    };

    przeszkoda(const std::string &NazwaPrzeszkody, const int NumerPrzeszkody, const Wektor3D& Skala, const Wektor3D& Polozenie)
        : _NazwaPrzeszkody(NazwaPrzeszkody),
          _NumerPrzeszkody(NumerPrzeszkody),
          Skala(Skala),
          Polozenie(Polozenie) {};

};
#endif