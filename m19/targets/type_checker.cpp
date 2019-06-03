#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void m19::type_checker::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
      node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void m19::type_checker::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void m19::type_checker::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}

void m19::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() == basic_type::TYPE_INT)
      node->type(new basic_type(4, basic_type::TYPE_INT));
  else if ( node->argument()->type()->name() == basic_type::TYPE_UNSPEC) {
      node->type(new basic_type(4, basic_type::TYPE_INT));
      node->argument()->type(new basic_type(4, basic_type::TYPE_INT));
  } else
      throw std::string("wrong type in unary logical expression");
      
}

//---------------------------------------------------------------------------

void m19::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void m19::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void m19::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

void m19::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl);
  if (node->argument()->type()->name() == basic_type::TYPE_INT)
      node->type(node->argument()->type());
  else
      throw std::string("integer expected");
}

void m19::type_checker::do_identity_node(m19::identity_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl);
  if (node->argument()->type()->name() == basic_type::TYPE_INT)
      node->type(node->argument()->type());
  else
      throw std::string("integer expected");
}

//---------------------------------------------------------------------------
void m19::type_checker::do_IntOnlyExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
      throw std::string("integer expression expected in binary operator (left)");
  
  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
      throw std::string("integer expression expected in binary operator (right)");
  
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------
void m19::type_checker::do_ScalarLogicalExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
      throw std::string("integer expression expected in binary logical expression (left)");
  
  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
      throw std::string("integer expression expected in binary logical expression (right)");
  
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void m19::type_checker::do_BooleanLogicalExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
      throw std::string("integer expression expected in binary expression");
  
  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
      throw std::string("integer expression expected in binary expression");
  
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void m19::type_checker::do_GeneralLogicalExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  
  if (node->left()->type()->name() != node->right()->type()->name())
      throw std::string("same type expected on both sides of equality operator");
  
  node->type(new basic_type(4, basic_type::TYPE_INT));
}



//---------------------------------------------------------------------------
      
void m19::type_checker::do_IDExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  
  if (node->left()->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else if (node->left()->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_INT)
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_INT)
      node->type(new basic_type(4, basic_type::TYPE_INT));
  else if (node->left()->type()->name() == basic_type::TYPE_UNSPEC && node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
      node->type(new basic_type(4, basic_type::TYPE_INT));
      node->left()->type(new basic_type(4, basic_type::TYPE_INT));
      node->right()->type(new basic_type(4, basic_type::TYPE_INT));
  } else 
      throw std::string("wrong types in binary expression");
  
}  

//---------------------------------------------------------------------------
void m19::type_checker::do_PIDExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  
  
  if (node->left()->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else if (node->left()->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_INT)
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else if (node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_INT) {
      node->type(new basic_type(4, basic_type::TYPE_POINTER));
      node->type()->_subtype = new basic_type(node->left()->type()->subtype()->size(), node->left()->type()->subtype()->name());
  }
  else if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_POINTER) {
      node->type(new basic_type(4, basic_type::TYPE_POINTER));
      node->type()->_subtype = new basic_type(node->right()->type()->subtype()->size(), node->right()->type()->subtype()->name());
  }
  else if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_INT)
      node->type(new basic_type(4, basic_type::TYPE_INT));
  else if (node->left()->type()->name() == basic_type::TYPE_UNSPEC && node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
      node->type(new basic_type(4, basic_type::TYPE_INT));
      node->left()->type(new basic_type(4, basic_type::TYPE_INT));
      node->right()->type(new basic_type(4, basic_type::TYPE_INT));
  } else 
      throw std::string("wrong types in binary expression (pointer)");
  
}      
      

void m19::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  do_PIDExpression(node, lvl);
}
void m19::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_PIDExpression(node, lvl);
}
void m19::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_IDExpression(node, lvl);
}
void m19::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  do_IDExpression(node, lvl);
}
void m19::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_IntOnlyExpression(node, lvl);
}
void m19::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_ScalarLogicalExpression(node, lvl);
}
void m19::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
   do_ScalarLogicalExpression(node, lvl);
}
void m19::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
   do_ScalarLogicalExpression(node, lvl);
}
void m19::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
   do_ScalarLogicalExpression(node, lvl);
}
void m19::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
   do_GeneralLogicalExpression(node, lvl);
}
void m19::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_GeneralLogicalExpression(node, lvl);
}

