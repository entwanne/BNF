#include <stdlib.h>
#include "visitor.h"

list_node_t* bnf_new_state(bnf_node_t* state, char* text, list_t mem)
{
  bnf_state_t* node = (bnf_state_t*) list_new_node(sizeof(*node), 0);
  if (node)
    {
      node->state = state;
      node->text = text;
      node->mem = mem;
    }
  return (list_node_t*) node;
}


bnf_visitor_t* bnf_new_visitor(void)
{
  bnf_visitor_t* visitor = malloc(sizeof(*visitor));
  if (visitor)
    {
      visitor->states = 0;
      visitor->next_states = 0;
    }
  return visitor;
}

void bnf_free_visitor(bnf_visitor_t* visitor)
{
  if (visitor)
    {
      list_clear(&visitor->states);
      list_clear(&visitor->next_states);
    }
  free(visitor);
}

#include <stdio.h>
void test_visitor(list_node_t* node_, void* p)
{
  bnf_state_t* node = (bnf_state_t*) node_;
  bnf_visitor_t* visitor = (bnf_visitor_t*) p;
  if (node && node->state && visitor)
    {
      /* printf("ok: %d %s\n", node->mem, node->state->type->name); */
      printf("visiting: ");
      bnf_print_node(node->state);
      printf("\n");
      if (node->state->type->visit(node, visitor))
	printf("match\n");
      /* if (node->mem < 10) */
      /* 	bnf_visitor_visit(visitor, node->state, node->mem + 1); */
    }
}

void bnf_visitor_launch(bnf_visitor_t* visitor, bnf_node_t* state, char* text)
{
  if (visitor)
    {
      bnf_visitor_visit(visitor, state, text, 0);
      while (visitor->next_states)
	{
	  list_clear(&visitor->states);
	  visitor->states = visitor->next_states;
	  visitor->next_states = 0;
	  list_apply_param(visitor->states, test_visitor, visitor);
	}
      bnf_free_visitor(visitor);
    }
}

void bnf_visitor_visit(bnf_visitor_t* visitor, bnf_node_t* state, char* text, list_t mem)
{
  if (visitor)
    list_push(&visitor->next_states, bnf_new_state(state, text, mem));
}
