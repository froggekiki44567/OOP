// main.cpp - Main program entry point
#include "studentas.h"
#include "failo_oper.h"
#include "papild.h"
#include <iostream>
#include <chrono>
#include <vector>

int main() {
    
    
    std::vector<Student> studentai;
    char pasirinkimas;

    std::cout << "Pasirinkite veiksmą:\n";
    std::cout << "1. Sugeneruoti studentų duomenis automatiškai\n";
    std::cout << "2. Įvesti studentų duomenis ranka\n";
    std::cout << "3. Nuskaityti studentų duomenis iš failo\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> pasirinkimas;

    
    switch (pasirinkimas) {
        case '1': {
            int studentuSk;
            std::cout << "Kiek studentų norite sugeneruoti? ";
            std::cin >> studentuSk;
            studentai = generuotiStudentus(studentuSk);
            break;
        }
        case '2':
            studentai = ivestiStudentus();
            break;
        case '3': {
            std::vector<std::string> failuPavadinimai = {
                "studentai10000.txt",
                "studentai100000.txt",
                "studentai1000000.txt"
            };
            std::cout << "Pasirinkite failą naudojimui (1, 2 arba 3): ";
            int failoPasirinkimas;
            std::cin >> failoPasirinkimas;
            
            if(failoPasirinkimas >=1 && failoPasirinkimas <= 3) {
                double skaitymoLaikas;
                studentai = nuskaitytiStudentus(failuPavadinimai[failoPasirinkimas - 1], skaitymoLaikas);
                std::cout << "Failo skaitymas užtruko: " << skaitymoLaikas << " sekundžių." << std::endl;
            } else {
                std::cout << "Neteisingas pasirinkimas!" << std::endl;
                return 1;
            }
            break;
        }
        default:
            std::cout << "Neteisingas pasirinkimas!" << std::endl;
            return 1;
    }

    // Rikiuoti studentus pagal pasirinkimą
    rikiuotiStudentusPagalPasirinkima(studentai);

    // Pasirinkti išvesties būdą
    pasirinktIšvestiesBuda(studentai);

    return 0;
}