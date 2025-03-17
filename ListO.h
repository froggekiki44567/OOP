#ifndef LISTO_H
#define LISTO_H

#include <list>
#include "studentas.h"

void rusiotiStudentusISFailusList(const std::string& failas, std::list<std::string>& failugenList);
void rikiuotiStudentusPriesSkirtymaList(std::list<Student>& studentai);

#endif