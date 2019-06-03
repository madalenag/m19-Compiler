#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/frame_size_calculator.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------

void m19::postfix_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void m19::postfix_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}
//---------------------------------------------------------------------------

void m19::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}


void m19::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
    if (_inFunctionBody) {

      _pf.INT(node->value()); //load to the stack
    }
    else
      _pf.SINT(node->value()); //data segment
}

void m19::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
    if (_inFunctionBody)
      _pf.DOUBLE(node->value()); //load to the stack
    else
      _pf.SDOUBLE(node->value()); //data segment
}

void m19::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) { 
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.SSTRING(node->value()); // output string characters
  
  /* leave the address on the stack */
  if (_function) {
     //local var initializer 
    _pf.TEXT(); // return to the TEXT segment
    _pf.ADDR(mklbl(lbl1)); // the string to be printed
  } else {
      //global var initializer
     _pf.DATA();
     _pf.SADDR(mklbl(lbl1));
  }
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE)
    _pf.DNEG(); // 2-complement
  else if (node->argument()->type()->name() == basic_type::TYPE_INT)
    _pf.NEG();
}

void m19::postfix_writer::do_identity_node(m19::identity_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
}


//---------------------------------------------------------------------------

void m19::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl + 2);
  _pf.INT(0);
  _pf.EQ();
  
}
void m19::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl = ++_lbl;
  node->left()->accept(this, lvl + 2);
  _pf.DUP32();
  _pf.JZ(mklbl(lbl));
  node->right()->accept(this, lvl + 2);
  _pf.AND();
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl));
}
void m19::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl = ++_lbl;
  node->left()->accept(this, lvl + 2);
  _pf.DUP32();
  _pf.JNZ(mklbl(lbl));
  node->right()->accept(this, lvl + 2);
  _pf.OR();
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl));
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl + 2);
  
  if (node->type()->name() == basic_type::TYPE_DOUBLE && node->left()->type()->name() == basic_type::TYPE_INT)
    _pf.I2D();
  else if (node->type()->name() == basic_type::TYPE_POINTER && node->left()->type()->name() == basic_type::TYPE_INT) {
    _pf.INT(3);
    _pf.SHTL();
  }
  
  node->right()->accept(this, lvl + 2);
  
  if (node->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_INT)
    _pf.I2D();
  else if (node->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_INT) {
    _pf.INT(3);
    _pf.SHTL();
  }
  
  if (node->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.DADD();
  else 
      _pf.ADD();
}


void m19::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  
  node->left()->accept(this, lvl + 2);
  if (node->type()->name() == basic_type::TYPE_DOUBLE && node->left()->type()->name() == basic_type::TYPE_INT)
    _pf.I2D();

  node->right()->accept(this, lvl + 2);
  
  if (node->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_INT)
    _pf.I2D();
  else if (node->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_INT) {
    _pf.INT(3);
    _pf.SHTL();
  }
  
  if (node->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.DSUB();
  else 
      _pf.SUB();  
}


void m19::postfix_writer::do_IDExpression(cdk::binary_expression_node * const node, int lvl) { 
  node->left()->accept(this, lvl + 2);
  if (node->type()->name() == basic_type::TYPE_DOUBLE && node->left()->type()->name() == basic_type::TYPE_INT)
    _pf.I2D();
  
  node->right()->accept(this, lvl + 2);
  if (node->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_INT)
    _pf.I2D();   
}

void m19::postfix_writer::do_ScalarLogicalExpression(cdk::binary_expression_node * const node, int lvl)  {
    node->left()->accept(this, lvl + 2);
    if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
        _pf.I2D();
    
    node->right()->accept(this, lvl + 2);
    if (node->right()->type()->name() == basic_type::TYPE_INT && node->left()->type()->name() == basic_type::TYPE_DOUBLE)
        _pf.I2D();
}

void m19::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  do_IDExpression(node, lvl); 

  if (node->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.DMUL();
  else
       _pf.MUL();
}


void m19::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  do_IDExpression(node, lvl); 

  if (node->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.DDIV();
  else
       _pf.DIV();
}


void m19::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}


void m19::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  do_ScalarLogicalExpression(node, lvl);
  _pf.LT();
}
void m19::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  do_ScalarLogicalExpression(node, lvl);
  _pf.LE();
}
void m19::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  do_ScalarLogicalExpression(node, lvl);
  _pf.GE();
}
void m19::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  do_ScalarLogicalExpression(node, lvl);
  _pf.GT();
}
void m19::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  do_ScalarLogicalExpression(node, lvl);
  _pf.NE();
}
void m19::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  do_ScalarLogicalExpression(node, lvl);
  _pf.EQ();
}


