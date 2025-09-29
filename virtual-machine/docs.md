# 16-bit Toy VM Instruction Set Architecture (ISA)

This document describes the instruction set for a 16-bit toy VM using **6-bit opcodes**.
All instructions are **16 bits (2 bytes)**; there are **no extension words**.
Large values must be loaded into registers first before use in operations.

---

## Instruction Word Layout (16 bits)

```
Bits 15–10 : Opcode (6 bits)        ; 64 possible instructions
Bits 9–8   : Addressing mode (2 bits) ; reg–reg, reg–imm4, reg–mem
Bits 7–4   : Destination register (4 bits) ; R0–R15
Bits 3–0   : Source register / small immediate (4 bits) / flags
```

### Addressing Mode (2 bits)

| Mode | Meaning |
|------|---------|
| 00   | Register–Register (dst = dst OP src) |
| 01   | Register–Immediate 4-bit (dst = dst OP imm4) |
| 10   | Register–Memory / Memory–Register (dst = MEM[src]) |
| 11   | Reserved / instruction-specific (not used for large immediates) |

> **Note:** All large values must be loaded into a register before use; there is no “fetch 16-bit immediate” mode.

---

## Registers

- **General purpose:** R0–R15
- **Special:**
  - `PC` — Program counter
  - `SP` — Stack pointer
  - `FLAGS` — Status flags

### FLAGS Register (bitwise)

| Bit | Name | Meaning |
|-----|------|--------|
| 0   | Z    | Zero flag (result == 0) |
| 1   | S    | Sign flag (result negative) |
| 2   | C    | Carry flag (unsigned overflow) |
| 3   | O    | Overflow flag (signed overflow) |
| 4–7 | —    | Reserved |

> Arithmetic, logic, and comparison instructions automatically update FLAGS.

---

## Opcode Table (6-bit)

| Opcode | Mnemonic       | Addressing Modes | Description |
|--------|----------------|-----------------|------------|
| 0x00   | NOP            | —               | No operation |
| 0x01   | MOV            | reg–reg / reg–imm4 | Copy value |
| 0x02   | LDI            | reg–imm16        | Load large immediate into register |
| 0x03   | ADD            | reg–reg / reg–imm4 | Add |
| 0x04   | SUB            | reg–reg / reg–imm4 | Subtract |
| 0x05   | MUL            | reg–reg / reg–imm4 | Multiply |
| 0x06   | DIV            | reg–reg / reg–imm4 | Divide |
| 0x07   | AND            | reg–reg / reg–imm4 | Bitwise AND |
| 0x08   | OR             | reg–reg / reg–imm4 | Bitwise OR |
| 0x09   | XOR            | reg–reg / reg–imm4 | Bitwise XOR |
| 0x0A   | NOT            | reg–reg          | Bitwise NOT |
| 0x0B   | SHL            | reg–imm4         | Shift left |
| 0x0C   | SHR            | reg–imm4         | Shift right |
| 0x0D   | LOAD             | reg–mem          | Load from memory |
| 0x0E   | STOR             | mem–reg          | Store to memory |
| 0x0F   | COMP            | reg–reg / reg–imm4 | Compare and set FLAGS |
| 0x10   | JUMP            | reg–mem          | Unconditional jump (PC = addr in reg or memory) |
| 0x11   | JZ             | reg–mem          | Jump if zero flag set |
| 0x12   | JNZ            | reg–mem          | Jump if zero flag clear |
| 0x13   | JG             | reg–mem          | Jump if greater (S=0 & Z=0) |
| 0x14   | JL             | reg–mem          | Jump if less (S=1) |
| 0x15   | CALL           | reg–mem          | Push return addr, jump to subroutine |
| 0x16   | RET            | —                | Return from CALL (pop PC) |
| 0x17   | PUSH           | reg              | Push register onto stack |
| 0x18   | POP            | reg              | Pop stack into register |
| 0x19   | HALT           | —                | Stop execution |
| 0x1A–0x3F | reserved    | —                | — |

> Opcodes above 0x19 are reserved for future expansion.

---

## Memory

- Word-addressable, 16-bit words
- Address space: 64 KB (0x0000–0xFFFF)
- `SP` grows downward: `PUSH` decrements SP, `POP` increments SP

---

## Control Flow

- **PC** increments by 1 (instruction word) after each instruction
- `CALL` pushes return address on stack; `RET` pops back into PC
- Conditional jumps (`JZ`, `JNZ`, `JG`, `JL`) test FLAGS

---

## Example Program

```asm
; Load large values into registers first
LDI R1, 10
LDI R2, 20

; Compare R1 and R2
CMP R1, R2
JL less

MOV R3, R1   ; R1 >= R2
JMP end

less:
MOV R3, R2   ; R1 < R2

end:
HALT
```

- All instructions are 16-bit words.
- Large values are preloaded into registers.
- Conditional jumps use FLAGS set by `CMP`.

for register offsets, you just need to compute that offset prior and then
send the one register to the instruction


ints are signed, using 2s compliment
