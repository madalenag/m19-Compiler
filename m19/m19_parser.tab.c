/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20170430

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "m19_parser.y"
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 13 "m19_parser.y"
typedef union {
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
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 65 "m19_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 57 "m19_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tINTEGER 257
#define tREAL 258
#define tIDENTIFIER 259
#define tSTRING 260
#define tREAD 261
#define tBREAK 262
#define tCONTINUE 263
#define tPRINTLN 264
#define tRETURN 265
#define tDGT 266
#define tDLT 267
#define tAPPLY 268
#define tSETA 269
#define tINTERVALO 270
#define tIFX 271
#define tOR 272
#define tAND 273
#define tEQ 274
#define tGE 275
#define tLE 276
#define tNE 277
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   15,   15,    5,    5,    9,    9,    7,    7,
    7,    7,    8,    8,   25,   25,   25,   25,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
   17,   17,   17,   20,   20,   13,   13,   21,   21,   21,
   22,   23,    1,    1,   27,   27,   27,   27,   27,   27,
   27,   30,   18,   18,   29,   29,   29,   24,   24,   31,
   28,   28,   12,   12,   11,   11,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,   16,   16,    4,    4,
    4,   10,   10,   10,   10,   10,    3,    3,    3,    3,
   14,   14,   19,   19,   19,   19,   19,   19,   19,   19,
   19,   19,   19,   19,   19,   19,   19,   19,   19,   19,
   19,   19,   19,   19,   19,   19,   19,   19,   26,   26,
   26,   26,   26,
};
static const YYINT yylen[] = {                            2,
    0,    1,    1,    2,    2,    1,    1,    1,    5,    3,
    5,    3,    4,    2,    1,    1,    1,    3,    6,    6,
    6,    6,    5,    5,    7,    9,    7,    6,    8,    6,
    1,    3,    0,    4,    4,    0,    1,    1,    1,    1,
    1,    1,    1,    2,    3,    2,    2,    2,    1,    1,
    1,    2,    1,    2,    4,    4,    1,    0,    1,    2,
    3,    4,    2,    3,    0,    1,    2,    2,    2,    1,
    1,    1,    1,    1,    1,    9,    1,    2,    5,    5,
    7,    1,    1,    3,    3,    0,    8,    7,    7,    6,
    1,    3,    1,    2,    2,    3,    3,    3,    3,    3,
    3,    3,    2,    3,    3,    3,    3,    3,    3,    1,
    3,    3,    3,    2,    2,    3,    1,    1,    1,    4,
    4,    6,    4,
};
static const YYINT yydefred[] = {                         0,
    0,   16,    0,   15,   17,    0,    3,    6,    7,    8,
    0,    0,    0,    0,    0,    5,    4,    0,   18,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   31,    0,
    0,   41,   42,    0,   43,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   93,   38,   40,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  115,    0,    0,    0,   44,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  114,    0,    0,    0,    0,    0,
    0,   20,    0,    0,    0,    0,    0,    0,    0,   28,
   57,   53,    0,   51,   32,    0,    0,    0,    0,    0,
    0,    0,  113,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   99,   98,  100,    0,    0,    0,   19,
    0,    0,   30,   25,   60,   52,    0,    0,    0,   71,
   70,   72,    0,    0,   77,   74,   73,    0,    0,    0,
    0,    0,    0,   75,   54,   46,    0,   48,   34,    0,
    0,   35,  121,  123,  120,    0,   27,    0,    0,    0,
    0,   82,    0,    0,   63,   61,    0,    0,   78,   69,
   67,   68,    0,   45,    0,    0,    0,   29,   55,   56,
    0,    0,    0,    0,   64,   62,    0,    0,  122,   26,
    0,    0,    0,    0,    0,    0,   84,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   79,    0,    0,   90,
    0,    0,    0,    0,    0,   88,   89,    0,   81,    0,
   87,   76,
};
static const YYINT yydgoto[] = {                          6,
   42,  145,  146,  147,    7,    8,    9,   29,   11,  173,
  149,  150,  106,  107,   12,  151,   30,   99,  152,   44,
   45,   46,   47,  138,   31,   48,  100,  154,  102,  103,
  104,
};
static const YYINT yysindex[] = {                       125,
  303,    0, -257,    0,    0,    0,    0,    0,    0,    0,
  -18,  125, -216,    2,   75,    0,    0,   67,    0,   49,
   62,  303, 1034,  -21,   65,  303,  303,  303,    0,  150,
 -214,    0,    0,   71,    0, 1034, 1034, 1034, 1034,   15,
 1034, -142,  694,   29,    0,    0,    0,   91, 1034,  303,
 1034,  303,  271,  277,  305,  139,  303,   68, 1034,  694,
  241,  241,  437, 1034,    0, 1034, 1034,  490,    0, 1034,
 1034, 1034, 1034, 1034, 1034, 1034, 1034, 1034, 1034, 1034,
 1034, 1034, 1034, 1034,    0, 1034,  694,  307,  694,  320,
  137,    0,  139,    8,    8, 1034, 1034,  791,  -19,    0,
    0,    0,  -19,    0,    0,  129,  134,  694,   90,  694,
  148,  518,    0,  708,  736,  763,  403,  403,  403,  403,
  403,  241,  241,    0,    0,    0,  545,  694,  567,    0,
  147,  -31,    0,    0,    0,    0,  694,  160,  122,    0,
    0,    0,  -37,  956,    0,    0,    0,  146,   98,  791,
  849,  300,   12,    0,    0,    0,  -19,    0,    0, 1034,
 1034,    0,    0,    0,    0,  -31,    0,  139,    8,    8,
  -24,    0,   -2,  597,    0,    0,  190,  151,    0,    0,
    0,    0,  111,    0,  694,  634,  139,    0,    0,    0,
  -39,  964,  956,  -17,    0,    0,  221,  243,    0,    0,
 1034,  -25,   29,  -10,  934,  131,    0,  694,  849,  849,
  656, 1034,  849,  -14, 1022,  239,    0,   90,  678,    0,
  849,  849,  -13,  849, 1034,    0,    0,  849,    0,  687,
    0,    0,
};
static const YYINT yyrindex[] = {                       317,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  319,    0,    0,    0,    0,    0,  269,    0,    0,
    0,  326,    0,  276,  312,  326,  326,  326,    0,    0,
    0,    0,    0,   -9,    0,    0,    0,    0,    0,   26,
    0,  -33,  112,   50,    0,    0,    0,   80,    0,  326,
    0,  326,    0,    0,    0,   99,    0,  166,  289,  629,
  124,  159,    0,    0,    0,  289,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  313,    0,  314,    0,
  176,    0,  459,    0,    0,  295,  282,  258,  493,    0,
    0,    0,  631,    0,    0,    0,  345,    3,  104,  744,
    0,    0,    0,  510,  155,  236,  191,  272,  325,  349,
  410,  213,  248,    0,    0,    0,    0,  771,    0,    0,
  824,    0,    0,    0,    0,    0,  -28,    0,    0,    0,
    0,    0,    0,  136,    0,    0,    0,    0,    0,  258,
  264,    0,    0,    0,    0,    0,  865,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  215,    0,    0,    0,    0,    0,    0,
    0,    0,  269,    0,   57,    0,    0,    0,    0,    0,
    0,    0,    0,  379,    0,    0,  276,  312,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  235,    0,    0,
    0,    0,    0,    0,    0,  813,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,  875,    0,    0,  380,    0,    0,  608,  -75,    0,
  245,    0,  336,    1,    0,    0,  259,  288, 1103,  216,
 -110,    0,    0,  318,    5,  219,  -54, 1142,  -96,    0,
  -83,
};
#define YYTABLESIZE 1329
static const YYINT yytable[] = {                         39,
  201,   15,  155,   39,   13,   14,   39,   39,   39,   39,
   39,   39,   59,   39,   66,  156,   13,  210,   50,  158,
   96,  168,  148,  119,  202,   39,   39,  119,   39,  160,
  160,  119,  119,  119,  119,  119,  133,  119,  134,   49,
   16,  193,   18,   91,   58,  209,   91,  212,  119,  119,
  119,  119,  119,  119,   66,  187,  192,   39,  117,   39,
  155,   91,  117,   19,   59,   67,  117,  117,  117,  117,
  117,   97,  117,  184,  177,   64,  167,   65,  221,  228,
   86,  119,  118,  119,  117,  117,  118,  117,   27,   39,
  118,  118,  118,  118,  118,   91,  118,   92,   24,   25,
   92,   28,  153,   98,   52,   67,   26,   21,  118,  118,
   59,  118,  110,  188,   22,   92,  110,   69,  117,   83,
  110,  110,  110,  110,  110,   51,  110,   23,   23,   24,
   98,   24,  200,   24,   24,   24,  116,   20,  110,  110,
  116,  110,  118,  198,  116,  116,  116,  116,  116,   92,
  116,   84,   13,   85,  153,   13,   95,    3,   24,    4,
    5,    2,  116,  116,   95,  116,   95,   95,   95,  159,
   13,   23,  110,  197,  160,   23,   96,  160,   96,   86,
  161,   86,   95,   95,    1,   95,   96,  109,  162,  215,
   56,   94,  206,   57,   86,  109,  116,  132,  109,   94,
  169,   94,   94,   94,  175,  214,   14,  166,   23,   14,
   23,   23,   23,  109,  170,  223,   95,   94,   94,   34,
   94,  171,  176,  101,   14,   32,   33,   97,   35,   97,
   39,  101,   39,   39,  101,   23,   39,   97,   39,   39,
   39,   39,   39,   39,  191,   96,   94,  109,  195,  101,
  101,   94,  101,   96,  119,   96,   96,   96,   83,   98,
  119,   98,  119,  119,  119,  119,  119,  119,  107,   98,
  183,   96,   96,   83,   96,  196,  107,   82,   85,  107,
   97,   49,   80,  101,   53,   54,   55,   81,   97,  117,
   97,   97,   97,   85,  107,  117,  224,  117,  117,  117,
  117,  117,  117,   51,  102,   96,   97,   97,   88,   97,
   90,   91,  102,  118,   57,  102,    1,   92,    2,  118,
   57,  118,  118,  118,  118,  118,  118,   14,  107,   36,
  102,  102,  182,  102,   10,   58,   82,    4,    5,    2,
   97,   80,   78,  110,   79,   93,   81,  130,   57,  110,
   57,  110,  110,  110,  110,  110,  110,  104,  181,   73,
  131,   74,    1,   57,  102,  104,   33,  116,  104,   33,
   12,    9,   11,  116,   58,  116,  116,  116,  116,  116,
  116,  105,   65,  104,  104,   37,  104,   95,   66,  105,
  157,   17,  105,   95,  178,   95,   95,   95,   95,   95,
   95,  111,   94,   95,   94,   95,  203,  105,  105,  204,
  105,  113,   94,   95,  139,  113,    0,  104,  109,    0,
  113,  113,   94,  113,  109,  113,  109,  109,   94,    0,
   94,   94,   94,   94,   94,   94,    0,  113,  113,   82,
  113,  105,  106,    0,   80,   78,    0,   79,    0,   81,
  106,    0,    0,  106,  101,    0,    0,    0,   22,    0,
  101,    0,  101,  101,  101,  101,  101,  101,  106,  106,
    0,  106,    0,   82,    0,    0,   96,  109,   80,   78,
    0,   79,   96,   81,   96,   96,   96,   96,   96,   96,
    0,   22,   49,   22,   22,   22,   73,    0,   74,  107,
    0,    0,  106,    0,    0,  107,    0,  107,  107,  107,
    0,   97,    0,    0,    0,    0,    0,   97,   22,   97,
   97,   97,   97,   97,   97,   49,   82,   49,   49,   49,
    0,   80,   78,    0,   79,  102,   81,    0,    0,    0,
    0,  102,  108,  102,  102,  102,  102,  102,  102,   73,
  108,   74,   49,  108,   82,    0,    0,    0,    0,   80,
   78,    0,   79,  180,   81,    0,    0,    0,  108,    0,
    0,   70,   71,   72,   75,   76,   77,   73,    0,   74,
    0,   82,  113,    0,    0,    0,   80,   78,  104,   79,
    0,   81,    0,    0,  104,    0,  104,  104,  104,  104,
  104,  104,  108,   82,   73,    0,   74,   10,   80,   78,
  163,   79,  105,   81,    0,    0,    0,    0,  105,   10,
  105,  105,  105,  105,  105,  105,   73,    0,   74,    0,
   50,    0,    0,   82,    0,    0,    0,  164,   80,   78,
    0,   79,  113,   81,    0,    0,    0,    0,    0,    0,
  113,  113,  113,  113,  113,  113,   73,    0,   74,  165,
    0,  103,    0,   50,  105,   50,   50,   50,    0,  103,
   82,    0,  103,  106,    0,   80,   78,    0,   79,  106,
   81,  106,  106,  106,  106,  106,  106,  103,    0,  194,
   50,    0,   82,   73,    0,   74,  218,   80,   78,    0,
   79,    0,   81,    0,    0,   10,    0,    0,   70,   71,
   72,   75,   76,   77,   82,   73,    0,   74,    0,   80,
   78,  103,   79,   82,   81,    0,  199,    0,   80,   78,
   82,   79,    0,   81,    0,   80,   78,   73,   79,   74,
   81,    0,    0,    0,   82,  232,   73,    0,   74,   80,
   78,  172,   79,   73,   81,   74,    0,   10,    0,    0,
    0,   70,   71,   72,   75,   76,   77,   73,    0,   74,
    0,    0,   82,  108,    0,    0,  112,   80,   78,  108,
   79,  108,   81,    0,  112,    0,    0,  112,    0,   70,
   71,   72,   75,   76,   77,   73,    0,   74,    0,   82,
  207,    0,  112,  111,   80,   78,    0,   79,    0,   81,
    0,  111,    0,    0,  111,    0,   70,   71,   72,   75,
   76,   77,   73,   21,   74,    4,    5,    2,    0,  111,
   39,    0,    0,   37,    0,   38,  112,    0,   70,   71,
   72,   75,   76,   77,    0,    0,    0,    0,    0,    0,
    1,    0,   80,    0,   40,   80,   21,   80,   21,   21,
   21,    0,    0,  111,   47,    0,    0,    0,   70,   71,
   72,   75,   76,   77,    0,    0,   80,    0,    0,    0,
    0,  144,    0,   21,    0,    0,    0,    0,   39,    0,
    0,   37,  103,   38,    0,    0,    0,   47,  103,   47,
   47,   47,    0,   80,    0,   70,   71,   72,   75,   76,
   77,    0,   40,   98,    0,    0,   36,    0,    0,    0,
    0,    0,    0,    0,   47,    0,    0,   70,   71,   72,
   75,   76,   77,    0,    0,   80,    0,   80,   80,  144,
    0,    0,    0,    0,    0,    0,    0,  225,    0,   70,
   71,   72,   75,   76,   77,    0,    0,    0,   70,   71,
   72,   75,   76,   77,    0,   70,   71,   72,   75,   76,
   77,   98,    0,   39,   36,    0,   37,    0,   38,    0,
   71,   72,   75,   76,   77,    0,    0,    0,    0,    0,
    4,    5,    2,    0,    0,   39,    0,   40,   37,    0,
   38,    0,    0,   39,    0,    0,   37,  112,   38,   72,
   75,   76,   77,  112,    0,    1,    0,    0,    0,   40,
    0,    0,  205,    0,   41,  179,  213,   40,    0,    0,
    0,    0,    0,    0,  111,    0,    0,   75,   76,   77,
  111,    0,    0,    0,    0,    0,   41,   32,   33,   34,
   35,    0,  140,  141,   41,  142,    0,    0,  143,   36,
    0,   39,    0,    0,   37,    0,   38,    0,    0,   80,
   80,   80,   80,   39,   80,   80,   37,   80,   38,    0,
   80,   36,    0,  216,  217,   40,    0,  220,    0,   36,
    0,    0,    0,    0,    0,  226,  227,   40,  229,    0,
    0,    0,  231,    0,    0,   32,   33,   34,   35,    0,
  140,  141,   41,  142,  222,    0,  143,    0,    0,    0,
    0,    0,    0,    0,   41,   43,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   60,   61,
   62,   63,    0,   68,    0,    0,    0,   36,    0,    0,
    0,   87,    0,   89,    0,    0,    0,    0,    0,   36,
    0,  108,    0,    0,    0,    0,  110,    0,  108,  112,
    0,    0,  114,  115,  116,  117,  118,  119,  120,  121,
  122,  123,  124,  125,  126,  127,  128,    0,  129,    0,
   32,   33,   34,   35,    0,    0,    0,  101,  137,  137,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   32,   33,   34,   35,    0,    0,    0,    0,
   32,   33,   34,   35,    0,    0,    0,    0,    0,    0,
    0,    0,  101,    0,  101,  135,  136,    0,    0,    0,
  101,    0,    0,    0,  101,    0,  174,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  185,  186,    0,    0,    0,    0,    0,    0,
    0,    0,  101,    0,    0,    0,    0,    0,   32,   33,
   34,   35,    0,    0,    0,    0,    0,    0,    0,    0,
   32,   33,   34,   35,  108,  208,    0,    0,  101,    0,
    0,    0,    0,  211,    0,    0,    0,  108,    0,  101,
  189,  190,    0,    0,  219,    0,    0,  108,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  230,  101,
};
static const YYINT yycheck[] = {                         33,
   40,  259,   99,   37,    0,    1,   40,   41,   42,   43,
   44,   45,   41,   47,   40,   99,   12,   35,   40,  103,
   40,  132,   98,   33,   64,   59,   60,   37,   62,   44,
   44,   41,   42,   43,   44,   45,   91,   47,   93,   61,
   59,   44,  259,   41,  259,   63,   44,   58,   58,   59,
   60,   61,   62,   63,   40,  166,   59,   91,   33,   93,
  157,   59,   37,   62,   93,   91,   41,   42,   43,   44,
   45,   91,   47,  157,  150,   61,  131,   63,   93,   93,
   91,   91,   33,   93,   59,   60,   37,   62,   40,  123,
   41,   42,   43,   44,   45,   93,   47,   41,    0,   33,
   44,   40,   98,  123,   40,   91,   40,   33,   59,   60,
   40,   62,   33,  168,   40,   59,   37,  260,   93,   91,
   41,   42,   43,   44,   45,   61,   47,   61,   61,   63,
  123,   33,  187,   35,   36,   37,   33,   63,   59,   60,
   37,   62,   93,   33,   41,   42,   43,   44,   45,   93,
   47,   61,   41,   63,  150,   44,   33,   33,   60,   35,
   36,   37,   59,   60,   41,   62,   43,   44,   45,   41,
   59,   61,   93,   63,   44,    0,   40,   44,   40,   44,
   91,   91,   59,   60,   60,   62,   40,   33,   41,   59,
   41,   33,  192,   44,   59,   41,   93,   61,   44,   41,
   41,   43,   44,   45,   59,  205,   41,   61,   33,   44,
   35,   36,   37,   59,   93,  215,   93,   59,   60,  259,
   62,  259,  125,   33,   59,  257,  258,   91,  260,   91,
  264,   41,  266,  267,   44,   60,  270,   91,  272,  273,
  274,  275,  276,  277,  269,   33,  266,   93,   59,   59,
   60,   93,   62,   41,  264,   43,   44,   45,   44,  123,
  270,  123,  272,  273,  274,  275,  276,  277,   33,  123,
  259,   59,   60,   59,   62,  125,   41,   37,   44,   44,
   33,   61,   42,   93,   26,   27,   28,   47,   41,  264,
   43,   44,   45,   59,   59,  270,   58,  272,  273,  274,
  275,  276,  277,   61,   33,   93,   59,   60,   50,   62,
   52,   41,   41,  264,   44,   44,    0,   41,    0,  270,
   44,  272,  273,  274,  275,  276,  277,   59,   93,   41,
   59,   60,   33,   62,   59,   41,   37,   35,   36,   37,
   93,   42,   43,  264,   45,   41,   47,   41,   44,  270,
   44,  272,  273,  274,  275,  276,  277,   33,   59,   60,
   41,   62,   60,   44,   93,   41,   41,  264,   44,   44,
   59,   59,   59,  270,   93,  272,  273,  274,  275,  276,
  277,   33,  125,   59,   60,   41,   62,  264,  125,   41,
  103,   12,   44,  270,  150,  272,  273,  274,  275,  276,
  277,   66,  266,  267,  266,  267,  191,   59,   60,  191,
   62,   33,  266,  267,   97,   37,   -1,   93,  264,   -1,
   42,   43,  264,   45,  270,   47,  272,  273,  270,   -1,
  272,  273,  274,  275,  276,  277,   -1,   59,   60,   37,
   62,   93,   33,   -1,   42,   43,   -1,   45,   -1,   47,
   41,   -1,   -1,   44,  264,   -1,   -1,   -1,    0,   -1,
  270,   -1,  272,  273,  274,  275,  276,  277,   59,   60,
   -1,   62,   -1,   37,   -1,   -1,  264,   41,   42,   43,
   -1,   45,  270,   47,  272,  273,  274,  275,  276,  277,
   -1,   33,    0,   35,   36,   37,   60,   -1,   62,  264,
   -1,   -1,   93,   -1,   -1,  270,   -1,  272,  273,  274,
   -1,  264,   -1,   -1,   -1,   -1,   -1,  270,   60,  272,
  273,  274,  275,  276,  277,   33,   37,   35,   36,   37,
   -1,   42,   43,   -1,   45,  264,   47,   -1,   -1,   -1,
   -1,  270,   33,  272,  273,  274,  275,  276,  277,   60,
   41,   62,   60,   44,   37,   -1,   -1,   -1,   -1,   42,
   43,   -1,   45,  264,   47,   -1,   -1,   -1,   59,   -1,
   -1,  272,  273,  274,  275,  276,  277,   60,   -1,   62,
   -1,   37,   93,   -1,   -1,   -1,   42,   43,  264,   45,
   -1,   47,   -1,   -1,  270,   -1,  272,  273,  274,  275,
  276,  277,   93,   37,   60,   -1,   62,    0,   42,   43,
   93,   45,  264,   47,   -1,   -1,   -1,   -1,  270,   12,
  272,  273,  274,  275,  276,  277,   60,   -1,   62,   -1,
    0,   -1,   -1,   37,   -1,   -1,   -1,   93,   42,   43,
   -1,   45,  264,   47,   -1,   -1,   -1,   -1,   -1,   -1,
  272,  273,  274,  275,  276,  277,   60,   -1,   62,   93,
   -1,   33,   -1,   33,   57,   35,   36,   37,   -1,   41,
   37,   -1,   44,  264,   -1,   42,   43,   -1,   45,  270,
   47,  272,  273,  274,  275,  276,  277,   59,   -1,   93,
   60,   -1,   37,   60,   -1,   62,   41,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   98,   -1,   -1,  272,  273,
  274,  275,  276,  277,   37,   60,   -1,   62,   -1,   42,
   43,   93,   45,   37,   47,   -1,   93,   -1,   42,   43,
   37,   45,   -1,   47,   -1,   42,   43,   60,   45,   62,
   47,   -1,   -1,   -1,   37,   59,   60,   -1,   62,   42,
   43,  144,   45,   60,   47,   62,   -1,  150,   -1,   -1,
   -1,  272,  273,  274,  275,  276,  277,   60,   -1,   62,
   -1,   -1,   37,  264,   -1,   -1,   33,   42,   43,  270,
   45,  272,   47,   -1,   41,   -1,   -1,   44,   -1,  272,
  273,  274,  275,  276,  277,   60,   -1,   62,   -1,   37,
  193,   -1,   59,   33,   42,   43,   -1,   45,   -1,   47,
   -1,   41,   -1,   -1,   44,   -1,  272,  273,  274,  275,
  276,  277,   60,    0,   62,   35,   36,   37,   -1,   59,
   40,   -1,   -1,   43,   -1,   45,   93,   -1,  272,  273,
  274,  275,  276,  277,   -1,   -1,   -1,   -1,   -1,   -1,
   60,   -1,   40,   -1,   64,   43,   33,   45,   35,   36,
   37,   -1,   -1,   93,    0,   -1,   -1,   -1,  272,  273,
  274,  275,  276,  277,   -1,   -1,   64,   -1,   -1,   -1,
   -1,   91,   -1,   60,   -1,   -1,   -1,   -1,   40,   -1,
   -1,   43,  264,   45,   -1,   -1,   -1,   33,  270,   35,
   36,   37,   -1,   91,   -1,  272,  273,  274,  275,  276,
  277,   -1,   64,  123,   -1,   -1,  126,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   60,   -1,   -1,  272,  273,  274,
  275,  276,  277,   -1,   -1,  123,   -1,  125,  126,   91,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  270,   -1,  272,
  273,  274,  275,  276,  277,   -1,   -1,   -1,  272,  273,
  274,  275,  276,  277,   -1,  272,  273,  274,  275,  276,
  277,  123,   -1,   40,  126,   -1,   43,   -1,   45,   -1,
  273,  274,  275,  276,  277,   -1,   -1,   -1,   -1,   -1,
   35,   36,   37,   -1,   -1,   40,   -1,   64,   43,   -1,
   45,   -1,   -1,   40,   -1,   -1,   43,  264,   45,  274,
  275,  276,  277,  270,   -1,   60,   -1,   -1,   -1,   64,
   -1,   -1,   59,   -1,   91,  151,   93,   64,   -1,   -1,
   -1,   -1,   -1,   -1,  264,   -1,   -1,  275,  276,  277,
  270,   -1,   -1,   -1,   -1,   -1,   91,  257,  258,  259,
  260,   -1,  262,  263,   91,  265,   -1,   -1,  268,  126,
   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,  257,
  258,  259,  260,   40,  262,  263,   43,  265,   45,   -1,
  268,  126,   -1,  209,  210,   64,   -1,  213,   -1,  126,
   -1,   -1,   -1,   -1,   -1,  221,  222,   64,  224,   -1,
   -1,   -1,  228,   -1,   -1,  257,  258,  259,  260,   -1,
  262,  263,   91,  265,   93,   -1,  268,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   91,   23,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   36,   37,
   38,   39,   -1,   41,   -1,   -1,   -1,  126,   -1,   -1,
   -1,   49,   -1,   51,   -1,   -1,   -1,   -1,   -1,  126,
   -1,   59,   -1,   -1,   -1,   -1,   64,   -1,   66,   67,
   -1,   -1,   70,   71,   72,   73,   74,   75,   76,   77,
   78,   79,   80,   81,   82,   83,   84,   -1,   86,   -1,
  257,  258,  259,  260,   -1,   -1,   -1,   56,   96,   97,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  257,  258,  259,  260,   -1,   -1,   -1,   -1,
  257,  258,  259,  260,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   91,   -1,   93,   94,   95,   -1,   -1,   -1,
   99,   -1,   -1,   -1,  103,   -1,  144,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  160,  161,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  131,   -1,   -1,   -1,   -1,   -1,  257,  258,
  259,  260,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  257,  258,  259,  260,  192,  193,   -1,   -1,  157,   -1,
   -1,   -1,   -1,  201,   -1,   -1,   -1,  205,   -1,  168,
  169,  170,   -1,   -1,  212,   -1,   -1,  215,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  225,  187,
};
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 277
#define YYUNDFTOKEN 311
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,"'#'","'$'","'%'",0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,
0,0,0,0,0,0,0,"':'","';'","'<'","'='","'>'","'?'","'@'",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tINTEGER","tREAL",
"tIDENTIFIER","tSTRING","tREAD","tBREAK","tCONTINUE","tPRINTLN","tRETURN",
"tDGT","tDLT","tAPPLY","tSETA","tINTERVALO","tIFX","tOR","tAND","tEQ","tGE",
"tLE","tNE",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file :",
"file : decls",
"decls : declaration",
"decls : decls declaration",
"declaration : var_decls ';'",
"declaration : function",
"var_decls : variable",
"var_decls : var_decl",
"variable : data_type tIDENTIFIER '?' '=' expr",
"variable : data_type tIDENTIFIER '?'",
"variable : data_type tIDENTIFIER '!' '=' expr",
"variable : data_type tIDENTIFIER '!'",
"var_decl : data_type tIDENTIFIER '=' expr",
"var_decl : data_type tIDENTIFIER",
"data_type : '#'",
"data_type : '%'",
"data_type : '$'",
"data_type : '<' data_type '>'",
"function : data_type tIDENTIFIER '?' '(' func_args ')'",
"function : '!' tIDENTIFIER '?' '(' func_args ')'",
"function : data_type tIDENTIFIER '!' '(' func_args ')'",
"function : '!' tIDENTIFIER '!' '(' func_args ')'",
"function : data_type tIDENTIFIER '(' func_args ')'",
"function : '!' tIDENTIFIER '(' func_args ')'",
"function : '!' tIDENTIFIER '!' '(' func_args ')' body",
"function : data_type tIDENTIFIER '!' '(' func_args ')' '=' literal body",
"function : data_type tIDENTIFIER '!' '(' func_args ')' body",
"function : '!' tIDENTIFIER '(' func_args ')' body",
"function : data_type tIDENTIFIER '(' func_args ')' '=' literal body",
"function : data_type tIDENTIFIER '(' func_args ')' body",
"func_args : var_decl",
"func_args : func_args ',' var_decl",
"func_args :",
"func_call : tIDENTIFIER '(' opt_expressions ')'",
"func_call : '@' '(' opt_expressions ')'",
"opt_expressions :",
"opt_expressions : expressions",
"literal : integer",
"literal : string",
"literal : real",
"integer : tINTEGER",
"real : tREAL",
"string : tSTRING",
"string : string tSTRING",
"body : initial_section sections final_section",
"body : sections final_section",
"body : initial_section sections",
"body : initial_section final_section",
"body : sections",
"body : initial_section",
"body : final_section",
"initial_section : tDLT code_block",
"sections : section",
"sections : sections section",
"section : '(' opt_expr ')' code_block",
"section : '[' opt_expr ']' code_block",
"section : code_block",
"opt_expr :",
"opt_expr : expr",
"final_section : tDGT code_block",
"code_block : '{' opt_instructions '}'",
"code_block : '{' inner_decls opt_instructions '}'",
"inner_decls : var_decls ';'",
"inner_decls : inner_decls var_decls ';'",
"opt_instructions :",
"opt_instructions : instrs",
"instruction : expr ';'",
"instruction : expr '!'",
"instruction : expr tPRINTLN",
"instruction : tCONTINUE",
"instruction : tBREAK",
"instruction : tRETURN",
"instruction : conditional",
"instruction : iteration",
"instruction : code_block",
"instruction : tAPPLY tIDENTIFIER tSETA lval ':' expr tINTERVALO expr ';'",
"instrs : instruction",
"instrs : instrs instruction",
"conditional : '[' expr ']' '#' instruction",
"conditional : '[' expr ']' '?' instruction",
"conditional : '[' expr ']' '?' instruction ':' instruction",
"init_iteration : var_decl",
"init_iteration : expr",
"init_iteration : init_iteration ',' var_decl",
"init_iteration : init_iteration ',' expr",
"init_iteration :",
"iteration : '[' init_iteration ';' expressions ';' expressions ']' instruction",
"iteration : '[' init_iteration ';' ';' expressions ']' instruction",
"iteration : '[' init_iteration ';' expressions ';' ']' instruction",
"iteration : '[' init_iteration ';' ';' ']' instruction",
"expressions : expr",
"expressions : expressions ',' expr",
"expr : literal",
"expr : '-' expr",
"expr : '+' expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '/' expr",
"expr : expr '*' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : '~' expr",
"expr : expr tGE expr",
"expr : expr tLE expr",
"expr : expr tNE expr",
"expr : expr tEQ expr",
"expr : expr tOR expr",
"expr : expr tAND expr",
"expr : lval",
"expr : lval '=' expr",
"expr : '@' '=' expr",
"expr : '[' expr ']'",
"expr : lval '?'",
"expr : '@' '?'",
"expr : '(' expr ')'",
"expr : '@'",
"expr : func_call",
"lval : tIDENTIFIER",
"lval : lval '[' expr ']'",
"lval : '@' '[' expr ']'",
"lval : '(' expr ')' '[' expr ']'",
"lval : func_call '[' expr ']'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 1:
#line 69 "m19_parser.y"
	{ compiler->ast(yyval.sequence = new cdk::sequence_node(LINE)); }
