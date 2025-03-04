#include "generavimasf.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>

void generuotiStudentuFailus(const std::vector<int>& kiekiai, std::vector<std::string>& failuPavadinimai) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    for (int kiekis : kiekiai) {
        std::string failoPavadinimas = "Gstudentai" + std::to_string(kiekis) + ".txt";
        failuPavadinimai.push_back(failoPavadinimas);
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
    }
}
void rusiotiStudentusISFailus(const std::string& failopavadinimas){
    std:: ifstream inFile(failopavadinimas);
    if(!inFile){
        std::cerr << "Nepavyko atidaryti failo: " << failopavadinimas << std::endl;
        return;
    }
    std::vector<Student> studentai;
    std::string vardas, pavarde;
    int balas;

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
    rikiuotiStudentusPriesRusiavima(studentai);

    std::ofstream vargsciukaiFile("vargsciukai_" + failopavadinimas);
    std::ofstream kietiakaiFile("kietiakai_" + failopavadinimas);

    for(const auto& studentas : studentai){
        double galutinis = galutinisPazymys(studentas, true);
        if(galutinis < 5.0){
            vargsciukaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        } else {
            kietiakaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }
    }
    vargsciukaiFile.close();
    kietiakaiFile.close();
}
//atskiras rusiavimas generuotiems failams
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

    rikiuotiStudentus(studentai, rikiavimoPasirinkimas, tvarka);
}