CC := g++
CC_FLAGS := 
SHARED_CPP_FILES := $(shell find ../../SharedSource/PaletteHarmony/ -name '*.cpp')
SHARED_OBJ_FILES := $(patsubst ../../SharedSource/PaletteHarmony/%.cpp,../../Object/Shared%.o,$(SHARED_CPP_FILES))
CPP_FILES := $(shell find ../../Source/ -name '*.cpp')
OBJ_FILES := $(patsubst ../../Source/%.cpp,../../Object/NotShared%.o,$(CPP_FILES))
EXPERIMENT_CPP_FILES := $(shell find ./Source/ -name '*.cpp')
EXPERIMENT_OBJECT_FILES := $(patsubst ./Source/%.cpp,../../Object/Experiment%.o,$(EXPERIMENT_CPP_FILES))
ALL_OBJ := $(OBJ_FILES)
ALL_OBJ += $(SHARED_OBJ_FILES)
ALL_OBJ += $(EXPERIMENT_OBJ_FILES)
LD_LIBS := -lSDL -lSDL_image -lSDL_ttf

all : CC_FLAGS += -Wall -O2
all : ../../Object/MessageBox

debug: CC_FLAGS += -DDEBUG -ggdb
debug: ../../Object/MessageBox

profile: CC_FLAGS += -pg
profile: ../../Object/MessageBox

clean : 
	rm ../../Object/*.o ../../Object/MessageBox

../../Object/MessageBox : $(ALL_OBJ)
	$(CC) $(CC_FLAGS) -o ../../Object/MessageBox $(ALL_OBJ) $(LD_LIBS)

../../Object/NotShared%.o : ../../Source/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

../../Object/Shared%.o : ../../SharedSource/PaletteHarmony/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $< 

../../Object/Experiment%.o : ./Source/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

