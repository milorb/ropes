#include "ropes.hpp"

                  // *********** Rope public *********** //

void Rope::concat(const Rope& other) {
  root->_concat(*other.root);
}

char Rope::get(int idx) {
  return root->_get_char(idx);
}

void Rope::insert_elt(char c, int idx) {

}

void Rope::print() {
  root->_print();
}

size_t Rope::size() {
  return root->k_weight;
}

                  // *********** Rope constructors *********** //

Rope::Rope(std::string& s, int max) {
    root->weave(s, max);
}

Rope::Rope(const std::string& s, int max) {
    root->weave(s, max);
}


                  // *********** Rope_t private *********** //

void Rope_t::weave(const std::string& s, int str_max) {
  if (s.size() <= str_max) {
    weight = s.size();
    k_weight = weight;
    knot.tied = true;
    knot.conts = s;
    return;
  }

  std::shared_ptr<Rope_t> self = shared_from_this();

  size_t mid = s.size() / 2;
  std::string ls(s.begin(), s.begin() + mid);
  std::string rs(s.begin() + mid, s.end());

  k_weight = s.size();
  weight = ls.size();

  right = std::make_shared<Rope_t>();
  left = std::make_shared<Rope_t>();
  
  right->weave(rs, str_max);
  left->weave(ls, str_max);

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
  Rope_t_new->k_weight = r->k_weight;

  Rope_t_new->left = copy(r->left, Rope_t_new);
  Rope_t_new->right = copy(r->right, Rope_t_new);
  return Rope_t_new;
}

                  // *********** Rope_t public *********** //

void Rope_t::_concat(const Rope_t& r) {
  auto temp = std::make_unique<Rope_t>(*this);

  if (left) {
    weight = left->k_weight;
  } else {
    std::cout << 
          "error: attempt to call concatenate on empty Rope_t" 
                                                          << std::endl;
    std::exit(1);
  }

  k_weight = k_weight + r.k_weight;
  right = std::make_shared<Rope_t>(r);

  left = std::move(temp);
}

char Rope_t::_get_char(int idx) {
  if (idx >= k_weight) {
    std::cout << 
          "error: attempt to index into invalid range" 
                                                  << std::endl;
    std::exit(1);
  }
  if (knot.tied) {
    assert(idx < knot.conts.size());
    return knot.conts[idx];
  }
  if (idx < weight) {
    return left->_get_char(idx);
  } else { 
    return right->_get_char(idx - weight);
  }
}

void Rope_t::_insert_elt(char c, int idx) {
  
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
  k_weight = 0;
  weight = 0;
}
