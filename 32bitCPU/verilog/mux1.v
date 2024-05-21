`timescale 1ns/1ns
module mux1 (input [31:0] readdata, input [31:0] Aluresult, input Sel1, output [31:0] Outwritedata);
assign Outwritedata = Sel1 ? readdata : Aluresult;
endmodule
