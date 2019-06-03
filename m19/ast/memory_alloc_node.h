// $Id: memory_alloc_node.h,v 1.2 2019/03/18 14:30:06 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_MEMORYALLOCNODE_H__
#define __M19_MEMORYALLOCNODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace m19 {

  /**
   * Class for describing memory alloc nodes.
   */
  class memory_alloc_node: public cdk::unary_expression_node {

  public:
    inline memory_alloc_node(int lineno, cdk::expression_node *argument) :
        cdk::unary_expression_node(lineno, argument) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_memory_alloc_node(this, level);
    }

  };

} // m19

#endif
