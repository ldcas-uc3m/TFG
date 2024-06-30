---
marp: true
title: Analysis, Design and Implementation of a Didactic and Generic Assembly Language Simulator
theme: default
paginate: true
size: 4:3
math: mathjax
style: |
    img[alt~="center"] {
        display: block;
        margin: 0 auto;
    }
    @import 'https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.3.0/css/all.min.css'
---


<!-- _paginate: skip -->
![bg contain opacity:.04](img/uc3m_logo.svg)
# Analysis, Design and Implementation of a Didactic and Generic Assembly Language Simulator
By Luis Daniel Casais Mezquida

_Bachelor's Degree in Computer Science and Engineering  
Universidad Carlos III de Madrid_

Leganés, July 2024


---
<!--
"The structure of this presentation is the following"
"We start with the introduction... [next slide]"
-->
## Contents
1. Introduction: Motivation and Objectives
2. State of the Art
3. Design
4. Planning
5. Conclusions and Future Work


---

# Introduction


---
<!-- header: '**Introduction**' -->

<!--
- Need for ISA design the last few years (commercial war, hardware acceleration) -> need for prototyping and validation
- Learning how hardware works helps us build better programs

- Important to get the concepts of assembly -> ISA changes
- assembly is important (cybersecurity, efficiency)
-->
## Motivation
- ISA design **matters**
    - RISC-V, NPUs, etc.
    - Software built on top of hardware
- Learning assembly language is _hard_
    - Assembly language depends on ISA
    - Unintuitive
    - Few educational tools


---
<!--
- Interactive approach has been proven to help learning
-->
## Objectives
- Helping people learn assembly language programming
    - Understanding underlying concepts
    - Interactive approach
- Introduce people to ISA design

---
Create an assembly simulator that is:
- Agnostic
- Easily programmable
- Interactive
- Able to be executed in multiple platforms
- Performant
- FOSS


---
<!-- header: ''-->
<!--
See what we can learn
-->
# State of the Art


---
<!-- header: 'State of the Art'-->

## Specific simulators
E.g. [ARMLite](https://www.peterhigginson.co.uk/ARMlite/), [Kite](https://casl.yonsei.ac.kr/kite/).
- Simulate one ISA
- Educational
- Step-by-step execution
- Advanced features (pipelining)
- Error checking
- CLI/GUI
- I/O


---
## Generic simulators
<!--
Can incorporate some features from specific

- Sail used in proffesional settings (e.g. RISC-V) as theorem prover
- CREATOR from UC3M
-->
- Simulate user-defined ISA
- Two approaches:
    - Generate executable simulators (e.g. [Sail](https://github.com/rems-project/sail))
    - Interpret assembly instructions (e.g. [CREATOR](https://creatorsim.github.io/))

---
<!--
Plot of current simulators
- Balance didactic and generic
    - Validation / simplicity
-->
![w:550 center](../report/img/simulator_map.drawio.svg)


---
<!--
1. through the use of an powerfull, but easily understandable language
2. Interactive
3.
1. Important for education
2. Useful for teachers -> checking through scripts
3. Better
4. In order to be used in many settings
-->
## Desired features
1. Simple ISA definition
2. Step-by-step execution
3. I/O support
4. Error checking
5. Architecture validation support
6. FOSS
7. Multi-platform support



---
<!-- header: ''-->
# Design


---
<!-- header: 'Design'-->
<!--
Compile file with ISA definition into LUISP-DA, execute that
-->
## Overview
![center](img/compilation.png)


---
<!--
- Syscalls map number to type -> defined in ISA file
-->

## LUISP-DA
_assembLy analogoUs lISP DiAlect_
- Lisp-like DSL
    - Instructions are expressions
    - Simple, easy to use, and easily validatable
- Basic operators
    - Arithmetic and logical
    - Register and memory manipulation
- Conditionals and blocks
- System calls

---
<!--
* ISA defines syscall codes
-->
```lisp
; addi t0 t1 69
(reg! t0 (+ (reg t1) 69))
```

```lisp
; beq t0 t1 0x000001a4
(if (== (reg t0) (reg t1)) (pc! 0x000001a4) ())
```

```lisp
; jal ra 0x000001a4
(do (reg! ra (pc)) (pc! 0x000001a4))
```

```lisp
; exit*
(call 0)
```


---
## Architecture
<!--
- Based on real processor architecture
-->
![w:600 center](img/component_diagram.drawio.svg)


---
## Implementation (?)
- C++20
    - STL + [JSON for Modern C++](https://json.nlohmann.me/)
- Modular design
- LUISP-DA interpreter based on [Make a Lisp](https://github.com/kanaka/mal)
- https://github.com/ldcas-uc3m/TFG



---
<!-- header: ''-->
# Planning

---
<!-- header: 'Planning'-->
- **Duration:** 9 months, 315 h (35 h/month)
- **Cost:** 20.307,84 €


---
## Time estimation
<!--
- Iterative methodology
    - Based on Bohem's spiral model
    - Flexible -> allows backtracking
    - Encourages prototyping
- Divided in four iterations
- Hardest part was Interpreter (Control Unit)
-->
![center](img/gantt.svg)


---
<!--
- Personnel: Project Manager, Analyst, Programmer, Tester
-->
## Budget
<center>

| **Concept**    |     **Cost**    |
|----------------|-----------------|
| Personnel      |     11.850,00 € |
| Equipment      |        139,44 € |
| Indirect costs |        172,40 € |
| Risk (20%)     |      2.432,37 € |
| Benefits (15%) |      2.189,13 € |
| Tax (21%)      |      3.524,50 € |
| **TOTAL**      | **20.307,84 €** |

</center>



---
<!-- header: ''-->
# Conclusions and Future Work


---
<!-- header: 'Conclusions and Future Work'-->

## Conclusions
- Created a generic assembly language simulator
    - Instructions defined through a simple DSL
    - Portable to multiple platforms
    - Easily expandable
    - GPLv3
- Gained knowledge
    - Compiler design
    - Modern C++


---
## Future Work
- More operators (floating point, bitwise, etc.)
- Browser support (WASM)
- Ease of use features (breakpoints, save states, etc.)
- GUI
- Implementation improvements
    - `std::variant` for tokens
    - C++20 modules
    - C++23



---
<!-- header: ''-->
# Demo


---
<!-- _paginate: skip -->
![bg contain opacity:.04](img/uc3m_logo.svg)
# Analysis, Design and Implementation of a Didactic and Generic Assembly Language Simulator
By Luis Daniel Casais Mezquida

_Bachelor's Degree in Computer Science and Engineering  
Universidad Carlos III de Madrid_

Leganés, July 2024