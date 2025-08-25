ENVP= MACOSX_DEPLOYMENT_TARGET=10.6
ifneq (,$(findstring /cygdrive/,$(PATH)))
	UNAME := Cygwin
else
	ifneq (,$(findstring WINDOWS,$(PATH)))
		UNAME := Windows
	else
		UNAME := $(shell uname -s)
	endif
endif
ifeq ($(UNAME),Cygwin)
	CC := i686-w64-mingw32-gcc-11
else
	CC := gcc
endif
ifeq ($(MAKELEVEL),0)
export CC_FLAGS = -DPLATFORM_PC --std=c89 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused -Wmaybe-uninitialized -Wuninitialized -DREENTRANT
endif
XPMS := xpm/Seaweed1Bottom.xpm xpm/Seaweed1Top.xpm xpm/Sloogie.xpm xpm/SloogieFlip.xpm xpm/SloogieGlow.xpm xpm/SloogieGlowFlip.xpm xpm/SloogieHide.xpm xpm/SloogieHideFlip.xpm xpm/SloogieHideGlow.xpm xpm/SloogieHideGlowFlip.xpm xpm/Ripple1.xpm xpm/Ripple2.xpm xpm/Ripple3.xpm xpm/Ripple4.xpm xpm/Ripple5.xpm xpm/Ripple6.xpm xpm/FishHook.xpm xpm/Shark2.xpm xpm/SharkFlip.xpm xpm/SharkFin.xpm xpm/SharkFinFlip.xpm xpm/SharkGlow.xpm xpm/SharkFinGlow.xpm xpm/SharkFinGlowFlip.xpm xpm/SharkGlowFlip.xpm xpm/Fish5.xpm xpm/FishGlow.xpm xpm/FishGlowFlip.xpm xpm/Scene8.xpm xpm/DockSupports3.xpm xpm/Fish5Flip.xpm xpm/MowhawkFisherGlow2.xpm xpm/MowhawkFisher2.xpm xpm/PoleNoFish1.xpm xpm/PoleFish1.xpm xpm/PoleNoFish1Flip.xpm xpm/PoleFish1Flip.xpm xpm/ElderFisher2.xpm xpm/ElderFisherGlow.xpm xpm/SeaStar.xpm xpm/SeaHorse.xpm xpm/SeaHorseFlip.xpm xpm/Cloud1.xpm xpm/PointFish.xpm xpm/Salmon.xpm xpm/SalmonFlip.xpm
EXTRA_LD :=
ifdef NOMUSIC
MUS =
CC_FLAGS += -DNOMUSIC
else
MUS = mus/UkeSong1.c mus/JM.c mus/sound_sharkbite.c mus/sound_glimmer.c mus/sound_fishcatch.c mus/sound_cast.c
endif
ifdef DEBUGMODE
CC_FLAGS += -DDEBUG_MODE -ggdb
endif
ifdef ASANMODE
NOT_WORKING += This isnt working probably due to not linking libsdl2 statically
	CC_FLAGS += -DNOMUSIC -ggdb -fno-omit-frame-pointer -fsanitize=undefined -fno-common -O0
	ifeq ($(UNAME),Cygwin)
		CC_FLAGS += -mwindows -D_SDL_main_h -DSDL_main_h_
		EXTRA_LD += -lasan -lSDL2_mixer -lSDL2 -lSDL2main -lSDL2_image -lSDL2_net 
	else
		EXTRA_LD += -lasan -lSDL2_mixer -lSDL2 -lSDL2main -lSDL2_image -lSDL2_net -lpthread -ldl -lm
	endif
else
	ifeq ($(UNAME),Cygwin)
		EXTRA_LD += -Wl,-headerpad_max_install_names	-lSDL2_mixer -lSDL2 -lSDL2main -lSDL2_image -lSDL2_net
		CC_FLAGS += -mwindows -D_SDL_main_h -DSDL_main_h_
	else
		EXTRA_LD += -Wl,-headerpad_max_install_names	-lSDL2_mixer -lSDL2 -lSDL2main -lSDL2_image -lSDL2_net -lpthread -ldl -lm
	endif
endif

.PHONY: all clean xpm debugmode nomusic objdir config.tmp

all: obj/fishskysea

debugmode: 
	$(MAKE) DEBUGMODE=1 NOMUSIC=1

asanmode: 
	$(MAKE) ASANMODE=1 NOMUSIC=1

nomusic:
	$(MAKE) NOMUSIC=1

objdir:
	mkdir -p obj

obj/fishskysea: obj/xpmmain.o | objdir
	$(ENVP) $(CC) $(CC_FLAGS) obj/xpmmain.o -o obj/fishskysea $(EXTRA_LD) 

obj/xpmmain.o: premain.c config.tmp $(XPMS) $(MUS) main.c | objdir
	cat $^ > xpmmain.c
	$(ENVP) $(CC) $(CC_FLAGS) -c xpmmain.c -o obj/xpmmain.o

config.tmp: config.txt
	echo test
	sh ./cifyconfig.sh > config.tmp

clean:
	-rm obj/xpmmain.o obj/fishskysea 2> /dev/null