//---------------------------------------------------------------------------

void m19::postfix_writer::do_variable_node(cdk::variable_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  
  const std::string &id = node->name();
  
  if (id != "@") {
    std::shared_ptr<m19::symbol> symbol = _symtab.find(id);
    
    if (symbol->global())
        _pf.ADDR(node->name());
    else
        _pf.LOCAL(symbol->offset());
  } else {
    _pf.LOCAL(-_function->type()->size());
  }
}

void m19::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  os() << " ;; before rva" << std::endl;
  node->lvalue()->accept(this, lvl);
  if (node->type()->name() == basic_type::TYPE_DOUBLE)
    _pf.LDDOUBLE();
  else
    _pf.LDINT(); // depends on type size
}

void m19::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  node->rvalue()->accept(this, lvl + 2); // determine the new value
  
  if (node->type()->name() == basic_type::TYPE_DOUBLE) {
      if (node->rvalue()->type()->name() == basic_type::TYPE_INT) {
          _pf.I2D();
      }
      _pf.DUP64();
  } else {
      _pf.DUP32();
  }
  
  node->lvalue()->accept(this, lvl + 2); // where to store the value

  if (node->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.STDOUBLE(); // store the value at address
  else 
      _pf.STINT();
  
}



//---------------------------------------------------------------------------

void m19::postfix_writer::do_evaluation_node(m19::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.TRASH(node->argument()->type()->size());
  //exit(1)
}

void m19::postfix_writer::do_print_node(m19::print_node * const node, int lvl) {
    std::cout << "println" << std::endl;
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT || node->argument()->type()->name() == basic_type::TYPE_POINTER) {
    _functions_to_declare.insert("printi");  
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _functions_to_declare.insert("prints");
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _functions_to_declare.insert("printd");
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value's address
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  
  if (node->newline()) {
    _functions_to_declare.insert("println");
    _pf.CALL("println"); // print a newline
  }
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_read_node(m19::read_node * const node, int lvl) {
    //ver assert

}

/*
void m19::postfix_writer::do_apply_node(m19::apply_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    os() << " ;; before apply" << std::endl;
    int testslbl = ++_lbl;
    int endlbl= ++_lbl;
    
    node->lowIndex()->accept(this, lvl);
    
    std::shared_ptr<m19::symbol> symbol = std::make_shared <m19::symbol> (1, node->lowIndex()->type(), "" +node->lineno(), true, false);

    _offset -= node->lowIndex()->type()->size();
    int offset = _offset;
    symbol->set_offset(offset);
    
    _pf.LOCAL(symbol->offset());
    _pf.STINT();

    _functions_to_declare.insert("printi");
    _pf.ALIGN();
    _pf.LABEL(mklbl(testslbl));
    _pf.LOCAL(symbol->offset());
    _pf.LDINT();
    node->upperIndex()->accept(this, lvl);
    _pf.LE();
    _pf.JZ(mklbl(endlbl));

   
    _pf.LOCAL(symbol->offset());
    _pf.LDINT();
    _pf.INT(2);
    _pf.SHTL();
    node->vector()->accept(this, lvl);
    _pf.LDINT();
    _pf.ADD();
    _pf.LDINT();
    _pf.CALL("printi");

    _pf.CALL(node->identifier());
    _pf.TRASH(4);
    
    
    _pf.LOCAL(symbol->offset());
    _pf.LDINT();
    _pf.DUP32();
    _pf.INT(1);
    _pf.ADD();
    
    _pf.LOCAL(symbol->offset());
    _pf.STINT();
    _pf.TRASH(4);

    // _pf.CALL("printi");
    
    _pf.JMP(mklbl(testslbl));
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(endlbl));
    os() << " ;; after apply" << std::endl;
    }


//---------------------------------------------------------------------------

*/
void m19::postfix_writer::do_apply_node(m19::apply_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    
    int testlbl = ++_lbl, endlbl = ++_lbl;
    _offset -= node->lowIndex()->type()->size();
    int offset = _offset;
    
    //initializar
    node->lowIndex()->accept(this, lvl);
    _pf.LOCAL(offset);
    _pf.STINT();
    
    //comecar a condicao
    _pf.ALIGN();
    _pf.LABEL(mklbl(testlbl));
    
    _pf.LOCAL(offset);
    _pf.LDINT();
    node->upperIndex()->accept(this, lvl);
    _pf.LE();
    _pf.JZ(mklbl(endlbl));
    
    //chamar a instrucao

    _pf.LOCAL(offset);
    _pf.LDINT();
    
    if (node->vector()->type()->subtype()->name() == basic_type::TYPE_DOUBLE) {
        _pf.INT(3);
    }
    else {
        _pf.INT(2);
    }
    _pf.SHTL();
    node->vector()->accept(this, lvl);
    _pf.LDINT();
    _pf.ADD();
    
    if (node->vector()->type()->subtype()->name() == basic_type::TYPE_DOUBLE) {
        _pf.LDINT();
    }
    else {
        _pf.LDDOUBLE();
    }
    
    _pf.CALL(node->identifier());
    if (node->vector()->type()->subtype()->name() == basic_type::TYPE_DOUBLE)
        _pf.TRASH(8);
    else
        _pf.TRASH(4);
    
     //incrementar
    _pf.LOCAL(offset);
    _pf.LDINT();
    _pf.DUP32();
    _pf.INT(1);
    _pf.ADD();
    _pf.LOCAL(offset);
    _pf.STINT();
    _pf.JMP(mklbl(testlbl));
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(endlbl)); 
}
    
    
//---------------------------------------------------------------------------


