CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Iinclude
SRC = src/main.cpp src/app.cpp src/filehandler.cpp src/algorithms/RLEcompressor.cpp
TARGET = compress

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

TESTSRC = tests/test_main.cpp tests/test_rle.cpp \
			src/app.cpp src/filehandler.cpp src/algorithms/RLEcompressor.cpp

TESTTARGET = test_runner

test: $(TESTSRC)
	$(CXX) $(CXXFLAGS) -o $(TESTTARGET) $(TESTSRC)
	@echo "Running all tests..."
	./$(TESTTARGET)

clean:
	rm -f $(TARGET)
