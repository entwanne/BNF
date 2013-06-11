#include "bnf_call.h"

#include <stdio.h>
static void bnf_call_print(bnf_node_t* node)
{
  bnf_call_t* call = (bnf_call_t*) node;
  printf("[%s]", call->rule);
}

static int bnf_call_visit(bnf_state_t* state, bnf_visitor_t* visitor)
{
  bnf_call_t* call = (bnf_call_t*) state->state;
  bnf_rule_t* rule = bnf_visitor_find_rule(visitor, call->rule);
  if (rule)
    bnf_visitor_visit(visitor, rule->root, state->text, state->mem);
  return 0;
}


static bnf_nodetype_t g_bnf_call_nodetype = {"CALL", bnf_simple_free_node, bnf_call_print, bnf_call_visit, bnf_simple_find_next_node};

bnf_node_t* bnf_new_call(char* rule)
{
  bnf_call_t* node = (bnf_call_t*) bnf_new_node(sizeof(*node), 0, &g_bnf_call_nodetype);
  if (node)
    node->rule = rule;
  return (bnf_node_t*) node;
}
