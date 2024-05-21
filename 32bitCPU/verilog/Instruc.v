`timescale 1ns/1ns
module Instrucc (input [31:0] Dir, output [31:0] Instruccion);
reg [7:0] MI [255:0];
assign instruccion = ({MI[Dir],Dir+1,Dir+2,Dir+3});

initial
begin
	$readmemh ("TestF1_MemInst.mem", MI);
end

endmodule
