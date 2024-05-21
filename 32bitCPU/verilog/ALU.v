`timescale 1ns/1ns //Inicio
//inicio del modulo
module modecoder (input [31:0] Op1, input [31:0] Op2, input [2:0] sel, output reg [31:0] ALUResult, output zero);
//fin de entradas y salidas
reg [31:0] Result; //registros y asignaciones
assign ALUResult = Result;
always @* //comienzo del bloque always
 begin
 if (sel)
  begin
   case( 
       sel)
         4'b0000: 
                  Result = Op1 & Op2;
                  
         4'b0001: 
                  Result = Op1 | Op2;
                  
         4'b0010: 
                  Result = Op1 + Op2;
                  
         4'b0110: 
                  Result = Op1 - Op2;
                  
         4'b0111: 
                  Result = Op1 <= Op2;
                  
         4'b1100: 
                  Result = ~(Op1 | Op2);
                  
    default: Result = 0;
   endcase
  end
 end
endmodule