break;
case 2:
#line 70 "m19_parser.y"
	{ compiler->ast(yyval.sequence = yystack.l_mark[0].sequence); }
break;
case 3:
#line 73 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 4:
#line 74 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 5:
#line 77 "m19_parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 6:
#line 78 "m19_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 7:
#line 82 "m19_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 8:
#line 83 "m19_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 9:
#line 87 "m19_parser.y"
	{ yyval.node = new m19::variable_declaration_node(LINE, 2, yystack.l_mark[-4].type, *yystack.l_mark[-3].s, yystack.l_mark[0].expression); delete yystack.l_mark[-3].s;}
break;
case 10:
#line 88 "m19_parser.y"
	{ yyval.node = new m19::variable_declaration_node(LINE, 2, yystack.l_mark[-2].type, *yystack.l_mark[-1].s, nullptr); delete yystack.l_mark[-1].s;}
break;
case 11:
#line 89 "m19_parser.y"
	{ yyval.node = new m19::variable_declaration_node(LINE, 1, yystack.l_mark[-4].type, *yystack.l_mark[-3].s, yystack.l_mark[0].expression); delete yystack.l_mark[-3].s;}
break;
case 12:
#line 90 "m19_parser.y"
	{ yyval.node = new m19::variable_declaration_node(LINE, 1, yystack.l_mark[-2].type, *yystack.l_mark[-1].s, nullptr); delete yystack.l_mark[-1].s;}
