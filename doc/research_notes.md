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


### Assembly interpreter
Three ways to do it:

#### 1. [ANTLR](https://www.antlr.org/) 
To generate the lexer/parser and use ASTs and Visitors.
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

Why not:
1. No tengo ni idea sobre Procesadores del Lenguaje, ni tampoco tiene pinta de que esto sea lo mío. ANTLR es interesante, me encanta la idea de que le metes una gramática y te escupe una librería, y te deja hacer muchas cosas, pero creo que al menos para yo aprender y suplir esa asignatura que no me dejaron cursar, es mejor que aprenda haciéndolo desde cero. 2. Prefiero no tener dependencias, y ANTLR y CMake me quitan las ganas de vivir.
3. Hacerlo de esta forma permite definir tus propias arquitecturas, al final acaba siendo un intérprete más genérico, y se parece más a CREATOR, lo cual implica que os puede ser más útil a vosotros. 4. No hay que recompilar para cambiar la arquitectura (ésto le hace mucha ilusión a Jose Antonio). ANTLR no está pensado para implementar esta arquitectura con archivos de configuración como los descritos, y ésta arquitectura implica un parser muy simple (básicamente buscar en un diccionario) y un intérprete más parecido a como funciona una CPU: tienes un set de instrucciones en memoria y las vas ejecutando. Ni árboles ni leches.

#### 2. Use lex ([GNU flex](https://github.com/westes/flex)) and yacc ([GNU bison](https://www.gnu.org/software/bison/))
- J. Levine, D. Brown, T. Mason. lex & yacc, 2nd Edition. O'Reilly, 1992

