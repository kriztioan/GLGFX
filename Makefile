
CPP_FILES:=$(wildcard *.cpp)
OBJ_FILES:=$(patsubst %.cpp,%.o,$(CPP_FILES))
PROGS:=$(patsubst %.cpp,%,$(CPP_FILES))
CPPFLAGS:=-O2
LIBS:=-lz

all: $(PROGS)

$(PROGS): % : %.o
	$(CXX) -o $@ $< $(CPPFLAGS) ${LIBS}

$(OBJ_FILES): %.o : %.cpp 
	$(CXX) -c $< $(CPPFLAGS)

clean:
	$(RM) *.o $(PROGS)
