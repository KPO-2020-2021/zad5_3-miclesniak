#ifndef PLASKOWYZ_HH
#define PLASKOWYZ_HH

#include "BrylaGeometryczna.hh"
#include "przeszkoda.hh"
#include "prostopadloscian.hh"

class Plaskowyz : public przeszkoda
{
    prostopadloscian _Plaskowyz;

    protected:
    virtual bool TransformujBryle(std::ifstream &Plik_We,
                          std::ofstream &Plik_Wy, const BrylaGeometryczna *Br) const override final;

    public:
     Plaskowyz(const int NumerPrzeszkody,
          const Wektor3D &Polozenie, const Wektor3D &Skala)
        :przeszkoda("Plaskowyz",NumerPrzeszkody,Skala,Polozenie),_Plaskowyz(Skala,Polozenie+Wektor3D{0,0,Skala[2]/2},StworzNazwePlikuPrzeszkody()){};

    bool ObliczIZapiszWsplGlobalnePrzeszkody() const override final;
    virtual std::string WezNazwePlikuFinal() const override final
    {
        return _Plaskowyz.WezNazwePliku_BrylaFinalna();
    }

    void Wyswietl() override final
    {
        std::cout <<"Plaskowyz"<<"(";
        _Plaskowyz.WyswietlWsp();
        std::cout << ")";
    }

    std::string WezTypObiektu() const override final{ return "Plaskowyz"; };
};

#endif