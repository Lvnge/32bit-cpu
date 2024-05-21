`timescale 1ns/1ns  //Start Module
module BR (input Regwrite, //inputs
           input [4:0] RR1, 
           input [4:0] RR2, 
           input [31:0] WriteData, 
           input [31:0] WriteReg, 
           output reg [31:0] RD1, //output
           output reg [31:0] RD2);
reg [31:0] Heineken [0:31]; //Register Result
always @*  //Always module
 begin
  RD1 = Heineken [RR1];  //assign values
  RD2 = Heineken [RR2];
   if (Regwrite)  //IF module
     begin
      Heineken [WriteReg] = WriteData;
     end //end if module
 end  //end always module

initial
begin
  $readmemh ("TestF1_BReg.mem", Heineken);
end

endmodule //The END
