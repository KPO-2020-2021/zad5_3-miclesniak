#ifndef GORAOSTR_HH
#define GORAOSTR_HH

#include "BrylaGeometryczna.hh"
#include "przeszkoda.hh"
#include "prostopadloscian.hh"

class GoraOstr : public przeszkoda
{
    prostopadloscian _BrylaGoraOstr;

    protected:
    virtual bool TransformujBryle(std::ifstream &Plik_We,
                          std::ofstream &Plik_Wy, const BrylaGeometryczna *Br) const override final;

    public:
     GoraOstr(const int NumerPrzeszkody,const Wektor3D &Skala,
          const Wektor3D &Polozenie)
        :przeszkoda("GoraOstr",NumerPrzeszkody,Skala,Polozenie),_BrylaGoraOstr(Skala, Polozenie+Wektor3D{0,0,Skala[2]/2}, StworzNazwePlikuPrzeszkody()){};

    bool ObliczIZapiszWsplGlobalnePrzeszkody() const override final;
    virtual std::string WezNazwePlikuFinal() const override final
    {
        return _BrylaGoraOstr.WezNazwePliku_BrylaFinalna();
    }

    void Wyswietl() override final
    {
        std::cout <<"Gora z ostrym szczytem"<< "(";
        _BrylaGoraOstr.WyswietlWsp();
        std::cout << ")";
    }

    std::string WezTypObiektu() const override final{ return "Gora z ostrym szczytem"; };
};

#endif