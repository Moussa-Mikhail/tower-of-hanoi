CC=g++
CFLAGS=-c -g -O0 -std=c++11 -Wall
LDFLAGS=-static -static-libstdc++ -static-libgcc
SOURCES=main.cpp hanoi.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hanoi

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	del -f $(EXECUTABLE).exe $(OBJECTS)