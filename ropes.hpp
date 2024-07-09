#ifndef ROPES_HPP
#define ROPES_HPP

#include <memory>
#include <string>


struct Knot {
  Knot(std::string &s) : str(s) {}
// use Character for te
  std::string str;
};

class Rope {
public:
// leaf constructor
  Rope();
// primary constructor
  Rope(std::string &s) : Rope(s, std::make_shared<Rope>(this)) {};

private:
  Rope(std::string& s, std::shared_ptr<Rope> parent);
// assembles tree with leaf->chars.size() <= str_max
  void weave(std::string& s, const int str_max);

  std::shared_ptr<Rope> parent;
  std::shared_ptr<Rope> left;
  std::shared_ptr<Rope> right;
  std::shared_ptr<Knot> knot;
  uint64_t weight;
};

#endif