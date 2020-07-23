SRCDIR		:= src
INCDIR		:= include
BINDIR		:= bin

OBJFILES	:= $(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp))

OUT			:= libbaseline.a

CC			:= g++

LIBS		:= -lSDL2 -lGL -lGLEW
CFLAGS		:= -Wall -Wpedantic

SERVERSIDE	= 0
ifeq ($(SERVERSIDE),1)
CFLAGS		+= -DSERVERSIDE
else
OBJFILES	+= $(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/client/*.cpp))
endif

.PHONY: build clean

build: $(OBJFILES) | $(BINDIR)
	$(AR) rsv $(BINDIR)/$(OUT) $(OBJFILES)

clean:
	rm $(OBJFILES)
	rm $(BINDIR)/$(OUT)

%.o: %.cpp Makefile
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(BINDIR):
	mkdir bin
