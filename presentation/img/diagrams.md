# Source code for the diagrams
The diagrams are generated using [Mermaid](https://mermaid.js.org/).

### Compilation ([`compilation.png`](compilation.png))
```mermaid
graph LR;
    asm[fa:fa-file-code Assembly file] & json["
            fa:fa-file-alt ISA file
        "] --> compiler(fa:fa-industry Compiler);
    compiler --> lisp["fa:fa-list-ul LUISP-DA instructions"]
    compiler --> data["fa:fa-table-cells Program data"]
    lisp <-.-> cpu(fa:fa-microchip CPU)
    data <-.-> cpu
```

### Design
```mermaid
graph TD;
    compiler["fa:fa-industry Compiler"]

    cli["fa:fa-terminal CLI"]

    subgraph memory["fa:fa-memory Memory"]
        data["fa:fa-list-ul Data Memory"]
        text["fa:fa-table-cells Text Memory"]
    end

    subgraph cpu["fa:fa-microchip CPU"]
        reg["fab:fa-buffer Register File"]
        alu["fas:fa-gears ALU"]
        interp["fas:fa-circle-nodes Control Unit"]
    end

    cpu <--> memory
    cli <--> cpu
    cli <--> compiler
    compiler <--> memory
    cli <--> memory
```


### Gantt ([`gantt.svg`](gantt.svg))
1. Compile [`gantt.tex`](gantt.tex)
    ```bash
    pdflatex gantt.tex
    ```
2. Transform from PDF to SVG w/ [pdf2svg](https://github.com/dawbarton/pdf2svg) (Windows binaries in [jalios/pdf2svg-windows](https://github.com/jalios/pdf2svg-windows))
    ```bash
    pdf2svg gantt.pdf gantt.svg
    ```