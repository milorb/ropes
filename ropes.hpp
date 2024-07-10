#ifndef ROPES_HPP
#define ROPES_HPP

#include <memory>
#include <string>
#include <cassert>
#include <iostream>

/*
 data structure idea: ropes but all the leaf nodes are a linked list
*/

template <typename T>
struct Knot {
  bool tied = false;
  T conts;
};

class Rope_t : public std::enable_shared_from_this<Rope_t> {
private:
  // assembles tree with leaf->chars.size() <= str_max
  std::shared_ptr<Rope_t> copy(std::shared_ptr<Rope_t> r, std::weak_ptr<Rope_t> p);

  uint64_t weight;

public:
  Rope_t();

  void weave(const std::string& s, const int str_max); 
  void _concat(const Rope_t& r1);
  char _get_char(int idx);
  void _insert_elt(char c, int idx);
  void _print();
  
  std::weak_ptr<Rope_t> parent;
  std::shared_ptr<Rope_t> right;
  std::shared_ptr<Rope_t> left;
  Knot<std::string> knot;
  size_t k_weight;
};

class Rope {
private:
  std::shared_ptr<Rope_t> root = std::make_shared<Rope_t>();;
public:
  Rope() {}
  Rope(std::string& s, int max);
  Rope(const std::string& s, int max);

  void concat(const Rope& other);
  char get(int idx);
  void insert_elt(char c, int idx);
  void print();
  size_t size();
};

#endif