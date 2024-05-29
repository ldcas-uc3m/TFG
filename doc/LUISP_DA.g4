grammar LUISP_DA;


// TODO: fix this shit


/* PARSER */

expression
  : ATOMIC_SYMBOL
  | list
  | block
  | conditional
  | b_expression
  | op_expression
  | i_expression
  ;

b_expression
  : B_OP expression expression
  ;

op_expression
  : sum
  | get_register
  | set_register
  | get_pc
  | set_pc
  ;

i_expression
  : NUM
  | b_sum
  | '+' NUM NUM
  ;

sum
  : '+' i_expression i_expression
  | b_sum
  ;

b_sum  // base sum
  : '+' NUM NUM
  ;

get_register
  : 'reg' REG
  ;

set_register
  : 'reg!' REG expression
  ;
  
get_pc
  : 'pc'
  ;

set_pc
  : 'pc!' expression
  ;


list
  : '(' expression+ ')'
  ;

block
  : BLK expression+
  ;

conditional
  : CND b_expression b_expression?
  ;


/* LEXER */


B_OP
  : '<'
  | '<='
  | '>'
  | '>='
  | '=='
  | '!='
  ;


ATOMIC_SYMBOL
  : NUM
  | BOOL
  | NIL
  ;


BLK
  : 'do'
  ;

OP
  : '+'
  | 'reg'
  | 'reg!'
  | 'pc'
  | 'pc!'
  ;

NUM
  : [0-9]+
  ;

BOOL
  : 'true'
  | 'false'
  ;

NIL
  : 'nil'
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

CND
  : 'if'
  ;

WS
  : [ \r\n\t]+ -> skip
  ;