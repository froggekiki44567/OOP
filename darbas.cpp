#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <limits>
#include <cctype>

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
// medianaos skaiciavimo forma
double skaiciuotiMediana(std::vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;
    std::sort(pazymiai.begin(), pazymiai.end());
    size_t dydis = pazymiai.size();
    return (dydis % 2 == 0) ? (pazymiai[dydis/2 - 1] + pazymiai[dydis/2]) / 2.0 : pazymiai[dydis/2];
}

int main() {
    std::vector<Student> studentai;
    char pasirinkimas;
    do {
        Student studentas;
        std::cout << "\nĮveskite studento vardą: ";
        while (true) {
            std::cin >> studentas.vardas;
            if (Patikra(studentas.vardas)) {
                break;
            } else {
                std::cout << "Vardas turi būti sudarytas tik iš raidžių. Bandykite dar kartą: ";
            }
        }

        std::cout << "Įveskite studento pavardę: ";
        while (true) {
            std::cin >> studentas.pavarde;
            if (Patikra(studentas.pavarde)) {
                break;
            } else {
                std::cout << "Pavardė turi būti sudaryta tik iš raidžių. Bandykite dar kartą: ";
            }
        }

        while(true){
            std::cout << "Įveskite namų darbų pažymius (baigti įvesdami ne skaičių): ";
            int balas;
            while (std::cin >> balas) {
                if (balas < 0 || balas > 10) {
                    std::cout << "Įveskite balą nuo 0 iki 10!\n";
                    continue;
                }
                studentas.nd_balai.push_back(balas);
            }
            if (studentas.nd_balai.empty()) {
                std::cout << "Turite įvesti bent vieną namų darbą! Programa paleidžiama iš naujo!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        std::cout << "Įveskite egzamino balą (nuo 0 iki 10): ";
        while (!(std::cin >> studentas.egzaminas) || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
            std::cout << "Neteisingas įvedimas. Egzamino balas turi būti nuo 0 iki 10. Bandykite dar kartą: ";
        }
        
        studentai.push_back(studentas);
        
        std::cout << "Ar norite pridėti dar vieną studentą? (y/n): ";
        std::cin >> pasirinkimas;
        
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
                  << std::fixed << std::setprecision(2) << galutinisVidurkis << galutinisMediana << std::endl;
    }
    
    return 0;
}
