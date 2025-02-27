# makefile skirtas sukurti viena paleidziama faila

CXX = g++
CXXFLAGS = -std=c++20 -Wall


TARGET = kursiokai


SRCS = main.cpp studentas.cpp failo_oper.cpp papild.cpp


all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)


clean:
	rm -f $(TARGET)
