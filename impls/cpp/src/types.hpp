#pragma once

#include <cassert>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class ExceptionValue;
class FnValue;
class HashMapValue;
class IntegerValue;
class ListValue;
class SymbolValue;
class VectorValue;

class Value {
public:
  enum class Type {
    Exception,
    Fn,
    HashMap,
    Integer,
    List,
    Symbol,
    Vector,
  };

  virtual Type type() { assert(0); }
  virtual std::string inspect() { assert(0); }

  ExceptionValue *as_exception();
  FnValue *as_fn();
  HashMapValue *as_hash_map();
  IntegerValue *as_integer();
  ListValue *as_list();
  SymbolValue *as_symbol();
  VectorValue *as_vector();
};

// List value type
class ListValue : public Value {
public:
  ListValue() {}

  void push(Value *value) { m_list.push_back(value); }

  virtual Type type() { return Type::List; }
  virtual std::string inspect();

  auto begin() { return m_list.begin(); }
  auto end() { return m_list.end(); }

  bool is_empty() { return m_list.size() == 0; }
  size_t size() { return m_list.size(); }
  Value *at(size_t index) { return m_list.at(index); }

protected:
  std::vector<Value *> m_list{};
};

class VectorValue : public ListValue {
public:
  VectorValue(){};
  virtual Type type() { return Type::Vector; }
  virtual std::string inspect();

protected:
  std::vector<Value *> m_list{};
};

struct HashMapHash {
  std::size_t operator()(Value *key) const noexcept {
    return std::hash<std::string>{}(key->inspect());
  }
};
struct HashMapPred {
  constexpr bool operator()(Value *lhs, Value *rhs) const {
    return lhs == rhs; // FIXME
  }
};

// Hash map (hash table) value type
class HashMapValue : public ListValue {
public:
  HashMapValue() {}
  virtual std::string inspect();

  virtual bool operator==(const Value *);

  void set(Value *key, Value *val) { m_map[key] = val; }

  Value *get(Value *key) {
    auto search = m_map.find(key);
    if (search != m_map.end())
      return search->second;
    return nullptr;
  }

  auto begin() const { return m_map.begin(); }
  auto end() const { return m_map.end(); }
  size_t size() const { return m_map.size(); }

private:
  std::unordered_map<Value *, Value *, HashMapHash, HashMapPred> m_map;

protected:
  std::vector<Value *> m_list{};
};

// Symbol type
class SymbolValue : public Value {
public:
  SymbolValue(std::string_view str) : m_str{str} {}
  std::string str() { return m_str; }
  virtual Type type() { return Type::HashMap; }
  virtual std::string inspect(bool) { return str(); }

private:
  std::string m_str;
};

// Function pointer
using FnPtr = Value *(*)(size_t, Value **);

// Integer type
class IntegerValue : public Value {
public:
  IntegerValue(long l) : m_long{l} {}
  long to_long() { return m_long; }

private:
  long m_long{0};
};

// Function value pointer type
class FnValue : public Value {
public:
  // In
  FnValue(FnPtr fn) : m_fn{fn} {}
  // Out
  FnPtr to_fn() { return m_fn; }

private:
  FnPtr m_fn{nullptr};
};

// Exception (error) type
class ExceptionValue : public Value {
public:
  ExceptionValue(std::string message) : m_message{message} {}
  virtual Type type() { return Type::Exception; }
  virtual std::string inspect() { return "<exception" + m_message + ">"; }
  const std::string &message() { return m_message; }

private:
  std::string m_message;
};
