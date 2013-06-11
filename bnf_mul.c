#include "bnf_mul.h"

void bnf_mul_free(bnf_node_t* node)
{
  bnf_mul_t* mul = (bnf_mul_t*) node;
  bnf_free_node(mul->content);
  bnf_simple_free_node(node);
}

#include <stdio.h>
static void bnf_mul_print(bnf_node_t* node)
{
  bnf_mul_t* mul = (bnf_mul_t*) node;
  bnf_print_node(mul->content);
  if (mul->max < 0)
    printf(" × {%d, …}", mul->min);
  else if (mul->min == mul->max)
    printf(" × %d", mul->min);
  else
    printf(" × {%d, %d}", mul->min, mul->max);
}

static int bnf_mul_visit(bnf_state_t* state, bnf_visitor_t* visitor)
{
  (void) state;
  (void) visitor;
  printf("MUL NOT IMPLEMENTED\n");
  return 0;
}

static bnf_nodetype_t g_bnf_mul_nodetype = {"MUL", bnf_mul_free, bnf_mul_print, bnf_mul_visit, bnf_simple_find_next_node};

bnf_node_t* bnf_new_mul(bnf_node_t* content, int min, int max)
{
  bnf_mul_t* node = (bnf_mul_t*) bnf_new_node(sizeof(*node), 0, &g_bnf_mul_nodetype);
  if (node)
    {
      node->content = content;
      node->min = min;
      node->max = max;
    }
  return (bnf_node_t*) node;
}

bnf_node_t* bnf_new_optional(bnf_node_t* content)
{
  return bnf_new_mul(content, 0, 1);
}

bnf_node_t* bnf_new_plus(bnf_node_t* content)
{
  return bnf_new_mul(content, 1, -1);
}

bnf_node_t* bnf_new_star(bnf_node_t* content)
{
  return bnf_new_mul(content, 0, -1);
}
