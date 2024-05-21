`timescale 1ns/1ns
module mux3 (input [31:0] readdata2, input [31:0] singex, input Sel3, output [31:0] outaluop2);
assign outaluop2 = Sel3 ? readdata2 : singex;
endmodule