`timescale 1ns/1ns

module Parent();

wire [31:0] PC2ADDnDir, Mux2toPC, Add2Mux2, Instruction, Mux1Out2WriteData, RD1toALu, RD2toMux3;
wire [31:0] Mux3toALUOp2, AluResult2Mux1, Mux4toWriteReg;
wire [3:0] AluOp2AluControl;
wire [2:0] InstAluControl2Alu;
wire AluZero2And, AndOut2Mux2, AluSrc2Mux3, RegWriteEnable, Branch2And, Control2Mux4;


Add I_Add(
	.AddIn(PC2ADDnDir),
	.sumar(),
	.AddOut(Add2Mux2)
	);

modecoder I_ALU(
	.Op1(RD1toALu),
	.Op2(Mux3toALUOp2),
	.sel(InstAluControl2Alu),
	.ALUResult(AluResult2Mux1),
	.zero(AluZero2And)
	);

Alucontrol I_Alucontrol(
	.inst(Instruction[5:0]),
	.ALUOp(AluOp2AluControl),
	.instalu(InstAluControl2Alu)
	);

AND I_AND(
	.A(Branch2And),
	.B(AluZero2And),
	.C(AndOut2Mux2)
	);

BR I_BR(
	.Regwrite(RegWriteEnable),
	.RR1(Instruction[25:21]),
	.RR2(Instruction[20:16]),
	.WriteData(Mux1Out2WriteData),
	.WriteReg(Mux4toWriteReg),
	.RD1(RD1toALu),
	.RD2(RD2toMux3)
	);

Instrucc I_Instrucc(
	.Dir(PC2ADDnDir),
	.Instruccion(Instruction)
	);

mux1 I_mux1(
	.readdata(),
	.Aluresult(AluResult2Mux1),
	.Sel1(),
	.Outwritedata(Mux1Out2WriteData));

mux2 I_mux2(
	.AddoutIn(Add2Mux2),
	.ALU2result(),
	.Sel2(AndOut2Mux2),
	.Outpc(Mux2toPC)
	);

mux3 I_mux3(
	.readdata2(RD2toMux3),
	.singex(),
	.Sel3(AluSrc2Mux3),
	.outaluop2(Mux3toALUOp2)
	);

mux4 I_mux4(
	.inst3(Instruction[20:16]),
	.inst4(Instruction[15:11]),
	.Sel4(Control2Mux4),
	.outwritereg(Mux4toWriteReg)
	);

PC I_PC(
	.PCEntrada(Mux2toPC),
	.clk(),
	.PCSalida(PC2ADDnDir)
	);

UnidadDeControl I_UnidadDeControl(
	.InstruccionControl(Instruction[31:26]),
	.RegDst(Control2Mux4),
	.Branch(Branch2And),
	.MemToReg(),
	.ALUOp(AluOp2AluControl),
	.ALUSrc(AluSrc2Mux3),
	.RegWrite(RegWriteEnable)
	);
endmodule