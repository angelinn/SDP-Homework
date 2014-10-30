#include "Operator.h"

///
/// C-tor
///
Operator::Operator(char alpha, char sgn, int prior, int assoc) : letter(alpha), sign(sgn), priority(prior), associativity(assoc)
{ }
