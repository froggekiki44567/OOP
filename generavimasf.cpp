#include "generavimasf.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>

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

void rusiotiStudentusISFailus(const std::string& failopavadinimas, std::vector<std::string>& failugen) {
    std::ifstream inFile(failopavadinimas);
    if(!inFile){
        std::cerr << "Nepavyko atidaryti failo: " << failopavadinimas << std::endl;
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
    inFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start; 
    std::cout << "Failo: " << failopavadinimas << " skaitymas užtruko: " << duration.count() << " sekundžių." << std::endl;  

    rikiuotiStudentusPriesRusiavima(studentai);

    std::vector<Student> vargsciukai;
    std::vector<Student> kietiakai;

    auto start3 = std::chrono::high_resolution_clock::now();
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

    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration3 = end3 - start3;
    std::cout << "Failo: " << failopavadinimas << " skirstimas į failus užtruko: " << duration3.count() << " sekundžių." << std::endl;

    failugen.erase(std::remove(failugen.begin(), failugen.end(), failopavadinimas), failugen.end());
    while(!failugen.empty()){
        char pasirinkimas;
        std::cout << "Ar norite atlikti darbą su kitais failas? (y/n): ";
        std::cin >> pasirinkimas;

        if(pasirinkimas == 'Y' || pasirinkimas == 'y'){
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
        } else {
            break;
        }
    }
}

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
    rikiuotiStudentus(studentai, rikiavimoPasirinkimas, tvarka);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Rikiavimas užtruko: " << duration.count() << " sekundžių." << std::endl;
}