#### 3. ASM to lisp-like interpreter (LUISP-DA)
Create a lisp language and an interpreter for it. ASM translates to lisp through architecture.
- [Make A Lisp](https://github.com/kanaka/mal/blob/master/process/guide.md)
- Wepsim [lexical.js](https://github.com/wepsim/wepsim/blob/master/sim_sw/assembly/lexical.js) and [asm_v2.js](https://github.com/wepsim/wepsim/blob/master/sim_sw/assembly/asm_v2.js)
- [CREATOR RISC-V architecture config](https://github.com/creatorsim/creator/blob/master/architecture/RISC_V_RV32IMFD.json)


#### 4. Sail
https://github.com/rems-project/sail/tree/sail2


### Other useful links & bibliography
- [UC3M Computer structure repository](https://github.com/acaldero/uc3m_ec)
- PATTERSON, David A., HENNESSY, John L. Computer organization and design RISC-V Edition: The hardware/software interface. Segunda edición.  Morgan Kaufmann, 2021.
- [The RISC-V Instruction Set Manual](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)
- [RISC-V Reference Guide (CREATOR Simulator)](https://github.com/creatorsim/creator/blob/master/docs/risc_v_reference_guide.pdf)
- [CREATOR Simulator](https://github.com/creatorsim/creator)
- [A Guide to Parsing: Algorithms and Terminology](https://tomassetti.me/guide-parsing-algorithms-terminology/)
- [Language Processors OCW-UC3M](https://ocw.uc3m.es/course/view.php?id=131)
- [CS143 Compilers (Standford University)](https://web.stanford.edu/class/cs143/)
- José Daniel García Sánchez. Advanced C++ modern programming.
- A. V. Aho, Ravi Sethi, J. D. Ullman. Compiladores: Principios, Técnicas y Herramientas. Addison-Wesley Iberoamericana, 1990
- [Emulating a CPU in C++ (6502)](https://www.youtube.com/watch?v=qJgsuQoy9bc)
- [D. Solomons. Assemblers And Loaders.](https://www.davidsalomon.name/assem.advertis/AssemAd.html)
- Torben Ægidius Mogensen. Basics of Compiler Design, Anniversary edition. lulu.com, 2010.
- Andrew W. Appel. Modern Compiler Implementation in C. Cambridge University Press, 1998.



## WASM

### Useful links
- https://webassembly.org/



## C++ WASM Compilation

- Compile using [Emscripten](https://emscripten.org/)
- Allows for C++20 by using `-std=c++20` flag ([source](https://stackoverflow.com/questions/74508184/emscripten-and-c-20))

<!--
WIP

Install Emscripten by:
``` bash
git clone --depth=1 https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

Run:
```bash
source ~/emsdk/emsdk_env.sh
# CMAKE_TOOLCHAIN_FILE=$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
cd build
emcmake cmake ..
make
```
-->

- Guides:
    - [T. Deniffel - Pragmatic compiling of C++ to WebAssembly. A Guide.](https://medium.com/@tdeniffel/pragmatic-compiling-from-c-to-webassembly-a-guide-a496cc5954b8)
    - [MDN Web Docs - Compiling a New C/C++ Module to WebAssembly](https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm#emscripten_environment_setup)
    - [Compile C++ to WebAssembly and JavaScript using Emscripten and CMake](https://gist.github.com/ericoporto/8ce679ecb862a12795156d31f3ecac49)
    - [Emscripten with CMake](https://stunlock.gg/posts/emscripten_with_cmake/)
- Examples:
    - [floooh/pacman.c](https://github.com/floooh/pacman.c)



## WASM GUI
- [Qt for WebAssembly](https://doc.qt.io/qt-6/wasm.html)


## Report
- [Online Gantt Chart Generator](https://www.onlinegantt.com/#/gantt)
- [Mermaid Gantt Diagrams](https://mermaid.js.org/syntax/gantt.html)
- [Mermaid Flowcharts](https://mermaid.js.org/syntax/flowchart.html?id=flowcharts-basic-syntax)
- [SRS-latex-uc3m](https://github.com/jalopezg-git/SRS-latex-uc3m)




## C++
Why C++:
- Modern, but old language
- Strongly typed, safe, high-performance with zero-cost abstractions.
- Portability to WASM, Python Modules.

Useful stuff:
- [C++ reference](https://en.cppreference.com): C++ Bible
    - [Compiler support](https://en.cppreference.com/w/cpp/compiler_support): allows you to see which feature from each standard is implemented in which compiler. A godsend!
- [31 nooby C++ habits you need to ditch](https://www.youtube.com/watch?v=i_wDa2AS_8w)

### Casting
- `static_cast<target_type>(value)`


### Functions

- **Specifiers:** Modify the function's properties
    - [`noexcept`](https://en.cppreference.com/w/cpp/language/noexcept_spec): The function doesn't lauch exception. If it does, **shit goes down**.
    - [`[[nodiscard]]`](https://en.cppreference.com/w/cpp/language/attributes/nodiscard): You have to assign to something whatever the function returns.
    - [`inline`](https://en.cppreference.com/w/cpp/language/inline): Signals the compiler that you prefer to not deal with the overhead of a function call. Don't use with recursive functions.
    - [`constexpr`](https://en.cppreference.com/w/cpp/language/constexpr): The function results can be evaluated at compile time. Use with simple functions, without try-catch blocks.
- **Parameter passing convention:** Types of parameter passing.
    - **By value -** `type p`: It makes a copy.
    - **By constant value -** `type const p`: It makes a copy, but it can't be modified.
    - **By reference -** `type & p`: Passes a reference to the object.
    - **By constant reference -** `type const & p`: Passes a reference to the object, but it can't be modified.
    - **By movement -** `type && p`: Passes the ownership of the object to the function.

### Classes
- **Constructor**: Get executed when the object is created. Methods, same name as the class.
    - Called with its arguments with `class{ p1, p2, ...}`.
    - Initialization list `class(...) : p1{...}, p2{...}, ...`: List of constructors to be run before this constructor. Add here the constructors of the class members.  
    **IMPORTANT:** Class members don't initialize in the order that they appear, they are initialized in the order they are declared in.
- **Accesibility:**
    - `public`: Everyone can access.
        - Default in `struct`.
    - `private` Only members can access.
        - Default in `class`.
    - `protected`: Only members and children can access.
- **Specifiers:**
    - `final`: To prevent further inheritance.

#### Member functions (methods)
- **Specifiers:** Modify the function's properties
    - `static`: Allow for it to be called outside the class.
    - `const` (after parenthesis): Use it if you don't modify any class member.
    - `friend`: As if you define the function outside the class, you must pass a parameter for the class object. It has acces to the private members of the class.

### Enums
- Use `enum class`.


### Typedef
Don't use it, use aliases: `using new_type = old_type`.

### #define
Don't use it, use `constexpr`.

### Namespaces


### Templates and concepts
This is C++'s implementation of generic programming, which allows you to use the same function for different parameter types/classes. This is **not** overloading, because that requires two function definitions.

You declare a template through `template <NAME>`, and that `NAME` will represent any type defined in the template. A template only applies to the next function definition.

In order to constraint the number of types, you can use concepts, which are specified before the template type name. If no concept is specified, _all_ types will be valid.  
C++20 comes with some predefined concepts in the `<concepts>` header.

E.g. the following function allows to check if any integer number is even, allowing for all integer types (`int`, `long`, etc.).
```cpp
#include <concepts>

template <std::integral INT_T>
bool is_even(INT_T n) {
    return n % 2 == 0;
}

int two = 2;
long two_long = 2;

is_even(two);
is_even(two_long);
```

### Concepts



### Data structures
- `std::array<type, size>`: Classic arrays
- `std::vector<type>`: A non-fixed size array
    - Constructor: `{ value0, ... }`
    - To append a value, use `.push_back(value)`
- `std::map<keyType, valueType>`: Ordered key-value pairs. Keys must be constant.
    - Constructor: `{ {key0, value0}, ... }`
    - `[]` operator will create the element if it doesn't exist. Use `.at()` to access the element.
    - `.contains(key)` checks if a key exists in the map
- `std::unordered_map<keyType, valueType>`: Unordered `std::map`.


### Ranged loops

`for (type elem : iterable) {}`
- Remember you can use `auto` for the type (you still need to put your `const` and `&` if needed).
- You can use structured bindings in order to make your life easier: `for (type [memberA, memberB, ...] : iterable) {}`.  
  Specially usefull with maps. E.g.:
  ``` cpp
  std::unordered_map<std::string, std::array<int>> my_map { 
      {"A", [0, 1, 2]},
      {"B", [3, 4, 5]}
  };

  for (const auto & [key, value] : my_map) {
      std::cout << key << ": " << value << std::endl;
  }
  ```

### Lambdas
Nameless functions: `[captured_variable0, ...] (param_type param0, ...) -> return_type { <body> }`
- The return type is optional
- Captured variables are variables from the local scope to be passed to the lambda function
    - They are copied by default, use `&captured_variable` to reference it.
    - Use `[&]` to capture everything, `[=]` to copy everything.
  
E.g.:

``` cpp
int x = 69;
[&x] (int y) -> std::string { return std::to_string(y + x); }
```

- Useful to map keys to functions:
    ``` cpp
    int x = 69;
    std::string add_stuff(int y) {
        return std::to_string(y + x);
    }

    using myFunction = std::function<std::string (int)>;
    const std::unordered_map<std::string, myFunction> myMap {
        {
            "+",
            [&x] (int y) {return add_stuff(y);}
        }
    };

    int y = 420;
    myMap["+"](y)
    ```


### Exceptions
[Custom C++ Exceptions for Beginners](https://peterforgacs.github.io/2017/06/25/Custom-C-Exceptions-For-Beginners/)



### Header files
- [Classes and header files](https://www.learncpp.com/cpp-tutorial/classes-and-header-files/)


### JSON ([nlohmann/json](https://github.com/nlohmann/json))
- [Official Documentation](https://json.nlohmann.me/)

#### Instalation
- [Use CMake FetchContent](https://github.com/nlohmann/json?tab=readme-ov-file#embedded-fetchcontent)
- [Install (build from source) + CMake](https://github.com/nlohmann/json/issues/1755#issuecomment-1837675544)
- [submodules?](https://gist.github.com/gitaarik/8735255)

### Modules (C++ 20)
Theory:
- [C++20 Modules | A Gentle Introduction](https://www.studyplan.dev/pro-cpp/modules)
- [Understanding C++ Modules: Part 1: Hello Modules, and Module Units](https://vector-of-bool.github.io/2019/03/10/modules-1.html)
- [Understanding C++ Modules: Part 2: export, import, visible, and reachable](https://vector-of-bool.github.io/2019/03/31/modules-2.html)
- [Understanding C++ Modules: Part 3: Linkage and Fragments](https://vector-of-bool.github.io/2019/10/07/modules-3.html)

Practice:
- [Modules in the big three compilers: a small experiment](https://www.reddit.com/r/cpp/comments/zswkp8/modules_in_the_big_three_compilers_a_small/?share_id=0m1-wcoqw7Cjx4G9OBR2V&utm_content=2&utm_medium=android_app&utm_name=androidcss&utm_source=share&utm_term=1)
- [Simple usage of C++20 modules](https://vitaut.net/posts/2023/simple-cxx20-modules/)
- [import CMake; the Experiment is Over!](https://www.kitware.com/import-cmake-the-experiment-is-over/)

Couldn't get them to work, support is still shit.


## CMake
In order to structure the project with CMake, add a `CMakeLists.txt` for each source directory:
- On the root folder, the file will contain the project and compilation configuration. Make sure to include the subdirectories (where the source files are located, e.g. `src/`) with `add_subdirectory(<subdir>)`.  
  E.g. [`CMakeLists.txt`](../CMakeLists.txt)

- For library directories (any without a target/executable file), just write a `target_sources<name>)` and specify the library name and public and private header/source files, tipically all header (`.hpp`) files are public and all source (`.cpp`) files are private (but you can keep some header files private if you only need them for that library).
    - If you have subdirectories (tipically for private sub-libraries), you can just specify the relative path of the header/source files, there's no need to create a new `CMakeLists.txt` in the subdirectory.  
    E.g. [`src/cpu/CMakeLists.txt`](../src/cpu/CMakeLists.txt).

- For directories that require libraries (tipically those with targets/executables), you must link the libraries with `target_link_libraries(<target> [PUBLIC|PRIVATE] [<lib> ...] ...)` **after** the `add_executable(<name> <source>.cpp)`
    - If the libraries are in a subdirectory, create the libraries with `add_library(<name> [STATIC|INTERFACE])`, include the current directory (give acess to all other libraries) in all libraries with `target_include_directories(<lib> [STATIC|INTERFACE] ${CMAKE_CURRENT_LIST_DIR})` and include the subdirectories to be built with `add_subdirectory())` (assuming you have a `CMakeLists.txt` inside the subdirectories).  
    E.g. [`src/CMakeLists.txt`](../src/CMakeLists.txt).
        - For libraries that don't really need a source file, set them as interfaces. E.g. [`src/exceptions/`](../src/exceptions/).
        - Otherwise, set them as static. E.g. [`src/compiler/`](../src/compiler/).
    - If the libraries are already built, you just have to include them and link them.  
    E.g. [`test/CMakeLists.txt`](../test/CMakeLists.txt)

### Third-party libraries
In C++, third party libraries are shit. Not because of the code, but because of the instalation (because C++'s package management is literally non-existant).
There are three main ways to install a library:
- The easiest, brain-deadest way to install a library is to download it as a full header (`.hpp`) file, and just include it.
- You can also install it (build from source or through a Unix package manager, etc.), and use `find_package(...)` to locate it, `add_library(...)`, and `target_link_libraries(...)`.
- Since CMake 3.11, you can use `FetchContent` to download it at config time, just:
  ``` cmake
  include(FetchContent)

  FetchContent_Declare(
    <name>
    URL https://github.com/<user>/<repo>/releases/download/<tag>/<file>.tar.xz
  )
  FetchContent_MakeAvailable(<name>)
  target_link_libraries(...)
  ```
  E.g. [`src/CMakeLists.txt`](../src/CMakeLists.txt).

In order to use a library as a dependency of another library, remember to `target_link_libraries(<library> [PUBLIC|PRIVATE] <dependency>)`.  
E.g. [`src/compiler/CMakeLists.txt`](../src/compiler/CMakeLists.txt).

More info:
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- An alternative is [GRPBuild](https://docs.adacore.com/gprbuild-docs/html/gprbuild_ug/building_with_gprbuild.html) and [GNAT Project Manager](https://docs.adacore.com/gprbuild-docs/html/gprbuild_ug/gnat_project_manager.html)


### Circular dependencies
Just avoid them.
- [Circular Dependencies in C++](https://pvigier.github.io/2018/02/09/dependency-graph.html)