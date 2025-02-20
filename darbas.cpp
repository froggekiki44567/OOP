#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <limits>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono> // Add this include for timing

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

// funkcija kuri nuskaito studentu duomenis is failo
std::vector<Student> nuskaitytiStudentus(const std::string& failoPavadinimas) {
    std::vector<Student> studentai;
    std::ifstream inFile(failoPavadinimas);
    if (inFile.is_open()) {
        std::string line;
        // Skip the first line (header)
        std::getline(inFile, line);
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            Student studentas;
            iss >> studentas.vardas >> studentas.pavarde;
            int pazymys;
            std::vector<int> pazymiai;
            while (iss >> pazymys) {
                pazymiai.push_back(pazymys);
            }
            if (!pazymiai.empty()) {
                studentas.nd_balai = pazymiai;
                studentas.egzaminas = studentas.nd_balai.back();
                studentas.nd_balai.pop_back();
                studentai.push_back(studentas);
            } else {
                std::cerr << "Klaida: Studentas " << studentas.vardas << " " << studentas.pavarde << " neturi pažymių." << std::endl;
            }
        }
        inFile.close();
    } else {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
    }
    return studentai;
}

// funkcija kuri raso rezultatus i faila
void rasytiRezultatus(const std::string& failoPavadinimas, const std::vector<Student>& studentai) {
    std::ofstream outFile(failoPavadinimas);
    if (outFile.is_open()) {
        outFile << std::left << std::setw(12) << "Vardas" 
                << std::setw(14) << "Pavardė" 
                << std::setw(25) << "Galutinis (Vidurkis)" 
                << "Galutinis (Mediana)" << std::endl;
        outFile << "--------------------------------------------------------------------------" << std::endl;
        for (const auto& studentas : studentai) {
            double vidurkis = skaiciuotiVidurki(studentas.nd_balai);
            double galutinisVidurkis = 0.4 * vidurkis + 0.6 * studentas.egzaminas;
            double mediana = skaiciuotiMediana(studentas.nd_balai);
            double galutinisMediana = 0.4 * mediana + 0.6 * studentas.egzaminas;

            outFile << std::left << std::setw(12) << studentas.vardas
                    << std::setw(14) << studentas.pavarde
                    << std::fixed << std::setprecision(2) << std::setw(25) << galutinisVidurkis
                    << galutinisMediana << std::endl;
        }
        outFile.close();
    } else {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
    }
}

// funkcija kuri spausdina rezultatus i ekrana
void spausdintiRezultatus(const std::vector<Student>& studentai) {
    std::cout << "\nVardas        Pavardė       Galutinis (Vidurkis)     Galutinis (Mediana)" << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    for (const auto& studentas : studentai) {
        double vidurkis = skaiciuotiVidurki(studentas.nd_balai);
        double galutinisVidurkis = 0.4 * vidurkis + 0.6 * studentas.egzaminas;
        double mediana = skaiciuotiMediana(studentas.nd_balai);
        double galutinisMediana = 0.4 * mediana + 0.6 * studentas.egzaminas;

        std::cout << std::left << std::setw(12) << studentas.vardas
                  << std::setw(14) << studentas.pavarde
                  << std::fixed << std::setprecision(2) << std::setw(25) << galutinisVidurkis
                  << galutinisMediana << std::endl;
    }
}

// palyginimo funkcijos rikiavimui
bool palygintiPagalVarda(const Student& a, const Student& b) {
    return a.vardas < b.vardas;
}

bool palygintiPagalPavarde(const Student& a, const Student& b) {
    return a.pavarde < b.pavarde;
}

bool palygintiPagalVidurkiAsc(const Student& a, const Student& b) {
    double vidurkisA = 0.4 * skaiciuotiVidurki(a.nd_balai) + 0.6 * a.egzaminas;
    double vidurkisB = 0.4 * skaiciuotiVidurki(b.nd_balai) + 0.6 * b.egzaminas;
    return vidurkisA < vidurkisB;
}

bool palygintiPagalVidurkiDesc(const Student& a, const Student& b) {
    double vidurkisA = 0.4 * skaiciuotiVidurki(a.nd_balai) + 0.6 * a.egzaminas;
    double vidurkisB = 0.4 * skaiciuotiVidurki(b.nd_balai) + 0.6 * b.egzaminas;
    return vidurkisA > vidurkisB;
}

bool palygintiPagalMedianaAsc(const Student& a, const Student& b) {
    double medianaA = 0.4 * skaiciuotiMediana(a.nd_balai) + 0.6 * a.egzaminas;
    double medianaB = 0.4 * skaiciuotiMediana(b.nd_balai) + 0.6 * b.egzaminas;
    return medianaA < medianaB;
}

bool palygintiPagalMedianaDesc(const Student& a, const Student& b) {
    double medianaA = 0.4 * skaiciuotiMediana(a.nd_balai) + 0.6 * a.egzaminas;
    double medianaB = 0.4 * skaiciuotiMediana(b.nd_balai) + 0.6 * b.egzaminas;
    return medianaA > medianaB;
}

// funkcija kuri rikiuoja studentus pagal pasirinkima
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

int main() {
    srand(time(0));
    std::vector<std::string> testFiles = {"studentai100000.txt", "studentai10000.txt", "studentai10000.txt"};
    int numTests = 5;
    double totalTime = 0.0;

    for (const auto& file : testFiles) {
        double fileTotalTime = 0.0;
        for (int i = 0; i < numTests; ++i) {
            auto start = std::chrono::high_resolution_clock::now();

            std::vector<Student> studentai = nuskaitytiStudentus(file);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            fileTotalTime += duration.count();

            std::cout << "Failo " << file << " atidarymas ir nuskaitymas užtruko: " << duration.count() << " sekundžių\n";

            // Rikiuoti studentus pagal pasirinkimą
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

            // Pasirinkti išvesties būdą
            char outputChoice;
            std::cout << "Ar norite spausdinti rezultatus į ekraną ar į failą? (e/f): ";
            std::cin >> outputChoice;
            if (outputChoice == 'e' || outputChoice == 'E') {
                // Spausdinti rezultatus į ekraną
                spausdintiRezultatus(studentai);
            } else if (outputChoice == 'f' || outputChoice == 'F') {
                // Rašyti rezultatus į failą
                rasytiRezultatus("kursiokai.txt", studentai);
            } else {
                std::cout << "Neteisingas pasirinkimas!" << std::endl;
            }
        }
        double averageTime = fileTotalTime / numTests;
        totalTime += averageTime;
        std::cout << "Vidutinis laikas failui " << file << ": " << averageTime << " sekundžių\n";
    }

    double overallAverageTime = totalTime / testFiles.size();
    std::cout << "Bendras vidutinis laikas: " << overallAverageTime << " sekundžių\n";

    return 0;
}
