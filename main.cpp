#include "studentas.h"
#include "failo_oper.h"
#include "papild.h"
#include "ListO.h"
#include "DequeO.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <deque>
#include <fstream>
#include "generavimasf.h"
#include "testai.h"

void generuotiFailus(std::vector<std::string>& failugen) {
    std::vector<int> kiekiai = {1000, 10000, 100000, 1000000, 10000000};
    generuotiStudentuFailus(kiekiai, failugen);

    std::ofstream outFile("generuotasMixas.txt", std::ios::trunc);
    for (const auto& failas : failugen) {
        outFile << failas << std::endl;
    }
}

void nuskaitytiSugeneruotusFailus(std::vector<std::string>& failugen, std::list<std::string>& failugenList, std::deque<std::string>& failugenDeque) {
    std::ifstream inFile("generuotasMixas.txt");
    std::string failas;
    while (std::getline(inFile, failas)) {
        failugen.push_back(failas);
        failugenList.push_back(failas);
        failugenDeque.push_back(failas);
    }
}

int main() {
    std::vector<Student> studentai;
    char pasirinkimas;
    std::vector<std::string> failugen;
    std::list<std::string> failugenList;
    std::deque<std::string> failugenDeque;

    std::cout << "Pasirinkite veiksmą:\n";
    std::cout << "1. Sugeneruoti studentų failus\n";
    std::cout << "2. Sugeneruoti studentų duomenis automatiškai\n";
    std::cout << "3. Įvesti studentų duomenis ranka\n";
    std::cout << "4. Nuskaityti studentų duomenis iš failo\n";
    std::cout << "5. Testai su failais\n";
    std::cout << "6. Baigti programą\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> pasirinkimas;

    switch (pasirinkimas) {
        case '1': {
            generuotiFailus(failugen);
            break;
        }
        case '2': {
            int studentuSk;
            std::cout << "Kiek studentų norite sugeneruoti? ";
            std::cin >> studentuSk;
            studentai = generuotiStudentus(studentuSk);
            break;
        }
        case '3':
            studentai = ivestiStudentus();
            break;
        case '4': {
            std::vector<std::string> failuPavadinimai = {
                "studentai10000.txt",
                "studentai100000.txt",
                "studentai1000000.txt"
            };
            std::cout << "Pasirinkite failą naudojimui (1, 2 arba 3): ";
            int failoPasirinkimas;
            std::cin >> failoPasirinkimas;

            if (failoPasirinkimas >= 1 && failoPasirinkimas <= 3) {
                double skaitymoLaikas;
                studentai = nuskaitytiStudentus(failuPavadinimai[failoPasirinkimas - 1], skaitymoLaikas);
                std::cout << "Failo skaitymas užtruko: " << skaitymoLaikas << " sekundžių." << std::endl;
                rikiuotiStudentusPagalPasirinkima(studentai);

                pasirinktIšvestiesBuda(studentai);
            } else {
                std::cout << "Neteisingas pasirinkimas!" << std::endl;
                return 1;
            }
            break;
        }
        case '5': {
            nuskaitytiSugeneruotusFailus(failugen, failugenList, failugenDeque); // Populate all containers
            if (!failugen.empty()) {
                std::cout << "Pasirinkite kokį konteinerį naudoti (v - vector, l - list, d - deque): ";
                char konteinerioPasirinkimas;
                std::cin >> konteinerioPasirinkimas;

                switch(konteinerioPasirinkimas){
                    case 'v':
                        for(const auto& failas : failugen){
                            rusiotiStudentusISFailus(failas, failugen);
                        }
                        break;
                    case 'l':
                        for(const auto& failas : failugenList){
                            rusiotiStudentusISFailusList(failas, failugenList);
                        }
                        break;
                    case 'd':
                        for(const auto& failas : failugenDeque){
                            rusiotiStudentusISFailusDeque(failas, failugenDeque);
                        }
                        break;
                    default:
                        std::cout << "Neteisingas pasirinkimas!" << std::endl;
                        return 1;
                }
                /*
                auto start = std::chrono::high_resolution_clock::now();
                atliktiLaikoTestusSuFailais(failugen);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                std::cout << "Visos programos vykdymo laikas: " << duration.count() << " sekundžių." << std::endl;
                */
                } else {
                std::cout << "Nėra sugeneruotų failų testavimui." << std::endl;
            }
            break;
        }
        case '6':
            return 0;
        default:
            std::cout << "Neteisingas pasirinkimas!" << std::endl;
            return 1;
    }
    return 0;
}