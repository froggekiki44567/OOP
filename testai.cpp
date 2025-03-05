#include "testai.h"
#include "generavimasf.h"
#include <iostream>
#include <vector>
#include <string>

void atliktiLaikoTestusSuFailais(std::vector<std::string>& failugen) {
    while (!failugen.empty()) {
        std::cout << "Pasirinkite failą testavimui:\n";
        for (size_t i = 0; i < failugen.size(); ++i) {
            std::cout << i + 1 << ". " << failugen[i] << "\n";
        }
        std::cout << "Pasirinkimas: ";
        int failoPasirinkimas;
        std::cin >> failoPasirinkimas;

        if (failoPasirinkimas >= 1 && failoPasirinkimas <= failugen.size()) {
            rusiotiStudentusISFailus(failugen[failoPasirinkimas - 1], failugen);
        } else {
            std::cout << "Neteisingas pasirinkimas!" << std::endl;
        }

        char pasirinkimas;
        std::cout << "Ar norite atlikti testus su kitais failais? (y/n): ";
        std::cin >> pasirinkimas;

        if (pasirinkimas != 'Y' && pasirinkimas != 'y') {
            break;
        }
    }
}