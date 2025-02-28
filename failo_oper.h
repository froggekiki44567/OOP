
#ifndef FAILO_OPER_H
#define FAILO_OPER_H

#include "studentas.h"
#include <string>
#include <vector>

// Funkcijos failų skaitymui
std::vector<Student> nuskaitytiStudentus(const std::string& failoPavadinimas, double& skaitymoLaikas);

// Funkcijos rezultatų išvedimui
void spausdintiRezultatus(const std::vector<Student>& studentai);
void rasytiRezultatus(const std::string& failoPavadinimas, const std::vector<Student>& studentai);
void pasirinktIšvestiesBuda(const std::vector<Student>& studentai);

#endif