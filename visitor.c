#include <stdlib.h>
#include <string.h>
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

list_node_t* bnf_new_rule(char* name, bnf_node_t* root)
{
  bnf_rule_t* node = (bnf_rule_t*) list_new_node(sizeof(*node), 0);
  if (node)
    {
      node->name = name;
      node->root = root;
    }
  return (list_node_t*) node;
}


bnf_visitor_t* bnf_new_visitor(void)
{
  bnf_visitor_t* visitor = malloc(sizeof(*visitor));
  if (visitor)
    {
      visitor->rules = 0;
      visitor->states = 0;
      visitor->next_states = 0;
    }
  return visitor;
}

void bnf_visitor_register_rule(bnf_visitor_t* visitor, char* name, bnf_node_t* root)
{
  if (visitor)
    list_push(&visitor->rules, bnf_new_rule(name, root));
}

void bnf_free_visitor(bnf_visitor_t* visitor)
{
  if (visitor)
    {
      list_clear(&visitor->rules);
      list_clear(&visitor->states);
      list_clear(&visitor->next_states);
    }
  free(visitor);
}

#include <stdio.h>
static void test_visitor(list_node_t* node_, void* p)
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

static int find_rule_by_name(list_node_t* node, void* p)
{
  bnf_rule_t* rule = (bnf_rule_t*) node;
  char* name = (char*) p;
  if (rule && name && !strcmp(rule->name, name))
    return 1;
  return 0;
}

bnf_rule_t* bnf_visitor_find_rule(bnf_visitor_t* visitor, char* rule_name)
{
  return ((bnf_rule_t*) list_find_param(visitor->rules, find_rule_by_name, rule_name));
}

void bnf_visitor_launch(bnf_visitor_t* visitor, char* rule_name, char* text)
{
  bnf_rule_t* rule;
  if (visitor)
    {
      if ((rule = bnf_visitor_find_rule(visitor, rule_name)))
	{
	  bnf_visitor_visit(visitor, rule->root, text, 0);
	  while (visitor->next_states)
	    {
	      list_clear(&visitor->states);
	      visitor->states = visitor->next_states;
	      visitor->next_states = 0;
	      list_apply_param(visitor->states, test_visitor, visitor);
	    }
	}
      bnf_free_visitor(visitor);
    }
}

void bnf_visitor_visit(bnf_visitor_t* visitor, bnf_node_t* state, char* text, list_t mem)
{
  if (visitor)
    list_push(&visitor->next_states, bnf_new_state(state, text, mem));
}
