#ifndef ROPES_HPP
#define ROPES_HPP

#include <memory>
#include <string>
#include <cassert>
#include <iostream>
#include <list>
#include <stack>

/*
 data structure idea: ropes but all the leaf nodes are a linked list
*/

class Climber;
class Rope_t;
class Rope;

template <typename T>
struct Knot {
  bool tied = false;
  T conts;
};

class Rope_t : public std::enable_shared_from_this<Rope_t> {
private:
  // assembles tree with leaf->chars.size() <= str_max
  std::shared_ptr<Rope_t> copy(std::shared_ptr<Rope_t> r, std::weak_ptr<Rope_t> p);

public:
  Rope_t();

  void weave(const std::string& s, const int str_max,
                   std::list<std::shared_ptr<Rope_t>> l); 
  void _concat(const Rope_t& r1);
  char& _get_char(int idx);
  void _insert_elt(char c, int idx);
  void _print();
  
  std::weak_ptr<Rope_t> parent;
  std::shared_ptr<Rope_t> right;
  std::shared_ptr<Rope_t> left;

  Knot<std::string> knot;

  uint64_t weight;
};

class Rope {
public:
  Rope() {}
  Rope(std::string& s, int max);
  Rope(const std::string& s, int max);

  void concat(const Rope& other);
  void insert(int idx, char c);
  void print();
  size_t size();


  // random access O(log n)
  char& operator[](int idx) const;

private:
  std::shared_ptr<Rope_t> root = std::make_shared<Rope_t>();
  std::list<std::shared_ptr<Rope_t>> leaves;

friend class Climber;

public:

  class Climber {
  public:
    Climber() : cur(nullptr) {}
    Knot<std::string>& operator*() const {
        return cur->knot;
    }
    Knot<std::string>* operator->() const {
        return &(cur->knot);
    }

    Climber& operator++() {
        //moveToNext();
        return *this;
    }

    bool operator!=(const Climber& other) const {
        return cur != other.cur;
    }

  private:
    std::shared_ptr<Rope_t> cur;
    std::stack<std::shared_ptr<Rope_t>> path;
    
    Climber(std::shared_ptr<Rope_t> root);
  friend class Rope;
};

  Climber begin() {
    return Climber(root->left);
  }
  Climber end() { 
    return Climber(); 
  }

};

#endif