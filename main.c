#include "bnf_label.h"
#include "bnf_or.h"
#include "bnf_and.h"
/* #include "bnf_mul.h" */
#include "bnf_call.h"
#include "visitor.h"

#include <stdio.h>

int main(int ac, char** argv)
{
  /* bnf_node_t* node = bnf_new_and(bnf_new_label("toto"), bnf_new_label("tata")); */
  /* bnf_node_t* node = bnf_or_seq(bnf_new_mul(bnf_new_label("toto"), 0, 5), bnf_new_label("tata"), bnf_new_label("tutu"), 0); */
  /* bnf_node_t* node = bnf_or_seq(bnf_new_star(bnf_new_label("toto")), bnf_new_label("tata"), bnf_new_label("tutu"), 0); */
  /* bnf_node_t* node = bnf_or_seq(bnf_new_label("tata"), bnf_new_label("tutu"), 0); */
  bnf_node_t* node;
  bnf_node_t* node_num;
  bnf_visitor_t* visitor;
  if (ac > 1)
    {
      visitor = bnf_new_visitor();
      /* node = bnf_or_seq(bnf_new_call("NUMBER"), bnf_new_label("tata"), bnf_and_seq(bnf_new_label("tu"), bnf_or_seq(bnf_new_label("tu"), bnf_new_label("ut"), bnf_new_label(""), 0), 0), 0); */
      node_num = bnf_new_label("42");
      bnf_visitor_register_rule(visitor, "NUMBER", node_num);
      node = bnf_and_seq(bnf_new_call("NUMBER"), bnf_new_label("tutu"), 0);
      bnf_visitor_register_rule(visitor, "S", node);

      bnf_print_node(node);
      printf("\n");
      bnf_visitor_launch(visitor, "S", argv[1]);
      
      bnf_free_node(node);
      bnf_free_node(node_num);
    }
  else
    printf("Usage: %s string\n", argv[0]);
  return 0;
}
