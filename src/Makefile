.PHONY:	all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = g++
CC_OPTS = -O0 -g
LD = g++
LD_OPTS = -lSDL

# Targets

all: simpmd

clean:
	rm -f simpmd
	rm -f *.o
	rm -f *.dep

# Modules

OO = sim_core.o sim_display.o sim_processor.o

%.o: %.c
	$(CC) $(CC_OPTS) -c -o $@ $<

# Executable

simpmd: $(OO)
	$(LD) $(LD_OPTS) -o $@ $^

# Dependencies

include $(OO:.o=.dep)

%.dep: %.c
	@set -e ; $(CC) -MM $(CC_OPTS) $< | sed 's/\($*\)\.o *:/\1.o $@:/g' > $@

