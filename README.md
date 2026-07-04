### Chameleon project

##  Project description
 Chameleon is a high performance, lightweight Command-Line Interface (CLI) steganography application written fully in C++. 
 It allows users to securely embed and extract hidden texts inside uncompressed standard Bitmap images by subtly altering the Least Significant Bits (LSB) of the raw color pixels. 

##  how to use
write your secret message in secret.txt
then run your code using: ' g++ main.cpp encode.cpp decode.cpp -o main ' in your terminal,
then type ' ./main ' to execute the code.
choose number 1 in the first program run, notice the new file 'output.bmp' that contains the picture with the embeded text.
run again and choose 2, notice the file 'extracted.txt' that contains the extracted message from the photo.


##  Features
- structer: Organized package split logically into separate header, encoding, decoding, and driver files.
- Zero Dependencies: Built using the standard C++ libraries (`<iostream>`, `<fstream>`, `<vector>`, and `<string>`). making it portable.
- Manual Stream Offsets: uses file stream cursors `seekg` and `tellg` to dynamically calculate pixels.

### Programming Language
- C++

### Development Tools
- Visual Studio Code
- Git
- GitHub

## 📂 Project Structure

 Chameleon/
   ├── steganography.h
   ├── encode.cpp
   ├── decode.cpp
   ├── main.cpp
   ├── input.bmp *Your bmp file (Keep it within 100-500 KB)*
   └── secret.txt  *The text file of your secret text*

---

##  Author

**Raha Algethami**

Computer Engineering Student  
Taif University  
Saudi Arabia 🇸🇦