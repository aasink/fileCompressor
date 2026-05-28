#include <iostream>
using namespace std;

void test_rle();
void test_huffman();
void test_lzw();

int main() {
    test_rle();
    cout << "RLE test completed successfully 🎉\n\n" << endl;

    test_huffman();
    cout << "Huffman test completed successfully 🎉\n\n" << endl;

    test_lzw();
    cout << "LZW test completed successfully 🎉\n\n" << endl;

    cout << "All tests completed successfully 🎉\n" << endl;
    return 0;
}
