#ifndef __BNF_AND_H__
#define __BNF_AND_H__

#include "bnf_and_or.h"

typedef bnf_and_or_t bnf_and_t;

bnf_node_t* bnf_new_and(bnf_node_t* left, bnf_node_t* right);

bnf_node_t* vbnf_and_seq(bnf_node_t* first, va_list ap);
bnf_node_t* bnf_and_seq(bnf_node_t* first, ...);

#endif
