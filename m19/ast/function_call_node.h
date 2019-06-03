// $Id: function_call_node.h,v 1.4 2019/05/10 21:27:43 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_FUNCTIONCALL_H__
#define __M19_FUNCTIONCALL_H__

#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>

namespace m19 {

  /**
   * Class for describing function call nodes.
   */
  class function_call_node: public cdk::expression_node {
      std::string _identifier;
      cdk::sequence_node *_arguments;

  public:
    
    inline function_call_node(int lineno, const std::string &identifier, cdk::sequence_node *arguments):
        cdk::expression_node(lineno),_identifier(identifier), _arguments(arguments) {
    }

    
    inline std::string &identifier() {
        return _identifier;
    }
    
    inline cdk::sequence_node *arguments() {
        return _arguments;
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_call_node(this, level);
    }

  };

} // m19

#endif