break;
case 13:
#line 93 "m19_parser.y"
	{ yyval.node = new m19::variable_declaration_node(LINE, 0, yystack.l_mark[-3].type, *yystack.l_mark[-2].s, yystack.l_mark[0].expression); delete yystack.l_mark[-2].s;}
break;
case 14:
#line 94 "m19_parser.y"
	{ yyval.node = new m19::variable_declaration_node(LINE, 0, yystack.l_mark[-1].type, *yystack.l_mark[0].s, nullptr); delete yystack.l_mark[0].s;}
break;
case 15:
#line 98 "m19_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_INT); }
break;
case 16:
#line 99 "m19_parser.y"
	{ yyval.type = new basic_type(8, basic_type::TYPE_DOUBLE); }
break;
case 17:
#line 100 "m19_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_STRING); }
break;
case 18:
#line 101 "m19_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER);  yyval.type->_subtype=yystack.l_mark[-1].type;}
break;
case 19:
#line 105 "m19_parser.y"
	{ yyval.node = new m19::function_declaration_node(LINE, yystack.l_mark[-5].type, *yystack.l_mark[-4].s, 2, yystack.l_mark[-1].sequence); delete yystack.l_mark[-4].s;}
break;
case 20:
#line 106 "m19_parser.y"
	{ yyval.node = new m19::function_declaration_node(LINE, *yystack.l_mark[-4].s, 2, yystack.l_mark[-1].sequence); delete yystack.l_mark[-4].s;}
