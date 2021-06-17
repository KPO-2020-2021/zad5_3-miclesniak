#ifndef GORA_HH
#define GORA_HH

#include "BrylaGeometryczna.hh"
#include "przeszkoda.hh"
#include "prostopadloscian.hh"

class GoraZGrania : public przeszkoda
{
    prostopadloscian _BrylaGoryZGrania;

    protected:
    virtual bool TransformujBryle(std::ifstream &Plik_We,
                          std::ofstream &Plik_Wy, const BrylaGeometryczna *Br) const override final;

    public:
     GoraZGrania(const int NumerPrzeszkody,
          const Wektor3D &Polozenie,const Wektor3D &Skala)
        :przeszkoda("GoraZGrania",NumerPrzeszkody,Skala,Polozenie),_BrylaGoryZGrania(Skala,Polozenie+Wektor3D{0,0,Skala[2]/2},StworzNazwePlikuPrzeszkody()){};

    bool ObliczIZapiszWsplGlobalnePrzeszkody() const override final;
    virtual std::string WezNazwePlikuFinal() const override final
    {
        return _BrylaGoryZGrania.WezNazwePliku_BrylaFinalna();
    }
    void Wyswietl() override final
    {
        std::cout <<"Gora z dluga grania"<<"(";
        _BrylaGoryZGrania.WyswietlWsp();
        std::cout << ")";
    }
    std::string WezTypObiektu() const override final{ return "Gora z grania"; };
};

#endif