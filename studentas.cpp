// student.cpp - Implementation of student-related functions
#include "studentas.h"
#include "papild.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <random>
#include <limits>

// Skaičiavimo funkcijos
double skaiciuotiVidurki(const std::vector<int>& pazymiai) {
    return pazymiai.empty() ? 0.0 : std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0) / pazymiai.size();
}

double skaiciuotiMediana(std::vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;
    std::sort(pazymiai.begin(), pazymiai.end());
    size_t dydis = pazymiai.size();
    return (dydis % 2 == 0) ? (pazymiai[dydis/2 - 1] + pazymiai[dydis/2]) / 2.0 : pazymiai[dydis/2];
}

double galutinisPazymys(const Student& studentas, bool naudotiVidurki) {
    double ndRezultatas = naudotiVidurki ? 
                          skaiciuotiVidurki(studentas.nd_balai) : 
                          skaiciuotiMediana(studentas.nd_balai);
    return 0.4 * ndRezultatas + 0.6 * studentas.egzaminas;
}

// Generavimo funkcijos
Student generuotiStudenta() {
    Student studentas;
    std::string vardai[] = {"Jonas", "Petras", "Ona", "Ieva", "Marius"};
    std::string pavardes[] = {"Jonaitis", "Petraitis", "Onaitė", "Ievaitė", "Maraitis"};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 4);

    studentas.vardas = vardai[dist(gen)];
    studentas.pavarde = pavardes[dist(gen)];
    return studentas;
}

void generuotiPazymius(Student& studentas) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);
    std::uniform_int_distribution<> nd_dist(1, 10); // Bent 1 ND pažymys

    int nd_kiekis = nd_dist(gen);
    studentas.nd_balai.clear();
    for (int i = 0; i < nd_kiekis; i++) {
        studentas.nd_balai.push_back(dist(gen));
    }
    studentas.egzaminas = dist(gen);
}

std::vector<Student> generuotiStudentus(int kiekis) {
    std::vector<Student> studentai;
    for (int i = 0; i < kiekis; i++) {
        Student studentas = generuotiStudenta();
        generuotiPazymius(studentas);
        studentai.push_back(studentas);
    }
    return studentai;
}

