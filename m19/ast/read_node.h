// $Id: read_node.h,v 1.2 2019/03/19 17:09:36 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_READNODE_H__
#define __M19_READNODE_H__

#include <cdk/ast/expression_node.h>

namespace m19 {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::expression_node {

  public:
    inline read_node(int lineno) :
        cdk::expression_node(lineno) {
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_read_node(this, level);
    }

  };

} // m19

#endif
