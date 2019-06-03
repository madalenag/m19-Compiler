#ifndef __M19_SEMANTICS_POSTFIX_WRITER_H__
#define __M19_SEMANTICS_POSTFIX_WRITER_H__

#include <set>
#include <stack>
#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace m19 {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    cdk::symbol_table<m19::symbol> &_symtab;
    
    std::set<std::string> _functions_to_declare;
    
    bool _errors, _inFunctionBody, _inFunctionArgs;
    bool _hasFinalSection, _inFinalSection;
    std::shared_ptr<m19::symbol> _function;
    int _offset; //current framepointer (0 means no var)
    cdk::basic_postfix_emitter &_pf;
    int _lbl, _return, _finalSection;
    std::stack<int> _forIni, _forCondition, _forStep, _forEnd;

  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<m19::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _errors(false), _inFunctionBody(false), _inFunctionArgs(false), _hasFinalSection(false), _inFinalSection(false), _function(nullptr), _offset(0), _pf(pf), _lbl(0) , _return(0), _finalSection(0){
    }

  public:
    ~postfix_writer() {
      os().flush();
    }
    
    
  protected:
    void do_IDExpression(cdk::binary_expression_node * const node, int lvl);  
    void do_ScalarLogicalExpression(cdk::binary_expression_node * const node, int lvl);
    void do_ReturnOperation();

  private:
    void error(int lineno, std::string s) {
        std::cerr << "error: " << lineno << ": " << s << std::endl;
    }
    
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
    }

  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

} // m19

#endif
