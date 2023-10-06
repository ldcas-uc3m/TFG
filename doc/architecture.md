# Project architecture

## RISC-V architecture

### Instruction set

- System calls (`ecal`)
    - Print_int
    - Print_string
    - Read_int
    - Read_string
    - Exit
- Data transfer
    - `li`
    - `mv`
- Arithmetic (integer) -> convert reg to signed, operate, convert to unsigned
    - `add`
    - `addi`
    - `sub`
    - `mul`
    - `div`
    - `rem`
- Logical (integer)
    - `and`
    - `or`
    - `not`
        - 1's complement
    - `neg`
        - 2's complement
    - `xor`
    - `srli`
        - unsigned
    - `srai`
        - signed
    - `slli`
        - unsigned
    - `sra`
        - signed
    - `srl`
        - unsigned
- Branch (signed)
    - `beq`
    - `bne`
    - `blt`
    - `bge`
    - `bgt`
    - `ble`
- Memory Access
    - `la`
    - `lw`
    - `sw`
    - `lb`
    - `sb`
- Function Calls
    - `jal`
    - `jr`


### Functionalities

### Parser

Treat line by line

Line ::=
- Comment
- Line + comment
- Segment directive (`.data`, `.text`)
- Label + type directive + value (`.data`)
- Label + instruction (`.text`)
- Instruction (`.text`)

<!-- TODO: put in Backus-Naur Form -->

---


- "GDB" interface
    - With register status
- Registers
    - Treat as unsigned
- System calls
- Memory (dynamically generated)
- GUI

