#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <limits>
#include <cctype>
#include <algorithm>

// Struktūra studento duomenims
struct Student {
    std::string vardas;
    std::string pavarde;
    int* nd_balai;
    int nd_kiekis;
    int egzaminas;
};

// Susieto sąrašo mazgas
struct Node {
    Student studentas;
    Node* next;
};

// Funkcija tikrinanti, ar vardas ir pavardė sudaryti tik iš raidžių
bool Patikra(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c)) return false;
    }
    return true;
}

// Funkcija apskaičiuoti vidurkį
double skaiciuotiVidurki(const int* pazymiai, int dydis) {
    if (dydis == 0) return 0.0;
    int suma = 0;
    for (int i = 0; i < dydis; i++) {
        suma += pazymiai[i];
    }
    return static_cast<double>(suma) / dydis;
}

// Funkcija apskaičiuoti medianą
double skaiciuotiMediana(int* pazymiai, int dydis) {
    if (dydis == 0) return 0.0;
    std::sort(pazymiai, pazymiai + dydis);
    return (dydis % 2 == 0) ? (pazymiai[dydis/2 - 1] + pazymiai[dydis/2]) / 2.0 : pazymiai[dydis/2];
}

int main() {
    Node* head = nullptr;
    char pasirinkimas;
    
    do {
        Student studentas;
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
        
        studentas.nd_balai = nullptr;
        studentas.nd_kiekis = 0;
        
        std::cout << "Įveskite namų darbų pažymius (baigti įvesdami ne skaičių): ";
        int balas;
        while (std::cin >> balas) {
            if (balas < 0 || balas > 10) {
                std::cout << "Įveskite balą nuo 0 iki 10!\n";
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
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Įveskite egzamino balą (nuo 0 iki 10): ";
        while (!(std::cin >> studentas.egzaminas) || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
            std::cout << "Neteisingas įvedimas. Egzamino balas turi būti nuo 0 iki 10. Bandykite dar kartą: ";
        }
        
        Node* naujas = new Node{studentas, head};
        head = naujas;
        
        std::cout << "Ar norite pridėti dar vieną studentą? (y/n): ";
        std::cin >> pasirinkimas;
        
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
