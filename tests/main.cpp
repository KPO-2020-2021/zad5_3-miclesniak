#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"



// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"
#include "../include/Wektor3D.hh"
#include "../include/Macierz3x3.hh"
#include "../include/BrylaGeometryczna.hh"
#include "../include/Graniastoslup6.hh"
#include "../include/prostopadloscian.hh"
#include "../include/dron.hh"
#include "../include/Licznik.hh"

TEST_CASE("Test Konstruktora Bezparametrycznego Wektora")
{
    Wektor3D tmp;
    tmp = Wektor3D();
    double x = 0;
    CHECK(tmp[0] == x);
    CHECK(tmp[1] == x);
    CHECK(tmp[2] == x);
}

TEST_CASE("Test Konstruktora Parametrycznego Wektora")
{
    Wektor3D tmp;
    double ttmp[] = {10, 20, 30};
    tmp = Wektor3D(ttmp);
    double x = 10, y = 20, z = 30;
    CHECK(tmp[0] == x);
    CHECK(tmp[1] == y);
    CHECK(tmp[2] == z);
}

TEST_CASE("Test metody ustalającej paramerty wektora")
{
    Wektor3D tmp;
    tmp.setW(3, 31, 43);
    double x = 3, y = 31, z = 43;
    CHECK(tmp[0] == x);
    CHECK(tmp[1] == y);
    CHECK(tmp[2] == z);
}

TEST_CASE("Test porownania wektorów")
{
    double tmp1[] = {15, 10, 10};
    Wektor3D V1 = Wektor3D(tmp1);
    Wektor3D V2 = Wektor3D(tmp1);
    CHECK_EQ(V1 == V2, true);
}

TEST_CASE("Test porownania 2 wektorów")
{
    double tmp1[] = {15, 10, 10}, tmp2[] = {13, 11, 10};
    Wektor3D V1 = Wektor3D(tmp1);
    Wektor3D V2 = Wektor3D(tmp2);
    CHECK_EQ(V1 == V2, false);
}

TEST_CASE("Test dodawania wektorów")
{
    double tmp1[] = {10, 20, 30};
    double tmp2[] = {3.5, 7.89, 9.11};
    Wektor3D V1 = Wektor3D(tmp1);
    Wektor3D V2 = Wektor3D(tmp2);
    Wektor3D V3;
    V3 = V1 + V2;
    double wynik[] = {13.5, 27.89, 39.11};
    Wektor3D V4 = Wektor3D(wynik);

    CHECK(V3 == V4);
}

TEST_CASE("Test odejmowania wektorów")
{
    double tmp1[] = {15.0, 23.0, 10.0}, tmp2[] = {3.5, 7.89, 6.66};
    Wektor3D V1 = Wektor3D(tmp1);
    Wektor3D V2 = Wektor3D(tmp2);
    Wektor3D V3;
    V3 = V1 - V2;
    double wynik[] = {11.5, 15.11, 3.34};
    Wektor3D V4 = Wektor3D(wynik);

    CHECK(V3 == V4);
}

TEST_CASE("Test mnożenia wektora przez macierz")
{
    double tmp1[] = {1, 2, 3};
    double tmp2[] = {3, 6, 9};
    Wektor3D V1, Wynik, Prawidlowy;
    V1 = Wektor3D(tmp1);
    Prawidlowy = Wektor3D(tmp2);
    Macierz3x3 M1 = Macierz3x3(3);
    Wynik = V1 * M1;
    CHECK(Wynik == Prawidlowy);
}

TEST_CASE("Test wypisywania Wektora")
{
    std::stringstream os;
    Wektor3D tmp;
    double tab[] = {1, 2, 3};
    tmp = Wektor3D(tab);
    os << tmp;
    CHECK_EQ("    1.0000000000    2.0000000000    3.0000000000", os.str());
}

TEST_CASE("Test wczytywania Wektora")
{
    std::stringstream is;
    double tab[] = {3, 3, 2};
    Wektor3D V1, V2;
    V2 = Wektor3D(tab);
    is << "3 3 2 ";
    is >> V1;
    CHECK(V1 == V2);
}

TEST_CASE("Test operatora [] dla Wektora")
{
    Wektor3D V1;
    double tab[] = {5, 7, 1.11};
    V1 = Wektor3D(tab);
    CHECK_EQ(V1[0], 5);
    CHECK_EQ(V1[1], 7);
    CHECK_EQ(V1[2], 1.11);
}

