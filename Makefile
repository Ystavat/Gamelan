LIBS = -lGL -lglfw3 -lGLEW -lX11 -lpthread -ldl
GPP = g++ -std=c++11 -Wall -I $(srcdir)
GOO = $(GPP) -c

RM = rm -irf

srcdir = src/
bindir = bin/

SRC  := $(wildcard $(srcdir)*.cpp) $(wildcard $(srcdir)*/*.cpp) $(wildcard $(srcdir)*/*/*.cpp)
HEAD := $(wildcard $(srcdir)*.h)   $(wildcard $(srcdir)*/*.h)   $(wildcard $(srcdir)*/*/*.h)
OBJ := $(subst $(srcdir), $(bindir), $(SRC:.cpp=.o))
SUP := $(srcdir)config.h $(srcdir)core.h

PROG = Prog
all = $(PROG)

$(PROG) : $(OBJ)
	$(GPP) $(OBJ) -o $@ $(LIBS)

$(bindir)%.o : $(srcdir)%.cpp $(srcdir)%.h $(SUP)
	mkdir -p $(dir $@)
	$(GOO) $(word 1, $^) -o $@
$(bindir)main.o : $(srcdir)main.cpp $(SUP)
	mkdir -p $(dir $@)
	$(GOO) $(word 1, $^) -o $@

.PHONY : clean
clean :
	$(RM) $(bindir)*
	$(RM) $(PROG)
