#ifndef __BNF_LABEL_H__
#define __BNF_LABEL_H__

#include "bnf_node.h"

typedef struct bnf_label_s bnf_label_t;
struct bnf_label_s
{
  bnf_node_t base;
  char* label;
  size_t len;
};

bnf_node_t* bnf_new_label(char* label);

#endif
