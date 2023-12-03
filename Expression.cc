#include "Expression.h"

#include <stdexcept>
#include <ostream>

Expression::Expression(Node* root) 
    :root{root} {}

Expression::Expression(Expression const& other) {

}

Expression::Expression(Expression&& other) {
    
}

Expression::~Expression() {
    delete root;
}

Expression& Expression::operator=(Expression const& rhs) {

}

Expression& Expression::operator=(Expression&& rhs) {

}

double Expression::evaluate() const {
    return root->evalutate();
}

/* For part A */
void Expression::print_tree(std::ostream& os) const {
    root->print_tree(os);
}

/* For part B */
void Expression::print(std::ostream& os) const
{
    root->print(os);
}

/* For part C */
void Expression::expand()
{
    root = root->expand();
}
