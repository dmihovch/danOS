16 bit virtual machine

4 general purpose registers

3 byte 'instructions'

byte 1: 4 bits opcode, 2 bits mode (immediate value, memory address, single register, double register), 2 bits register
byte 2 + 3: 16 bits for either value, memory address or register


Memory Segmentation:

65336 bytes indexes 0 - 65335

0x0000 - 0x3FFF ; Program code
0x4000 - 0x5FFF ; Data/global variables
0x6000 - 0xCFFF ; Heap (starts at 0x6000)
0xD000 - 0xFEFF ; Stack (starts at 0xFEFF)
0xFF00 - 0xFFFF ; I/O / special addresses



Instruction layout:

Byte 1: 0000|opcode 00|mode 00|register
Byte 2 + 3: values, addresses, registers

modes:
    00 - immediate value
    01 - memory address
    10 - register id
    11 - special mode, zero or one operand,
         if this is the case, byte 2 will
         contain information on how to handle,
         and will tell you if another byte was
         needed to encode all the necessary data

byte 2 (special mode):
    top two bits (most significant bits):
    00 - zero operands, no extra memory
    01 - one operand, no extra memory
    10 - one operand extra memory

zero operands
one operand no extra memory
one operand extra memory



Instruction set:

all ints are signed, using twos compliment

ADD : 0x01 ; 0001 ; addition
SUB : 0x02 ; 0010 ; subtraction
MUL : 0x03 ; 0011 ; multiplaction
DIV : 0x04 ; 0100 ; division (no floating point, truncate decimal)
LOD : 0x05 ; 0101 ; load
STR : 0x06 ; 0110 ; store
JMP : 0x07 ; 0111 ; jump
