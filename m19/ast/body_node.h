// $Id: body_node.h,v 1.3 2019/03/20 12:13:21 ist187546 Exp $ -*- c++ -*-
#ifndef __M19_BODYNODE_H__
#define __M19_BODYNODE_H__

#include <cdk/ast/basic_node.h>
#include "ast/section_node.h"
#include "ast/initial_section_node.h"
#include "ast/final_section_node.h"

namespace m19 {

  /**
   * Class for describing body nodes.
   */
  class body_node: public cdk::basic_node {
    m19::initial_section_node *_initial_sec;
    cdk::sequence_node *_sections; 
    m19::final_section_node *_final_sec;

  public:
    inline body_node(int lineno, m19::initial_section_node *initial_sec, cdk::sequence_node *sections, m19::final_section_node *final_sec) :
        cdk::basic_node(lineno), _initial_sec(initial_sec), _sections(sections), _final_sec(final_sec) {
    }

  public:
    inline m19::initial_section_node *initial_section() {
        return _initial_sec;
    }
    
    inline cdk::sequence_node *sections() {
        return _sections;
    }
    
    inline m19::final_section_node *final_section() {
        return _final_sec;
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_body_node(this, level);
    }

  };

} // m19

#endif
