#ifndef INSTRUCTIONV2_H
#define INSTRUCTIONV2_H

#include <iostream>
#include <string>
#include <bitset>

class instructionV2{
private:
    std::string assemblerInstruction;
    std::string binaryInstruction;

    std::string getInstructionTypeR(std::string [], bool&);
    std::string getInstructionTypeI(std::string [], bool&);
    std::string getInstructionTypeJ(std::string [], bool&);
    std::string getConvertedArgument(const std::string&, const std::string&, bool&);

    int getNumber(const std::string&);
    bool isNumber(const std::string&);

public:
    instructionV2();

    std::string getAssemblerInstruction() const;
    std::string getBinaryInstruction() const;

    std::string toString() const;

    void setAssemblerInstruction(const std::string&);
    void setBinaryInstruction(const std::string&);

    bool converter();

    friend std::ostream& operator << (std::ostream&, const instructionV2&);

};

#endif // INSTRUCTIONV2_H
