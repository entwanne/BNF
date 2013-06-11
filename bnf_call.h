#ifndef __BNF_CALL_H__
#define __BNF_CALL_H__

#include "bnf_node.h"

typedef struct bnf_call_s bnf_call_t;
struct bnf_call_s
{
  bnf_node_t base;
  char* rule;
};

bnf_node_t* bnf_new_call(char* rule);

#endif