void m19::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
  do_BooleanLogicalExpression(node, lvl);
}
void m19::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
  do_BooleanLogicalExpression(node, lvl);
}

//---------------------------------------------------------------------------

void m19::type_checker::do_variable_node(cdk::variable_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  
  if (id != "@") {
    std::shared_ptr<m19::symbol> symbol = nullptr;
    
    symbol = _symtab.find(id);

    if (symbol != nullptr) {
        node->type(symbol->type());
    } else {
        throw id;
    }
  } else 
      node->type(_function->type());
}

void m19::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}


/*
void m19::type_checker::do_check_pointer_level(basic_type *p, basic_type *q) {
    for (; p != nullptr; p = p->subtype())
        if (p->name() != q->name()) throw std::string ("wrong assignment to pointer");
}
*/
    
void m19::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->lvalue()->accept(this, lvl + 4);
  node->rvalue()->accept(this, lvl + 4);
  
  if (node->lvalue()->type()->name() == basic_type::TYPE_INT) {
      if (node->rvalue()->type()->name()==basic_type::TYPE_INT) {
          node->type(new basic_type(4, basic_type::TYPE_INT));
      } else if (node->rvalue()->type()->name()==basic_type::TYPE_UNSPEC) {
          node->type(new basic_type(4, basic_type::TYPE_INT));
          node->rvalue()->type(new basic_type(4, basic_type::TYPE_INT));
      } else {
          throw std::string("wrong assignment to integer");
      }
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_POINTER) {
      if (node->rvalue()->type()->name()==basic_type::TYPE_POINTER) { 
          //do_check_pointer_level(node->lvalue()->type(), node->rvalue()->type());
          if (node->rvalue()->type()->subtype()->name() == basic_type::TYPE_UNSPEC) {
            node->rvalue()->type()->_subtype = new basic_type(node->lvalue()->type()->subtype()->size(), 
                                                              node->lvalue()->type()->subtype()->name());
          }
          node->type(new basic_type(4, basic_type::TYPE_POINTER));
      } else if (node->rvalue()->type()->name()==basic_type::TYPE_INT) {
          cdk::integer_node *var = dynamic_cast<cdk::integer_node*>(node->rvalue());
          if (var->value() == 0)
            node->type(new basic_type(4, basic_type::TYPE_POINTER));
          else 
              throw std::string("wrong assignment to pointer");      
      } else if (node->rvalue()->type()->name() == basic_type::TYPE_UNSPEC){
          node->type(new basic_type(4, basic_type::TYPE_ERROR));
          node->rvalue()->type(new basic_type(4, basic_type::TYPE_ERROR));
      } else
          throw std::string("wrong assignment to pointer");      
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE) {
      if (node->rvalue()->type()->name()==basic_type::TYPE_DOUBLE ||
          node->rvalue()->type()->name()==basic_type::TYPE_INT) {
          node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
      } else if (node->rvalue()->type()->name()==basic_type::TYPE_UNSPEC) {
          node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
          node->rvalue()->type(new basic_type(8, basic_type::TYPE_DOUBLE));
      } else {
          throw std::string("wrong assignment to real");
      }
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_STRING) {
      if (node->rvalue()->type()->name()==basic_type::TYPE_STRING) {
          node->type(new basic_type(4, basic_type::TYPE_STRING));
      } else if (node->rvalue()->type()->name()==basic_type::TYPE_UNSPEC) {
          node->type(new basic_type(4, basic_type::TYPE_STRING));
          node->rvalue()->type(new basic_type(4, basic_type::TYPE_STRING));
      } else {
          throw std::string("wrong assignment to string");
      }
  }
  else {
      throw std::string("wrong types in assignment");
  }
  
}


//---------------------------------------------------------------------------


void m19::type_checker::do_evaluation_node(m19::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void m19::type_checker::do_print_node(m19::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() == basic_type::TYPE_VOID) {
      throw std::string("wrong type in print argument");
  }
}

//---------------------------------------------------------------------------

void m19::type_checker::do_read_node(m19::read_node * const node, int lvl) {
  node->type(new basic_type(0, basic_type::TYPE_UNSPEC));
}

//---------------------------------------------------------------------------

