/*
  Implement the classes:
  - Node
  - Number
  - Operator
  - Addition
  - Subtraction
  - Multiplication
  - Division

  Node should have the following (pure virtual) members:
  - double evaluate()
    + Calculate the expression stored in 'this'
  - void print(std::ostream& os)
    + print the expression represented in 'this'
  - void print_tree(std::ostream& os, int depth)
    + print a textual representation of the expression tree
  - Node* clone()
    + return a a new instance of the expression stored in 'this'
 */

#ifndef Node_H
#define Node_H

#include <iostream>

class Node
{
private:
  /* data */
public:
  virtual ~Node() = default;
  virtual double evalutate() const = 0;
  virtual void print(std::ostream& os) const = 0;
  virtual void print_tree(std::ostream& os, int depth = 0) const = 0;
  virtual Node* clone() const = 0;
  virtual Node* expand() = 0;
};

class Number : public Node {
private:
  double value;
public:
  Number(double value);
  double evalutate() const override;
  void print(std::ostream& os) const override;
  void print_tree(std::ostream& os, int depth = 0) const override;
  Node* clone() const override;
  virtual Node* expand() override;
};

class Operator : public Node {
protected:
  Node* left;
  Node* right;
  virtual std::string glyph() const = 0;
  static Node* left_expand(Operator* root);
  static Node* right_expand(Operator* root);
public:
  Operator(Node* left, Node* right);
  ~Operator();
  void print_tree(std::ostream& os, int depth = 0) const override;
  virtual Node* expand() override;
};


class Addition : public Operator {
public:
  using Operator::Operator;
  double evalutate() const override;
  void print(std::ostream& os) const override;
  Node* clone() const override;
protected:
  std::string glyph() const override;
};

class Subtraction : public Addition {
public:
  using Addition::Addition;
  double evalutate() const override;
  Node* clone() const override;
protected:
  std::string glyph() const override;
};

class Multiplication : public Operator {
public:
  using Operator::Operator;
  double evalutate() const override;
  void print(std::ostream& os) const override;
  Node* clone() const override;
protected:
  std::string glyph() const override;
private:
  void print(Node* expression, std::ostream& os) const;
};

class Division : public Multiplication {
public:
  using Multiplication::Multiplication;
  double evalutate() const override;
  void print(std::ostream& os) const override;
  Node* clone() const override;
protected:
  std::string glyph() const override;
};

#endif // Node_H