`timescale 1ns/1ns
module Add (input reg [31:0] AddIn, input reg [2:0] sumar, output reg [31:0] AddOut);
assign sumar = 4;
assign AddOut = AddIn + sumar;
endmodule
