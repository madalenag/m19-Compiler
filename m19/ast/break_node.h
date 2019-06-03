// $Id: break_node.h,v 1.3 2019/03/19 17:09:36 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_BREAKNODE_H__
#define __M19_BREAKNODE_H__

#include <cdk/ast/basic_node.h>

namespace m19 {

  /**
   * Class for describing break nodes.
   */
  class break_node: public cdk::basic_node {

  public:
    inline break_node(int lineno) :
        cdk::basic_node(lineno) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_break_node(this, level);
    }

  };

} // m19

#endif
