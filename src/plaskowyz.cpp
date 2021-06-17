#include "plaskowyz.hh"

bool Plaskowyz::TransformujBryle(std::ifstream &Plik_We,
                                   std::ofstream &Plik_Wy,const BrylaGeometryczna *Br) const
{
    assert(Plik_We.good());
    assert(Plik_Wy.good());

    Wektor3D Wierz;

    for (unsigned int Ind_krawedz = 0; Ind_krawedz < 5; ++Ind_krawedz)
    {
        for (unsigned int Ind_wierz = 0; Ind_wierz < 4; ++Ind_wierz)
        {
            Plik_We >> Wierz;
            if (Plik_We.fail())
                return false;
            Wierz = Br->Skaluj(Wierz);
            Wierz = Br->TransfdoUkladuRodzica(Wierz);
            Plik_Wy << Wierz << std::endl;
            if (Plik_Wy.fail())
                return false;
        }
        Plik_Wy << std::endl; // Dodatkowa linia oddzielająca krawędzie
    }
    return !Plik_Wy.fail();
}

bool Plaskowyz::ObliczIZapiszWsplGlobalnePrzeszkody() const
{
    std::ifstream Plik_Wz(_Plaskowyz.WezNazwePliku_BrylaWzorcowa());
    std::ofstream Plik_Finalny(_Plaskowyz.WezNazwePliku_BrylaFinalna());
    if (!Plik_Wz.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << _Plaskowyz.WezNazwePliku_BrylaWzorcowa() << std::endl
                  << std::endl;
        return false;
    }
    if (!Plik_Finalny.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: "
                  << _Plaskowyz.WezNazwePliku_BrylaFinalna() << std::endl
                  << std::endl;
        return false;
    }
    return TransformujBryle(Plik_Wz, Plik_Finalny, &_Plaskowyz);
}
