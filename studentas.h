// student.h - Student structure and related functions
#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

// Struktura kuri saugo studento duomenis
struct Student {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd_balai;
    int egzaminas;
};

// Funkcijos darbui su studentų duomenimis
double skaiciuotiVidurki(const std::vector<int>& pazymiai);
double skaiciuotiMediana(std::vector<int> pazymiai);
double galutinisPazymys(const Student& studentas, bool naudotiVidurki = true);

// Funkcijos generavimui ir įvedimui
Student generuotiStudenta();
void generuotiPazymius(Student& studentas);
std::vector<Student> generuotiStudentus(int kiekis);
std::vector<Student> ivestiStudentus();

// Rikiavimo funkcijos
bool palygintiPagalVarda(const Student& a, const Student& b);
bool palygintiPagalPavarde(const Student& a, const Student& b);
bool palygintiPagalVidurkiAsc(const Student& a, const Student& b);
bool palygintiPagalVidurkiDesc(const Student& a, const Student& b);
bool palygintiPagalMedianaAsc(const Student& a, const Student& b);
bool palygintiPagalMedianaDesc(const Student& a, const Student& b);
void rikiuotiStudentus(std::vector<Student>& studentai, char pasirinkimas, char tvarka = 'a');
void rikiuotiStudentusPagalPasirinkima(std::vector<Student>& studentai);

#endif