# Research notes


## RISC-V architecture

### Instruction set
- RV32I has 38 instructions and is an minimal implementation of RISC-V (see [The RISC-V Instruction Set Manual](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf), Ch.02).
- You can even do a instruction set of 6: [PDP-5](https://gordonbell.azurewebsites.net/Digital/PDP%205%20Manual%201964.pdf).


#### Branch instructions
You can do all branch instructions with two: `beq` and `blt`:
- `bne r0 r1 label` =
    - `beq r0 r1 PC+1`
    - `beq zero zero label`
- `bgt t0 t1 label` = `blt t1 t0 label`
- `ble t0 t1 label` =
    - `blt t0 t1 label`
    - `beq t0 t1 label`
- `bge t0 t1 label` =
    - `blt t1 t0 label`
    - `beq t0 t1 label`


### Parser
Three ways to do it:
1. Use [ANTLR](https://www.antlr.org/) to generate the parser.
    - T. Parr. Language Implementation Patterns: Create Your Own Domain-Specific and General Programming Languages. Pragmatic Bookshelf, 2009  
        - P.25. Tree-Based Interpreter (p. 243)
            - P.4. LL(k) Recursive-Descent Parser (p. 59)
            - P.9. Homogeneous AST (p. 109)
            - P.12. External Tree Visitor (p. 131)
        - P.28. Register-Based Bytecode Interpreter (p. 281)
        - 10.2 Defining an Assembly Language Syntax (p. 257)
    - [Antlr4 for C++ with CMake: A practical example](https://beyondtheloop.dev/Antlr-cpp-cmake/)
    - [ANTLR C++ Documentation](https://github.com/antlr/antlr4/blob/master/doc/cpp-target.md)
    - [Writing interpreters with ANTLR](https://gjdanis.github.io/2016/01/23/roman/)
    - [Step by step creation of a simple compiler using ANTLR4](https://medium.com/@isetitra/step-by-step-creation-of-a-simple-compiler-using-antlr4-9285755cf943)
    - [Building a Scripting Language with Antlr 4 and C#](https://github.com/Doddler/Scripting-Language-Guide)
    - [Creating a LISP-like Interpreter (Introduction to ANTLR)](https://simonodonoghue.blog/2019/12/09/creating-a-lisp-like-interpreter-introduction-to-antlr/)
    - [Easy intro to writing a BASIC interpreter (with ANTLR)](https://mateiw.github.io/antlr-intro/)
    - [Getting Started with ANTLR in C++](https://tomassetti.me/getting-started-antlr-cpp/)
    - [Listeners And Visitors](https://tomassetti.me/listeners-and-visitors/)
    - [Best Practices for ANTLR Parsers](https://tomassetti.me/best-practices-for-antlr-parsers/)
    - [The ANTLR Mega Tutorial](https://tomassetti.me/antlr-mega-tutorial/)

2. Use lex ([GNU flex](https://github.com/westes/flex)) and yacc ([GNU bison](https://www.gnu.org/software/bison/))
    - J. Levine, D. Brown, T. Mason. lex & yacc, 2nd Edition. O'Reilly, 1992

3. By hand (programming the parser)
    - Wepsim [lexical.js](https://github.com/wepsim/wepsim/blob/master/sim_sw/assembly/lexical.js) and [asm_v2.js](https://github.com/wepsim/wepsim/blob/master/sim_sw/assembly/asm_v2.js)
    - [CREATOR RISC-V architecture config](https://github.com/creatorsim/creator/blob/master/architecture/RISC_V_RV32IMFD.json)
    - A. V. Aho, Ravi Sethi, J. D. Ullman. Compiladores: Principios, Técnicas y Herramientas. Addison-Wesley Iberoamericana, 1990
    - [Emulating a CPU in C++ (6502)](https://www.youtube.com/watch?v=qJgsuQoy9bc)


### Other useful links & bibliography
- [UC3M Computer structure repository](https://github.com/acaldero/uc3m_ec)
- PATTERSON, David A., HENNESSY, John L. Computer organization and design RISC-V Edition: The hardware/software interface. Segunda edición.  Morgan Kaufmann, 2021.
- [The RISC-V Instruction Set Manual](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)
- [RISC-V Reference Guide (CREATOR Simulator)](https://github.com/creatorsim/creator/blob/master/docs/risc_v_reference_guide.pdf)
- [CREATOR Simulator](https://github.com/creatorsim/creator)
- [A Guide to Parsing: Algorithms and Terminology](https://tomassetti.me/guide-parsing-algorithms-terminology/)
- [Language Processors OCW-UC3M](https://ocw.uc3m.es/course/view.php?id=131)
- [CS143 Compilers (Standford University)](https://web.stanford.edu/class/cs143/)



## WASM

### Useful links
- https://webassembly.org/



## C++ WASM Compilation
- Compile using [Emscripten](https://emscripten.org/)
- Allows for C++20 by using `-std=c++20` flag ([source](https://stackoverflow.com/questions/74508184/emscripten-and-c-20))
- Guides:
    - [T. Deniffel - Pragmatic compiling of C++ to WebAssembly. A Guide.](https://medium.com/@tdeniffel/pragmatic-compiling-from-c-to-webassembly-a-guide-a496cc5954b8)
    - [MDN Web Docs - Compiling a New C/C++ Module to WebAssembly](https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm#emscripten_environment_setup)



## WASM GUI
- [Qt for WebAssembly](https://doc.qt.io/qt-6/wasm.html)


## Report
- [Online Gantt Chart Generator](https://www.onlinegantt.com/#/gantt)
- [Mermaid Gantt Diagrams](https://mermaid.js.org/syntax/gantt.html)
- [Mermaid Flowcharts](https://mermaid.js.org/syntax/flowchart.html?id=flowcharts-basic-syntax)
