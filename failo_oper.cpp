// file_operations.cpp - Implementation of file input/output operations
#include "failo_oper.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>

std::vector<Student> nuskaitytiStudentus(const std::string& failoPavadinimas, double& skaitymoLaikas) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Student> studentai;
    std::ifstream inFile(failoPavadinimas);
    
    if (inFile.is_open()) {
        std::stringstream buffer;
        buffer << inFile.rdbuf();
        inFile.close();

        std::string line;
        // Praleisti antraštės eilutę
        std::getline(buffer, line);
        
        while (buffer) {
            std::getline(buffer, line);
            if (!buffer.eof()) {
                Student studentas;
                std::stringstream ss(line);
                ss >> studentas.vardas >> studentas.pavarde;
                int pazymys;
                std::vector<int> pazymiai;
                while (ss >> pazymys) {
                    pazymiai.push_back(pazymys);
                }
                if (!pazymiai.empty()) {
                    studentas.nd_balai = std::vector<int>(pazymiai.begin(), pazymiai.end()-1);
                    studentas.egzaminas = pazymiai.back();
                    studentai.push_back(studentas);
                } else {
                    std::cerr << "Klaida: Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi pažymių." << std::endl;
                }
            }
        }
    } else {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> duration = end - start;
    skaitymoLaikas = duration.count();

    return studentai;
}

void spausdintiRezultatus(const std::vector<Student>& studentai) {
    std::cout << "\nVardas        Pavardė       Galutinis (Vidurkis)     Galutinis (Mediana)" << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    for (const auto& studentas : studentai) {
        double galutinisVidurkis = galutinisPazymys(studentas, true);
        double galutinisMediana = galutinisPazymys(studentas, false);

        std::cout << std::left << std::setw(12) << studentas.vardas
                  << std::setw(14) << studentas.pavarde
                  << std::fixed << std::setprecision(2) << std::setw(25) << galutinisVidurkis
                  << galutinisMediana << std::endl;
    }
}

void rasytiRezultatus(const std::string& failoPavadinimas, const std::vector<Student>& studentai) {

    std::ofstream outFile(failoPavadinimas);
    if (outFile.is_open()) {
        outFile << std::left << std::setw(20) << "Vardas" 
                << std::setw(20) << "Pavardė" 
                << std::setw(30) << "Galutinis (Vidurkis)" 
                << "Galutinis (Mediana)" << std::endl;
        outFile << "-------------------------------------------------------------------------------" << std::endl;
        
        for (const auto& studentas : studentai) {
            double galutinisVidurkis = galutinisPazymys(studentas, true);
            double galutinisMediana = galutinisPazymys(studentas, false);

            outFile << std::left << std::setw(20) << studentas.vardas
                    << std::setw(20) << studentas.pavarde
                    << std::fixed << std::setprecision(2) << std::setw(30) << galutinisVidurkis
                    << galutinisMediana << std::endl;
        }
        outFile.close();
    } else {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
    }  
}

void pasirinktIšvestiesBuda(const std::vector<Student>& studentai) {
    char outputChoice;
    std::cout << "Ar norite spausdinti rezultatus į ekraną ar į failą? (e/f): ";
    std::cin >> outputChoice;
    
    if (outputChoice == 'e' || outputChoice == 'E') {
        // Spausdinti rezultatus į ekraną
        spausdintiRezultatus(studentai);
    } else if (outputChoice == 'f' || outputChoice == 'F') {
        // Rašyti rezultatus į failą
        rasytiRezultatus("kursiokai.txt", studentai);
    } else {
        std::cout << "Neteisingas pasirinkimas!" << std::endl;
    }
}