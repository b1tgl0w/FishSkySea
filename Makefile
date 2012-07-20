CC := g++
CC_FLAGS := 
CPP_FILES := $(wildcard Source/*.cpp)
OBJ_FILES := $(patsubst Source/%.cpp,Object/%.o,$(CPP_FILES))
LD_LIBS := -lSDL -lSDL_image

all : CC_FLAGS += -Wall -O2
all : Object/SeabassShowdown

debug: CC_FLAGS += -DDEBUG -ggdb
debug: Object/SeabassShowdown

profile: CC_FLAGS += -pg
profile: Object/SeabassShowdown

clean : 
	rm Object/*.o Object/SeabassShowdown

Object/SeabassShowdown : $(OBJ_FILES)
	$(CC) $(CC_FLAGS) -o Object/SeabassShowdown $(OBJ_FILES) $(LD_LIBS)

Object/%.o : Source/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

