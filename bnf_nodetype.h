#ifndef __BNF_NODETYPE_H__
#define __BNF_NODETYPE_H__

typedef struct bnf_visitor_s __bnf_visitor_t;
typedef struct bnf_state_s __bnf_state_t;

typedef struct bnf_nodetype_s bnf_nodetype_t;
struct bnf_nodetype_s
{
  const char* name;
  void (*free)(bnf_node_t*);
  void (*print)(bnf_node_t*);
  int (*visit)(__bnf_state_t*, __bnf_visitor_t*);
  bnf_node_t* (*find_next)(bnf_node_t*, bnf_node_t*);
};

#endif
