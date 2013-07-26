CC := g++
CC_FLAGS := 
SHARED_CPP_FILES := $(wildcard SharedSource/PaletteHarmony/*.cpp)
SHARED_OBJ_FILES := $(patsubst SharedSource/PaletteHarmony/%.cpp,Object/Shared%.o,$(SHARED_CPP_FILES))
CPP_FILES := $(wildcard Source/*.cpp)
OBJ_FILES := $(patsubst Source/%.cpp,Object/NotShared%.o,$(CPP_FILES))
ALL_OBJ := $(OBJ_FILES)
ALL_OBJ += $(SHARED_OBJ_FILES)
LD_LIBS := -lSDL -lSDL_image -lSDL_ttf

all : CC_FLAGS += -Wall -Wextra -O2 -Wno-unused-variable
all : Object/SeaBassShowdown

debug: CC_FLAGS += -DDEBUG -ggdb
debug: Object/SeaBassShowdown

profile: CC_FLAGS += -pg
profile: Object/SeaBassShowdown

warnings: CC_FLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wmaybe-uninitialized -Wuninitialized
warnings : Object/SeaBassShowdown

uninit: CC_FLAGS += -Wuninitialized -Wmaybe-uninitialized -O3
uninit : Object/SeaBassShowdown

clean : 
	rm Object/*.o Object/SeaBassShowdown

Object/SeaBassShowdown : $(ALL_OBJ)
	$(CC) $(CC_FLAGS) -o Object/SeaBassShowdown $(ALL_OBJ) $(LD_LIBS)

Object/NotShared%.o : Source/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

Object/Shared%.o : SharedSource/PaletteHarmony/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

