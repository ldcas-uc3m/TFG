# Project architecture

## Instruction set
- System calls (`ecal`)
    - Print_int
    - Print_string
    - Print_char
    - Read_int
    - Read_string
    - Read_char
    - Exit
- Data transfer
    - `li`
    - `mv`
- Arithmetic (integer)
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
    - `neg`
    - `xor`
    - `srli`
    - `slli`
- Branch
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
- Function Calls
    - `jal`
    - `jr`


## Functionalities
- Parser
- "GDB" interface
    - With register status
- Registers
- System calls
- `.data`, `.text`
- Tags
- Indexed Addressing
- Memory (dynamically generated)
- Comments
- Load files
- GUI