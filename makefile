#########################
# customise these
SRC_DIR := ./Memake
CFILES := $(wildcard $(SRC_DIR)/*.cpp)
PROG := main
CFLAGS := -Wall -Wextra -g -std=c++11
LDFLAGS :=
########################

# -MMD generates dependencies while compiling
CFLAGS += -MMD
CC := clang++

OBJFILES := $(CFILES:.cpp=.o)
DEPFILES := $(CFILES:.cpp=.d)

$(PROG) : $(OBJFILES) main.o
	$(LINK.o) $(LDFLAGS) -o $@ $^ -lSDL2 $(CFLAGS)

clean :
	rm -f $(PROG) $(OBJFILES) $(DEPFILES) main.o

build:
	$(MAKE) clean
	$(MAKE)

-include $(DEPFILES)