break;
case 21:
#line 107 "m19_parser.y"
	{ yyval.node = new m19::function_declaration_node(LINE, yystack.l_mark[-5].type, *yystack.l_mark[-4].s, 1, yystack.l_mark[-1].sequence); delete yystack.l_mark[-4].s;}
break;
case 22:
#line 108 "m19_parser.y"
	{ yyval.node = new m19::function_declaration_node(LINE, *yystack.l_mark[-4].s, 1, yystack.l_mark[-1].sequence); delete yystack.l_mark[-4].s;}
break;
case 23:
#line 109 "m19_parser.y"
	{ yyval.node = new m19::function_declaration_node(LINE, yystack.l_mark[-4].type, *yystack.l_mark[-3].s, 0, yystack.l_mark[-1].sequence); delete yystack.l_mark[-3].s;}
break;
case 24:
#line 110 "m19_parser.y"
	{ yyval.node = new m19::function_declaration_node(LINE, *yystack.l_mark[-3].s, 0, yystack.l_mark[-1].sequence); delete yystack.l_mark[-3].s;}
break;
case 25:
#line 112 "m19_parser.y"
	{ yyval.node = new m19::function_definition_node(LINE,*yystack.l_mark[-5].s, 1, yystack.l_mark[-2].sequence, yystack.l_mark[0].body); delete yystack.l_mark[-5].s;}
