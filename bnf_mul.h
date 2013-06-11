#ifndef __BNF_MUL_H__
#define __BNF_MUL_H__

#include "bnf_node.h"

typedef struct bnf_mul_s bnf_mul_t;
struct bnf_mul_s
{
  bnf_node_t base;
  bnf_node_t* content;
  int min;
  int max;
};

bnf_node_t* bnf_new_mul(bnf_node_t* content, int min, int max);
bnf_node_t* bnf_new_optional(bnf_node_t* content);
bnf_node_t* bnf_new_plus(bnf_node_t* content);
bnf_node_t* bnf_new_star(bnf_node_t* content);

#endif
