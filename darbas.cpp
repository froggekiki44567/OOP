#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <limits>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// struktura kuri saugo studento duomenis
struct Student {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd_balai;
    int egzaminas;
};

// funkcija kuri suskaiciuoja vidurki is pazymiu
double skaiciuotiVidurki(const std::vector<int>& pazymiai) {
    return pazymiai.empty() ? 0.0 : std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0) / pazymiai.size();
}

// funckija kuri patikrina ar nera ivesti skaiciai yra raides (varde, pavardėje)
bool Patikra(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

// medianos skaiciavimo forma
double skaiciuotiMediana(std::vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;
    std::sort(pazymiai.begin(), pazymiai.end());
    size_t dydis = pazymiai.size();
    return (dydis % 2 == 0) ? (pazymiai[dydis/2 - 1] + pazymiai[dydis/2]) / 2.0 : pazymiai[dydis/2];
}

// funkcija generuoti atsitiktinius studento duomenis
Student generuotiStudenta() {
    Student studentas;
    std::string vardai[] = {"Jonas", "Petras", "Ona", "Ieva", "Marius"};
    std::string pavardes[] = {"Jonaitis", "Petraitis", "Onaitė", "Ievaitė", "Maraitis"};
    studentas.vardas = vardai[rand() % 5];
    studentas.pavarde = pavardes[rand() % 5];
    return studentas;
}

// funkcija generuoti atsitiktinius namų darbų pažymius
void generuotiPazymius(Student& studentas) {
    int nd_kiekis = rand() % 5 + 1;
    for (int i = 0; i < nd_kiekis; i++) {
        studentas.nd_balai.push_back(rand() % 11);
    }
    studentas.egzaminas = rand() % 11;
}

int main() {
    srand(time(0));
    std::vector<Student> studentai;
    char pasirinkimas;
    char autogenravimas;
    int studentuSk;

    std::cout << "Ar norite sugeneruoti studentų vardus ir pavardes automatiškai? (y/n): ";
    std::cin >> autogenravimas;

    if (autogenravimas == 'y' || autogenravimas == 'Y') {
        std::cout << "Kiek studentų norite sugeneruoti? ";
        std::cin >> studentuSk;
    }

    do {
        Student studentas;
        if (autogenravimas == 'y' || autogenravimas == 'Y') {
            for (int i = 0; i < studentuSk; i++) {
                studentas = generuotiStudenta();
                char generuotiPazymiusPasirinkimas;
                std::cout << "Ar norite sugeneruoti namų darbų pažymius automatiškai (kiekvienam studentui atskirtai spaust reikia)? (y/n): ";
                std::cin >> generuotiPazymiusPasirinkimas;

                if (generuotiPazymiusPasirinkimas == 'y' || generuotiPazymiusPasirinkimas == 'Y') {
                    generuotiPazymius(studentas);
                } else {
                    while (true) {
                        std::cout << "Įveskite namų darbų pažymius (baigti įvesdami ne skaičių): ";
                        int balas;
                        bool validInput = false;
                        while (std::cin >> balas) {
                            if (balas < 0 || balas > 10) {
                                std::cout << "Įveskite balą nuo 0 iki 10!\n";
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                continue;
                            }
                            studentas.nd_balai.push_back(balas);
                            validInput = true;
                        }
                        if (!validInput && studentas.nd_balai.empty()) {
                            std::cout << "Turite įvesti bent vieną namų darbą! Bandykite dar kartą.\n";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }

                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "Įveskite egzamino balą (nuo 0 iki 10): ";
                    while (!(std::cin >> studentas.egzaminas) || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
                        std::cout << "Neteisingas įvedimas. Egzamino balas turi būti nuo 0 iki 10. Bandykite dar kartą: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }

                studentai.push_back(studentas);
            }
            break;
        } else {
            std::cout << "\nĮveskite studento vardą: ";
            while (true) {
                std::cin >> studentas.vardas;
                if (Patikra(studentas.vardas)) break;
                std::cout << "Vardas turi būti sudarytas tik iš raidžių. Bandykite dar kartą: ";
            }

            std::cout << "Įveskite studento pavardę: ";
            while (true) {
                std::cin >> studentas.pavarde;
                if (Patikra(studentas.pavarde)) break;
                std::cout << "Pavardė turi būti sudaryta tik iš raidžių. Bandykite dar kartą: ";
            }

            char generuotiPazymiusPasirinkimas;
            std::cout << "Ar norite sugeneruoti namų darbų pažymius automatiškai? (y/n): ";
            std::cin >> generuotiPazymiusPasirinkimas;

            if (generuotiPazymiusPasirinkimas == 'y' || generuotiPazymiusPasirinkimas == 'Y') {
                generuotiPazymius(studentas);
            } else {
                while (true) {
                    std::cout << "Įveskite namų darbų pažymius (baigti įvesdami ne skaičių): ";
                    int balas;
                    bool validInput = false;
                    while (std::cin >> balas) {
                        if (balas < 0 || balas > 10) {
                            std::cout << "Įveskite balą nuo 0 iki 10!\n";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }
                        studentas.nd_balai.push_back(balas);
                        validInput = true;
                    }
                    if (!validInput && studentas.nd_balai.empty()) {
                        std::cout << "Turite įvesti bent vieną namų darbą! Bandykite dar kartą.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    } else {
                        break;
                    }
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Įveskite egzamino balą (nuo 0 iki 10): ";
                while (!(std::cin >> studentas.egzaminas) || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
                    std::cout << "Neteisingas įvedimas. Egzamino balas turi būti nuo 0 iki 10. Bandykite dar kartą: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            studentai.push_back(studentas);

            std::cout << "Ar norite pridėti dar vieną studentą? (y/n): ";
            std::cin >> pasirinkimas;
        }

    } while (pasirinkimas == 'y' || pasirinkimas == 'Y');

    std::cout << "\nVardas        Pavardė       Galutinis (Vidurkis)     Galutinis (Mediana)" << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    for (const auto& studentas : studentai) {
        double vidurkis = skaiciuotiVidurki(studentas.nd_balai);
        double galutinisVidurkis = 0.4 * vidurkis + 0.6 * studentas.egzaminas;
        double mediana = skaiciuotiMediana(studentas.nd_balai);
        double galutinisMediana = 0.4 * mediana + 0.6 * studentas.egzaminas;

        std::cout << std::left << std::setw(12) << studentas.vardas
                  << std::setw(14) << studentas.pavarde
                  << std::fixed << std::setprecision(2) << std::setw(20) << galutinisVidurkis
                  << galutinisMediana << std::endl;
    }

    return 0;
}
