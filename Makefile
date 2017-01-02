CFLAGS=-static -Wall -g 
LDFLAGS=

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TARGET=bin/timer

all: $(TARGET)

$(TARGET): build $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

build:
	@mkdir -p bin

dev:CFLAGS+=-DNDEBUG
dev: all

clean:
	rm -rf bin/main src/*.o *.dSYM
