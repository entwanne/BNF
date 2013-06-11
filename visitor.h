#ifndef __VISITOR_H__
#define __VISITOR_H__

#include "list.h"
#include "bnf_node.h"

typedef struct bnf_state_s bnf_state_t;
struct bnf_state_s
{
  list_node_t base;
  bnf_node_t* state;
  char* text;
  list_t mem;
};

typedef struct bnf_visitor_s bnf_visitor_t;
struct bnf_visitor_s
{
  list_t states;
  list_t next_states;
};

list_node_t* bnf_new_state(bnf_node_t* state, char* text, list_t mem);

bnf_visitor_t* bnf_new_visitor(void);
void bnf_free_visitor(bnf_visitor_t* visitor);
void bnf_visitor_launch(bnf_visitor_t* visitor, bnf_node_t* state, char* text);
void bnf_visitor_visit(bnf_visitor_t* visitor, bnf_node_t* state, char* text, list_t mem);

#endif