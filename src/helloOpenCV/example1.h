#pragma once

#include <string>

class Example1
{
public:
    void OpenImage(const std::string imgPath);
    void HomographyExample1(const std::string& imgPath);
    void HomographyExample2(const std::string& imgPathSrc, const std::string& imgPathDst);
};