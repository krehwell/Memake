#########################
# customise these
SRC_DIR := ./Memake
CFILES := $(wildcard $(SRC_DIR)/*.cpp)
PROG := main
CFLAGS := -Wall -Wextra -g
LDFLAGS :=
########################

# -MMD generates dependencies while compiling
CFLAGS += -MMD
CC := g++

OBJFILES := $(CFILES:.cpp=.o)
DEPFILES := $(CFILES:.cpp=.d)

$(PROG) : $(OBJFILES) main.o
	$(LINK.o) $(LDFLAGS) -o $@ $^ -lSDL2

clean :
	rm -f $(PROG) $(OBJFILES) $(DEPFILES) main.o

build:
	$(MAKE) clean
	$(MAKE)

-include $(DEPFILES)
