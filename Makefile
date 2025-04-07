//noampuni99@gmail.com

# Compiler and flags
CC = g++
CFLAGS = -Wall -std=c++11

# Source and object files
SRCS = Graph.cpp Algorithms.cpp Queue.cpp PriorityQueue.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

# Output file name
TARGET = ex1

# Default target
all: $(TARGET)

# Executable build
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule for object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencies
main.o: main.cpp Graph.hpp Algorithms.hpp
Graph.o: Graph.cpp Graph.hpp
PriorityQueue.o: PriorityQueue.cpp PriorityQueue.hpp
Queue.o: Queue.cpp Queue.hpp
Algorithms.o: Algorithms.cpp Algorithms.hpp Graph.hpp Queue.hpp PriorityQueue.hpp

# Clean object files and executable
clean:
	rm -f *.o $(TARGET)

# Run the main program
Main: $(TARGET)
	./$(TARGET)

# Run unit tests
test: test_graph.cpp Graph.o Algorithms.o Queue.o PriorityQueue.o
	$(CC) $(CFLAGS) -o test_graph test_graph.cpp Graph.o Algorithms.o Queue.o PriorityQueue.o

# Check memory leaks with valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

.PHONY: all clean Main valgrind test
