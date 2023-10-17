grammar riscv_asm;


/* PARSER */

// a programm is a block followed by an end-of-file
prog: block EOF;

// the list of accepted statements
statement
    : ADD REGISTER REGISTER REGISTER
    | ADDI REGISTER REGISTER NUMBER
    ;

// a block is a list of statementes where each statement is followed by
// either a newline or the end of file
block
    : (statement (NEWLINE+ | EOF))*
    ;



/* LEXER */

// operators
ADD : 'add' ;
ADDI : 'addi' ;

// comments
COMMENT : '#' ~[\r\n]* ;

// literals
REGISTER        : 't'[0-6] ;  // match identifiers
NUMBER          : [0-9]+ ('.' [0-9]+)?;   // match integers
STRINGLITERAL   : '"' ~ ["\r\n]* '"' ;
NEWLINE         :'\r'? '\n' ;  // return newlines to parser (end-statement signal)
WS              : [ \t]+ -> skip ; // toss out whitespace






// Line ::=
// - Comment
// - Line + comment
// - Segment directive (`.data`, `.text`)
// - Label + type directive + value (`.data`)
// - Label + instruction (`.text`)
// - Instruction (`.text`)