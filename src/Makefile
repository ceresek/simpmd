.PHONY:	all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = g++
CC_OPTS =
LD = g++
LD_OPTS = -lSDL -lpopt -lrt

ifdef RELEASE
CC_OPTS += -O2 -D RELEASE
else
CC_OPTS += -O0 -g
endif

BIN = ../bin

# Targets

all: $(BIN)/simpmd

clean:
	rm -f *.o
	rm -f *.dep

# Modules

OO = sim_core.o sim_display.o sim_keyboard.o sim_processor.o sim_speaker.o sim_tape.o sim_timing.o

%.o: %.c
	$(CC) $(CC_OPTS) -c -o $@ $<

# Executable

$(BIN)/simpmd: $(OO)
	$(LD) $(LD_OPTS) -o $@ $^

# Dependencies

include $(OO:.o=.dep)

%.dep: %.c
	@set -e ; $(CC) -MM $(CC_OPTS) $< | sed 's/\($*\)\.o *:/\1.o $@:/g' > $@

