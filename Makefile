CC=gcc-14          # Use GCC 14
CFLAGS=-g -Wextra -Wall
SRC=server.c       # List of source files
TARGET=server      # Name of the final executable

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

build: all

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)