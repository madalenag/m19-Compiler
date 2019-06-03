#ifndef __M19_SEMANTICS_SYMBOL_H__
#define __M19_SEMANTICS_SYMBOL_H__

#include <string>
#include <vector>
#include <cdk/basic_type.h>

namespace m19 {

  class symbol {
      
    std::string _name;
    long _value; // hack!
    int _qualifier;
    basic_type *_type;
    bool _initialized;
    int _offset = 0;
    bool _function;
    bool _forward = false;
    std::vector<unsigned long int> _argsType;

  public:
    symbol(int qualifier, basic_type *type, const std::string &name, bool initialized, bool function, bool forward = false) :
       _name(name), _value(0), _qualifier(qualifier), _type(type), _initialized(initialized), _function(function), _forward(forward) {
    }

    virtual ~symbol() {
      delete _type;
    }

    basic_type *type() const {
      return _type;
    }
    const std::string &name() const {
      return _name;
    }
    long value() const {
      return _value;
    }
    long value(long v) {
      return _value = v;
    }
    int qualifier() const {
        return _qualifier;
    }
    bool isFunction() const {
        return _function;
    }
    bool isVariable() const {
        return !_function;
    }
    bool forward() const {
        return _forward;
    }
    bool global() const {
        return _offset == 0;
    }
    void set_offset(int offset) {
        _offset = offset;
    }
    int offset() const {
        return _offset;
    }
    bool initialized() const {
        return _initialized;
    }

    void insertArgType(unsigned long int type) {
        _argsType.push_back(type);
    }
    size_t sizeOfArgs() {
        return _argsType.size();
    }
    std::vector<unsigned long int> argsType() {
        return _argsType;
    }
    
  };

} // m19

#endif
