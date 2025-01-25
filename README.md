# 32-bit MIPS CPU

## Project Description
I led a team of three people to develop a 32-bit MIPS CPU from scratch. The project utilized Verilog and Assembly to create a fully functional CPU, which includes key components like the ALU, Control Unit, Memory Registry, and Memory Bank. This project provided hands-on experience with CPU design and verification.

## Architecture Overview
The CPU architecture includes the following key components:
- **ALU (Arithmetic Logic Unit)**: Performs arithmetic and logical operations.
- **Control Unit**: Directs the operations of the CPU by generating control signals.
- **Memory Registry**: Holds the contents of registers and other temporary data.
- **Memory Bank**: Stores data and instructions.
- **Program Counter (PC)**: Keeps track of the current instruction's address.
- **Add**: Defines the addition operation used in the ALU.
- **Multiplexers**: Multiplexers that handle selecting inputs based on control signals to ensure the correct data flows through the CPU.
- **ALUControl**: Controls the operation of the ALU, determining which specific operation (add, subtract, etc.) to perform.
- **TypeR**: A specific instruction type in the MIPS architecture that includes a register-based operation, affecting the instruction format or execution.

## Features
- **32-bit MIPS Instruction Set**: Supports standard MIPS operations such as ADD, SUB, AND, OR, etc.
- **Basic ALU Operations**: Addition, subtraction, and bitwise operations.
- **Control Logic**: Determines the operations to perform based on the opcode and other instruction fields.
- **Memory and Register File**: Basic operations to fetch and store data.
- **Tested Operations**: Basic tests ran through the ALU to ensure correctness.

## Technologies/Tools Used
- **Verilog**: Used for hardware description and design.
- **ModelSim**: For simulation and testing of Verilog code.
- **Assembly**: To test CPU instructions and verify functionality.
- **C++**: Initially intended for decoding assembly instructions (though this feature isn't fully functional yet).

## How to Build/Run the Project
I will provide instructions to test this code in the following weeks. Stay tuned for the detailed steps!

## Usage
I will provide detailed instructions once I finish the instruction decoder, keep an eye out for further updates!

## Testing
I will provide specific testing prompts in the coming weeks to help validate the functionality and ensure correctness. Keep an eye out for further updates!

## Future Work
- **Instruction Decoder**: Improve and complete the instruction decoder to allow the CPU to decode and execute assembly instructions directly.

## Contributing
This project was completed as part of my schoolwork, and no further contributions are being accepted. Any future work will be completed by me for further learning.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.
