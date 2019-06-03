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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
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
extern YYSTYPE yylval;
