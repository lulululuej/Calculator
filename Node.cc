#include "Node.h"
#include <iomanip>

/*
  Implement the functionality of the Node hierarchy
 */

/**** Number ****/
Number::Number(double value) 
  :value{value} {}

double Number::evalutate() const {
  return value;
}

void Number::print(std::ostream& os) const {
  os << evalutate();
}

void Number::print_tree(std::ostream& os, int depth) const {
  os << std::setw(depth) << "";
  print(os);
  os << std::endl;
}

Node* Number::clone() const {
  return new Number{value};
}

Node* Number::expand()
{
    return this;
}

/**** Operator ****/
Operator::Operator(Node* left, Node* right)
  :left{left}, right{right} {}

Operator::~Operator() {
  delete left;
  delete right;
}

void Operator::print_tree(std::ostream& os, int depth) const {
  //std::cout << "depth: " << depth << std::endl;
  left->print_tree(os, depth+3);
  os << std::setw(depth) << " " << "/\n"
     << std::setw(depth) << "" << glyph() << "\n"
     << std::setw(depth) << " " << "\\\n";
  right->print_tree(os, depth+3);
}
/* 
  Todo : To transform the multiplication of an addition expression into 
          an addition of two multiplication expressions
          (1+2)*3 -> (1*3)+(2*3)
*/
Node* Operator::left_expand(Operator* root) {
  auto child {dynamic_cast<Operator*>(root->left)};
  root->left = child->left;
  child->left = root;
  child->right = new Multiplication(child->right, root->right->clone());
  return child->expand();
}

Node* Operator::right_expand(Operator* root) {
  auto child {dynamic_cast<Operator*>(root->right)};
  root->right = child->right; // 1
  child->right = root;
  child->left = new Multiplication(child->left, root->left->clone());
  return child->expand();
}

Node* Operator::expand()
{
  left = left->expand();
  right = right->expand();
  if (typeid(*this) == typeid(Multiplication))
  {
      if (dynamic_cast<Addition*>(left))
      {
          return left_expand(this);
      }
      else if (dynamic_cast<Addition*>(right))
      {
          return right_expand(this);
      }
  }
  return this;
}

/**** Addition ****/
double Addition::evalutate() const {
  return left->evalutate() + right->evalutate();
}

void Addition::print(std::ostream& os) const {
  left->print(os);
  os << glyph();
  right->print(os);
}

Node* Addition::clone() const {
  return new Addition(left->clone(), right->clone());
}

std::string Addition::glyph() const {
  return "+";
}

/**** Subtraction ****/
double Subtraction::evalutate() const {
  return left->evalutate() - right->evalutate();
}

Node* Subtraction::clone() const {
  return new Subtraction(left->clone(), right->clone());
}

std::string Subtraction::glyph() const {
  return "-";
}

/**** Multiplication ****/
double Multiplication::evalutate() const {
  return left->evalutate() * right->evalutate();
}

void Multiplication::print(std::ostream& os) const {
  print(left, os);
  os << glyph();
  print(right, os);
}

void Multiplication::print(Node* expression, std::ostream& os) const {
  if (dynamic_cast<Addition*>(expression)) {
    os << '(';
    expression->print(os);
    os << ')';
  }
  else {
    expression->print(os);
  }
}

Node* Multiplication::clone() const {
  return new Multiplication(left->clone(), right->clone());
}

std::string Multiplication::glyph() const {
  return "*";
}

/**** Division ****/
double Division::evalutate() const {
  return left->evalutate() / right->evalutate();
}

void Division::print(std::ostream& os) const {
  left->print(os);
  os << glyph();
  right->print(os);
}

Node* Division::clone() const {
  return new Division(left->clone(), right->clone());
}

std::string Division::glyph() const {
  return "/";
}