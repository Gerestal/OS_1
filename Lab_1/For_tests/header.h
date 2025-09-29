
#pragma once

#include <string>
#include <istream>
#include <ostream>

std::string ReadBinaryFileName(std::istream& in, std::ostream& out);
int ReadRecordCount(std::istream& in, std::ostream& out);
