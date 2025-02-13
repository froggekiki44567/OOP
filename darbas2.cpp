#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <limits>
#include <cctype>
#include <algorithm>
#include <ctime>

// struktura kuri saugo studento duomenis
struct Student {
    std::string vardas;
    std::string pavarde;
    int* nd_balai;
    int nd_kiekis;
    int egzaminas;
};

// susieto sąrašo mazgas
struct Node {
    Student studentas;
    Node* next;
};

// funkcija kuri suskaiciuoja vidurki is pazymiu
double skaiciuotiVidurki(const int* pazymiai, int dydis) {
    if (dydis == 0) return 0.0;
    int suma = 0;
    for (int i = 0; i < dydis; i++) {
        suma += pazymiai[i];
    }
    return static_cast<double>(suma) / dydis;
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

// medianaos skaiciavimo forma
double skaiciuotiMediana(int* pazymiai, int dydis) {
    if (dydis == 0) return 0.0;
    std::sort(pazymiai, pazymiai + dydis);
    return (dydis % 2 == 0) ? (pazymiai[dydis/2 - 1] + pazymiai[dydis/2]) / 2.0 : pazymiai[dydis/2];
}

// funkcija generuoti atsitiktinius studento duomenis
Student generuotiStudenta() {
    Student studentas;
    std::string vardai[] = {"Jonas", "Petras", "Ona", "Ieva", "Marius"};
    std::string pavardes[] = {"Jonaitis", "Petraitis", "Onaitė", "Ievaitė", "Maraitis"};
    studentas.vardas = vardai[rand() % 5];
    studentas.pavarde = pavardes[rand() % 5];
    studentas.nd_kiekis = rand() % 5 + 1;
    studentas.nd_balai = new int[studentas.nd_kiekis];
    for (int i = 0; i < studentas.nd_kiekis; i++) {
        studentas.nd_balai[i] = rand() % 11;
    }
    studentas.egzaminas = rand() % 11;
    return studentas;
}

// funkcija generuoti atsitiktinius namų darbų pažymius
void generuotiPazymius(Student& studentas) {
    studentas.nd_kiekis = rand() % 5 + 1;
    studentas.nd_balai = new int[studentas.nd_kiekis];
    for (int i = 0; i < studentas.nd_kiekis; i++) {
        studentas.nd_balai[i] = rand() % 11;
    }
}

int main() {
    srand(time(0));
    Node* head = nullptr;
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
                Node* naujas = new Node;
                naujas->studentas = studentas;
                naujas->next = head;
                head = naujas;
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
            std::cout << "Ar norite sugeneruoti namų darbų pažymius automatiškai (kiekvienas studentas bus nauja eilute)? (y/n): ";
            std::cin >> generuotiPazymiusPasirinkimas;

            if (generuotiPazymiusPasirinkimas == 'y' || generuotiPazymiusPasirinkimas == 'Y') {
                generuotiPazymius(studentas);
            } else {
                studentas.nd_balai = nullptr;
                studentas.nd_kiekis = 0;

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

                        int* temp = new int[studentas.nd_kiekis + 1];
                        for (int i = 0; i < studentas.nd_kiekis; i++) {
                            temp[i] = studentas.nd_balai[i];
                        }
                        temp[studentas.nd_kiekis] = balas;
                        delete[] studentas.nd_balai;
                        studentas.nd_balai = temp;
                        studentas.nd_kiekis++;
                        validInput = true;
                    }
                    if (!validInput && studentas.nd_kiekis == 0) {
                        std::cout << "Turite įvesti bent vieną namų darbą! Bandykite dar kartą.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    } else {
                        break;
                    }
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

            Node* naujas = new Node;
            naujas->studentas = studentas;
            naujas->next = head;
            head = naujas;

            std::cout << "Ar norite pridėti dar vieną studentą? (y/n): ";
            std::cin >> pasirinkimas;
        }

    } while (pasirinkimas == 'y' || pasirinkimas == 'Y');

    std::cout << "\nVardas        Pavardė       Galutinis (Vidurkis)     Galutinis (Mediana)" << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;

    Node* current = head;
    while (current) {
        double vidurkis = skaiciuotiVidurki(current->studentas.nd_balai, current->studentas.nd_kiekis);
        double galutinisVidurkis = 0.4 * vidurkis + 0.6 * current->studentas.egzaminas;
        double mediana = skaiciuotiMediana(current->studentas.nd_balai, current->studentas.nd_kiekis);
        double galutinisMediana = 0.4 * mediana + 0.6 * current->studentas.egzaminas;

        std::cout << std::left << std::setw(12) << current->studentas.vardas
                  << std::setw(14) << current->studentas.pavarde
                  << std::fixed << std::setprecision(2) << std::setw(20) << galutinisVidurkis
                  << galutinisMediana << std::endl;

        current = current->next;
    }

    while (head) {
        Node* temp = head;
        head = head->next;
        delete[] temp->studentas.nd_balai;
        delete temp;
    }

    return 0;
}
