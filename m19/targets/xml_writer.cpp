#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated


//---------------------------------------------------------------------------

static std::string type_name(basic_type *type) {
    if (type->name() == basic_type::TYPE_INT) return "integer";
    if (type->name() == basic_type::TYPE_DOUBLE) return "double";
    if (type->name() == basic_type::TYPE_STRING) return "string";
    if (type->name() == basic_type::TYPE_VOID)  return "void";
    if (type->name() == basic_type::TYPE_POINTER) {
        std::string s = "pointer";
        basic_type *p = type->subtype();
        while (p) {
            s+= " to " + type_name(p);
            p = p->subtype();
        }
        return s;
    } else 
        return "unknown type";
    
}
    
static std::string qualifier_name(int val) {
        if (val == 0)
            return "private";
        else if (val == 1)
            return "public";
        else if (val == 2)
            return "import";
        return "unknow qualifier";
    }
    

//---------------------------------------------------------------------------

void m19::xml_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node,lvl);
}


void m19::xml_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}


void m19::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<" << node->label() << " size='"<< node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++) {
      cdk::basic_node *n = node->node(i);
      if (n==nullptr) {
          break;
      }
      n->accept(this, lvl + 2);
  }
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------
void m19::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  process_literal(node, lvl);
}
void m19::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  process_literal(node, lvl);
}

void m19::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  process_literal(node, lvl);
}

