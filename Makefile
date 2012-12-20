CC := g++
CC_FLAGS := 
SHARED_CPP_FILES := $(wildcard SharedSource/PaletteHarmony/*.cpp)
SHARED_OBJ_FILES := $(patsubst SharedSource/PaletteHarmony/%.cpp,Object/Shared%.o,$(SHARED_CPP_FILES))
CPP_FILES := $(wildcard Source/*.cpp)
OBJ_FILES := $(patsubst Source/%.cpp,Object/NotShared%.o,$(CPP_FILES))
ALL_OBJ := $(OBJ_FILES)
ALL_OBJ += $(SHARED_OBJ_FILES)
LD_LIBS := -lSDL -lSDL_image -lSDL_ttf

all : CC_FLAGS += -Wall -O2
all : Object/SeaBassShowdown

debug: CC_FLAGS += -DDEBUG -ggdb
debug: Object/SeaBassShowdown

profile: CC_FLAGS += -pg
profile: Object/SeaBassShowdown

clean : 
	rm Object/*.o Object/SeaBassShowdown

Object/SeaBassShowdown : $(ALL_OBJ)
	$(CC) $(CC_FLAGS) -o Object/SeaBassShowdown $(ALL_OBJ) $(LD_LIBS)

Object/NotShared%.o : Source/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

Object/Shared%.o : SharedSource/PaletteHarmony/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

