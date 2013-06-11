#include <string.h>
#include "bnf_label.h"

#include <stdio.h>
static void bnf_label_print(bnf_node_t* node)
{
  bnf_label_t* label = (bnf_label_t*) node;
  printf("<%s>", label->label);
}

#include <stdlib.h>
static int bnf_label_visit(bnf_state_t* state, bnf_visitor_t* visitor)
{
  bnf_label_t* label = (bnf_label_t*) state->state;
  bnf_node_t* next;
  bnf_rule_exit_t* rule_exit;
  /* printf("LABEL\n"); */
  if (!strncmp(label->label, state->text, label->len))
    {
      state->text += label->len;
      next = bnf_find_next_node(state->state, 0);
      /* bnf_print_node(next); */
      while (!next && state->mem)
	{
	  rule_exit = (bnf_rule_exit_t*) list_pop(&state->mem);
	  next = bnf_find_next_node(rule_exit->caller, 0);
	  free(rule_exit);
	}
      if (!next && !*state->text)
	return 1;
      bnf_visitor_visit(visitor, next, state->text, state->mem);
    }
  return 0;
}


static bnf_nodetype_t g_bnf_label_nodetype = {"LABEL", bnf_simple_free_node, bnf_label_print, bnf_label_visit, bnf_simple_find_next_node};

bnf_node_t* bnf_new_label(char* label)
{
  bnf_label_t* node = (bnf_label_t*) bnf_new_node(sizeof(*node), 0, &g_bnf_label_nodetype);
  if (node)
    {
      node->label = label;
      node->len = strlen(label);
    }
  return (bnf_node_t*) node;
}
