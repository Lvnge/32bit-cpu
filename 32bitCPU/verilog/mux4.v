`timescale 1ns/1ns
module mux4 (input [4:0] inst3, input [4:0] inst4, input Sel4, output [31:0] outwritereg);
assign outwritereg = Sel4 ? inst3 : inst4;
endmodule
