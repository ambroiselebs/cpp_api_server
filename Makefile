CXX = c++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -Iincludes
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*/*.cpp)
TARGET = server

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

fclean: clean

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
