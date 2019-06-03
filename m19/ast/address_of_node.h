// $Id: address_of_node.h,v 1.4 2019/03/19 17:09:35 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_ADDRESSOFNODE_H__
#define __M19_ADDRESSOFNODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>

namespace m19 {

  /**
   * Class for describing address of nodes.
   */
  class address_of_node: public cdk::expression_node {
      cdk::lvalue_node *_lvalue;
      

  public:
    inline address_of_node(int lineno, cdk::lvalue_node *lvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue){
    }
    
    inline cdk::lvalue_node *lvalue() {
        return _lvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_address_of_node(this, level);
    }

  };

} // m19

#endif
