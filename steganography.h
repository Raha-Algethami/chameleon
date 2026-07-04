#pragma once
#include <string>

bool encodeMessage(const std::string& txtFile, const std::string& bmpFile, const std::string& outputFile);
bool decodeMessage(const std::string& bmpFile, const std::string& outputFile);