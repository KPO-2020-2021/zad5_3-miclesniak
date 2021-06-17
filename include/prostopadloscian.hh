#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include "BrylaGeometryczna.hh"

class prostopadloscian: public BrylaGeometryczna
{
    public:
    prostopadloscian(const Wektor3D &skala,const Wektor3D &polozenie): BrylaGeometryczna(PLIKWZ_SZESCIAN,skala,polozenie){};

    prostopadloscian(const Wektor3D &skala,const Wektor3D &polozenie,const std::string& NazwaPlikuWynik): BrylaGeometryczna(PLIKWZ_SZESCIAN,skala,polozenie,NazwaPlikuWynik){};
};


#endif