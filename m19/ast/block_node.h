// $Id: block_node.h,v 1.3 2019/03/19 17:09:35 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_BLOCKNODE_H__
#define __M19_BLOCKNODE_H__

#include <cdk/ast/sequence_node.h>

namespace m19 {

  /**
   * Class for describing block nodes.
   */
  class block_node: public cdk::basic_node {
      cdk::sequence_node *_declarations;
      cdk::sequence_node *_instructions;

  public:
    inline block_node(int lineno, cdk::sequence_node *declarations, cdk::sequence_node *instructions) :
        cdk::basic_node(lineno), _declarations(declarations), _instructions(instructions) {
    }

  public:
    cdk::sequence_node *declarations() {
        return _declarations;
    }
    
    cdk::sequence_node *instructions() {
        return _instructions;
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_block_node(this, level);
    }

  };

} // m19

#endif
