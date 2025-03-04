#include "generavimasf.h"
#include <fstream>
#include <iostream>
#include <random>

void generuotiStudentuFailus(const std::vector<int>& kiekiai) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    for (int kiekis : kiekiai) {
        std::string failoPavadinimas = "Gstudentai" + std::to_string(kiekis) + ".txt";
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
