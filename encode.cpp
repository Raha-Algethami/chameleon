#include "steganography.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

bool encodeMessage(const string& txtFile, const string& bmpFile, const string& outputFile) {
    ifstream secretFile(txtFile);
    ifstream inFile(bmpFile, ios::binary);
    if (!inFile || !secretFile) return false;

    // Read the secret message text fully into memory
    string message((istreambuf_iterator<char>(secretFile)), istreambuf_iterator<char>());
    message.push_back('\0'); // Secret marker tag so the decoder knows where to stop

    // 1. Safely locate where the pixel data actually begins (Byte 10)
    inFile.seekg(10, ios::beg);
    uint32_t dataOffset;
    inFile.read(reinterpret_cast<char*>(&dataOffset), sizeof(dataOffset));

    // 2. Read the entire dynamic structural header perfectly
    inFile.seekg(0, ios::beg);
    vector<char> header(dataOffset);
    inFile.read(header.data(), dataOffset);

    // 3. Read all remaining data directly as pixel color bytes
    inFile.seekg(0, ios::end);
    size_t fileSize = inFile.tellg();
    size_t pixelDataSize = fileSize - dataOffset;
    
    inFile.seekg(dataOffset, ios::beg);
    vector<char> pixels(pixelDataSize);
    inFile.read(pixels.data(), pixelDataSize);
    inFile.close();

    if (message.size() * 8 > pixels.size()) return false;

  
    size_t pixelIdx = 0;
    for (char ch : message) {
        for (int bit = 0; bit < 8; ++bit) {
            int msgBit = (ch >> bit) & 1; // 1 in binary is 00000001, so we can use bitwise AND to isolate the bit we want
            pixels[pixelIdx] = (pixels[pixelIdx] & 0xFE) | msgBit; // 0xFE is 11111110, so we can use bitwise AND to clear the LSB of the pixel byte, then OR it with the message bit to set the LSB to the desired value
            pixelIdx++;
        }
    }
    ofstream outFile(outputFile, ios::binary);
    if (!outFile) return false;
    outFile.write(header.data(), header.size());
    outFile.write(pixels.data(), pixels.size());
    return true;
}