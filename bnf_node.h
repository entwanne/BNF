#ifndef __BNF_NODE_H__
#define __BNF_NODE_H__

#include <sys/types.h>

typedef struct bnf_node_s bnf_node_t;
struct bnf_node_s
{
  bnf_node_t* parent;
  struct bnf_nodetype_s* type;
};

#include "bnf_nodetype.h"


bnf_node_t* bnf_new_node(size_t alloc_size, bnf_node_t* parent, bnf_nodetype_t* type);
void bnf_simple_free_node(bnf_node_t* node);
bnf_node_t* bnf_simple_find_next_node(bnf_node_t* node, bnf_node_t* referer);

void bnf_free_node(bnf_node_t* node);
void bnf_print_node(bnf_node_t* node);
bnf_node_t* bnf_find_next_node(bnf_node_t* node, bnf_node_t* referer);


#include "visitor.h"

#endif
