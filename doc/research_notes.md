# Research notes


## RISC-V architecture

### Instruction set
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

### Functionalities
- Parser
- "GDB" interface
    - With register status
- Registers
- System calls
- `.data`, `.text`
- Tags
- Indexed Addressing
- Memory (dynamically generated)
- GUI


### Useful links & bibliography
- [UC3M Computer structure repository](https://github.com/acaldero/uc3m_ec)
- PATTERSON, David A., HENNESSY, John L. Computer organization and design RISC-V Edition: The hardware/software interface. Segunda edición.  Morgan Kaufmann, 2021. ISBN: 0128122757
- [RISC-V Reference Guide (CREATOR Simulator)](https://github.com/creatorsim/creator/blob/master/docs/risc_v_reference_guide.pdf)
- [CREATOR Simulator](https://github.com/creatorsim/creator)



## C++ WASM Compilation
- Compile using [Emscripten](https://emscripten.org/)
- Allows for C++20 by using `-std=c++20` flag ([source](https://stackoverflow.com/questions/74508184/emscripten-and-c-20))
- Guides:
    - [T. Deniffel - Pragmatic compiling of C++ to WebAssembly. A Guide.](https://medium.com/@tdeniffel/pragmatic-compiling-from-c-to-webassembly-a-guide-a496cc5954b8)
    - [MDN Web Docs - Compiling a New C/C++ Module to WebAssembly](https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm#emscripten_environment_setup)



## WASM GUI
- [Qt for WebAssembly](https://doc.qt.io/qt-6/wasm.html)