LIBS = -lGL -lglfw3 -lGLEW -lX11 -lpthread -ldl -lz
GPP = g++ -std=c++14 -Wall -I $(srcCor) -I $(srcApp)
GOO = $(GPP) -c

RM = rm -irf

cordir = Gamelan/
appdir = Sandbox/
srcdir = Sources/
bindir = bin/
srcCor = $(cordir)$(srcdir)
srcApp = $(appdir)$(srcdir)
main   = $(appdir)$(srcdir)sandbox.cpp

SRC  := $(wildcard $(srcCor)*.cpp) $(wildcard $(srcCor)*/*.cpp) $(wildcard $(srcCor)*/*/*.cpp)\
	$(wildcard $(srcApp)*.cpp) $(wildcard $(srcApp)*/*.cpp) $(wildcard $(srcApp)*/*/*.cpp)
HEAD := $(wildcard $(srcdir)*.h)   $(wildcard $(srcdir)*/*.h)   $(wildcard $(srcdir)*/*/*.h)\
	$(wildcard $(srcApp)*.h)   $(wildcard $(srcApp)*/*.h)   $(wildcard $(srcApp)*/*/*.h)
OBJ  := $(subst $(srcCor), $(bindir), $(subst $(srcApp), $(bindir), $(SRC:.cpp=.o)))
SUP  := $(srcCor)config.h $(srcCor)core.h $(srcCor)gamelan.h

PROG = $(appdir)Prog
all = $(PROG)

$(PROG) : $(OBJ)
	$(GPP) $(OBJ) -o $@ $(LIBS)

$(bindir)%.o : $(srcCor)%.cpp $(srcCor)%.h $(SUP)
	mkdir -p $(dir $@)
	$(GOO) $(word 1, $^) -o $@
$(bindir)%.o : $(srcApp)%.cpp $(srcApp)%.h $(SUP)
	mkdir -p $(dir $@)
	$(GOO) $(word 1, $^) -o $@
prompt = "Compile _ as main?"
$(bindir)%.o : $(srcApp)%.cpp $(SUP)
	#$(prompt:_=$(word 1, $^))
	#read REPLY
	mkdir -p $(dir $@)
	$(GOO) $(word 1, $^) -o $@
	
.PHONY : clean
clean :
	$(RM) $(bindir)*
	$(RM) $(PROG)

.PHONY : re
re :
	touch $(main)
	make
