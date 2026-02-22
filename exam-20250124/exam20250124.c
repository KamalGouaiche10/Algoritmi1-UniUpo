/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/******************************************************************************/
/*** NOME:                                                                  ***/
/*** COGNOME:                                                               ***/
/*** MATRICOLA:                                                             ***/
/******************************************************************************/


#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/hashtable.h>

/**** BEGIN of EXERCISE #1 ****/

// Dichiarazioni delle funzioni helper
static int upo_bst_contains(const upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp);
static void *upo_bst_lca_imple(const upo_bst_node_t *node, const void *key1, const void *key2, upo_bst_comparator_t key_cmp);
void *upo_bst_lcp_imple(const upo_bst_node_t *node, const void *key1, const void *key2, upo_bst_comparator_t key_cmp);
double upo_ht_linprob_avg_collisions(const upo_ht_linprob_t ht, const upo_ht_key_list_t key_list);


// Funzione principale per trovare il Lowest Common Ancestor
void *upo_bst_lca(const upo_bst_t tree, const void *key1, const void *key2) {
   if(upo_bst_is_empty(tree)|| key1==NULL || key2==NULL){
    return NULL;
   }
   if(!upo_bst_contains(tree->root,key1,tree->key_cmp)||!upo_bst_contains(tree->root,key2,tree->key_cmp)){
    return NULL;
   }

   return upo_bst_lca_imple(tree->root,key1,key2,tree->key_cmp);

}

// Implementazione ricorsiva del Lowest Common Ancestor
static void *upo_bst_lca_imple(const upo_bst_node_t *node, const void *key1, const void *key2, upo_bst_comparator_t key_cmp) {
    if(node==NULL)return NULL;
    int cmp1=key_cmp(key1,node->key);
    int cmp2=key_cmp(key2,node->key);

    if(cmp1>0 && cmp2>0){
        return upo_bst_lca_imple(node->right,key1,key2,key_cmp);
    }

    if(cmp1<0 && cmp2<0){
        return upo_bst_lca_imple(node->left,key1,key2,key_cmp);
    }
    return node->key;
   
}
// Funzione helper per verificare se una chiave esiste nel BST
static int upo_bst_contains(const upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp) {
    if (node == NULL || key == NULL)
        return 0;

    int cmp1 = cmp(key, node->key);

    if (cmp1 == 0)
        return 1;
    else if (cmp1 < 0) {
        return upo_bst_contains(node->left, key, cmp);
    } else {
        return upo_bst_contains(node->right, key, cmp);
    }
}
// Algoritmo LCP (Lowest Common Parent) - Inverso di LCA
// Trova il percorso dal nodo radice fino alle chiavi specificate

/*void *upo_bst_lcp(const upo_bst_t tree, const void *key1, const void *key2)
{
    if(upo_bst_is_empty(tree) || key1 == NULL || key2 == NULL) {
        return NULL;
    }

    if(!upo_bst_contains(tree->root, key1, tree->key_cmp) || !upo_bst_contains(tree->root, key2, tree->key_cmp)) {
        return NULL;
    }
    return upo_bst_lcp_imple(tree->root, key1, key2, tree->key_cmp);
}


void *upo_bst_lcp_imple(const upo_bst_node_t *node, const void *key1, const void *key2, upo_bst_comparator_t key_cmp)
{
    if(node == NULL) return NULL;
    
    int cmp1 = key_cmp(key1, node->key);
    int cmp2 = key_cmp(key2, node->key);

    if(cmp1 > 0 && cmp2 > 0) {
        return upo_bst_lcp_imple(node->left, key1, key2, key_cmp);
    }
    if(cmp1 < 0 && cmp2 < 0) {
        return upo_bst_lcp_imple(node->right, key1, key2, key_cmp);
    }
    else {
        return node->key;
    }
}*/


/**** END of EXERCISE #1 ****/


/**** BEGIN of EXERCISE #2 ****/


double upo_ht_linprob_avg_collisions(const upo_ht_linprob_t ht, const upo_ht_key_list_t key_list) 
{
     if(upo_ht_linprob_is_empty(ht)||ht==NULL || key_list==NULL) return -1;
    int found=1;
    int total_collisiones=0;
    int num_keys=0;

    upo_ht_key_list_node_t*current=key_list;
    while(current!=NULL){
        size_t hash=ht->key_hash(current->key,ht->capacity);
        found=0;
        int collisions=0;

        for(size_t i=0;i<ht->capacity && !found;i++){
            size_t pos=(hash+i)%ht->capacity;

            if(ht->slots[pos].key==NULL && !ht->slots[pos].tombstone){
                break;
            }

            if(ht->slots[pos].key!=NULL && ht->key_cmp(ht->slots[pos].key,current->key)==0){
                total_collisiones+=collisions;
                num_keys++;
                found=1;
            }
            else{
                collisions++;
            }
        }
        current=current->next;
    }
    if(num_keys==0)return -1;
    
    return (double) total_collisiones/num_keys;
}
/**** END of EXERCISE #2 ****/
/* Implementare un algoritmo che ritorni la lista delle chiavi in un
(BST) che sono minori o uguali a una chiave k. Dato un BST e una chiave k (non
necessariamente contenuta nel BST), il numero di chiavi nel BST minori o uguali a k si
ottiene contando tutte le chiavi contenute nel BST che sono minori della o uguali alla
chiave k.*/
/*upo_bst_key_list_t upo_bst_keys_le(const upo_bst_t bst, const void*key){
    if(bst==NULL || bst->root==NULL|| key==NULL) return NULL;

    upo_bst_key_list_t *list=NULL;

    upo_bst_keys_le_imple(bst->root,key,bst->key_cmp,&list);
    return list;
}

void upo_bst_keys_le_imple(upo_bst_node_t *node,const void *key,upo_bst_comparator_t key_cmp, upo_bst_key_list_t *list){
    if(node!=NULL){
        upo_bst_keys_le_imple(node->left,key,key_cmp,list);
        if(key_cmp(key,node->key) <= 0){
            upo_bst_key_list_node_t *list_node=malloc(sizeof(upo_bst_key_list_node_t));
            list_node->key=node->key;
            list_node->next=*list;
            *list=list_node;
        }
        upo_bst_keys_le_imple(node->right,key,key_cmp,list);
    }
}*/