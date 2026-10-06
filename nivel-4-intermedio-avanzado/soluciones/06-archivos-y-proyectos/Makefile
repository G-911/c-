CXX = g++
CXXFLAGS = -std=c++17 -Wall

# El programa final se arma con los dos .o
prog: main.o agenda.o
	$(CXX) $(CXXFLAGS) main.o agenda.o -o prog

# Cada .o depende de su .cpp y del .h que incluye
main.o: main.cpp agenda.h
	$(CXX) $(CXXFLAGS) -c main.cpp

agenda.o: agenda.cpp agenda.h
	$(CXX) $(CXXFLAGS) -c agenda.cpp

clean:
	rm -f *.o prog