break;
case 26:
#line 113 "m19_parser.y"
	{ yyval.node = new m19::function_definition_node(LINE,yystack.l_mark[-8].type, *yystack.l_mark[-7].s, 1, yystack.l_mark[-1].expression, yystack.l_mark[-4].sequence, yystack.l_mark[0].body); delete yystack.l_mark[-7].s;}
break;
case 27:
#line 114 "m19_parser.y"
	{ yyval.node = new m19::function_definition_node(LINE,yystack.l_mark[-6].type, *yystack.l_mark[-5].s, 1, nullptr, yystack.l_mark[-2].sequence, yystack.l_mark[0].body); delete yystack.l_mark[-5].s;}
break;
case 28:
#line 115 "m19_parser.y"
	{ yyval.node = new m19::function_definition_node(LINE,*yystack.l_mark[-4].s, 0,yystack.l_mark[-2].sequence, yystack.l_mark[0].body); delete yystack.l_mark[-4].s;}
break;
case 29:
#line 116 "m19_parser.y"
	{ yyval.node = new m19::function_definition_node(LINE,yystack.l_mark[-7].type, *yystack.l_mark[-6].s, 0, yystack.l_mark[-1].expression, yystack.l_mark[-4].sequence, yystack.l_mark[0].body); delete yystack.l_mark[-6].s;}
