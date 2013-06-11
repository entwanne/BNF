#include <stdlib.h>
#include "list.h"

list_node_t* list_new_node(size_t alloc_size, list_node_t* next)
{
  list_node_t* node = malloc(alloc_size);
  if (node)
    node->next = next;
  return node;
}

void list_push(list_t* list, list_node_t* node)
{
  if (list && node)
    {
      node->next = *list;
      *list = node;
    }
}

void list_pushback(list_t* list, list_node_t* node)
{
  list_node_t* tmp;
  if (!*list)
    {
      list_push(list, node);
      return ;
    }
  for (tmp = *list; tmp && tmp->next; tmp = tmp->next);
  if (node)
    tmp->next = node;
}

void list_clear(list_t* list)
{
  list_apply(*list, (list_apply_t) free);
  *list = 0;
}

list_node_t* list_get_next_node_r(list_t list, list_t* slist)
{
  list_node_t* node;
  if (list)
    *slist = list;
  node = *slist;
  if (*slist)
    *slist = node->next;
  return node;
}

list_node_t* list_get_next_node(list_t list)
{
  static list_t slist;
  return list_get_next_node_r(list, &slist);
}

list_node_t* list_pop(list_t* list)
{
  list_node_t* node = 0;
  if (*list)
    {
      node = *list;
      *list = node->next;
      node->next = 0;
    }
  return node;
}

void list_apply(list_t list, list_apply_t f)
{
  list_node_t* node;
  list_t slist = 0;
  for (node = list; (node = list_get_next_node_r(node, &slist)); node = 0)
    f(node);
}

void list_apply_param(list_t list, list_apply_param_t f, void* p)
{
  list_node_t* node;
  list_t slist = 0;
  for (node = list; (node = list_get_next_node_r(node, &slist)); node = 0)
    f(node, p);
}

size_t list_size(list_t list)
{
  size_t n;
  for (n = 0; list; n++, list = list->next)
    ;
  return n;
}
