#ifndef __BNF_OR_H__
#define __BNF_OR_H__

#include "bnf_and_or.h"

typedef bnf_and_or_t bnf_or_t;

bnf_node_t* bnf_new_or(bnf_node_t* left, bnf_node_t* right);

bnf_node_t* vbnf_or_seq(bnf_node_t* first, va_list ap);
bnf_node_t* bnf_or_seq(bnf_node_t* first, ...);

#endif