break;
case 30:
#line 117 "m19_parser.y"
	{ yyval.node = new m19::function_definition_node(LINE,yystack.l_mark[-5].type, *yystack.l_mark[-4].s, 0, nullptr, yystack.l_mark[-2].sequence, yystack.l_mark[0].body); delete yystack.l_mark[-4].s;}
break;
case 31:
#line 120 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 32:
#line 121 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-2].sequence); }
break;
case 33:
#line 122 "m19_parser.y"
	{ yyval.sequence = nullptr; }
break;
case 34:
#line 125 "m19_parser.y"
	{ yyval.expression = new m19::function_call_node(LINE, *yystack.l_mark[-3].s, yystack.l_mark[-1].sequence); delete yystack.l_mark[-3].s; }
break;
case 35:
#line 126 "m19_parser.y"
	{ yyval.expression = new m19::function_call_node(LINE, "@", yystack.l_mark[-1].sequence); }
break;
case 36:
#line 129 "m19_parser.y"
	{ yyval.sequence = nullptr; }
break;
case 37:
#line 130 "m19_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 38:
#line 133 "m19_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression;}
break;
case 39:
#line 134 "m19_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s);}
break;
case 40:
#line 135 "m19_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression;}
break;
case 41:
#line 138 "m19_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 42:
#line 141 "m19_parser.y"
	{ yyval.expression = new cdk::double_node(LINE, yystack.l_mark[0].d); }
