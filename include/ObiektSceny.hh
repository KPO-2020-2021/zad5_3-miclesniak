#ifndef OBIEKTSCENY_HH
#define OBIEKTSCENY_HH

/**
 * @brief 
 * 
 */

class ObiektSceny
{

public:
virtual bool CzyMoznaLadowwac(const int Promien, const Wektor3D& Srodek, void* WskNaDrona = nullptr) const = 0;

virtual std::string WezTypObiektu()const  = 0;
};


#endif
