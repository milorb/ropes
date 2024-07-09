#include "ropes.hpp"

Rope::Rope(const std::string &s) {
  weave(s, 5);
}

void Rope::weave(const std::string& s, int str_max) {
  if (s.size() <= str_max) {
    knot.str = s;
    return;
  }
  
  size_t mid = s.size() / 2;
  weight = mid;
  std::string ls(s.begin(), s.begin() + mid);
  std::string rs(s.begin() + mid, s.end());

  left = new Rope(ls);
  right = new Rope(rs);
  left->parent = this;
  right->parent = this;
}

Rope::~Rope() {
  delete left;
  delete right;
}