TEST_CASE("Test konstruktora Macierzy")
{
    Macierz3x3 tmp;
    tmp = Macierz3x3();
    CHECK(tmp(0, 1) == 0);
    CHECK(tmp(1, 0) == 0);
    CHECK(tmp(1, 1) == 0);
    CHECK(tmp(0, 0) == 0);
    CHECK(tmp(0, 2) == 0);
    CHECK(tmp(1, 2) == 0);
    CHECK(tmp(2, 0) == 0);
    CHECK(tmp(2, 1) == 0);
    CHECK(tmp(2, 2) == 0);
}

TEST_CASE("Test konstruktora Macierzy z argumentem")
{
    Macierz3x3 tmp;
    tmp = Macierz3x3(3);
    CHECK(tmp(0, 1) == 0);
    CHECK(tmp(1, 0) == 0);
    CHECK(tmp(1, 1) == 3);
    CHECK(tmp(0, 0) == 3);
    CHECK(tmp(0, 2) == 0);
    CHECK(tmp(1, 2) == 0);
    CHECK(tmp(2, 0) == 0);
    CHECK(tmp(2, 1) == 0);
    CHECK(tmp(2, 2) == 3);
}

TEST_CASE("Test konstruktora parametrycznego Macierzy")
{
    double tmp1[3][3] = {{10, 20, 54.3}, {29.999, 40.6, 123}, {14.1, 21.1, 15.17}};
    Macierz3x3 tmp;
    tmp = Macierz3x3(tmp1);
    CHECK(tmp(0, 1) == 20);
    CHECK(tmp(1, 0) == 29.999);
    CHECK(tmp(1, 1) == 40.6);
    CHECK(tmp(0, 0) == 10);
    CHECK(tmp(0, 2) == 54.3);
    CHECK(tmp(1, 2) == 123);
    CHECK(tmp(2, 0) == 14.1);
    CHECK(tmp(2, 1) == 21.1);
    CHECK(tmp(2, 2) == 15.17);
}

