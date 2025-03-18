#include "generavimasf.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>

//generuojam failus su studentais
void generuotiStudentuFailus(const std::vector<int>& kiekiai, std::vector<std::string>& failugen) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    for (int kiekis : kiekiai) {
        std::string failoPavadinimas = "Gstudentai" + std::to_string(kiekis) + ".txt";
        failugen.push_back(failoPavadinimas);
        std::ofstream outFile(failoPavadinimas);
        if (!outFile) {
            std::cerr << "Nepavyko sukurti failo: " << failoPavadinimas << std::endl;
            continue;
        }

        outFile << std::left << std::setw(20) <<  "Vardas" << std::setw(20) <<  "Pavarde";
        for (int i = 1; i <= 15; i++) {
            outFile << std::setw(10) << ("ND" + std::to_string(i));
        }
        outFile << std::setw(10) << " Egz." << std::endl;

        for (int i = 1; i <= kiekis; i++) {
            outFile << std::left << std::setw(20) <<  ("Vardas" + std::to_string(i))
             << std::setw(20) << (" Pavarde" + std::to_string(i));
            for (int j = 0; j < 15; j++) {
                outFile << std::setw(10) << dist(gen);
            }
            outFile << std::setw(10) << dist(gen) << std::endl;
        }

        outFile.close();

        auto end = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<double> duration = end - start;
        std::cout << "Failo: " << failoPavadinimas << " generavimas užtruko: " << duration.count() << " sekundžių." << std::endl;
    }
}