break;
case 43:
#line 145 "m19_parser.y"
	{ yyval.s = yystack.l_mark[0].s ;}
break;
case 44:
#line 146 "m19_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[-1].s + *yystack.l_mark[0].s); delete yystack.l_mark[-1].s; delete yystack.l_mark[0].s; }
break;
case 45:
#line 151 "m19_parser.y"
	{ yyval.body = new m19::body_node(LINE, yystack.l_mark[-2].initial_section, yystack.l_mark[-1].sequence, yystack.l_mark[0].final_section); }
break;
case 46:
#line 152 "m19_parser.y"
	{ yyval.body = new m19::body_node(LINE, nullptr, yystack.l_mark[-1].sequence, yystack.l_mark[0].final_section); }
break;
case 47:
#line 153 "m19_parser.y"
	{ yyval.body = new m19::body_node(LINE, yystack.l_mark[-1].initial_section, yystack.l_mark[0].sequence, nullptr); }
break;
case 48:
#line 154 "m19_parser.y"
	{ yyval.body = new m19::body_node(LINE, yystack.l_mark[-1].initial_section, nullptr, yystack.l_mark[0].final_section); }
break;
case 49:
#line 155 "m19_parser.y"
	{ yyval.body = new m19::body_node(LINE, nullptr, yystack.l_mark[0].sequence, nullptr); }
break;
case 50:
#line 156 "m19_parser.y"
	{ yyval.body = new m19::body_node(LINE, yystack.l_mark[0].initial_section, nullptr, nullptr); }
break;
case 51:
#line 157 "m19_parser.y"
	{ yyval.body = new m19::body_node(LINE, nullptr, nullptr, yystack.l_mark[0].final_section); }
break;
case 52:
#line 160 "m19_parser.y"
	{ yyval.initial_section = new m19::initial_section_node(LINE, yystack.l_mark[0].code_block); }
break;
case 53:
#line 163 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].section); }
break;
case 54:
#line 164 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].section, yystack.l_mark[-1].sequence); }
break;
case 55:
#line 167 "m19_parser.y"
	{ yyval.section = new m19::section_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].code_block, 1); }
break;
case 56:
#line 168 "m19_parser.y"
	{ yyval.section = new m19::section_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].code_block, 2);}
break;
case 57:
#line 169 "m19_parser.y"
	{ yyval.section = new m19::section_node(LINE, nullptr, yystack.l_mark[0].code_block, 0); }
break;
case 58:
#line 173 "m19_parser.y"
	{ yyval.expression = nullptr; }
break;
case 59:
#line 174 "m19_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 60:
#line 179 "m19_parser.y"
	{ yyval.final_section = new m19::final_section_node(LINE, yystack.l_mark[0].code_block); }
break;
case 61:
#line 183 "m19_parser.y"
	{ yyval.code_block = new m19::block_node(LINE, nullptr, yystack.l_mark[-1].sequence); }
break;
case 62:
#line 184 "m19_parser.y"
	{ yyval.code_block = new m19::block_node(LINE, yystack.l_mark[-2].sequence, yystack.l_mark[-1].sequence); }
break;
case 63:
#line 187 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].node); }
break;
case 64:
#line 188 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].node,yystack.l_mark[-2].sequence); }
break;
case 65:
#line 192 "m19_parser.y"
	{ yyval.sequence = nullptr; }
