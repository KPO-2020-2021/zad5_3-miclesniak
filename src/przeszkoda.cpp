#include "przeszkoda.hh"
#include "Wektor3D.hh"
#include "definicje.hh"
#include <cassert>
#include <fstream>
#include <sstream>

std::string przeszkoda::StworzNazwePlikuPrzeszkody() const
{
    ostringstream Strm;
    Strm <<"dat/"<< _NazwaPrzeszkody << _NumerPrzeszkody << ".dat";
    return Strm.str();
}