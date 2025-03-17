#include "DequeO.h"
#include "studentas.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <iostream>
#include <deque>

void rusiotiStudentusISFailusDeque(const std::string& failopavadinimas, std::deque<std::string>& failugenDeque) {
    bool darboPabaiga = false;
    if (darboPabaiga) {
        return;
    }
    std::ifstream inFile(failopavadinimas);
    if (!inFile) {
        std::cerr << "Nepavyko atidaryti failo: " << failopavadinimas << std::endl;
        return;
    }
    std::deque<Student> studentai;
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

    rikiuotiStudentusPriesSkirstymaDeq(studentai);

    char strategijosPasirinkimas;
    std::cout << "Pasirinkite strategiją:\n";
    std::cout << "1. Paprasta strategija\n";
    std::cout << "2. Bendro studentų konteinerio skaidymas\n";
    std::cout << "3. Naudojant algoritmus\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> strategijosPasirinkimas;

    if (strategijosPasirinkimas == '1') {
        std::deque<Student> vargsciukai;
        std::deque<Student> kietiakai;

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
        std::deque<Student> vargsciukai;

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
        std::deque<Student> vargsciukai;
        std::deque<Student> kietiakai;

        auto start3 = std::chrono::high_resolution_clock::now();

        // Using std::partition to separate vargsciukai and kietiakai
        auto it = std::partition(studentai.begin(), studentai.end(), [](const Student& studentas) {
            return galutinisPazymys(studentas, true) < 5.0;
        });

        // Copy vargsciukai to vargsciukai deque
        std::copy(studentai.begin(), it, std::back_inserter(vargsciukai));
        // Copy kietiakai to kietiakai deque
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

    failugenDeque.erase(std::remove(failugenDeque.begin(), failugenDeque.end(), failopavadinimas), failugenDeque.end());
    while (!failugenDeque.empty()) {
        char pasirinkimas;
        std::cout << "Ar norite baigti darbą? (y/n): ";
        std::cin >> pasirinkimas;

        if (pasirinkimas == 'Y' || pasirinkimas == 'y') {
            darboPabaiga = true;
            return; // Exit the function to finish the work
        } else {
            std::cout << "Pasirinkite failą naudojimui:\n";
            for (size_t i = 0; i < failugenDeque.size(); ++i) {
                std::cout << i + 1 << ". " << failugenDeque[i] << "\n";
            }
            std::cout << "Pasirinkimas: ";
            int failoPasirinkimas;
            std::cin >> failoPasirinkimas;

            if (failoPasirinkimas >= 1 && failoPasirinkimas <= failugenDeque.size()) {
                rusiotiStudentusISFailusDeque(failugenDeque[failoPasirinkimas - 1], failugenDeque);
            } else {
                std::cout << "Neteisingas pasirinkimas!" << std::endl;
            }
        }
    }
}

void rikiuotiStudentusPriesSkirstymaDeq(std::deque<Student>& studentai) {
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
        std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
            return a.vardas < b.vardas;
        });
    } else if (rikiavimoPasirinkimas == '2') {
        std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
            return a.pavarde < b.pavarde;
        });
    } else if (rikiavimoPasirinkimas == '3') {
        if (tvarka == 'a') {
            std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
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
            std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
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