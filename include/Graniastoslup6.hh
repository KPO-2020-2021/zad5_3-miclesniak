#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

#include "BrylaGeometryczna.hh"


using namespace std;

class Graniastoslup: public BrylaGeometryczna
{
public:
Graniastoslup(const Wektor3D &Skala, const Wektor3D &Polozenie) : BrylaGeometryczna(PLIKWZ_GRANIASTOSLUP6, Skala, Polozenie){};

};
#endif 

