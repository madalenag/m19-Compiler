// $Id: continue_node.h,v 1.3 2019/03/19 17:09:36 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_CONTINUENODE_H__
#define __M19_CONTINUENODE_H__

#include <cdk/ast/basic_node.h>

namespace m19 {

  /**
   * Class for describing continue nodes.
   */
  class continue_node: public cdk::basic_node {

  public:
    inline continue_node(int lineno) :
        cdk::basic_node(lineno) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_continue_node(this, level);
    }

  };

} // m19

#endif
