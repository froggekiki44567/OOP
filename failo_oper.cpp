// cia funkcijos susijusios su failu operacijomis
#include "failo_oper.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>

std::vector<Student> nuskaitytiStudentus(const std::string& failoPavadinimas, double& skaitymoLaikas) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Student> studentai;

    try {
        std::ifstream inFile(failoPavadinimas);
        if (!inFile) {
            throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
        }

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        inFile.close();

        std::string line;
        // Praleisti antraštės eilutę
        if (!std::getline(buffer, line)) {
            throw std::runtime_error("Failas tuščias arba sugadintas: " + failoPavadinimas);
        }

        while (std::getline(buffer, line)) {
            Student studentas;
            std::stringstream ss(line);
            ss >> studentas.vardas >> studentas.pavarde;

            if (ss.fail()) {
                std::cerr << "Klaida skaitant studento duomenis eilutėje: " << line << std::endl;
                continue;  // Pereiname prie kitos eilutės
            }

            int pazymys;
            std::vector<int> pazymiai;
            while (ss >> pazymys) {
                pazymiai.push_back(pazymys);
            }

            if (pazymiai.empty()) {
                std::cerr << "Klaida: Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi pažymių." << std::endl;
                continue;  // Pereiname prie kitos eilutės
            }
            
            studentas.egzaminas = pazymiai.back();
            pazymiai.pop_back();
            
            studentas.nd_balai = pazymiai;
            
            studentai.push_back(studentas);
        }

    } catch (const std::exception& e) {
        std::cerr << "Klaida nuskaitant studentus: " << e.what() << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    skaitymoLaikas = std::chrono::duration<double>(end - start).count();

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