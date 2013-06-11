#include "bnf_and_or.h"

void bnf_and_or_free(bnf_node_t* node)
{
  bnf_and_or_t* and = (bnf_and_or_t*) node;
  bnf_free_node(and->left);
  bnf_free_node(and->right);
  bnf_simple_free_node(node);
}


bnf_node_t* bnf_new_and_or(bnf_nodetype_t* type, bnf_node_t* left, bnf_node_t* right)
{
  bnf_and_or_t* node = (left && right) ? (bnf_and_or_t*) bnf_new_node(sizeof(*node), 0, type) : 0;
  if (node)
    {
      node->left = left;
      node->right = right;
      left->parent = (bnf_node_t*) node;
      right->parent = (bnf_node_t*) node;
    }
  return (bnf_node_t*) node;
}


bnf_node_t* vbnf_and_or_seq(bnf_and_or_ctor_t ctor, bnf_node_t* first, va_list ap)
{
  bnf_node_t* second;
  while (first && (second = va_arg(ap, bnf_node_t*)))
    first = ctor(first, second);
  return first;
}

bnf_node_t* bnf_and_or_seq(bnf_and_or_ctor_t ctor, bnf_node_t* first, ...)
{
  va_list ap;
  va_start(ap, first);
  return vbnf_and_or_seq(ctor, first, ap);
}
