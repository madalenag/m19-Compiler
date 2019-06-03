// $Id: indexing_node.h,v 1.2 2019/03/19 17:09:36 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_INDEXINGNODE_H__
#define __M19_INDEXINGNODE_H__

#include <cdk/ast/lvalue_node.h>
#include <cdk/ast/expression_node.h>

namespace m19 {

  /**
   * Class for describing indexing nodes.
   */
  class indexing_node: public cdk::lvalue_node {
      cdk::expression_node *_base;
      cdk::expression_node *_index;

  public:
    inline indexing_node(int lineno, cdk::expression_node *base, cdk::expression_node *index) :
        cdk::lvalue_node(lineno), _base(base), _index(index){
    }
    
    inline cdk::expression_node *base() {
        return _base;
    }

    inline cdk::expression_node *index() {
        return _index;
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_indexing_node(this, level);
    }

  };

} // m19

#endif