void m19::xml_writer::do_apply_node(m19::apply_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_unary_expression(cdk::unary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}
void m19::xml_writer::do_binary_expression(cdk::binary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_not_node(cdk::not_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

void m19::xml_writer::do_identity_node(m19::identity_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

void m19::xml_writer::do_and_node(cdk::and_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

void m19::xml_writer::do_or_node(cdk::or_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}
void m19::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void m19::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_variable_node(cdk::variable_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "<" << node->label() << ">" << node->name() << "</" << node->label() << ">" << std::endl;
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  
  node->lvalue()->accept(this, lvl + 2);
  node->rvalue()->accept(this, lvl + 2);
  closeTag(node, lvl);
}


//---------------------------------------------------------------------------

void m19::xml_writer::do_evaluation_node(m19::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_print_node(m19::print_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_read_node(m19::read_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_for_node(m19::for_node * const node, int lvl) {
  openTag(node, lvl);
  
  if (node->init()) {
    openTag("init", lvl + 2);
    node->init()->accept(this, lvl + 4);
    closeTag("init", lvl + 2);
  }

  if (node->condition()) {
    openTag("condition", lvl + 2);
    node->condition()->accept(this, lvl + 4);
    closeTag("condition", lvl + 2);
  }
  if (node->step()) {
    openTag("step", lvl + 2);
    node->step()->accept(this, lvl + 4);
    closeTag("step", lvl + 2);
  }
  if (node->instr()) {
    openTag("block", lvl + 2);
    node->instr()->accept(this, lvl + 4);
    closeTag("block", lvl + 2);
  }
  
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_return_node(m19::return_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_continue_node(m19::continue_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_break_node(m19::break_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_address_of_node(m19::address_of_node * const node, int lvl) {
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 2);
  closeTag(node, lvl);  
}


//---------------------------------------------------------------------------

void m19::xml_writer::do_block_node(m19::block_node * const node, int lvl) {
  openTag(node, lvl);
  
  openTag("declarations", lvl + 2);
  if (node->declarations()) {
      node->declarations()->accept(this, lvl + 4);
  }
  closeTag("declarations", lvl + 2);
  
  openTag("instructions", lvl + 2);
  if (node->instructions()) {
      node->instructions()->accept(this, lvl + 4);
  }
  closeTag("instructions", lvl + 2);
  
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_indexing_node(m19::indexing_node * const node, int lvl) {
  openTag(node, lvl);
  
  openTag("base", lvl + 2);
  node->base()->accept(this, lvl + 4);
  closeTag("base", lvl + 2);
  
  openTag("index", lvl + 2);
  node->index()->accept(this, lvl + 4);
  closeTag("index", lvl + 2);
  
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_memory_alloc_node(m19::memory_alloc_node * const node, int lvl) {
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_variable_declaration_node(m19::variable_declaration_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  reset_new_symbol();
  os() << std::string(lvl, ' ') << "<" << node->label() << " name='" << node->name() << "' qualifier='" << qualifier_name(node->qualifier()) << "' type='"<< type_name(node->type()) << "'>" << std::endl;
  
  if (node->initializer()) {
      openTag("initializer", lvl);
      node->initializer()->accept(this, lvl + 4);
      closeTag("initializer", lvl);
  }
  closeTag(node, lvl);

}

//---------------------------------------------------------------------------

void m19::xml_writer::do_function_declaration_node(m19::function_declaration_node * const node, int lvl) {
    if (_inFunctionBody || _inFunctionArgs) {
        error(node->lineno(), "cannot declare function in body or in args");
        return;
    }
    
    //fix
    ASSERT_SAFE_EXPRESSIONS
    reset_new_symbol();
    
    os() << std::string(lvl, ' ') << "<" << node->label() << " name='" << node->identifier() << "' qualifier='" << qualifier_name(node->qualifier()) << "' type='"<< type_name(node->type()) << "'>" << std::endl; 
    
    
    openTag("arguments", lvl);
    if (node->arguments()) {
        node->arguments()->accept(this, lvl + 4);
    }
    closeTag("arguments", lvl);
    
    closeTag(node, lvl);
}

//---------------------------------------------------------------------------


void m19::xml_writer::do_function_definition_node(m19::function_definition_node * const node, int lvl) {
    if (_inFunctionBody || _inFunctionArgs) {
        error(node->lineno(), "cannot declare function in body or in args");
        return;
    }
    
    //fix
    ASSERT_SAFE_EXPRESSIONS

    
    _function = new_symbol();
    reset_new_symbol();
    
    _inFunctionBody = true;
    _symtab.push();
    
    os() << std::string(lvl, ' ') << "<" << node->label() << " name='" << node->identifier() << "' qualifier='" << qualifier_name(node->qualifier()) << "' type='"<< type_name(node->type()) << "'>" << std::endl;

    openTag("arguments", lvl);
    if (node->arguments()) {
        _inFunctionArgs = true;
        node->arguments()->accept(this, lvl + 4);
        _inFunctionArgs = false;
    }
    closeTag("arguments", lvl);
    
    node->body()->accept(this, lvl + 2);
    closeTag(node, lvl);
    
    _symtab.pop();
    _inFunctionBody = false;
    
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_function_call_node(m19::function_call_node * const node, int lvl) {
    os() << std::string(lvl, ' ') << "<" << node->label() << " name='" << node->identifier()  << "'>"  << std::endl; 
    
    openTag("arguments", lvl);
    if (node->arguments()) {
        node->arguments()->accept(this, lvl + 4);
    }
    closeTag("arguments", lvl);
    
    closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_body_node(m19::body_node * const node, int lvl) {
  openTag(node, lvl);
  
  openTag("initialsection", lvl + 2);
  if (node->initial_section()) {
    node->initial_section()->accept(this, lvl + 4);
  }
  closeTag("initialsection", lvl + 2);
  
  openTag("section", lvl + 2);
  if (node->sections()) {
    node->sections()->accept(this, lvl + 4);
  }
  closeTag("section", lvl + 2);
  
  openTag("finalsection", lvl + 2);
  if (node->final_section()) {
    node->final_section()->accept(this, lvl + 4);
  }
  closeTag("finalsection", lvl + 2);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_section_node(m19::section_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  
  openTag("expression", lvl + 2);
  if (node->expression()) {
    node->expression()->accept(this, lvl + 4);
  }
  closeTag("expression", lvl + 2);
  
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_initial_section_node(m19::initial_section_node * const node, int lvl){
  ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_final_section_node(m19::final_section_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void m19::xml_writer::do_if_node(m19::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  if (node->condition())
    node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  if (node->block())
    node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void m19::xml_writer::do_if_else_node(m19::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  if (node->condition())
    node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  if (node->thenblock())
    node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  if (node->elseblock())
    node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}
