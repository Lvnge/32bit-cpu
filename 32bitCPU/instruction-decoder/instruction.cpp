#include "instruction.h"

using namespace std;

Instruction::Instruction(){}

string Instruction::getAssemblerInstruction() const{
    return assemblerInstruction;
}

string Instruction::getBinaryInstruction() const{
    return binaryInstruction;
}

string Instruction::toString() const{
    string result;
    result = binaryInstruction;
    result += " | ";
    result += assemblerInstruction;
    result += "\n";

    return result;
}

void Instruction::setAssemblerInstruction(const string& assemblerInstruccion){
    this->assemblerInstruction = assemblerInstruccion;
}

void Instruction::setBinaryInstruction(const string& binaryInstruction){
    this->binaryInstruction = binaryInstruction;
}

bool Instruction::converter(){
    int noOperations = 21;
    int pos = 0, cont = 0;
    bool status = true;

    string textAux(assemblerInstruction);
    string words[4] = {"-","-","-","-"};
    string delimiter = " ";
    string operationType[noOperations][2] = {
                                    {"nop","R"},
                                    {"add","R"},
                                    {"sub","R"},
                                    {"mul","R"},
                                    {"div","R"},
                                    {"or","R"},
                                    {"and","R"},
                                    {"slt","R"},
                                    {"nop","R"},
                                    {"addi","I"},
                                    {"subi","I"},
                                    {"ori","I"},
                                    {"andi","I"},
                                    {"lw","I"},
                                    {"sw","I"},
                                    {"slti","I"},
                                    {"beq","I"},
                                    {"bne","I"},
                                    {"bgtz","I"},
                                    {"j","J"},
                                    {"jal","J"}
                              };



    //Ciclo en el cual divide los argumentos de la instruccion recibida y lo guarda en un arreglo de tipo string
    while (status) {
        pos = textAux.find(delimiter);
        words[cont] = textAux.substr(0, pos);
        textAux.erase(0, pos + delimiter.length());
        cont++;
        if(pos == -1)
            status = false;
    }


    //Ciclo el cual separa la instruccion recibida segun su tipo y realiza la conversion a binario
    for(int x = 0; x < noOperations; x++){
        if(words[0] == operationType[x][0]){
            if(operationType[x][1] == "R")
                binaryInstruction = getInstructionTypeR(words, status);
            if(operationType[x][1] == "I")
                binaryInstruction = getInstructionTypeI(words, status);
            if(operationType[x][1] == "J")
                binaryInstruction = getInstructionTypeJ(words, status);
        }
    }

    return status;
}

string Instruction::getInstructionTypeR(string w[], bool& status){
    int noOperations = 8;
    string result, op = "000000", rs, rt, rd, shamt = "00000", funct;
    string operation[noOperations][2] = {
                                          {"add","100000"},
                                          {"sub","100010"},
                                          {"mul","000010"},
                                          {"div","011010"},
                                          {"or","000101"},
                                          {"and","000100"},
                                          {"slt","101010"},
                                          {"nop","000000"}
                                        };

    for(int x = 0; x < noOperations; x++){
        if(w[0] == operation[x][0]){
            funct = operation[x][1];
        }
    }


    if(w[0] == "nop"){
        rd = "00000";
        rs = "00000";
        rt = "00000";
        status = true;

    }else if(w[0] == "div"){
        bitset<5> rs5(stoi(getConvertedArgument(w[1],"R", status)));
        rs = rs5.to_string();

        bitset<5> rt5(stoi(getConvertedArgument(w[2],"R", status)));
        rt = rt5.to_string();

        rd = "00000";

    }else{

        bitset<5> rd5(stoi(getConvertedArgument(w[1],"R", status)));
        rd = rd5.to_string();

        bitset<5> rs5(stoi(getConvertedArgument(w[2],"R", status)));
        rs = rs5.to_string();

        bitset<5> rt5(stoi(getConvertedArgument(w[3],"R", status)));
        rt = rt5.to_string();

    }

    result = op + rs + rt + rd + shamt + funct;

    return result;
}