std::vector<Student> ivestiStudentus() {
    std::vector<Student> studentai;
    char pasirinkimas;

    do {
        Student studentas;

        // Input student name
        while (true) {
            try {
                std::cout << "\nĮveskite studento vardą: ";
                std::cin >> studentas.vardas;

                if (std::cin.fail()) {
                    throw std::runtime_error("Netinkama įvestis!");
                }
                if (!tikrintiRaides(studentas.vardas)) {
                    throw std::runtime_error("Vardas turi būti sudarytas tik iš raidžių!");
                }

                break;  // Teisinga įvestis – išeiname iš ciklo
            } catch (const std::exception& e) {
                std::cerr << "Klaida įvedant vardą: " << e.what() << " Bandykite dar kartą.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        // Input student surname
        while (true) {
            try {
                std::cout << "Įveskite studento pavardę: ";
                std::cin >> studentas.pavarde;

                if (!tikrintiRaides(studentas.pavarde)) {
                    throw std::runtime_error("Pavardė turi būti sudaryta tik iš raidžių!");
                }

                break;  // Teisinga įvestis – išeiname iš ciklo
            } catch (const std::exception& e) {
                std::cerr << "Klaida įvedant pavardę: " << e.what() << " Bandykite dar kartą.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        // Input homework grades
        while (true) {
            try {
                std::cout << "Įveskite namų darbų pažymius (baigti įvesdami ne skaičių): ";
                int balas;
                studentas.nd_balai.clear();
                bool validInput = false;

                while (std::cin >> balas) {
                    if (balas < 0 || balas > 10) {
                        std::cerr << "Neteisingas pažymys. Pažymiai turi būti nuo 0 iki 10. Bandykite dar kartą: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                    studentas.nd_balai.push_back(balas);
                    validInput = true;
                }

                if (!validInput) {
                    throw std::runtime_error("Nenurodyti namų darbų pažymiai!");
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            } catch (const std::exception& e) {
                std::cerr << "Klaida įvedant pažymius: " << e.what() << " Bandykite dar kartą.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        // Input exam grade
        while (true) {
            try {
                std::cout << "Įveskite egzamino balą (nuo 0 iki 10): ";
                std::cin >> studentas.egzaminas;

                if (std::cin.fail() || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
                    throw std::runtime_error("Egzamino balas turi būti nuo 0 iki 10!");
                }

                break;
            } catch (const std::exception& e) {
                std::cerr << "Klaida įvedant egzamino balą: " << e.what() << " Bandykite dar kartą.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        studentai.push_back(studentas);

        std::cout << "Ar norite pridėti dar vieną studentą? (y/n): ";
        std::cin >> pasirinkimas;
    } while (pasirinkimas == 'y' || pasirinkimas == 'Y');

    return studentai;
}

// Rikiavimo funkcijos
bool palygintiPagalVarda(const Student& a, const Student& b) {
    return a.vardas < b.vardas;
}

bool palygintiPagalPavarde(const Student& a, const Student& b) {
    return a.pavarde < b.pavarde;
}

bool palygintiPagalVidurkiAsc(const Student& a, const Student& b) {
    return galutinisPazymys(a, true) < galutinisPazymys(b, true);
}

bool palygintiPagalVidurkiDesc(const Student& a, const Student& b) {
    return galutinisPazymys(a, true) > galutinisPazymys(b, true);
}

bool palygintiPagalMedianaAsc(const Student& a, const Student& b) {
    return galutinisPazymys(a, false) < galutinisPazymys(b, false);
}

bool palygintiPagalMedianaDesc(const Student& a, const Student& b) {
    return galutinisPazymys(a, false) > galutinisPazymys(b, false);
}

void rikiuotiStudentus(std::vector<Student>& studentai, char pasirinkimas, char tvarka) {
    switch (pasirinkimas) {
        case '1':
            std::sort(studentai.begin(), studentai.end(), palygintiPagalVarda);
            break;
        case '2':
            std::sort(studentai.begin(), studentai.end(), palygintiPagalPavarde);
            break;
        case '3':
            if (tvarka == 'a' || tvarka == 'A') {
                std::sort(studentai.begin(), studentai.end(), palygintiPagalVidurkiAsc);
            } else {
                std::sort(studentai.begin(), studentai.end(), palygintiPagalVidurkiDesc);
            }
            break;
        case '4':
            if (tvarka == 'a' || tvarka == 'A') {
                std::sort(studentai.begin(), studentai.end(), palygintiPagalMedianaAsc);
            } else {
                std::sort(studentai.begin(), studentai.end(), palygintiPagalMedianaDesc);
            }
            break;
        default:
            std::cerr << "Neteisingas pasirinkimas!" << std::endl;
            break;
    }
}

void rikiuotiStudentusPagalPasirinkima(std::vector<Student>& studentai) {
    char rikiavimoPasirinkimas;
    std::cout << "Pasirinkite rikiavimo būdą:\n";
    std::cout << "1. Pagal vardą\n";
    std::cout << "2. Pagal pavardę\n";
    std::cout << "3. Pagal galutinį vidurkį\n";
    std::cout << "4. Pagal galutinę medianą\n";
    std::cout << "Pasirinkimas: ";
    std::cin >> rikiavimoPasirinkimas;

    char tvarka = 'a';
    if (rikiavimoPasirinkimas == '3' || rikiavimoPasirinkimas == '4') {
        std::cout << "Pasirinkite rikiavimo tvarką:\n";
        std::cout << "a. Didėjimo tvarka\n";
        std::cout << "d. Mažėjimo tvarka\n";
        std::cout << "Pasirinkimas: ";
        std::cin >> tvarka;
    }

    rikiuotiStudentus(studentai, rikiavimoPasirinkimas, tvarka);
}