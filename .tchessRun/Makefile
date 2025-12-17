CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = .techessRun
OBJS = main.o board.o pieces.o display.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp board.h display.h
	$(CXX) $(CXXFLAGS) -c main.cpp

board.o: board.cpp board.h pieces.h
	$(CXX) $(CXXFLAGS) -c board.cpp

pieces.o: pieces.cpp pieces.h board.h
	$(CXX) $(CXXFLAGS) -c pieces.cpp

display.o: display.cpp display.h board.h pieces.h
	$(CXX) $(CXXFLAGS) -c display.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