TEST_CASE("Test przeciazenia porownania dla Macierzy")
{
    Macierz3x3 M1, M2;
    double tmp1[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    double tmp2[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    M1 = Macierz3x3(tmp1);
    M2 = Macierz3x3(tmp2);

    CHECK_EQ(M1 == M2, true);
}

TEST_CASE("Test przeciazenia porownania dla Macierzy 2")
{
    Macierz3x3 M1, M2;
    double tmp1[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    double tmp2[3][3] = {{10.100, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    M1 = Macierz3x3(tmp1);
    M2 = Macierz3x3(tmp2);

    CHECK_EQ(M1 == M2, false);
}

TEST_CASE("Test przeciazenia mnozenia Macierz Razy Macierz")
{
    Macierz3x3 M1, M2, Wynik, Prawidlowy;
    double tmp1[3][3] = {{10, 20, 54}, {29, 40, 12}, {14, 21, 15}};
    double tmp2[3][3] = {{10, 5, 3}, {2, 45, 13}, {4, 1, 1.5}};
    double tmp3[3][3] = {{356, 1004, 371}, {418, 1957, 625}, {242, 1030, 337.5}};
    M1 = Macierz3x3(tmp1);
    M2 = Macierz3x3(tmp2);
    Prawidlowy = Macierz3x3(tmp3);
    Wynik = M1 * M2;
    CHECK(Wynik == Prawidlowy);
}

TEST_CASE("Przeciazenie () dla Macierzy")
{
    Macierz3x3 M1;
    double tmp1[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    M1 = Macierz3x3(tmp1);

    CHECK(M1(0, 0) == 10.123);
    CHECK(M1(1, 0) == 29.999);
    CHECK(M1(2, 2) == 15.17);
}

TEST_CASE("Test metody clear")
{
    Macierz3x3 tmp;
    double tmp1[3][3] = {{10.123, 20.89, 54.3}, {29.999, 40.654, 123}, {14.13, 21.1, 15.17}};
    tmp = Macierz3x3(tmp1);
    tmp.clear();

    CHECK(tmp(0, 1) == 0);
    CHECK(tmp(1, 0) == 0);
    CHECK(tmp(1, 1) == 0);
    CHECK(tmp(0, 0) == 0);
    CHECK(tmp(0, 2) == 0);
    CHECK(tmp(1, 2) == 0);
    CHECK(tmp(2, 0) == 0);
    CHECK(tmp(2, 1) == 0);
    CHECK(tmp(2, 2) == 0);
}

TEST_CASE("Test metody SetX"){
    Macierz3x3 M1;
    double alfa = 0.5;
    M1 = Macierz3x3();
    M1.setX(alfa);
    CHECK(M1(1,1) == cos(alfa * PI / 180));
    CHECK(M1(1,2) == -sin(alfa * PI / 180)); 
    CHECK(M1(2,1) == sin(alfa * PI / 180));  
    CHECK(M1(2,2) == cos(alfa * PI / 180));
    CHECK(M1(0,0) == 1);
}

TEST_CASE("Test metody SetY"){
    Macierz3x3 M1;
    double alfa = 0.5;
    M1 = Macierz3x3();
    M1.setY(alfa);
    CHECK(M1(0,0) == cos(alfa * PI / 180));
    CHECK(M1(2,0) == -sin(alfa * PI / 180)); 
    CHECK(M1(0,2) == sin(alfa * PI / 180));  
    CHECK(M1(2,2) == cos(alfa * PI / 180));
    CHECK(M1(1,1) == 1);
}

TEST_CASE("Test metody SetZ"){
    Macierz3x3 M1;
    double alfa = 0.5;
    M1 = Macierz3x3();
    M1.setZ(alfa);
    CHECK(M1(0,0) == cos(alfa * PI / 180));
    CHECK(M1(0,1) == -sin(alfa * PI / 180)); 
    CHECK(M1(1,0) == sin(alfa * PI / 180));  
    CHECK(M1(1,1) == cos(alfa * PI / 180));
    CHECK(M1(2,2) == 1);
}



TEST_CASE("Przeciazenie wypisywania dla Macierzy")
{
    std::stringstream os;
    Macierz3x3 M1;
    double tmp[3][3] = {{15, 22, 11}, {3, 11, 5},{1, 2 , 3}};
    M1 = Macierz3x3(tmp);
    os << M1;
    CHECK_EQ("|    15.0000000000    22.0000000000    11.0000000000 |\n|     3.0000000000    11.0000000000     5.0000000000 |\n|     1.0000000000     2.0000000000     3.0000000000 |\n", os.str());
}

TEST_CASE("Konstruktor parametryczny ukladu")
{
    Wektor3D W1 = {3,0,1};
    double Kat = 28.7;
    uklad U1 = uklad(W1,Kat);
    CHECK(U1.WezPolozenie() == W1);
    CHECK(U1.WezKat() == Kat);
}

TEST_CASE("Konstruktor Graniastoslup"){
    Wektor3D W1 = {3,0,1};
    Wektor3D W2 = {11,5,3};
    Graniastoslup G1 = Graniastoslup(W1,W2);
    CHECK(G1.WezPolozenie() == W2);
    CHECK(G1.WezSkale() == W1);
    CHECK(G1.WezNazwePliku_BrylaWzorcowa() == PLIKWZ_GRANIASTOSLUP6 );
}

TEST_CASE("Konstruktor Prostopadloscian"){
     Wektor3D W1 = {11,3.4,1};
    Wektor3D W2 = {12.1,5.123,3};
    prostopadloscian P1 = prostopadloscian(W1,W2);
    CHECK(P1.WezPolozenie() == W2);
    CHECK(P1.WezSkale() == W1);
    CHECK(P1.WezNazwePliku_BrylaWzorcowa() == PLIKWZ_SZESCIAN );
}

TEST_CASE("Konstruktor Drona"){
    Wektor3D W1 = {3.4,33,12.31};
    double Kat = 312.1;
    Dron D1 = Dron(W1,Kat);
    CHECK(D1.WezKat() == Kat);
    CHECK(D1.WezPolozenie() == W1);
}

TEST_CASE("Test zliczania wektorów"){
    Wektor3D W1,W2,W3,W4;
    CHECK(Licznik<Wektor3D>::WezAkt() == 4);
    CHECK(Licznik<Wektor3D>::WezSume() == 70);
}

TEST_CASE("Test translacji do ukladu Rodzica"){
    Wektor3D W1 = {5,3,5.33},W2 = { 5.9450603291, 5.0325559766, 6.3300000000};
    Wektor3D W3 = {3,0,1};
    double Kat = 28.7;
    uklad U1 = uklad(W3,Kat);
    CHECK(U1.TransfdoUkladuRodzica(W1) == W2);
}

