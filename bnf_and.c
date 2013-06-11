#include "bnf_and.h"

#include <stdio.h>
static void bnf_and_print(bnf_node_t* node)
{
  bnf_and_t* and = (bnf_and_t*) node;
  printf("( ");
  bnf_print_node(and->left);
  printf(" AND ");
  bnf_print_node(and->right);
  printf(" )");
}

static int bnf_and_visit(bnf_state_t* state, bnf_visitor_t* visitor)
{
  bnf_and_t* and = (bnf_and_t*) state->state;
  /* printf("AND\n"); */
  bnf_visitor_visit(visitor, and->left, state->text, state->mem);
  return 0;
}

static bnf_node_t* bnf_and_find_next_node(bnf_node_t* node, bnf_node_t* referer)
{
  bnf_and_t* and = (bnf_and_t*) node;
  if (referer == and->left)
    return and->right;
  return bnf_find_next_node(node->parent, node);
}


static bnf_nodetype_t g_bnf_and_nodetype = {"AND", bnf_and_or_free, bnf_and_print, bnf_and_visit, bnf_and_find_next_node};

bnf_node_t* bnf_new_and(bnf_node_t* left, bnf_node_t* right)
{
  return bnf_new_and_or(&g_bnf_and_nodetype, left, right);
}


bnf_node_t* vbnf_and_seq(bnf_node_t* first, va_list ap)
{
  return vbnf_and_or_seq(bnf_new_and, first, ap);
}

bnf_node_t* bnf_and_seq(bnf_node_t* first, ...)
{
  va_list ap;
  va_start(ap, first);
  return vbnf_and_or_seq(bnf_new_and, first, ap);
}
