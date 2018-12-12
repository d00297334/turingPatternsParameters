CSSFLAGS := -std=c++11 -o
CXXFLAGS := -std=c++11 -g
CXXFLAGS := -std=c++11 -Wall -g  -DUSE_COLOR_TABLE
CXX := g++
TARGETS := turing_command

all: $(TARGETS)

run: $(TARGETS)
	./turing_command

memtest: turing_command
	valgrind --leak-check=full ./turing_command

debug: turing_command
	gdb ./turing_command

turing_command: turing_command.o TuringPattern.o JuliaSet.o MandelbrotSet.o PPM.o ColorTable.o ComplexFractal.o
	$(CXX) $(CXXFLAGS) -o $@ $^

turing_command.o: turing_command.cpp JuliaSet.h PPM.h ColorTable.h MandelbrotSet.h ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

PPM.o: PPM.cpp PPM.h
	$(CXX) $(CXXFLAGS) -c $<

TuringPattern.o: TuringPattern.cpp TuringPattern.h ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

JuliaSet.o: JuliaSet.cpp JuliaSet.h PPM.h ColorTable.h ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h PPM.h ColorTable.h ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

ComplexFractal.o: ComplexFractal.cpp PPM.h ColorTable.h ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

ColorTable.o: ColorTable.cpp ColorTable.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	-rm -f turing_command
	-rm -f *.o
	-rm -f *~
