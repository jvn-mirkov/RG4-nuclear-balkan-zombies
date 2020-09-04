PROGRAM = NBZ
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra
LDLIBS = -lglut -lGLU -lGL -lm

$(PROGRAM) : ControlMatrix.o Map.o Box.o Player.o Bomb.o main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS) && ./nbz

ControlMatrix.o: ControlMatrix.cpp ControlMatrix.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS)

Map.o: Map.cpp Map.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS)

Box.o: Box.cpp Box.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS)

Player.o: Player.cpp Player.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS)

Bomb.o: Bomb.cpp Bomb.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS)

.PHONY : clean

clean:
	-rm *.o
