CC := g++
CC_FLAGS :=  -std=c++11
SHARED_CPP_FILES := $(wildcard SharedSource/PaletteHarmony/*.cpp)
SHARED_OBJ_FILES := $(patsubst SharedSource/PaletteHarmony/%.cpp,Object/Shared%.o,$(SHARED_CPP_FILES))
SDL2_CPP_FILES := $(wildcard Library/SDL2/Source/*.cpp)
SDL2_OBJ_FILES := $(patsubst Library/SDL2/Source/%.cpp,Object/SDL2%.o,$(SDL2_CPP_FILES))
CPP_FILES := $(wildcard Source/*.cpp)
OBJ_FILES := $(patsubst Source/%.cpp,Object/NotShared%.o,$(CPP_FILES))
ALL_OBJ := $(OBJ_FILES)
ALL_OBJ += $(SDL2_OBJ_FILES)
ALL_OBJ += $(SHARED_OBJ_FILES)
LD_LIBS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all : CC_FLAGS += -Wall -Wextra -O2 -Wno-unused-variable
all : 
	mkdir -p Object
all : Object/FishSkySea

debug: CC_FLAGS += -DDEBUG -ggdb
debug: Object/FishSkySea

profile: CC_FLAGS += -pg
profile: Object/FishSkySea

warnings: CC_FLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wmaybe-uninitialized -Wuninitialized
warnings : Object/FishSkySea

uninit : CC_FLAGS += -Wuninitialized -Wmaybe-uninitialized -O3
uninit : Object/FishSkySea

clean : 
	rm Object/*.o Object/FishSkySea

Object/FishSkySea : $(ALL_OBJ)
	$(CC) $(CC_FLAGS) -o Object/FishSkySea $(ALL_OBJ) $(LD_LIBS)

Object/NotShared%.o : Source/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

Object/Shared%.o : SharedSource/PaletteHarmony/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

Object/SDL2%.o : Library/SDL2/Source/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

