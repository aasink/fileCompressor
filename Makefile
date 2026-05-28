CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Iinclude
SRC = src/main.cpp src/app.cpp src/filehandler.cpp src/algorithms/RLEcompressor.cpp src/algorithms/HUFFMANcompressor.cpp src/algorithms/LZWcompressor.cpp
TARGET = compress

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

TESTSRC = tests/test_main.cpp tests/test_rle.cpp tests/test_huffman.cpp tests/test_lzw.cpp \
			src/app.cpp src/filehandler.cpp src/algorithms/RLEcompressor.cpp src/algorithms/HUFFMANcompressor.cpp src/algorithms/LZWcompressor.cpp

TESTTARGET = test_runner

test: $(TESTSRC)
	$(CXX) $(CXXFLAGS) -o $(TESTTARGET) $(TESTSRC)
	@echo "Running all tests..."
	./$(TESTTARGET)

clean:
	rm -f $(TARGET)
