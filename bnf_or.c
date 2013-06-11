#include "bnf_or.h"

#include <stdio.h>
static void bnf_or_print(bnf_node_t* node)
{
  bnf_or_t* or = (bnf_or_t*) node;
  printf("( ");
  bnf_print_node(or->left);
  printf(" OR ");
  bnf_print_node(or->right);
  printf(" )");
}

static int bnf_or_visit(bnf_state_t* state, bnf_visitor_t* visitor)
{
  bnf_or_t* or = (bnf_or_t*) state->state;
  /* printf("OR\n"); */
  bnf_visitor_visit(visitor, or->left, state->text, state->mem);
  bnf_visitor_visit(visitor, or->right, state->text, state->mem);
  return 0;
}


static bnf_nodetype_t g_bnf_or_nodetype = {"OR", bnf_and_or_free, bnf_or_print, bnf_or_visit, bnf_simple_find_next_node};

bnf_node_t* bnf_new_or(bnf_node_t* left, bnf_node_t* right)
{
  return bnf_new_and_or(&g_bnf_or_nodetype, left, right);
}


bnf_node_t* vbnf_or_seq(bnf_node_t* first, va_list ap)
{
  return vbnf_and_or_seq(bnf_new_or, first, ap);
}

bnf_node_t* bnf_or_seq(bnf_node_t* first, ...)
{
  va_list ap;
  va_start(ap, first);
  return vbnf_and_or_seq(bnf_new_or, first, ap);
}
