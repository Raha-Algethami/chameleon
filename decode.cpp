#include "steganography.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint> 

using namespace std;

bool decodeMessage(const string& bmpFile, const string& outputFile) {
    ifstream inFile(bmpFile, ios::binary);
    if (!inFile) return false;

    // 1. locate where the pixel data actually begins (Byte 10)
    inFile.seekg(10, ios::beg);
    uint32_t dataOffset;
    inFile.read(reinterpret_cast<char*>(&dataOffset), sizeof(dataOffset));

    inFile.seekg(0, ios::end);                 
    size_t fileSize = inFile.tellg();
    size_t pixelDataSize = fileSize - dataOffset; 

    // 3. go to the starting byte of the pixels
    inFile.seekg(dataOffset, ios::beg);

    // 4. Read the pixel bytes directly into our new vector block
    vector<char> pixels(pixelDataSize);
    inFile.read(pixels.data(), pixelDataSize);
    inFile.close();

    string extractedMessage = "";
    size_t pixelIdx = 0;

    // Reconstruct characters bit by bit from pixel LSB tracking layer
    while (pixelIdx < pixels.size()) {
        char ch = 0;
        for (int bit = 0; bit < 8; ++bit) {
            if (pixelIdx >= pixels.size()) break;
            ch |= ((pixels[pixelIdx++] & 1) << bit);
        }
        if (ch == '\0') break; 
        extractedMessage.push_back(ch);
    }

    // Save out recovered plaintext payload string into the target file
    ofstream outFile(outputFile);
    if (!outFile) return false;
    outFile << extractedMessage;
    return true;
}