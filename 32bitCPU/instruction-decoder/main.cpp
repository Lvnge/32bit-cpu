#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "instruction.h"
#include "instructionV2.h"
#include "singlylinkedlist.h"

using namespace std;

void decoderV1();
void decoderV2();

int main(){
    int opc;


    cout<<"En que formato desea trabajar . . ."<<endl<<endl<<endl;
    cout<<"--------------------------------------------------------"<<endl
        <<" [1] Numeros                     [2] Letras            "<<endl<<endl
        <<" add $0 $9 $4                    add $t1 $s0 $s2       "<<endl
        <<" sw $5 1200($10)                 sw $t0 20($zero)      "<<endl
        <<" beq $3 $9 50                    beq $t1 $s0 20        "<<endl
        <<" j 40                            j 1200                "<<endl
        <<" jal 31                          jal $ra               "<<endl
        <<" nop                             nop                   "<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"[Opcion] -> ";

    cin>>opc;
    system("cls");

    switch(opc){
    case 1:
        decoderV2();
        break;
    case 2:
        decoderV1();
        break;
    default:
        cout<<"Error - opcion no disponible"<<endl;
    }


    return 0;
}

void decoderV1(){
    SinglyLinkedList<Instruction> instructions;
    Instruction aux;
    string str;
    bool state = true;


    cout<<"Decodificador Instrucciones Ensamblador"<<endl<<"--------------------------------------------"<<endl<<endl;
    cout<<"Ingrese las intrucciones en ensamblador, para finalizar con la escritura escriba la palabra  ->  end "<<endl;

    cout<<endl<<endl<<endl<<endl<<"             Instrucciones Ensamblador"<<endl
        <<"--------------------------------------------------------"<<endl;


    while(state){
        getline(cin, str);

        if(str == "end"){
            state = false;
        }

        aux.setAssemblerInstruction(str);

        if(aux.converter()){
            instructions.insertData(aux);
        }
    }



    cout<<endl<<endl<<endl<<endl<<"             Lista de instrucciones ingresadas"<<endl
        <<"--------------------------------------------------------"<<endl
        <<"             Binaria             |     Ensamblador               "<<endl
        <<"--------------------------------------------------------"<<endl;

    cout<<instructions.toString();

    cout<<"--------------------------------------------------------"<<endl;

    system("pause");


    cout<<endl<<endl<<endl<<endl<<"             Archivo con extension .mem"<<endl
        <<"--------------------------------------------------------"<<endl;

    ofstream doc("Instruction_Memory.mem", ios::out);

    if(!doc){
        cout<<endl<<"Error al intentar ingresar a Instruction_Memory.mem";
    }else{
        doc << instructions;
        cout<<"Archivo con la extension .mem creado exitosamente . . . "<<endl<<endl<<endl;
    }

    doc.close();

    system("pause");
}

void decoderV2(){
    SinglyLinkedList<instructionV2> instructions;
    instructionV2 aux;
    string str;
    bool state = true;

    cout<<"Decodificador Instrucciones Ensamblador"<<endl<<"--------------------------------------------"<<endl<<endl;
    cout<<"Ingrese las intrucciones en ensamblador, para finalizar con la escritura escriba la palabra  ->  end "<<endl;

    cout<<endl<<endl<<endl<<endl<<"             Instrucciones Ensamblador"<<endl
        <<"--------------------------------------------------------"<<endl;


    while(state){
        getline(cin, str);

        if(str == "end"){
            state = false;
        }

        aux.setAssemblerInstruction(str);

        if(aux.converter()){
            instructions.insertData(aux);
        }
    }



    cout<<endl<<endl<<endl<<endl<<"             Lista de instrucciones ingresadas"<<endl
        <<"--------------------------------------------------------"<<endl
        <<"             Binaria             |     Ensamblador               "<<endl
        <<"--------------------------------------------------------"<<endl;

    cout<<instructions.toString();

    cout<<"--------------------------------------------------------"<<endl;

    system("pause");


    cout<<endl<<endl<<endl<<endl<<"             Archivo con extension .mem"<<endl
        <<"--------------------------------------------------------"<<endl;

    ofstream doc("Instruction_Memory.mem", ios::out);

    if(!doc){
        cout<<endl<<"Error al intentar ingresar a Instruction_Memory.mem";
    }else{
        doc << instructions;
        cout<<"Archivo con la extension .mem creado exitosamente . . . "<<endl<<endl<<endl;
    }

    doc.close();

    system("pause");


}
