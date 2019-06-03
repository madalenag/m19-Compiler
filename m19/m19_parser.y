%{
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                           i;	/* integer value */
  double                        d;
  std::string                   *s;	/* symbol name or string literal */
  cdk::basic_node               *node;	/* node pointer */
  cdk::sequence_node            *sequence;
  cdk::expression_node          *expression; /* expression nodes */
  cdk::lvalue_node              *lvalue;
  
  basic_type                    *type;
  m19::block_node               *code_block;
  m19::section_node             *section;
  m19::initial_section_node     *initial_section;
  m19::final_section_node       *final_section;
  m19::body_node                *body;
};


%token <i> tINTEGER
%token <d> tREAL
%token <s> tIDENTIFIER tSTRING
%token tREAD tBREAK tCONTINUE tPRINTLN tRETURN tDGT tDLT tAPPLY tSETA tINTERVALO

%type <s> string
%type <node> instruction iteration conditional declaration 
%type <node> function variable var_decl var_decls 
%type <sequence> init_iteration opt_instructions inner_decls opt_expressions
%type <sequence> expressions decls instrs file func_args sections opt_expressions
%type <expression> expr func_call literal integer real opt_expr
%type <type> data_type
%type <lvalue> lval
%type <body> body
%type <code_block> code_block
%type <section> section
%type <initial_section> initial_section
%type <final_section> final_section

%nonassoc tIFX

%right '='
%nonassoc ':' '~'
%left tOR
%left tAND
%left tEQ 
%left  '<' '>' tGE tLE tNE
%left '+' '-'
%left '*' '/' '%' 
%nonassoc '?'



%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file: /*empty*/                { compiler->ast($$ = new cdk::sequence_node(LINE)); }
    | decls                    { compiler->ast($$ = $1); }
    ;

decls: declaration                    { $$ = new cdk::sequence_node(LINE, $1); }        
     | decls declaration              { $$ = new cdk::sequence_node(LINE, $2, $1); } 
     ;
     
declaration: var_decls ';'           { $$ = $1; }
           | function                { $$ = $1; }
           ;
           
           
var_decls: variable      { $$ = $1; }
         | var_decl      { $$ = $1; }
         ;
         
         
variable: data_type tIDENTIFIER '?' '=' expr { $$ = new m19::variable_declaration_node(LINE, 2, $1, *$2, $5); delete $2;}
        | data_type tIDENTIFIER '?'          { $$ = new m19::variable_declaration_node(LINE, 2, $1, *$2, nullptr); delete $2;} 
        |data_type tIDENTIFIER '!' '=' expr  { $$ = new m19::variable_declaration_node(LINE, 1, $1, *$2, $5); delete $2;}
        | data_type tIDENTIFIER '!'          { $$ = new m19::variable_declaration_node(LINE, 1, $1, *$2, nullptr); delete $2;}   
        ;

var_decl: data_type tIDENTIFIER '=' expr { $$ = new m19::variable_declaration_node(LINE, 0, $1, *$2, $4); delete $2;}
        | data_type tIDENTIFIER          { $$ = new m19::variable_declaration_node(LINE, 0, $1, *$2, nullptr); delete $2;}           
        ;

        
