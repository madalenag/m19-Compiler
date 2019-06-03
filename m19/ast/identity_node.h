// $Id: identity_node.h,v 1.1 2019/03/17 23:02:59 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_IDENTITYNODE_H__
#define __M19_IDENTITYNODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace m19 {

  /**
   * Class for describing identity nodes.
   */
  class identity_node: public cdk::unary_expression_node {

  public:
    inline identity_node(int lineno, cdk::expression_node *argument) :
        cdk::unary_expression_node(lineno, argument) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_identity_node(this, level);
    }

  };

} // m19

#endif
