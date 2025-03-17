#include "ListO.h"
#include "studentas.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <iostream>
#include <list>

void rusiotiStudentusISFailusList(const std::string& failopavadinimas, std::list<std::string>& failugenList) {
    bool darboPabaiga = false;
    if (darboPabaiga) {
        return;
    }
    std::ifstream inFile(failopavadinimas);
    if (!inFile) {
        std::cerr << "Nepavyko atidaryti failo: " << failopavadinimas << std::endl;
        return;
    }
    std::list<Student> studentai;
    std::string vardas, pavarde;
    int balas;

    auto start = std::chrono::high_resolution_clock::now();

    std::string eilute;
    std::getline(inFile, eilute);

    while (inFile >> vardas >> pavarde) {
        Student studentas;
        studentas.vardas = vardas;
        studentas.pavarde = pavarde;

        for (int i = 0; i < 15; i++) {
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

    rikiuotiStudentusPriesSkirtymaList(studentai);

    char strategijosPasirinkimas;
    std::cout << "Pasirinkite strategiją:\n";
    std::cout << "1. Paprasta strategija\n";
    std::cout << "2. Bendro studentų konteinerio skaidymas\n";
    std::cout << "3. Naudojant algoritmus\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> strategijosPasirinkimas;

    if (strategijosPasirinkimas == '1') {
        std::list<Student> vargsciukai;
        std::list<Student> kietiakai;

        auto start3 = std::chrono::high_resolution_clock::now();
        for (const auto& studentas : studentai) {
            double galutinis = galutinisPazymys(studentas, true);
            if (galutinis < 5.0) {
                vargsciukai.push_back(studentas);
            } else {
                kietiakai.push_back(studentas);
            }
        }

        std::ofstream vargsciukaiFile("vargsciukai_" + failopavadinimas);
        std::ofstream kietiakaiFile("kietiakai_" + failopavadinimas);

        for (const auto& studentas : vargsciukai) {
            double galutinis = galutinisPazymys(studentas, true);
            vargsciukaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        for (const auto& studentas : kietiakai) {
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
    } else if (strategijosPasirinkimas == '2') {
        std::list<Student> vargsciukai;

        auto start3 = std::chrono::high_resolution_clock::now();
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

        for (const auto& studentas : vargsciukai) {
            double galutinis = galutinisPazymys(studentas, true);
            vargsciukaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        for (const auto& studentas : studentai) {
            double galutinis = galutinisPazymys(studentas, true);
            kietiakaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        vargsciukaiFile.close();
        kietiakaiFile.close();

        vargsciukai.clear();
        studentai.clear();

        auto end3 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration3 = end3 - start3;
        std::cout << "Failo: " << failopavadinimas << " skirstimas į failus užtruko: " << duration3.count() << " sekundžių." << std::endl;
    } else if (strategijosPasirinkimas == '3') {
        std::list<Student> vargsciukai;
        std::list<Student> kietiakai;

        auto start3 = std::chrono::high_resolution_clock::now();

        // Using std::partition to separate vargsciukai and kietiakai
        auto it = std::partition(studentai.begin(), studentai.end(), [](const Student& studentas) {
            return galutinisPazymys(studentas, true) < 5.0;
        });

        // Copy vargsciukai to vargsciukai list
        std::copy(studentai.begin(), it, std::back_inserter(vargsciukai));
        // Copy kietiakai to kietiakai list
        std::copy(it, studentai.end(), std::back_inserter(kietiakai));

        std::ofstream vargsciukaiFile("vargsciukai_" + failopavadinimas);
        std::ofstream kietiakaiFile("kietiakai_" + failopavadinimas);

        for (const auto& studentas : vargsciukai) {
            double galutinis = galutinisPazymys(studentas, true);
            vargsciukaiFile << studentas.vardas << " " << studentas.pavarde << " " << galutinis << std::endl;
        }

        for (const auto& studentas : kietiakai) {
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
    }

    failugenList.erase(std::remove(failugenList.begin(), failugenList.end(), failopavadinimas), failugenList.end());
    while (!failugenList.empty()) {
        char pasirinkimas;
        std::cout << "Ar norite baigti darbą? (y/n): ";
        std::cin >> pasirinkimas;

        if (pasirinkimas == 'Y' || pasirinkimas == 'y') {
            darboPabaiga = true;
            return; // Exit the function to finish the work
        } else {
            std::cout << "Pasirinkite failą naudojimui:\n";
            int index = 1;
            for (const auto& failas : failugenList) {
                std::cout << index++ << ". " << failas << "\n";
            }
            std::cout << "Pasirinkimas: ";
            int failoPasirinkimas;
            std::cin >> failoPasirinkimas;

            if (failoPasirinkimas >= 1 && failoPasirinkimas <= failugenList.size()) {
                auto it = failugenList.begin();
                for (int i = 1; i < failoPasirinkimas; ++i) {
                    ++it;
                }
                rusiotiStudentusISFailusList(*it, failugenList);
            } else {
                std::cout << "Neteisingas pasirinkimas!" << std::endl;
            }
        }
    }
}

void rikiuotiStudentusPriesSkirtymaList(std::list<Student>& studentai) {
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
    if (rikiavimoPasirinkimas == '1') {
        studentai.sort([](const Student& a, const Student& b) {
            return a.vardas < b.vardas;
        });
    } else if (rikiavimoPasirinkimas == '2') {
        studentai.sort([](const Student& a, const Student& b) {
            return a.pavarde < b.pavarde;
        });
    } else if (rikiavimoPasirinkimas == '3') {
        if (tvarka == 'a') {
            studentai.sort([](const Student& a, const Student& b) {
                double sumA = 0;
                for (int balas : a.nd_balai) {
                    sumA += balas;
                }
                double vidurkisA = sumA / a.nd_balai.size();

                double sumB = 0;
                for (int balas : b.nd_balai) {
                    sumB += balas;
                }
                double vidurkisB = sumB / b.nd_balai.size();

                return vidurkisA < vidurkisB;
            });
        } else if (tvarka == 'd') {
            studentai.sort([](const Student& a, const Student& b) {
                double sumA = 0;
                for (int balas : a.nd_balai) {
                    sumA += balas;
                }
                double vidurkisA = sumA / a.nd_balai.size();

                double sumB = 0;
                for (int balas : b.nd_balai) {
                    sumB += balas;
                }
                double vidurkisB = sumB / b.nd_balai.size();

                return vidurkisA > vidurkisB;
            });
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Rikiavimas užtruko: " << duration.count() << " sekundžių." << std::endl;
}