data_type: '#'                  { $$ = new basic_type(4, basic_type::TYPE_INT); }
         | '%'                  { $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
         | '$'                  { $$ = new basic_type(4, basic_type::TYPE_STRING); }
         | '<' data_type '>'    { $$ = new basic_type(4, basic_type::TYPE_POINTER);  $$->_subtype=$2;}
        /* | tDLT data_type tDGT  { $$ = new basic_type(4, basic_type::TYPE_POINTER);  $$->_subtype=new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype->_subtype = $2;}*/
         ;

function: data_type tIDENTIFIER '?' '(' func_args ')' { $$ = new m19::function_declaration_node(LINE, $1, *$2, 2, $5); delete $2;}
        | '!' tIDENTIFIER '?' '(' func_args ')'        { $$ = new m19::function_declaration_node(LINE, *$2, 2, $5); delete $2;}
        |  data_type tIDENTIFIER '!' '(' func_args ')' { $$ = new m19::function_declaration_node(LINE, $1, *$2, 1, $5); delete $2;}
        | '!' tIDENTIFIER '!' '(' func_args ')'        { $$ = new m19::function_declaration_node(LINE, *$2, 1, $5); delete $2;}
        |  data_type tIDENTIFIER '(' func_args ')'     { $$ = new m19::function_declaration_node(LINE, $1, *$2, 0, $4); delete $2;}
        | '!' tIDENTIFIER  '(' func_args ')'           { $$ = new m19::function_declaration_node(LINE, *$2, 0, $4); delete $2;}
       
        |'!' tIDENTIFIER '!' '(' func_args ')' body                 { $$ = new m19::function_definition_node(LINE,*$2, 1, $5, $7); delete $2;}
        | data_type tIDENTIFIER '!' '(' func_args ')' '=' literal body { $$ = new m19::function_definition_node(LINE,$1, *$2, 1, $8, $5, $9); delete $2;}
        | data_type tIDENTIFIER '!''(' func_args ')' body              { $$ = new m19::function_definition_node(LINE,$1, *$2, 1, nullptr, $5, $7); delete $2;}
        | '!' tIDENTIFIER '(' func_args ')' body                       { $$ = new m19::function_definition_node(LINE,*$2, 0,$4, $6); delete $2;}
        | data_type tIDENTIFIER '(' func_args ')' '=' literal body     { $$ = new m19::function_definition_node(LINE,$1, *$2, 0, $7, $4, $8); delete $2;}
        | data_type tIDENTIFIER  '(' func_args ')' body                { $$ = new m19::function_definition_node(LINE,$1, *$2, 0, nullptr, $4, $6); delete $2;}
        ;
        
func_args: var_decl                     { $$ = new cdk::sequence_node(LINE, $1); }
        | func_args ',' var_decl        { $$ = new cdk::sequence_node(LINE, $3, $1); } 
        |                               { $$ = nullptr; }
        ;

func_call: tIDENTIFIER '(' opt_expressions ')' { $$ = new m19::function_call_node(LINE, *$1, $3); delete $1; }
        | '@' '('opt_expressions ')' { $$ = new m19::function_call_node(LINE, "@", $3); }
        ;

opt_expressions: /* empty */          { $$ = nullptr; }
                | expressions               { $$ = $1; }
                ;
        
literal : integer { $$ = $1;}
        | string { $$ = new cdk::string_node(LINE, $1);}
        | real { $$ = $1;}
        ;

integer: tINTEGER       { $$ = new cdk::integer_node(LINE, $1); }
       ;

real   : tREAL          { $$ = new cdk::double_node(LINE, $1); }
       ; 
       

string : tSTRING        { $$ = $1 ;} 
       | string tSTRING { $$ = new std::string(*$1 + *$2); delete $1; delete $2; }
       ;


   
body: initial_section sections final_section { $$ = new m19::body_node(LINE, $1, $2, $3); }
    | sections final_section                 { $$ = new m19::body_node(LINE, nullptr, $1, $2); }
    | initial_section sections               { $$ = new m19::body_node(LINE, $1, $2, nullptr); }
    | initial_section final_section          { $$ = new m19::body_node(LINE, $1, nullptr, $2); }
    | sections                               { $$ = new m19::body_node(LINE, nullptr, $1, nullptr); }
    | initial_section                        { $$ = new m19::body_node(LINE, $1, nullptr, nullptr); }
    | final_section                          { $$ = new m19::body_node(LINE, nullptr, nullptr, $1); }
    ; 

initial_section: tDLT code_block            { $$ = new m19::initial_section_node(LINE, $2); }
               ;
              
sections: section                           { $$ = new cdk::sequence_node(LINE, $1); }
        | sections section                  { $$ = new cdk::sequence_node(LINE,$2, $1); }
        ;
        
section: '(' opt_expr ')' code_block            { $$ = new m19::section_node(LINE, $2, $4, 1); }
       | '[' opt_expr ']' code_block            { $$ = new m19::section_node(LINE, $2, $4, 2);}
       | code_block                         { $$ = new m19::section_node(LINE, nullptr, $1, 0); }
       ;
 
 
opt_expr: /*emtpy */  { $$ = nullptr; }
         | expr     { $$ = $1; }
         ;



final_section: tDGT code_block              { $$ = new m19::final_section_node(LINE, $2); }
             ;
             

code_block: '{' opt_instructions'}'                     { $$ = new m19::block_node(LINE, nullptr, $2); }
          | '{' inner_decls opt_instructions '}'        { $$ = new m19::block_node(LINE, $2, $3); }
          ;
          
inner_decls: var_decls ';'             { $$ = new cdk::sequence_node(LINE, $1); }
           | inner_decls var_decls ';' { $$ = new cdk::sequence_node(LINE, $2,$1); }
           ;

           
opt_instructions: /* empty */         { $$ = nullptr; }
                | instrs              { $$ = $1; }
                ;
                
                
instruction: expr ';'                  { $$ = new m19::evaluation_node(LINE, $1); }
           | expr '!'                  { $$ = new m19::print_node(LINE, $1, false); }
           | expr tPRINTLN             { $$ = new m19::print_node(LINE, $1, true); }
           | tCONTINUE                 { $$ = new m19::continue_node(LINE); }
           | tBREAK                    { $$ = new m19::break_node(LINE); }
           | tRETURN                   { $$ = new m19::return_node(LINE); }
           | conditional               { $$ = $1; } 
           | iteration                 { $$ = $1; }
           | code_block                { $$ = $1; }
           | tAPPLY tIDENTIFIER tSETA lval ':' expr tINTERVALO expr ';'{ $$ = new m19::apply_node(LINE, *$2, $4, $6, $8); delete $2; }
           ;   
           

instrs: instruction                    { $$ = new cdk::sequence_node(LINE, $1); }        
      | instrs instruction             { $$ = new cdk::sequence_node(LINE, $2, $1); } 
      ;
      

conditional : '[' expr ']' '#' instruction      { $$ = new m19::if_node(LINE, $2, $5); }
            | '[' expr ']' '?' instruction %prec tIFX     { $$ = new m19::if_node(LINE, $2, $5); }
            | '[' expr ']' '?' instruction ':' instruction { $$ = new m19::if_else_node(LINE, $2, $5, $7); }
            ;



init_iteration  : var_decl   { $$ = new cdk::sequence_node(LINE, $1); }
                | expr  { $$ = new cdk::sequence_node(LINE, $1); }
                | init_iteration ',' var_decl { $$ = new cdk::sequence_node(LINE, $3, $1); } 
                | init_iteration ',' expr { $$ = new cdk::sequence_node(LINE, $3, $1); } 
                |    { $$ = nullptr; }
                ;
 
 
iteration : '[' init_iteration ';' expressions ';' expressions ']' instruction   { $$ = new m19::for_node(LINE, $2, $4,  $6, $8); }
          | '[' init_iteration ';' ';' expressions ']' instruction               { $$ = new m19::for_node(LINE, $2, nullptr,  $5, $7); }
          | '[' init_iteration ';' expressions ';' ']' instruction               { $$ = new m19::for_node(LINE, $2, $4, nullptr, $7); }
          | '[' init_iteration ';' ';' ']' instruction                           { $$ = new m19::for_node(LINE, $2, nullptr,  nullptr, $6); }
          ;

expressions: expr                    { $$ = new cdk::sequence_node(LINE, $1); }        
           | expressions ',' expr    { $$ = new cdk::sequence_node(LINE, $3, $1); } 
           ;      
        
expr : literal                   { $$ = $1; }
     | '-' expr                  { $$ = new cdk::neg_node(LINE, $2); }
     | '+' expr                  { $$ = new m19::identity_node(LINE, $2); }
     | expr '+' expr	         { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	         { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '/' expr             { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '*' expr	         { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '%' expr	         { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	         { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	         { $$ = new cdk::gt_node(LINE, $1, $3); }
     | '~' expr                  { $$ = new cdk::neg_node(LINE, $2); }
     | expr tGE expr	         { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr             { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr	         { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr	         { $$ = new cdk::eq_node(LINE, $1, $3); }
     | expr tOR expr	         { $$ = new cdk::or_node(LINE, $1, $3); }
     | expr tAND expr            { $$ = new cdk::and_node(LINE, $1, $3); }
     | lval                      { $$ = new cdk::rvalue_node(LINE, $1); } 
     | lval '=' expr             { $$ = new cdk::assignment_node(LINE, $1, $3); }
     | '@' '=' expr              { $$ = new cdk::assignment_node(LINE, new cdk::variable_node(LINE, "@"), $3);  }
     | '[' expr ']'              { $$ = new m19::memory_alloc_node(LINE, $2); }
     | lval '?'                  { $$ = new m19::address_of_node(LINE, $1); }  
     | '@' '?'                  { $$ = new m19::address_of_node(LINE, nullptr); } 
     | '(' expr ')'              { $$ = $2; }
     | '@'                       { $$ = new m19::read_node(LINE); }  
     | func_call                 { $$ = $1; }
     ;

lval : tIDENTIFIER       { $$ = new cdk::variable_node(LINE, *$1); delete $1;}
     | lval '[' expr ']' { $$ = new m19::indexing_node(LINE,  new cdk::rvalue_node(LINE, $1), $3);}
     | '@' '[' expr ']' { $$ = new m19::indexing_node(LINE, nullptr , $3);}
     | '(' expr ')''[' expr ']' { $$ = new m19::indexing_node(LINE, $2, $5);}
     | func_call '[' expr ']'  { $$ = new m19::indexing_node(LINE, $1, $3);}
     ;



%%
