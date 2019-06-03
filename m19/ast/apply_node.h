// $Id: variable_declaration_node.h,v 1.7 2019/04/11 17:42:18 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_APPLY_H__
#define __M19_APPLY_H__

#include <cdk/ast/basic_node.h>

//teste pratico

namespace m19 {

  /**
   * Class for describing variable declaration nodes.
   */
  class apply_node: public cdk::basic_node {
    std::string _identifier;
    cdk::lvalue_node *_vector;
    cdk::expression_node *_lowIndex;
    cdk::expression_node *_upperIndex;

  public:
    inline apply_node(int lineno, const std::string &identifier, cdk::lvalue_node *vec, cdk::expression_node *lI, cdk::expression_node *uI) :
        cdk::basic_node(lineno), _identifier(identifier), _vector(vec), _lowIndex(lI), _upperIndex(uI) {
    }

  public:

    const std::string &identifier() const {
        return _identifier;
    }
    
    inline cdk::lvalue_node *vector() {
        return _vector;
    }
    
    inline cdk::expression_node *lowIndex() {
        return _lowIndex;
    }
    
    inline cdk::expression_node *upperIndex() {
        return _upperIndex;
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_apply_node(this, level);
    }

  };

} // m19

#endif
