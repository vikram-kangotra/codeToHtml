#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "htmlConverter.h"

class ArgumentError : public std::exception {};

class FileDoesNotExit : public std::exception
{
public:
    FileDoesNotExit(const std::string& fileName)
        :   mFileName(fileName) {}

    const char* what() const noexcept
    {
        return mFileName.c_str();
    }
private:
    std::string mFileName;
};

std::string readAll(const std::string& fileName)
{
    std::ifstream file(fileName, std::ios::ate);

    if(!file.is_open()) {
        throw FileDoesNotExit(fileName);
    }

    const int length = file.tellg();
    file.seekg(0, std::ifstream::beg);

    std::unique_ptr<char> str(new char[length]);
    file.read(str.get(), length);

    return std::string(str.get());
}

void writeAll(const std::string& fileName, const std::string& data)
{
    std::ofstream file(fileName);
    file.write(data.c_str(), data.length());
}

int main(int argc, char* argv[])
{
    try {
        if(argc != 1)
            throw ArgumentError();

        std::string program = readAll("temp.cpp");

        Lexer lexer(program);

        HtmlConverter htmlConverter(lexer);
        std::string html = htmlConverter.convert();

        writeAll("output.html", html);

    } catch(const std::runtime_error& err) {
        std::cout << err.what();
        return -1;
    } catch(const ArgumentError& err) {
        std::cerr << "Usage: " << argv[0] << " file";
    }

    return 0;
}
