#include "ropes.hpp"

                  // *********** Rope public *********** //

void Rope::concat(const Rope& other) {
  auto temp = std::make_shared<Rope_t>();
  temp->left = root->left;
  temp->right = other.root->left;
  temp->weight = root->weight;
  root->left = temp;
  root->weight += other.root->weight;
}

void Rope::insert(int idx, char c) {

}

void Rope::print() {
  root->left->_print();
}

size_t Rope::size() {
  return root->weight;
}

char& Rope::operator[](int idx) const {
  return root->left->_get_char(idx);
}

                  // *********** Rope constructors *********** //

Rope::Rope(std::string& s, int max) {
    root->weight = s.size();
    root->left = std::make_shared<Rope_t>();
    root->left->weave(s, max, leaves);
}

Rope::Rope(const std::string& s, int max) {
    root->weight = s.size();
    root->left = std::make_shared<Rope_t>();
    root->left->weave(s, max, leaves);
}


                  // *********** Rope_t private *********** //

void Rope_t::weave(const std::string& s, int str_max, 
                         std::list<std::shared_ptr<Rope_t>> l) {
  
  std::shared_ptr<Rope_t> self = shared_from_this();

  if (s.size() <= str_max) {
    weight = s.size();
    knot.tied = true;
    knot.conts = s;
    l.push_back(self);
    return;
  }

  size_t mid = s.size() / 2;
  std::string ls(s.begin(), s.begin() + mid);
  std::string rs(s.begin() + mid, s.end());

  weight = ls.size();

  right = std::make_shared<Rope_t>();
  left = std::make_shared<Rope_t>();
  
  right->weave(rs, str_max, l);
  left->weave(ls, str_max, l);

  right->parent = self;
  left->parent = self;
}

std::shared_ptr<Rope_t> Rope_t::copy(
  std::shared_ptr<Rope_t> r, std::weak_ptr<Rope_t> p) {
  if (!r) {
    return nullptr;
  }
  auto Rope_t_new = std::make_shared<Rope_t>();

  Rope_t_new->parent = p;

  Rope_t_new->knot = r->knot;
  Rope_t_new->weight = r->weight;

  Rope_t_new->left = copy(r->left, Rope_t_new);
  Rope_t_new->right = copy(r->right, Rope_t_new);
  return Rope_t_new;
}

                  // *********** Rope_t public *********** //

void Rope_t::_concat(const Rope_t& r) {
  auto temp = std::make_unique<Rope_t>(*this);
  if (!left) {
    std::cout << 
          "error: attempt to call concatenate on empty Rope_t" 
                                                          << std::endl;
    std::exit(1);
  }

  right = std::make_shared<Rope_t>(r);
  left = std::move(temp);
}

char& Rope_t::_get_char(int idx) {
  // TODO : add max range
  if (idx < 0) {
    std::cout << 
          "error: attempt to index into invalid range" 
                                                  << std::endl;
    std::exit(1);
  }
  if (knot.tied) {
    if (idx >= knot.conts.size()) {
      std::cout << "idx: " << idx << " size: " << weight; 
    }
    return knot.conts[idx];
  }
  if (idx < weight) {
    return left->_get_char(idx);
  } else { 
    return right->_get_char(idx - weight);
  }
}

void Rope_t::_insert_elt(char c, int idx) {
  // idx >= k_weight || 
  if (idx < 0) {
    std::cout << 
          "error: attempt to index into invalid range" 
                                                  << std::endl;
    std::exit(1);
  }


}

void Rope_t::_print() {
  if (!knot.conts.empty()) {
    std::cout << knot.conts;
    return;
  } else {
    if (left) {
	    left->_print();
    }
    if (right) {
	    right->_print();
    }
  }
}

                  // *********** Rope_t constructors *********** //

Rope_t::Rope_t() {
  right = nullptr;
  left = nullptr;
  knot = Knot<std::string>();
  weight = 0;
}
