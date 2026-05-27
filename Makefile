CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Iinclude
SRC = src/main.cpp src/app.cpp src/filehandler.cpp src/algorithms/RLEcompressor.cpp src/algorithms/HUFFMANcompressor.cpp
TARGET = compress

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

TESTSRC = tests/test_main.cpp tests/test_rle.cpp tests/test_huffman.cpp \
			src/app.cpp src/filehandler.cpp src/algorithms/RLEcompressor.cpp src/algorithms/HUFFMANcompressor.cpp

TESTTARGET = test_runner

test: $(TESTSRC)
	$(CXX) $(CXXFLAGS) -o $(TESTTARGET) $(TESTSRC)
	@echo "Running all tests..."
	./$(TESTTARGET)

clean:
	rm -f $(TARGET)
