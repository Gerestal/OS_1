
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include "header.h"


TEST(ReadBinaryFileNameTests, ReturnsValidName) {
    std::stringstream in("file.bin\n");
    std::stringstream out;
    std::string name = ReadBinaryFileName(in, out);
    EXPECT_EQ(name, "file.bin");
    EXPECT_NE(out.str().find("Enter the name of the binary file"), std::string::npos);
}


TEST(ReadBinaryFileNameTests, SkipsForbiddenAndReadsNext) {
    
    std::stringstream in("bad|name\ngood_name.bin\n");
    std::stringstream out;
    std::string name = ReadBinaryFileName(in, out);
    EXPECT_EQ(name, "good_name.bin");
    
    EXPECT_NE(out.str().find("contains invalid characters"), std::string::npos);
}


TEST(ReadRecordCountTests, ReadsPositiveCount) {
    std::stringstream in("3\n");
    std::stringstream out;
    int cnt = ReadRecordCount(in, out);
    EXPECT_EQ(cnt, 3);
    EXPECT_NE(out.str().find("Enter the number of employees"), std::string::npos);
}


TEST(ReadRecordCountTests, SkipsNegativeAndReadsNext) {
    std::stringstream in("-5\n2\n");
    std::stringstream out;
    int cnt = ReadRecordCount(in, out);
    EXPECT_EQ(cnt, 2);
    
    EXPECT_NE(out.str().find("can't be negative"), std::string::npos);
}


TEST(ReadRecordCountTests, ThrowsOnBadInputOrEOF) {
    std::stringstream in;
    std::stringstream out;
    EXPECT_THROW({
        ReadRecordCount(in, out);
        }, std::runtime_error);
}