void m19::type_checker::do_for_node(m19::for_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void m19::type_checker::do_return_node(m19::return_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void m19::type_checker::do_continue_node(m19::continue_node * const node, int lvl) {
    //EMPTY
}


//---------------------------------------------------------------------------

void m19::type_checker::do_break_node(m19::break_node * const node, int lvl) {
    //EMPTY
}



//---------------------------------------------------------------------------


void m19::type_checker::do_apply_node(m19::apply_node * const node, int lvl) {
    node->lowIndex()->accept(this, lvl + 2);
    node->upperIndex()->accept(this, lvl + 2);
    node->vector()->accept(this, lvl + 2);
    
    std::shared_ptr<m19::symbol> symbol = _symtab.find(node->identifier());
    
    if (symbol) {
        if (symbol->forward())
            throw std::string("wrong num of args");
        
        if (!symbol->isFunction())
            throw std::string("not a function");
        
        if (symbol->sizeOfArgs() != 1)
            throw std::string("wrong num of args");
        
        std::vector<unsigned long int> args = symbol->argsType();
        
        if (args[0] != node->vector()->type()->subtype()->name()) 
            throw std::string("wrong type of args");
    }
    
}

//---------------------------------------------------------------------------

void m19::type_checker::do_block_node(m19::block_node * const node, int lvl) {
    if (node->declarations())
        node->declarations()->accept(this, lvl + 2);
    if (node->instructions())
        node->instructions()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void m19::type_checker::do_indexing_node(m19::indexing_node * const node, int lvl) {
  ASSERT_UNSPEC;
  
  node->index()->accept(this, lvl + 2);
  if (node->index()->type()->name() != basic_type::TYPE_INT)
      throw std::string("integer expression  expected in index left-value");
  
  if (node->base()) {
      node->base()->accept(this, lvl + 2);
      if (node->base()->type()->name() != basic_type::TYPE_POINTER)
          throw std::string("pointer expression  expected in index left-value");
      node->type(new basic_type(node->base()->type()->subtype()->size(), 
                                    node->base()->type()->subtype()->name()));
  } else {
      if (_function->type()->name() != basic_type::TYPE_POINTER)
          throw std::string("return pointer expression  expected in index left-value");
      node->type(new basic_type(_function->type()->subtype()->size(), 
                                    _function->type()->subtype()->name()));
  }
}
//---------------------------------------------------------------------------

void m19::type_checker::do_address_of_node(m19::address_of_node * const node, int lvl) {
  ASSERT_UNSPEC;
  if (node->lvalue()) {
    node->lvalue()->accept(this, lvl + 2);
    std::cout << "addr: " << node->lvalue()->type()->subtype()->name() << std::endl;
    if (node->lvalue()->type()->name() == basic_type::TYPE_INT || 
        node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE || 
        node->lvalue()->type()->name() == basic_type::TYPE_STRING || 
        node->lvalue()->type()->name() == basic_type::TYPE_POINTER ) {
        node->type(new basic_type(4, basic_type::TYPE_POINTER));
        node->type()->_subtype = new basic_type(node->lvalue()->type()->size(), node->lvalue()->type()->name());
    } else {
        throw std::string("wrong type in unary expression");
    }
  } else {
      if (!_function)
        throw std::string("outside function: trying to access @"); 
      
  }
}

//---------------------------------------------------------------------------

void m19::type_checker::do_memory_alloc_node(m19::memory_alloc_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
      throw std::string("integer expression expected in allocation expression");
  
  basic_type *mytype = new basic_type(4, basic_type::TYPE_POINTER);
  mytype->_subtype = new basic_type(0, basic_type::TYPE_UNSPEC);
  node->type(mytype);
}

//---------------------------------------------------------------------------

void m19::type_checker::do_variable_declaration_node(m19::variable_declaration_node * const node, int lvl) {
  
  if (node->initializer() != nullptr) {
      node->initializer()->accept(this, lvl + 2);
      
      if (node->type()->name() == basic_type::TYPE_INT) {
          if (node->initializer()->type()->name() != basic_type::TYPE_INT)
              throw std::string("wrong type for initializer (integer expected).");
      } else if (node->type()->name() == basic_type::TYPE_DOUBLE) {
          if (node->initializer()->type()->name() != basic_type::TYPE_DOUBLE
              && node->initializer()->type()->name() != basic_type::TYPE_INT)
              throw std::string("wrong type for initializer (integer or double expected).");
      } else if (node->type()->name() == basic_type::TYPE_STRING) {
          if (node->initializer()->type()->name() != basic_type::TYPE_STRING)
              throw std::string("wrong type for initializer (string expected).");
      } else if (node->type()->name() == basic_type::TYPE_POINTER) { //fix
          if (node->initializer()->type()->name() != basic_type::TYPE_POINTER && node->initializer()->type()->name() != basic_type::TYPE_INT)
              throw std::string("wrong type for initializer (pointer expected).");
          if (node->initializer()->type()->name() == basic_type::TYPE_INT) {
               cdk::integer_node *var = dynamic_cast<cdk::integer_node*>(node->initializer());
               if (var->value() == 0) {
                    node->initializer()->type(new basic_type(4, basic_type::TYPE_POINTER));
                    node->initializer()->type()->_subtype = new basic_type(0, basic_type::TYPE_UNSPEC);
               }
               else 
                    throw std::string("wrong type for initializer (nullpointer expected)"); 
          }
          if (node->initializer()->type()->subtype()->name() == basic_type::TYPE_UNSPEC) {
              node->initializer()->type()->_subtype = new basic_type(node->type()->subtype()->size(), node->type()->subtype()->name());
          }
      } else {
          throw std::string("unknown type for initializer.");
      }
  }
  
  const std::string &id = node->name();
  
  std::shared_ptr<m19::symbol> symbol = std::make_shared <m19::symbol> (node->qualifier(),node->type(), id, (bool)node->initializer(), false);
  if (_symtab.insert(id, symbol)){
      _parent->set_new_symbol(symbol); 
  } else {
      throw std::string("variable '" + id + "' redeclared");
  }
  //node->initializer()->type(node->type());
  
}


//---------------------------------------------------------------------------

void m19::type_checker::do_function_insert_types(cdk::sequence_node * const args, std::shared_ptr<m19::symbol> function, int lvl) {
    size_t numArgs = args->size();

    for (size_t i = 0; i < numArgs; i++) {
        m19::variable_declaration_node *arg_var = dynamic_cast<m19::variable_declaration_node*>(args->node(i));
        unsigned long int type = arg_var->type()->name();
        function->insertArgType(type);
    }
}

//---------------------------------------------------------------------------

void m19::type_checker::do_function_check_types(size_t numArgs,  std::shared_ptr<m19::symbol> previous,  std::shared_ptr<m19::symbol> function, int lvl) {
    if (previous->sizeOfArgs() != numArgs)
        throw std::string("conflicting declaration for'" + function->name() + "' wrong num of args");
    else {
        std::vector<unsigned long int> functionTypes = function->argsType();
        std::vector<unsigned long int> previousTypes = previous->argsType();
        
        for (size_t i = 0; i < numArgs; i++) {
            if (functionTypes[i] != previousTypes[i])
                throw std::string("conflicting declaration for'" + function->name() + "' wrong type of args");
        }
    }
}
    
    
    
//---------------------------------------------------------------------------



void m19::type_checker::do_function_declaration_node(m19::function_declaration_node * const node, int lvl) {
    std::string id;
    
    if (node->identifier() == "m19")
        id = "_main";
    else if (node->identifier() == "_main")
        id = "._main";
    else 
        id = node->identifier();
    
    std::shared_ptr<m19::symbol> function = std::make_shared<m19::symbol>(node->qualifier(), node->type(), id, false, true, true);
    std::shared_ptr<m19::symbol> previous = _symtab.find(function->name());
    
    if (node->arguments()) {
        node->arguments()->accept(this, lvl + 2);
        do_function_insert_types(node->arguments(), function, lvl);
    }
    
    if (previous) 
        do_function_check_types(node->arguments()->size(), previous, function, lvl); 
    else {
        _symtab.insert(function->name(), function);
        _parent->set_new_symbol(function);
    }
}

//---------------------------------------------------------------------------

void m19::type_checker::do_function_definition_node(m19::function_definition_node * const node, int lvl) {
    std::string id;
    
    if (node->identifier() == "m19")
        id = "_main";
    else if (node->identifier() == "_main")
        id = "._main";
    else 
        id = node->identifier();

    
    std::shared_ptr<m19::symbol> function = std::make_shared<m19::symbol>(node->qualifier(), node->type(), id, (bool)node->literal(), true);
    function->set_offset(-node->type()->size());
    
    //literal
     if (node->type()->name() != basic_type::TYPE_VOID ) {
         if (node->literal() != nullptr ) {
            node->literal()->accept(this, lvl + 2);
            
            if (node->type()->name() == basic_type::TYPE_INT) {
                if (node->literal()->type()->name() != basic_type::TYPE_INT)
                    throw std::string("wrong type for literal (integer expected).");
            } else if (node->type()->name() == basic_type::TYPE_DOUBLE) {
                if (node->literal()->type()->name() != basic_type::TYPE_DOUBLE
                    && node->literal()->type()->name() != basic_type::TYPE_INT)
                    throw std::string("wrong type for literal (integer or double expected).");
            } else if (node->type()->name() == basic_type::TYPE_STRING) {
                if (node->literal()->type()->name() != basic_type::TYPE_STRING)
                    throw std::string("wrong type for literal (string expected).");
            } else if (node->type()->name() == basic_type::TYPE_POINTER) { //fix
                if (node->literal()->type()->name() != basic_type::TYPE_POINTER)
                    throw std::string("wrong type for literal (pointer expected).");
            } else {
                throw std::string("unknown type for literal.");
            }
         }
     }
     
    if (node->arguments()) {
        //node->arguments()->accept(this, lvl + 2);
        do_function_insert_types(node->arguments(), function, lvl);
    } 
    
    
    
    
    std::shared_ptr<m19::symbol> previous = _symtab.find(function->name());
    if (previous) {
       if (node->arguments()) do_function_check_types(node->arguments()->size(), previous, function, lvl); 
       if (previous->forward() 
           && ((previous->qualifier() == 0 && node->qualifier() == 0) || (previous->qualifier() == 1 && node->qualifier() ==  1) || (previous->qualifier() == 2 && node->qualifier() ==  2))) {
           _symtab.replace(function->name(), function);
           _parent->set_new_symbol(function);
  
       } else {
           throw std::string("conflicting definition for '" + function->name() + "'");
       }
    } else {
       _symtab.insert(function->name(), function);
       _parent->set_new_symbol(function); 

    }
       
}

//---------------------------------------------------------------------------

void m19::type_checker::do_function_call_node(m19::function_call_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->identifier();
  std::shared_ptr<m19::symbol> symbol = nullptr;
  
  if (id == "@")
      symbol = _symtab.find(_function->name());
  else
      symbol = _symtab.find(id);
  
  if (symbol == nullptr) throw std::string("symbol'"+ id + "' is undeclared.");
  if (!symbol->isFunction()) throw std::string("symbol'"+ id + "' is not a function.");
  node->type(symbol->type());
  
  std::vector<unsigned long int> previousTypes = symbol->argsType();
  
  if (node->arguments()) {
      node->arguments()->accept(this, lvl + 4);
      if (symbol->sizeOfArgs() != node->arguments()->size())
           throw std::string("conflicting call for'" + id + "' wrong num of args");
          
      for (size_t i = 0; i < node->arguments()->size(); i++) {
        cdk::expression_node *arg = dynamic_cast<cdk::expression_node*>(node->arguments()->node(i));
        unsigned long int type = arg->type()->name();
        if (type != previousTypes[i] && !(previousTypes[i] == basic_type::TYPE_DOUBLE && type == basic_type::TYPE_INT)) {
            throw std::string("conflicting call for'" + id + "' wrong type of args");
        }
      }
        
  }
}



//---------------------------------------------------------------------------

void m19::type_checker::do_body_node(m19::body_node * const node, int lvl) {
  
}

//---------------------------------------------------------------------------

void m19::type_checker::do_section_node(m19::section_node * const node, int lvl) {
  
}

//---------------------------------------------------------------------------

void m19::type_checker::do_initial_section_node(m19::initial_section_node * const node, int lvl) {
  
}

//---------------------------------------------------------------------------

void m19::type_checker::do_final_section_node(m19::final_section_node * const node, int lvl) {
  
}


//---------------------------------------------------------------------------

void m19::type_checker::do_if_node(m19::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  if (node->condition()->type()->name() != basic_type::TYPE_INT)
      throw std::string("expected integer condition");
}

void m19::type_checker::do_if_else_node(m19::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
    if (node->condition()->type()->name() != basic_type::TYPE_INT)
      throw std::string("expected integer condition");
}
