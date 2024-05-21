`timescale 1ns/1ns
module PC (input reg [31:0] PCEntrada, input clk, output reg [31:0] PCSalida);
always @(posedge clk)
begin
  PCSalida = PCEntrada;
end
endmodule
