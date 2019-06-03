// $Id: for_node.h,v 1.3 2019/05/20 15:19:46 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_FORNODE_H__
#define __M19_FORNODE_H__

#include <cdk/ast/sequence_node.h>


namespace m19 {

  /**
   * Class for describing for-cycle nodes.
   */
  class for_node: public cdk::basic_node {
    cdk::sequence_node *_init;
    cdk::sequence_node *_condition; 
    cdk::sequence_node *_step;
    cdk::basic_node *_instr;

  public:
    inline for_node(int lineno, cdk::sequence_node *init, cdk::sequence_node *condition, cdk::sequence_node *step, cdk::basic_node *instr) :
        basic_node(lineno), _init(init), _condition(condition), _step(step), _instr(instr) {
    }
    
  public:
    inline cdk::sequence_node *init() {
      return _init;
    }
    
    inline cdk::sequence_node *condition() {
      return _condition;
    }
    
    inline cdk::sequence_node *step() {
      return _step;
    }
    
    
    inline cdk::basic_node *instr() {
      return _instr;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_for_node(this, level);
    }

  };

} // m19

#endif
