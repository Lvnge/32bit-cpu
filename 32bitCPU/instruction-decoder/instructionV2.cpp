#include "instructionV2.h"

using namespace std;

instructionV2::instructionV2(){}

string instructionV2::getAssemblerInstruction() const{
    return assemblerInstruction;
}

string instructionV2::getBinaryInstruction() const{
    return binaryInstruction;
}

string instructionV2::toString() const{
    string result;
    result = binaryInstruction;
    result += " | ";
    result += assemblerInstruction;
    result += "\n";

    return result;
}

void instructionV2::setAssemblerInstruction(const string& assemblerInstruccion){
    this->assemblerInstruction = assemblerInstruccion;
}

void instructionV2::setBinaryInstruction(const string& binaryInstruction){
    this->binaryInstruction = binaryInstruction;
}

bool instructionV2::converter(){
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

string instructionV2::getInstructionTypeR(string w[], bool& status){
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

string instructionV2::getInstructionTypeI(string w[], bool& status){
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

string instructionV2::getInstructionTypeJ(string w[], bool& status){
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

string instructionV2::getConvertedArgument(const string& str, const string& typeInstruction, bool& status){
        int type;
        string result = "-1";
        string arguments[32][2] = {
                                      {"$0","0"},
                                      {"$1","1"},
                                      {"$2","2"},
                                      {"$3","3"},
                                      {"$4","4"},
                                      {"$5","5"},
                                      {"$6","6"},
                                      {"$7","7"},
                                      {"$8","8"},
                                      {"$9","9"},
                                      {"$10","10"},
                                      {"$11","11"},
                                      {"$12","12"},
                                      {"$13","13"},
                                      {"$14","14"},
                                      {"$15","15"},
                                      {"$16","16"},
                                      {"$17","17"},
                                      {"$18","18"},
                                      {"$19","19"},
                                      {"$20","20"},
                                      {"$21","21"},
                                      {"$22","22"},
                                      {"$23","23"},
                                      {"$24","24"},
                                      {"$25","25"},
                                      {"$26","26"},
                                      {"$27","27"},
                                      {"$28","28"},
                                      {"$29","29"},
                                      {"$30","30"},
                                      {"$31","31"}
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

int instructionV2::getNumber(const string& str){
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

bool instructionV2::isNumber(const string& str){
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

ostream& operator << (ostream& os, const instructionV2& i){
    os << i.binaryInstruction.substr(0,8) << endl;
    os << i.binaryInstruction.substr(8,8) << endl;
    os << i.binaryInstruction.substr(16,8) << endl;
    os << i.binaryInstruction.substr(24,8) << endl;
    return os;
}
