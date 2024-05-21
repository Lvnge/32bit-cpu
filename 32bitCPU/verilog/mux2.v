`timescale 1ns/1ns
module mux2 (input [31:0] AddoutIn, input [31:0] ALU2result, input Sel2, output [31:0] Outpc);
assign outpc = Sel2 ? AddoutIn : ALU2result;
endmodule
