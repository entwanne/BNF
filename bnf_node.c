#include <stdlib.h>
#include "bnf_node.h"

bnf_node_t* bnf_new_node(size_t alloc_size, bnf_node_t* parent, bnf_nodetype_t* type)
{
  bnf_node_t* node = malloc(alloc_size);
  if (node)
    {
      node->parent = parent;
      node->type = type;
    }
  return node;
}

void bnf_simple_free_node(bnf_node_t* node)
{
  free(node);
}

bnf_node_t* bnf_simple_find_next_node(bnf_node_t* node, bnf_node_t* referer)
{
  (void) referer;
  if (node->parent)
    return bnf_find_next_node(node->parent, node);
  return 0;
}


void bnf_free_node(bnf_node_t* node)
{
  if (node && node->type && node->type->free)
    node->type->free(node);
}

void bnf_print_node(bnf_node_t* node)
{
  if (node && node->type && node->type->print)
    node->type->print(node);
}

bnf_node_t* bnf_find_next_node(bnf_node_t* node, bnf_node_t* referer)
{
  if (node && node->type && node->type->find_next)
    return node->type->find_next(node, referer);
  return 0;
}
