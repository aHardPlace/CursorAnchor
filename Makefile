CXX  = g++
EXE  = CursorAnchor.exe
OBJS = \
	resources.o    \
	CursorAnchor.o

CXXFLAGS  = -s -O3
CXXFLAGS += -std=c++11 -fno-exceptions -fno-rtti
CXXFLAGS += -Wall -Wextra -pedantic

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXE)

simple: CursorAnchor.o
	$(CXX) $(CXXFLAGS) CursorAnchor.o -o $(EXE)

CursorAnchor.o: CursorAnchor.cpp
	$(CXX) $(CXXFLAGS) -c $<

resources.o: resources.rc
	windres -i resources.rc -o resources.o

clean:
	del *.o && del $(EXE)