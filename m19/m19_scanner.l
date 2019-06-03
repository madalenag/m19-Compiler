%option c++ prefix="m19_scanner_" outfile="m19_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{ 
// make relevant includes before including the parser's tab file
#include <string>
#include <sstream>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>
#include <cmath>
#include "m19_parser.tab.h"

static std::ostringstream strlit;

// don't change this
#define yyerror LexerError


double engNotation(const char* num) {
    int exp = 0;
    std::string strnum(num);
    int dim = strnum.length();
    
    for (int i = 0; i < dim; i++) {
        if (strnum[i] == 'a') exp = -18;
        else if (strnum[i] == 'f') exp = -15;
        else if (strnum[i] == 'p') exp = -12;
        else if (strnum[i] == 'n') exp = -9;
        else if (strnum[i] == 'u') exp = -6;
        else if (strnum[i] == 'm') exp = -3;
        else if (strnum[i] == 'k') exp = 3;
        else if (strnum[i] == 'M') exp = 6;
        else if (strnum[i] == 'G') exp = 9;
        else if (strnum[i] == 'T') exp = 12;
        else if (strnum[i] == 'P') exp = 15;
        else if (strnum[i] == 'E') exp = 18;
        if(exp != 0) {
            strnum.replace(i, 1, "."); 
            break;
        }
    }
    return stod(strnum, nullptr) * pow(10,exp);
}



%}

INT             [[:digit:]]+

HEX             [0-9a-fA-F]

ENG             [afpnumkMGTPE]

LETTER          [A-Za-z]

ALNUM           [A-Za-z0-9_]

IDENTIFIER      {LETTER}{ALNUM}* 

%x X_STRING X_COMMENT X_STR_IGNORE X_BAR
%%
"//".*$                ;  

"/*"                   yy_push_state(X_COMMENT);
<X_COMMENT>"/*"        yy_push_state(X_COMMENT);
<X_COMMENT>"*/"        yy_pop_state();
<X_COMMENT>.|\n        ;


"&&"                   return tAND;
"||"                   return tOR;
">="                   return tGE; 
"<="                   return tLE; 
"=="                   return tEQ; 
"!="                   return tNE; 

"apply"                return tAPPLY;
".."                   return tINTERVALO;
"->"                   return tSETA;

"!!"                   return tPRINTLN;
">>@"                  return tBREAK;
"@>>"                  return tCONTINUE;
">@<"                  return tRETURN;
">>"                   return tDGT;
"<<"                   return tDLT;


"\""                   yy_push_state(X_STRING);
<X_STRING>\\           yy_push_state(X_BAR);
<X_STRING>"\""         {
                        yylval.s = new std::string(strlit.str());
                        strlit.str(""); yy_pop_state();
                        return tSTRING;
                       }
<X_STRING>.            strlit << *yytext;
<X_STRING>\n           yyerror("newline in string");


<X_BAR>n               strlit << '\n'; yy_pop_state();
<X_BAR>r               strlit << '\r'; yy_pop_state();
<X_BAR>t               strlit << '\t'; yy_pop_state();
<X_BAR>"\""            strlit << '"'; yy_pop_state();
<X_BAR>0               yy_pop_state(); yy_pop_state();yy_push_state(X_STR_IGNORE);
<X_BAR>\\              strlit << '\\'; yy_pop_state();
<X_BAR>{HEX}{1,2}      {strlit << (char)(unsigned char)strtoul(yytext, nullptr, 16);
                        yy_pop_state();
                        }
<X_BAR>.               strlit << *yytext; yy_pop_state();


<X_STR_IGNORE>\"       { yylval.s = new std::string(strlit.str());
                         strlit.str(""); yy_pop_state();
                         return tSTRING;
                       }
<X_STR_IGNORE>.        ;




[0-9][0-9]*            yylval.i = strtoul(yytext, nullptr, 10); return tINTEGER;
"0x"{HEX}+             yylval.i = strtoul(yytext, nullptr, 16); return tINTEGER;
"0x"[g-zG-Z]+          yyerror("Invalid base 16 number");


{INT}[.]{INT}          yylval.d = strtod(yytext, NULL); return tREAL;
{INT}{ENG}{INT}        yylval.d = engNotation(yytext); return tREAL;


{IDENTIFIER}           yylval.s = new std::string(yytext); return tIDENTIFIER;


[-()<>=+*/;:.,]        return *yytext;
[!?@$#%{}\[\]]         return *yytext;


[ \t\n\r]+             ; /* ignore whitespace */


.                      yyerror("Unknown character");

%%
