TARGET = example
INCDIR = ..

VPATH = ..
SOURCE = main.cpp Debouncer.cpp

CC = g++
FLAGS = -std=c++11 -Wall
CXXFLAGS = -I$(INCDIR) $(FLAGS)
LDFLAGS = $(FLAGS)

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(SOURCE:.cpp=.o)
HEADERS = $(wildcard *.h)

%.o: %.cpp $(HEADERS)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o $(TARGET)