void m19::postfix_writer::do_for_node(m19::for_node * const node, int lvl) {
  _symtab.push();
  
 _forCondition.push(++_lbl);
 _forStep.push( ++_lbl);
 _forEnd.push(++_lbl);
      
  if (node->init()) node->init()->accept(this, lvl + 4);
  
  if  (node->condition()) {
       size_t i = 0;
       for (; i < node->condition()->size() - 1; i++)
            node->condition()->node(i)->accept(this, lvl);
       
       cdk::expression_node *cond = dynamic_cast<cdk::expression_node*>(node->condition()->node(i));
       _pf.LABEL(mklbl(_forCondition.top()));
       cond->accept(this, lvl + 4);
       _pf.JZ(mklbl(_forEnd.top()));
  }
  
  _symtab.push();
  node->instr()->accept(this, lvl + 4);
  _symtab.pop();
  
  if (node->step()) {
      _pf.LABEL(mklbl(_forStep.top()));
      node->step()->accept(this, lvl + 4);
  }
  
  _pf.JMP(mklbl(_forCondition.top()));
  
  _pf.LABEL(mklbl(_forEnd.top()));
  
  _forCondition.pop();
  _forStep.pop(); 
  _forEnd.pop();
 
  _symtab.pop();
  
  
  //fix
  
  /*ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  _pf.LABEL(mklbl(lbl1 = ++_lbl));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl2 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));*/
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_continue_node(m19::continue_node * const node, int lvl) {
  if (_forEnd.size())
      _pf.JMP(mklbl(_forStep.top()));
  else
      error(node->lineno(), "continue outside for");
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_break_node(m19::break_node * const node, int lvl) {
  if (_forEnd.size())
      _pf.JMP(mklbl(_forEnd.top()));
  else
      error(node->lineno(), "break outside for");  
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_return_node(m19::return_node * const node, int lvl) {
    //std::cout << "ret node " << _return << std::endl;
    if (_hasFinalSection) {
        if (_inFinalSection)
            _pf.JMP(mklbl(_return));
        else 
            _pf.JMP(mklbl(_finalSection));
    } else 
        _pf.JMP(mklbl(_return));
  
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_ReturnOperation() {
   if (_function->type()->name() != basic_type::TYPE_VOID) {
        _pf.LOCAL(-_function->type()->size());
        if (_function->type()->name() == basic_type::TYPE_DOUBLE) {
            _pf.LDDOUBLE();
            _pf.STFVAL64();
        }
        else {
            _pf.LDINT();
            _pf.STFVAL32();
        }
        
   }

   _pf.LEAVE();
   _pf.RET();
    
  
}


//---------------------------------------------------------------------------

void m19::postfix_writer::do_block_node(m19::block_node * const node, int lvl) {
  if (node->declarations()) node->declarations()->accept(this, lvl + 2);
  if (node->instructions()) node->instructions()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_address_of_node(m19::address_of_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    node->lvalue()->accept(this, lvl + 2);
}


//---------------------------------------------------------------------------

void m19::postfix_writer::do_indexing_node(m19::indexing_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    
    node->index()->accept(this, lvl);
    
    if (node->base()) {
        if (node->base()->type()->subtype()->name() == basic_type::TYPE_DOUBLE) {
            _pf.INT(3);
        }
        else
            _pf.INT(2);
        _pf.SHTL();
        node->base()->accept(this, lvl);
        _pf.ADD();
    } else {
        
         if (_function->type()->subtype()->name() == basic_type::TYPE_DOUBLE)
            _pf.INT(3);
        else
            _pf.INT(2);       
        _pf.SHTL();
        _pf.LOCAL(-_function->type()->size());
        _pf.LDINT();
        _pf.ADD();
    }
    
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_memory_alloc_node(m19::memory_alloc_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
        
    node->argument()->accept(this, lvl);
    
    if (node->type()->subtype()->name() == basic_type::TYPE_DOUBLE) {
        _pf.INT(3);
    }
    else 
        _pf.INT(2);
    
    _pf.SHTL();
    _pf.ALLOC();
    _pf.SP(); //put base pointer in stack
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_variable_declaration_node(m19::variable_declaration_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  
  const std::string &id = node->name();
  int offset = 0, typesize = node->type()->size();
  
  if (_inFunctionBody) {
      _offset -= typesize;
      offset = _offset;
  } else if (_inFunctionArgs) {
      offset = _offset;
      _offset += typesize;
  } else {
      offset = 0; //global
  }
  
  std::shared_ptr<m19::symbol> symbol = new_symbol();
  if (symbol) {
      symbol->set_offset(offset);
      //reset_new_symbol();
  }
  
  if (_inFunctionBody) {
      //local variables then no action is needed
      if (node->initializer()) {
          node->initializer()->accept(this, lvl);
          if (node->type()->name() == basic_type::TYPE_DOUBLE) {
              if (node->initializer()->type()->name() == basic_type::TYPE_INT)
                  _pf.I2D();
              _pf.LOCAL(symbol->offset());
              _pf.STDOUBLE();
          } else {
              _pf.LOCAL(symbol->offset());
              _pf.STINT();
          }
      }
  } else {
      if (!_function) {
          if (node->initializer() == nullptr) {
              _pf.BSS();
              _pf.ALIGN();
              _pf.LABEL(id);
              _pf.SALLOC(typesize);
          } else {              
              if (node->type()->name() == basic_type::TYPE_INT || node->type()->name() == basic_type::TYPE_DOUBLE || node->type()->name() == basic_type::TYPE_POINTER) {
                  _pf.DATA();
                  _pf.ALIGN();
                  _pf.LABEL(id);
 
                  if (node->type()->name() == basic_type::TYPE_INT || node->type()->name() == basic_type::TYPE_POINTER) 
                      node->initializer()->accept(this, lvl);
                  else if (node->type()->name() == basic_type::TYPE_DOUBLE) {
                      if (node->initializer()->type()->name() == basic_type::TYPE_DOUBLE) 
                          node->initializer()->accept(this, lvl);
                      else if (node->initializer()->type()->name() == basic_type::TYPE_INT) {
                          cdk::integer_node *d = dynamic_cast<cdk::integer_node*>(node->initializer());
                          cdk::double_node ddi(d->lineno(), d->value());
                          ddi.accept(this, lvl);
                      } else {
                          std::cerr << node->lineno() << ": '" << id << "' has bad initializer for real value\n";
                          _errors = true;
                      }
                          
                  }
              } else if (node->type()->name() == basic_type::TYPE_STRING) {
                  _pf.DATA();
                  _pf.ALIGN();
                  _pf.LABEL(id);
                  node->initializer()->accept(this, lvl);
              } else { 
                  std::cerr << node->lineno() << ": '" << id << "' has unexpected initializer\n";
                  _errors = true;
              }
          }
      }
  }
  
  
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_function_declaration_node(m19::function_declaration_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    
    if (_inFunctionBody || _inFunctionArgs) {
        error (node->lineno(), "cannot declare function in body or in arguments");
        return;
    }
    
    
    if (!new_symbol()) return;
    _functions_to_declare.insert(node->identifier()); //insere na declare o nome da func
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_function_definition_node(m19::function_definition_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    
    if (_inFunctionBody || _inFunctionArgs) {
        error (node->lineno(), "cannot define function in body or in arguments");
        return;
    }
    
    
    _function = new_symbol();
    _functions_to_declare.erase(_function->name());
    //reset_new_symbol();
    
    _offset = 8; // prepare for args and return value
    _symtab.push(); // scope of args
    if (node->arguments()) {
        _inFunctionArgs = true;
        for (size_t ix = 0; ix < node->arguments()->size(); ix++) {
            cdk::basic_node *arg = node->arguments()->node(ix);
            if (arg == nullptr) break;
            arg->accept(this, 0);
        }
        _inFunctionArgs = false;
    }
    
    _pf.TEXT();
    _pf.ALIGN();
    if (node->qualifier() == 1) _pf.GLOBAL(_function->name(), _pf.FUNC());
    _pf.LABEL(_function->name());
    
    frame_size_calculator calc(_compiler, _symtab);
    node->accept(&calc, lvl);
    _pf.ENTER(calc.localsize()); //size reserved for local vars
    
    _return = ++_lbl;
    _inFunctionBody = true;
    
    if (!node->literal()) {
        if (_function->type()->name() == basic_type::TYPE_INT || 
            _function->type()->name() == basic_type::TYPE_POINTER) {
            _pf.INT(0);
            _pf.LOCAL(-_function->type()->size());
            _pf.STINT(); 
        }
    } else {
        node->literal()->accept(this, lvl + 2);
        
        if (_function->type()->name() == basic_type::TYPE_DOUBLE && node->literal()->type()->name() == basic_type::TYPE_INT)
            _pf.I2D();
        
        _pf.LOCAL(-_function->type()->size());
        if (_function->type()->name() == basic_type::TYPE_DOUBLE)
            _pf.STDOUBLE();
        else
            _pf.STINT();
    }
    
    _offset = -_function->type()->size();
    
    os() << " ;; before body " << std::endl;
    node->body()->accept(this, lvl + 4);
    os() << " ;; after body " << std::endl;
    
    _inFunctionBody = false;
    _symtab.pop();
    
    /*if (node->identifier() == "m19") {
        _pf.INT(0);
        _pf.STFVAL32();
    }*/
    
    _pf.LABEL(mklbl(_return)); 
    do_ReturnOperation();
    
    if (node->identifier() == "m19") {
        for (std::string s: _functions_to_declare)
            _pf.EXTERN(s);
    
        
    }
  
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_function_call_node(m19::function_call_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  os() << " ;; func call" << std::endl;
  size_t argsSize = 0;

  const std::string &id = (node->identifier() == "@") ? _function->name() : node->identifier();
  std::shared_ptr<m19::symbol> function = _symtab.find(id);
  std::vector<unsigned long int> types = function->argsType();


  if (node->arguments()) { 
      for (int ax = node->arguments()->size() - 1; ax >= 0; ax--) {
          cdk::expression_node *arg = dynamic_cast<cdk::expression_node*>(node->arguments()->node(ax));
          arg->accept(this, lvl + 2);
          if (types[ax] == basic_type::TYPE_DOUBLE && arg->type()->name() == basic_type::TYPE_INT) {
              _pf.I2D();
              arg->type(new basic_type(8, basic_type::TYPE_DOUBLE));
          }
          argsSize += arg->type()->size();
      }
  }
  
  _pf.CALL(id);
  
  if (argsSize != 0) _pf.TRASH(argsSize);
  
  if (function->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.LDFVAL64();
  else
      _pf.LDFVAL32();
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_body_node(m19::body_node * const node, int lvl) {
    //_symtab.push(); //for body local vars
    _hasFinalSection = (bool) node->final_section();
    _finalSection = ++_lbl;
     
    if (node->initial_section()) node->initial_section()->accept(this, lvl + 2);
    if (node->sections()) node->sections()->accept(this, lvl + 2);
    if (node->final_section()) node->final_section()->accept(this, lvl + 2);
   // _symtab.pop();
  
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_initial_section_node(m19::initial_section_node * const node, int lvl) {
    _inFinalSection = false;
    node->block()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_section_node(m19::section_node * const node, int lvl) {
    _inFinalSection = false;
    _symtab.push(); //for body local vars
    
    if (node->exclusive()) {
        int lbl1;
        if (node->expression()) {
            node->expression()->accept(this, lvl + 2);
            _pf.JZ(mklbl(lbl1 = ++_lbl));
        }
        node->block()->accept(this, lvl + 2);
        if (_hasFinalSection) _pf.JMP(mklbl(_finalSection));
        else _pf.JMP(mklbl(_return));
        _pf.LABEL(mklbl(lbl1));
    } 
    else if (node->inclusive()) {
        int lbl1;
        if (node->expression()) {
            node->expression()->accept(this, lvl + 2);
            _pf.JZ(mklbl(lbl1 = ++_lbl));
        } 
        node->block()->accept(this, lvl + 2);
        _pf.LABEL(mklbl(lbl1));
    }
    else {
       node->block()->accept(this, lvl + 2); 
    }
  
    _symtab.pop();
}


//---------------------------------------------------------------------------

void m19::postfix_writer::do_final_section_node(m19::final_section_node * const node, int lvl) {
    _inFinalSection = true;
    _pf.LABEL(mklbl(_finalSection));
    
    _symtab.push(); //for final section local vars
    node->block()->accept(this, lvl + 2);
    _symtab.pop();
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_if_node(m19::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void m19::postfix_writer::do_if_else_node(m19::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}
