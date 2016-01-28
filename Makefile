CXX  = g++
EXE  = build\CursorAnchor.exe
OBJS = \
	build\resources.o		\
	build\CursorAnchor.o

CXXFLAGS  = -s -O3
CXXFLAGS += -std=c++11 -fno-exceptions -fno-rtti
CXXFLAGS += -Wall -Wextra -Weffc++ -pedantic

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXE)

simple: build\CursorAnchor.o
	$(CXX) $(CXXFLAGS) CursorAnchor.o -o $(EXE)

build\CursorAnchor.o: src\CursorAnchor.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build\resources.o: src\resources.rc
	windres -i src\resources.rc -o build\resources.o

clean:
	del *.o && del $(EXE)