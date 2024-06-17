#pragma once

#include <cassert>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class ExceptionValue;

class Value {
public:
  enum class Type {
    Exception,
    False,
    Fn,
    HashMap,
    Integer,
    Keyword,
    List,
    Nil,
    String,
    Symbol,
    True,
    Vector,
  };

  virtual Type type() const = 0;
  virtual std::string inspect(bool print_readably = false) const = 0;

  virtual bool is_exception() const { return false; }
  virtual bool is_list() const { return false; }
  virtual bool is_listy() const { return false; }
  virtual bool is_nil() const { return false; }
  virtual bool is_true() const { return false; }

  virtual bool operator==(const Value *other) const { return this == other; }
  bool operator!=(const Value *other) const { return !(*this == other); }

  ExceptionValue *as_exception();

  const ExceptionValue *as_exception() const;
};

class ListValue : public Value {
public:
  ListValue() {}

  void push(Value *value) { m_list.push_back(value); }

  virtual Type type() const override { return Type::List; }
  virtual std::string inspect(bool print_readably = false) const override;
  virtual bool is_list() const override { return true; }
  virtual bool is_listy() const override { return true; }

  virtual bool operator==(const Value *) const override;

  auto begin() { return m_list.begin(); }
  auto end() { return m_list.end(); }

  bool is_empty() const { return m_list.size() == 0; }
  size_t size() const { return m_list.size(); }
  Value *at(size_t index) const { return m_list.at(index); }

protected:
  std::vector<Value *> m_list{};
};

class VectorValue : public ListValue {
public:
  VectorValue(){};

  virtual Type type() const override { return Type::Vector; }
  virtual std::string inspect(bool print_readably = false) const override;
  virtual bool is_list() const override { return false; }

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

class HashMapValue : public ListValue {
public:
  HashMapValue() {}
  virtual Type type() const override { return Type::HashMap; }
  virtual std::string inspect();

  virtual bool operator==(const Value *) const override;

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

class SymbolValue : public Value {
public:
  SymbolValue(std::string_view str) : m_str{str} {}
  // copy when call str
  std::string str() { return m_str; }
  bool matches(const char *str) const { return m_str == str; }
  virtual Type type() const override { return Type::Symbol; }
  virtual std::string inspect(bool) const override { return str(); }

private:
  std::string m_str;
};