break;
case 66:
#line 193 "m19_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 67:
#line 197 "m19_parser.y"
	{ yyval.node = new m19::evaluation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 68:
#line 198 "m19_parser.y"
	{ yyval.node = new m19::print_node(LINE, yystack.l_mark[-1].expression, false); }
break;
case 69:
#line 199 "m19_parser.y"
	{ yyval.node = new m19::print_node(LINE, yystack.l_mark[-1].expression, true); }
break;
case 70:
#line 200 "m19_parser.y"
	{ yyval.node = new m19::continue_node(LINE); }
break;
case 71:
#line 201 "m19_parser.y"
	{ yyval.node = new m19::break_node(LINE); }
break;
case 72:
#line 202 "m19_parser.y"
	{ yyval.node = new m19::return_node(LINE); }
break;
case 73:
#line 203 "m19_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 74:
#line 204 "m19_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 75:
#line 205 "m19_parser.y"
	{ yyval.node = yystack.l_mark[0].code_block; }
break;
case 76:
#line 206 "m19_parser.y"
	{ yyval.node = new m19::apply_node(LINE, *yystack.l_mark[-7].s, yystack.l_mark[-5].lvalue, yystack.l_mark[-3].expression, yystack.l_mark[-1].expression); delete yystack.l_mark[-7].s; }
break;
case 77:
#line 210 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 78:
#line 211 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 79:
#line 215 "m19_parser.y"
	{ yyval.node = new m19::if_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[0].node); }
break;
case 80:
#line 216 "m19_parser.y"
	{ yyval.node = new m19::if_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[0].node); }
break;
case 81:
#line 217 "m19_parser.y"
	{ yyval.node = new m19::if_else_node(LINE, yystack.l_mark[-5].expression, yystack.l_mark[-2].node, yystack.l_mark[0].node); }
break;
case 82:
#line 222 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 83:
#line 223 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression); }
break;
case 84:
#line 224 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-2].sequence); }
break;
case 85:
#line 225 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression, yystack.l_mark[-2].sequence); }
break;
case 86:
#line 226 "m19_parser.y"
	{ yyval.sequence = nullptr; }
break;
case 87:
#line 230 "m19_parser.y"
	{ yyval.node = new m19::for_node(LINE, yystack.l_mark[-6].sequence, yystack.l_mark[-4].sequence,  yystack.l_mark[-2].sequence, yystack.l_mark[0].node); }
break;
case 88:
#line 231 "m19_parser.y"
	{ yyval.node = new m19::for_node(LINE, yystack.l_mark[-5].sequence, nullptr,  yystack.l_mark[-2].sequence, yystack.l_mark[0].node); }
break;
case 89:
#line 232 "m19_parser.y"
	{ yyval.node = new m19::for_node(LINE, yystack.l_mark[-5].sequence, yystack.l_mark[-3].sequence, nullptr, yystack.l_mark[0].node); }
break;
case 90:
#line 233 "m19_parser.y"
	{ yyval.node = new m19::for_node(LINE, yystack.l_mark[-4].sequence, nullptr,  nullptr, yystack.l_mark[0].node); }
break;
case 91:
#line 236 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression); }
break;
case 92:
#line 237 "m19_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression, yystack.l_mark[-2].sequence); }
break;
case 93:
#line 240 "m19_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 94:
#line 241 "m19_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 95:
#line 242 "m19_parser.y"
	{ yyval.expression = new m19::identity_node(LINE, yystack.l_mark[0].expression); }
break;
case 96:
#line 243 "m19_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 97:
#line 244 "m19_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 98:
#line 245 "m19_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 99:
#line 246 "m19_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 100:
#line 247 "m19_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 101:
#line 248 "m19_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 102:
#line 249 "m19_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 103:
#line 250 "m19_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 104:
#line 251 "m19_parser.y"
	{ yyval.expression = new cdk::ge_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 105:
#line 252 "m19_parser.y"
	{ yyval.expression = new cdk::le_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 106:
#line 253 "m19_parser.y"
	{ yyval.expression = new cdk::ne_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 107:
#line 254 "m19_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 108:
#line 255 "m19_parser.y"
	{ yyval.expression = new cdk::or_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 109:
#line 256 "m19_parser.y"
	{ yyval.expression = new cdk::and_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 110:
#line 257 "m19_parser.y"
	{ yyval.expression = new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 111:
#line 258 "m19_parser.y"
	{ yyval.expression = new cdk::assignment_node(LINE, yystack.l_mark[-2].lvalue, yystack.l_mark[0].expression); }
break;
case 112:
#line 259 "m19_parser.y"
	{ yyval.expression = new cdk::assignment_node(LINE, new cdk::variable_node(LINE, "@"), yystack.l_mark[0].expression);  }
break;
case 113:
#line 260 "m19_parser.y"
	{ yyval.expression = new m19::memory_alloc_node(LINE, yystack.l_mark[-1].expression); }
break;
case 114:
#line 261 "m19_parser.y"
	{ yyval.expression = new m19::address_of_node(LINE, yystack.l_mark[-1].lvalue); }
break;
case 115:
#line 262 "m19_parser.y"
	{ yyval.expression = new m19::address_of_node(LINE, nullptr); }
break;
case 116:
#line 263 "m19_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 117:
#line 264 "m19_parser.y"
	{ yyval.expression = new m19::read_node(LINE); }
break;
case 118:
#line 265 "m19_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 119:
#line 268 "m19_parser.y"
	{ yyval.lvalue = new cdk::variable_node(LINE, *yystack.l_mark[0].s); delete yystack.l_mark[0].s;}
break;
case 120:
#line 269 "m19_parser.y"
	{ yyval.lvalue = new m19::indexing_node(LINE,  new cdk::rvalue_node(LINE, yystack.l_mark[-3].lvalue), yystack.l_mark[-1].expression);}
break;
case 121:
#line 270 "m19_parser.y"
	{ yyval.lvalue = new m19::indexing_node(LINE, nullptr , yystack.l_mark[-1].expression);}
break;
case 122:
#line 271 "m19_parser.y"
	{ yyval.lvalue = new m19::indexing_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-1].expression);}
break;
case 123:
#line 272 "m19_parser.y"
	{ yyval.lvalue = new m19::indexing_node(LINE, yystack.l_mark[-3].expression, yystack.l_mark[-1].expression);}
break;
#line 1379 "m19_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
