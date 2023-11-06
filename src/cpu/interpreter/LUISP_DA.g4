grammar LUISP_DA;


/* PARSER */

expression
  : ATOMIC_SYMBOL
  | list
  ;

list
  : '(' expression+ ')'
  | block
  ;


block
  : BEG list+
  ;


/* LEXER */


ATOMIC_SYMBOL
  : BEG
  | SYM
  | REG
  | INM
  ;


BEG
  : 'begin'
  ;

SYM
  : '+'
  | 'reg'
  | 'reg!'
  | 'pc'
  | 'pc!'
  ;

REG  // depends on architecture, here we'll use RISC-V
  : 'zero'
  | 'ra'
  | 'sp'
  | 'gp'
  | 'tp'
  | 'fp'
  | 't'[0-6]
  | 'a'[0-7]
  | 's'[0-9]
  | 's1'[0-1]
  | 'x'[0-9]
  | 'x'[1-2][0-9]
  | 'x3'[0-1]
  ;

INM
  : [0-9]+
  ;


WS
  : [ \r\n\t]+ -> skip
  ;