#ifndef ROPES_HPP
#define ROPES_HPP

#include <memory>
#include <string>

#include <iostream>

struct Knot {
  Knot() : str("") {}
  std::string str;
};

class Rope {
public: 
// leaf constructor
  Rope() : left(nullptr), right(nullptr), knot(Knot()), weight(0) {}
// primary constructorthis
  Rope(const std::string &s);
  ~Rope();

  Rope* parent;
  Rope* left;
  Rope* right;
  Knot knot;
  uint64_t weight;

private:
// assembles tree with leaf->chars.size() <= str_max
  void weave(const std::string& s, const int str_max);
};

#endif