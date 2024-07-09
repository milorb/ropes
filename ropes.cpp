#include "ropes.hpp"

Rope::Rope() {
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  knot = nullptr;
  weight = 0;
}

Rope::Rope(std::string& s, std::shared_ptr<Rope> p) {
  parent = p;
  weave(s, 5);
}

void Rope::weave(std::string& s, const int str_max) {
  if (s.empty()) {
    knot = std::make_shared<Knot>(s);
    return;
  }
  if (s.size() <= str_max) {
    weight = s.size();
    knot = std::make_shared<Knot>(s);
    return;
  } 

  size_t mid = s.size() / 2;
  weight = mid;
  std::string ls(s.begin(), s.begin() + mid);
  std::string rs(s.begin() + mid + 1, s.end() - 1);
  left = std::make_shared<Rope>(ls, std::make_shared<Rope>(this));
  right = std::make_shared<Rope>(rs, std::make_shared<Rope>(this));
}