
#ifndef BINARYFILEEXCEPTION_H
#define BINARYFILEEXCEPTION_H
#include <exception>
#include <stdexcept>
#include <string>
namespace xmorph {
class BinaryFileException : public std::runtime_error {
private:
    std::string filename;
public:
    BinaryFileException(const std::string& s )
            : std::runtime_error( "Error reading binary file: " ), filename(s){}

    virtual const char* what() const throw() {
        std::string result(std::runtime_error::what());
        result+= ":" + filename;
        return result.c_str();
    }
    std::string getFilename() const {
        return filename;
    }
};
}
#endif //BINARYFILEEXCEPTION_H
