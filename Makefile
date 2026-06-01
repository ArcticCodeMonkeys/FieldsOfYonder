
CC = g++
CFLAGS = -std=c++17 -O2 -I.
TARGET = yonder

all: $(TARGET)

$(TARGET): main.cpp yonder.cpp civ.cpp tile.cpp resource.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp yonder.cpp civ.cpp tile.cpp resource.cpp

clean:
	rm -f $(TARGET)

.PHONY: all clean
