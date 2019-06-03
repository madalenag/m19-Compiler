// $Id: section_node.h,v 1.4 2019/05/20 12:52:02 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_SECTIONNODE_H__
#define __M19_SECTIONNODE_H__

#include <cdk/ast/expression_node.h>
#include "ast/block_node.h"

namespace m19 {

  /**
   * Class for describing section nodes.
   */
  class section_node: public cdk::basic_node {
      cdk::expression_node *_expression;
      m19::block_node *_block;
      int _conditional;

  public:
    inline section_node(int lineno, cdk::expression_node *expression, m19::block_node *block, int conditional) :
        cdk::basic_node(lineno),_expression(expression), _block(block), _conditional(conditional) {
    }

    inline m19::block_node *block() {
        return _block;
    }
    
    inline cdk::expression_node *expression() {
        return _expression;
    }
    
    inline bool exclusive() {
        return _conditional == 2;
    }
    
    inline bool inclusive() {
        return _conditional == 1;
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_section_node(this, level);
    }

  };

} // m19

#endif