string Instruction::getInstructionTypeI(string w[], bool& status){
    int pos, noOperations = 9;
    string result, op, rs, rt, immediate;
    string operation[noOperations][2] = {
                                          {"addi","001000"},
                                          {"ori","001101"},
                                          {"andi","001100"},
                                          {"lw","100011"},
                                          {"sw","101011"},
                                          {"slti","001010"},
                                          {"beq","000100"},
                                          {"bne","000101"},
                                          {"bgtz","000111"}
                                        };

    for(int x = 0; x < noOperations; x++){
        if(w[0] == operation[x][0]){
            op = operation[x][1];
        }
    }

    if(w[0] == "lw" || w[0] == "sw" ){
        bitset<5> rt5(stoi(getConvertedArgument(w[1],"I", status)));
        rt = rt5.to_string();

        pos = w[2].find("(");

        bitset<16> immediate16(getNumber(w[2].substr(0, pos)));
        immediate = immediate16.to_string();

        string aux = w[2].substr(pos + 1);
        aux = aux.substr(0,aux.size() - 1);

        bitset<5> rs5(stoi(getConvertedArgument(aux,"I", status)));
        rs = rs5.to_string();

    }else if(w[0] == "bne" || w[0] == "beq"){
        bitset<5> rs5(stoi(getConvertedArgument(w[1],"I", status)));
        rs = rs5.to_string();

        bitset<5> rt5(stoi(getConvertedArgument(w[2],"I", status)));
        rt = rt5.to_string();

        bitset<16> immediate16(stoi(getConvertedArgument(w[3],"I", status)));
        immediate = immediate16.to_string();

    }else if(w[0] == "bgtz"){
        bitset<5> rs5(stoi(getConvertedArgument(w[1],"I", status)));
        rs = rs5.to_string();

        bitset<16> immediate16(stoi(getConvertedArgument(w[2],"I", status)));
        immediate = immediate16.to_string();

        bitset<5> rt5(0);
        rt = rt5.to_string();

    }else{
        bitset<5> rt5(stoi(getConvertedArgument(w[1],"I", status)));
        rt = rt5.to_string();

        bitset<5> rs5(stoi(getConvertedArgument(w[2],"I", status)));
        rs = rs5.to_string();

        bitset<16> immediate16(stoi(getConvertedArgument(w[3],"I", status)));
        immediate = immediate16.to_string();

    }

    result = op + rs + rt + immediate;

    return result;
}

string Instruction::getInstructionTypeJ(string w[], bool& status){
    int noOperations = 2;
    string result, op, address;
    string operation[noOperations][2] = {
                                           {"j","000010"},
                                           {"jal","000011"}
                                        };

    for(int x = 0; x < noOperations; x++){
        if(w[0] == operation[x][0]){
            op = operation[x][1];
        }
    }

    bitset<26> address26(stoi(getConvertedArgument(w[1],"J", status)));
    address = address26.to_string();

    result = op + address;

    return result;
}

string Instruction::getConvertedArgument(const string& str, const string& typeInstruction, bool& status){
        int type;
        string result = "-1";
        string arguments[32][2] = {
                                      {"$zero","0"},
                                      {"$at","1"},
                                      {"$v0","2"},
                                      {"$v1","3"},
                                      {"$a0","4"},
                                      {"$a1","5"},
                                      {"$a2","6"},
                                      {"$a3","7"},
                                      {"$t0","8"},
                                      {"$t1","9"},
                                      {"$t2","10"},
                                      {"$t3","11"},
                                      {"$t4","12"},
                                      {"$t5","13"},
                                      {"$t6","14"},
                                      {"$t7","15"},
                                      {"$s0","16"},
                                      {"$s1","17"},
                                      {"$s2","18"},
                                      {"$s3","19"},
                                      {"$s4","20"},
                                      {"$s5","21"},
                                      {"$s6","22"},
                                      {"$s7","23"},
                                      {"$t8","24"},
                                      {"$t9","25"},
                                      {"$k0","26"},
                                      {"$k1","27"},
                                      {"$gp","28"},
                                      {"$sp","29"},
                                      {"$fp","30"},
                                      {"$ra","31"}
                                   };



        if(typeInstruction == "R" || typeInstruction == "r")
            type = 1;
        if(typeInstruction == "I" || typeInstruction == "i")
            type = 2;
        if(typeInstruction == "J" || typeInstruction == "j")
            type = 3;


        switch(type){
        case 1:
            for(int x = 0; x < 32; x++){
                if(str == arguments[x][0]){
                    result = arguments[x][1];
                    status = true;
                    break;
                }else{
                    status = false;
                }
            }


            break;

        case 2:
        case 3:
            for(int x = 0; x < 32; x++){
                if(str == arguments[x][0]){
                    result = arguments[x][1];
                    status = true;
                    break;
                }else{
                    status = false;
                }
            }

            if(!status){
                if(isNumber(str)){
                    result = str;
                    status = true;
                }else{
                    status = false;
                }
            }

            break;

        default:
            cout<<"Error tipo de instruccion no aceptada - getConvertedArgument() "<<endl;
            status = false;
        }

        return result;
}

int Instruction::getNumber(const string& str){
    int result;
    string aux;

    for(int x = 0; x < str.size(); x++){
        if(str[x] >= 48 && str[x] <= 57){
            aux = str[x];
            result = result * 10 + stoi(aux);
        }
    }

    return result;

}

bool Instruction::isNumber(const string& str){
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

ostream& operator << (ostream& os, const Instruction& i){
    os << i.binaryInstruction.substr(0,8) << endl;
    os << i.binaryInstruction.substr(8,8) << endl;
    os << i.binaryInstruction.substr(16,8) << endl;
    os << i.binaryInstruction.substr(24,8) << endl;
    return os;
}





