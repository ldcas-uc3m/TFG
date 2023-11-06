# Project architecture


## Parser

General functionality:
1. Translate from ASM to Lisp dialect (LUISP-DA) instructions using the architecture definition file (LUISP-DA instructions already codified in config file)
2. Save those instructions to memory, in order for them to be executed by the CPU

``` mermaid
graph LR;
    asm[fa:fa-file-code Assembly file] & json["
            fa:fa-file-alt Architecture config file
            (JSON)
        "] --> parser(fa:fa-industry Parser);
    parser -.-> lisp["
                    fa:fa-align-justify LUISP-DA instructions
                    (.text)
                "]
    lisp --> cpu(fa:fa-microchip CPU)
```
<!-- Icons from https://fontawesome.com/icons -->


### Architecture definition file
<!-- TODO -->


## LUISP-DA
assembLy analogoUs Interpreted liSP DiAlect
<!--
Lisp  
Ubiquitous  
Interpreted  
Simple  
Post  
-  
Decoding language for  
Assembly
-->

It's a Lisp-like language, where instructions are defined as a list (`LST`).
- A list is always in between parenthesis:
    ```lisp
    (+ 1 2)
    ```
- Its first element is called the symbol (`SYM`), or operator, which will be applied to the rest of the elements of the list.  
    In the example:
    ```lisp
    (+ 1 2)
    ```
    The operator `+` is applied to `1` and `2`, giving as a result `3`.
- A list can be an element of another list. Inner lists are computed first, and they return the evaluation of the list.  
    In the example:
    ```lisp
    (+ 1 (+ 2 2))
    ```
    The operator `+` is applied to `2` and `2`, giving as a result `4`:
    ```lisp
    (+ 1 4)
    ```
    Then the operator `+` is applied to `1` and `4` (`(+ 2 2)`), giving as a result `5`.

The atomic symbols implemented are:
- `INM`: Integer numbers
- `REG`: Registers defined in the architecture file
- `SYM`: Operators

The implemented operators (with its operands) are:
- `+ A B`: Adds two inmediates (`INM`) `A` and `B`
- `reg A`: Returns the value stored in register (`REG`) `A`
- `reg! A B`: Stores the inmediate (`INM`) `B` in register (`REG`) `A`
- `pc `: Returns the value stored in the PC
- `pc! A`: Stores the inmediate (`INM`) `A` in the PC

A block `BEG` is also implemented. This allows to sequentially execute multiple instructions inside one instruction (PC is not updated for those instructions).

After each instruction, the PC is updated.


You have the full grammar definition of the language in [LUISP_DA.g4](../src/cpu/interpreter/LUISP_DA.g4).


## CPU

An interpreter for the LUISP-DA language.

``` mermaid
flowchart TD
    subgraph CPU
        Interpreter --> ALU
        Interpreter --> RegisterFile
        ALU --> RegisterFile

    end

```


### Interpreter

``` mermaid
stateDiagram-v2

    [*] --> read_inst: Instruction

    state READ {
        read_inst --> read_str
        read_str --> tokenize
        read_str --> read_token

        --

        read_token --> read_atom
        read_token --> read_list
        read_list --> read_token
    }

    read_inst --> EVAL: AST

    state EVAL {
        eval_token --> eval_ast
        eval_ast --> eval
    }

    EVAL --> repl_env
```



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


The full grammar is defined in [`riscv_asm.g4`](../src/parser/riscv_asm.g4).


### Register File (`RegisterFile`)
The Register File class can be found in [register_file.hpp](../src/cpu/register_file.hpp), and takes an initializer list of strings with the names of the registers.

The class is composed of three parts:
- A vector of unsigned 32b integers `_rf` with the values of the registers (indexed by ints, as it's a vector).
- A vector of strings `_reg_names` with the names of the registers from the initializer list, which acts as a map between the register indexes (ints) and the register names (index → name).
- A map `_reg_map` between the register names and the register indexes (name → index).

This is done so you can access the value of a register either by name (that's why you need `_reg_map`) or by index, by overloading the `[]` operator, and so that you can print the names of the registers with the values (that's why you need `_reg_names`), by overloading the `<<` operator.

#### Display modes

The Register File also has different display modes. These modes control how the RF will be displayed when using the `<<` operator.  
There are three modes:
- Hexadecimal (`rfdmode::HEX`): Displays the values as hex values
- Signed (`rfdmode::SIG`): Displays the values as signed integers
- Unsigned (`rfdmode::USG`): Displays the values as unsigned integers

These modes are defined in the `rfdmode::dmode` enum and can be changed through the `RegisterFile.setdmode()` method (which the `_dmode` attribute).




---


- "GDB" interface
    - With register status
- Registers
    - Treat as unsigned
- System calls
- Memory (dynamically generated)
- GUI
- Savestates