//rusiuojam studentus i gerus blogus, skaitom is failo
bool baigtidarba = false;
void rusiotiStudentusISFailus(const std::string& failopavadinimas, std::vector<std::string>& failugen) {
    if(baigtidarba){
        return;
    }
    
    std::cout << "Pasirinkite failą naudojimui:\n";
    for (size_t i = 0; i < failugen.size(); ++i) {
        std::cout << i + 1 << ". " << failugen[i] << "\n";
    }
    std::cout << "Pasirinkimas: ";
    int failoPasirinkimas;
    std::cin >> failoPasirinkimas;

    if (failoPasirinkimas < 1 || failoPasirinkimas > failugen.size()) {
        std::cout << "Neteisingas pasirinkimas!" << std::endl;
        return;
    }

    std::string pasirinktasFailas = failugen[failoPasirinkimas - 1];

    std::ifstream inFile(pasirinktasFailas);
    if(!inFile){
        std::cerr << "Nepavyko atidaryti failo: " << pasirinktasFailas << std::endl;
        return;
    }
    std::vector<Student> studentai;
    std::string vardas, pavarde;
    int balas;
    
    auto start = std::chrono::high_resolution_clock::now();

    std::string eilute;
    std::getline(inFile, eilute);

    while(inFile >> vardas >> pavarde){
        Student studentas;
        studentas.vardas = vardas;
        studentas.pavarde = pavarde;
        
        for(int i = 0; i < 15; i++){
            inFile >> balas;
            studentas.nd_balai.push_back(balas);
        }
        inFile >> studentas.egzaminas;
        studentai.push_back(studentas);
    }   
    inFile.close(); // skaitimo pabaiga

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Failo: " << pasirinktasFailas << " skaitymas su vector užtruko: " << duration.count() << " sekundžių." << std::endl;

    rikiuotiStudentusPriesRusiavima(studentai); // kreipimas i rusiavima pries perduodant i konteinerius

    // strategijos pasirinkimas
    char strategijosPasirinkimas;
    std::cout << "Pasirinkite strategiją:\n";
    std::cout << "1. Paprasta strategija\n";
    std::cout << "2. Bendro studentų konteinerio skaidymas\n";
    std::cout << "3. Naudojant algoritmus\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> strategijosPasirinkimas;

    // #1 strategija
    if (strategijosPasirinkimas == '1') {
        std::vector<Student> vargsciukai;
        std::vector<Student> kietiakai;

        // #1 strategijos laiko pradzia
        auto start = std::chrono::high_resolution_clock::now();
        for(const auto& studentas : studentai){
            double galutinis = galutinisPazymys(studentas, true);
            if(galutinis < 5.0){
                vargsciukai.push_back(studentas);
            } else {
                kietiakai.push_back(studentas);
            }
        }

        std::ofstream vargsciukaiFile("vargsciukai_" + failopavadinimas);
        std::ofstream kietiakaiFile("kietiakai_" + failopavadinimas);

        for(const auto& studentas : vargsciukai){
            double galutinis = galutinisPazymys(studentas, true);
            vargsciukaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        for(const auto& studentas : kietiakai){
            double galutinis = galutinisPazymys(studentas, true);
            kietiakaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        vargsciukaiFile.close();
        kietiakaiFile.close();

        vargsciukai.clear();
        kietiakai.clear();

        //#1 strategijos laiko pabaiga
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration3 = end - start;
        std::cout << "Failo: " << failopavadinimas << " skirstimas į failus su vector ir #1 strategija užtruko: " << duration3.count() << " sekundžių." << std::endl;
    } 
    // #2 strategija
    else if (strategijosPasirinkimas == '2') {
        std::vector<Student> vargsciukai;
        auto start = std::chrono::high_resolution_clock::now(); // #2 strategijos laiko pradzia
        auto it = studentai.begin();
        while (it != studentai.end()) {
            double galutinis = galutinisPazymys(*it, true);
            if (galutinis < 5.0) {
                vargsciukai.push_back(*it);
                it = studentai.erase(it);
            } else {
                ++it;
            }
        }

        std::ofstream vargsciukaiFile("vargsciukai_" + failopavadinimas);
        std::ofstream kietiakaiFile("kietiakai_" + failopavadinimas);

        for(const auto& studentas : vargsciukai){
            double galutinis = galutinisPazymys(studentas, true);
            vargsciukaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        for(const auto& studentas : studentai){
            double galutinis = galutinisPazymys(studentas, true);
            kietiakaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        vargsciukaiFile.close();
        kietiakaiFile.close();

        vargsciukai.clear();
        studentai.clear();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Failo: " << failopavadinimas << " skirstimas į failus su vector ir #2 strategija užtruko: " << duration.count() << " sekundžių." << std::endl;
    }
    // #3 strategija
    else if (strategijosPasirinkimas == '3') {
        std::vector<Student> vargsciukai;
        std::vector<Student> kietiakai;

        // #3 strategijos laiko pradzia
        auto start = std::chrono::high_resolution_clock::now();

        //std::partition kad atskirti vargšciukus nuo kietiakų
        auto it = std::partition(studentai.begin(), studentai.end(), [](const Student& studentas) {
            return galutinisPazymys(studentas, true) < 5.0;
        });

        // Kopijuojami vargšciukai ir kietiakai i vektorius
        std::copy(studentai.begin(), it, std::back_inserter(vargsciukai));
        
        std::copy(it, studentai.end(), std::back_inserter(kietiakai));

        std::ofstream vargsciukaiFile("vargsciukai_" + failopavadinimas);
        std::ofstream kietiakaiFile("kietiakai_" + failopavadinimas);

        for(const auto& studentas : vargsciukai){
            double galutinis = galutinisPazymys(studentas, true);
            vargsciukaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        for(const auto& studentas : kietiakai){
            double galutinis = galutinisPazymys(studentas, true);
            kietiakaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        vargsciukaiFile.close();
        kietiakaiFile.close();

        vargsciukai.clear();
        kietiakai.clear();

        // #3 strategijos laiko pabaiga
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Failo: " << failopavadinimas << " skirstimas į failus su vector ir #3 strategija užtruko: " << duration.count() << " sekundžių." << std::endl;
    }

    // panaudoto failo trinimas
    failugen.erase(std::remove(failugen.begin(), failugen.end(), failopavadinimas), failugen.end());
    while(!failugen.empty()){
        char pasirinkimas;
        std::cout << "Ar norite baigti darbą? (y/n): ";
        std::cin >> pasirinkimas;
   
        // darbo pabaigos klausimas
        if(pasirinkimas == 'Y' || pasirinkimas == 'y'){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            baigtidarba = true;
            break;
        } else {
            std::cout << "Pasirinkite failą naudojimui:\n";
            for(size_t i = 0; i < failugen.size(); ++i){
                std::cout << i + 1 << ". " << failugen[i] << "\n";
            }
            std::cout << "Pasirinkimas: ";
            int failoPasirinkimas;
            std::cin >> failoPasirinkimas;

            if(failoPasirinkimas >= 1 && failoPasirinkimas <= failugen.size()){
                rusiotiStudentusISFailus(failugen[failoPasirinkimas - 1], failugen);
            } else {
                std::cout << "Neteisingas pasirinkimas!" << std::endl;
            }
        }
    }
}

//rikiavimo fukcija
void rikiuotiStudentusPriesRusiavima(std::vector<Student>& studentai) {
    char rikiavimoPasirinkimas;
    std::cout << "Pasirinkite rikiavimo būdą:\n";
    std::cout << "1. Pagal vardą\n";
    std::cout << "2. Pagal pavardę\n";
    std::cout << "3. Pagal galutinį vidurkį\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> rikiavimoPasirinkimas;

    char tvarka = 'a';
    if (rikiavimoPasirinkimas == '3') {
        std::cout << "Pasirinkite rikiavimo tvarką:\n";
        std::cout << "a. Didėjimo tvarka\n";
        std::cout << "d. Mažėjimo tvarka\n";
        std::cout << "Pasirinkimas: ";
        std::cin >> tvarka;
    }

    auto start = std::chrono::high_resolution_clock::now();
    rikiuotiStudentus(studentai, rikiavimoPasirinkimas, tvarka); // kreipiamasi i rikiavimo funkcija studentas.cpp
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Rikiavimas su vector užtruko: " << duration.count() << " sekundžių." << std::endl;
}