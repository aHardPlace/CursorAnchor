CC	 = gcc
CXX  = g++
OBJS = 		\
	resources.o	\
	CursorAnchor.o

COMPILER_FLAGS	= -s -O3
WARNING_FLAGS	= -Wall -Wextra -pedantic
EXE = CursorAnchor.exe

all: $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(WARNING_FLAGS) $(COMPILER_FLAGS)

simple: CursorAnchor.o
	$(CXX) -o $(EXE) CursorAnchor.o $(WARNING_FLAGS) $(COMPILER_FLAGS)

CursorAnchor.o: CursorAnchor.cpp
	$(CXX) -c $< $(WARNING_FLAGS) $(COMPILER_FLAGS)

resources.o: resources.rc
	windres -i resources.rc -o resources.o

clean:
	del *.o && del $(EXE)