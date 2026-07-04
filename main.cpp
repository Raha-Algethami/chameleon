#include <iostream>
#include "steganography.h"
using namespace std;

int main() {
    int choice;
    cout << "***** CHAMELEON PROJECT *****" << endl;
    cout << "1> Encode Message (Hide message)" << endl;
    cout << "2> Decode Message (Show message)" << endl;
    cout << "Enter your choice (1 or 2 only): ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        if (encodeMessage("secret.txt", "input.bmp", "output.bmp")) {
            cout << "\nMessage hidden successfully in the file 'output.bmp'!!!" << endl;
        } else {
            cout << "\nERROR: Failed to encode message :(" << endl;
        }
        break;
    case 2:
        if (decodeMessage("output.bmp", "extracted.txt")) {
            cout << "\nMessage extracted successfully in the file 'extracted.txt'!!!" << endl;
        } else {
            cout << "\nERROR: Failed to detect message :(" << endl;
        }
        break;

    default:
        cout << "\nERROR: Invalid number selection." << endl;
        break;
    }
    return 0;
}