#ifndef __BNF_AND_OR_H__
#define __BNF_AND_OR_H__

#include <stdarg.h>

#include "bnf_node.h"

typedef struct bnf_and_or_s bnf_and_or_t;
struct bnf_and_or_s
{
  bnf_node_t base;
  bnf_node_t* left;
  bnf_node_t* right;
};

bnf_node_t* bnf_new_and_or(bnf_nodetype_t* type, bnf_node_t* left, bnf_node_t* right);

typedef bnf_node_t* (*bnf_and_or_ctor_t)(bnf_node_t*, bnf_node_t*);
bnf_node_t* vbnf_and_or_seq(bnf_and_or_ctor_t ctor, bnf_node_t* first, va_list ap);
bnf_node_t* bnf_and_or_seq(bnf_and_or_ctor_t ctor, bnf_node_t* first, ...);

void bnf_and_or_free(bnf_node_t* node);

#endif
