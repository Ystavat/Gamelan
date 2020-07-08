LIBS = -lGL -lGLU -lglfw3 -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lz
GPP = g++ -std=c++11 -Wall -I $(srcdir) #-I Dependencies/GLEW/include/ -I Dependencies/GLFW/include/
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

$(bindir)%.o : $(srcdir)%.cpp $(SUP)
	mkdir -p $(dir $@)
	$(GOO) $(word 1, $^) -o $@

.PHONY : clean
clean :
	$(RM) $(bindir)*
