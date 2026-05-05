CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = huffman
SRCS = main.cpp bitstream.cpp frequency_table.cpp huffman_tree.cpp encoder.cpp decoder.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
