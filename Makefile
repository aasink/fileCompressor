CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Iinclude
SRC = src/main.cpp src/app.cpp src/filehandler.cpp src/algorithms/RLEcompressor.cpp
TARGET = compress

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

clean:
	rm -f $(TARGET)
