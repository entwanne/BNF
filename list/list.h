#ifndef __LIST_H__
#define __LIST_H__

#include <sys/types.h>

typedef struct list_node_s list_node_t;
/**
 * \brief Maillon de liste chaînée générique
 */
struct list_node_s
{
  /**
   * \brief Maillon suivant
   */
  list_node_t* next;
};

/**
 * \brief Liste chaînée générique
 */
typedef list_node_t* list_t;

typedef void (*list_apply_t)(list_node_t*);
typedef void (*list_apply_param_t)(list_node_t*, void*);

/**
 * \brief Instancie un nouveau maillon
 * \param alloc_size : taille de la zone mémoire à allouer
 * \param next : pointeur sur le maillon suivant
 * \return pointeur sur le maillon
 */
list_node_t* list_new_node(size_t alloc_size, list_node_t* next);
/**
 * \brief Ajout d'un maillon dans la liste
 * \param list : pointeur sur la liste
 * \param content : nouveau maillon
 */
void list_push(list_t* list, list_node_t* node);
/**
 * \brief Ajout d'un maillon à la fin d'une liste
 * \param list : pointeur sur la liste
 * \param content : nouveau maillon
 */
void list_pushback(list_t* list, list_node_t* node);
/**
 * \brief Vide une liste
 * \param list: liste à vider
 */
void list_clear(list_t* list);
/**
 * \brief Parcours une liste maillon par maillon
 * \param list : liste pour commencer un nouveau parcours, 0 pour continuer le parcours actuel
 * \param slist : pointeur sur une liste vide utilisée comme buffer
 * \return pointeur sur le maillon actuel
 */
list_node_t* list_get_next_node_r(list_t list, list_t* slist);
/**
 * \brief Parcours une liste maillon par maillon
 * \param list : liste pour commencer un nouveau parcours, 0 pour continuer le parcours actuel
 * \return pointeur sur le maillon actuel
 */
list_node_t* list_get_next_node(list_t list);
/**
 * \brief Supprime le maillon en tête de liste
 * \param list : pointeur sur la liste concernée
 * \return pointeur sur le maillon supprimé
 */
list_node_t* list_pop(list_t* list);
/**
 * \brief Applique une fonction à tous les maillons d'une liste
 * \param list : liste concernée
 * \param f : fonction à appliquer
 */
void list_apply(list_t list, list_apply_t f);
void list_apply_param(list_t list, list_apply_param_t f, void* p);
/**
 * \brief Calcule la taille d'une liste
 * \param list : liste à mesurer
 * \return taille de la liste
 */
size_t list_size(list_t list);

#endif
