CC := g++
CC_FLAGS :=  -std=c++11
CPP_FILES := $(wildcard Source/*.cpp)
OBJ_FILES := $(patsubst Source/%.cpp,Object/NotShared%.o,$(CPP_FILES))
ALL_OBJ := $(OBJ_FILES)
LD_LIBS := -lSDL2 -lSDL2_image 

all : CC_FLAGS += -Wall -Wextra -O2 -Wno-unused-variable
all : Object/CollisionDetectionPp

debug: CC_FLAGS += -DDEBUG -ggdb
debug: Object/CollisionDetectionPp

profile: CC_FLAGS += -pg
profile: Object/CollisionDetectionPp

warnings: CC_FLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wmaybe-uninitialized -Wuninitialized
warnings : Object/CollisionDetectionPp

uninit : CC_FLAGS += -Wuninitialized -Wmaybe-uninitialized -O3
uninit : Object/CollisionDetectionPp

clean : 
	rm Object/*.o Object/CollisionDetectionPp

Object/CollisionDetectionPp : $(ALL_OBJ)
	mkdir -p Object
	$(CC) $(CC_FLAGS) -o Object/CollisionDetectionPp $(ALL_OBJ) $(LD_LIBS)

Object/NotShared%.o : Source/%.cpp
	mkdir -p Object
	$(CC) $(CC_FLAGS) -c -o $@ $< 

