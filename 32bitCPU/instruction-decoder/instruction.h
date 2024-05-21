#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <string>
#include <bitset>

class Instruction{
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
    Instruction();

    std::string getAssemblerInstruction() const;
    std::string getBinaryInstruction() const;

    std::string toString() const;

    void setAssemblerInstruction(const std::string&);
    void setBinaryInstruction(const std::string&);

    bool converter();

    friend std::ostream& operator << (std::ostream&, const Instruction&);

};

#endif // INSTRUCTION_H
