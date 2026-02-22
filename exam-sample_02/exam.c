/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/******************************************************************************/
/*** NOME: Kamal                                                           ***/
/*** COGNOME: Gouaiche                                                     ***/
/*** MATRICOLA: 20054145                                                   ***/
/******************************************************************************/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/hashtable.h>

// Forward declarations for helper functions
upo_bst_node_t* findNode(upo_bst_node_t* node, const void* key,  upo_bst_comparator_t key_cmp, size_t* depth);
size_t upo_bst_subtree_count_even_impl(upo_bst_node_t* node, size_t depth);
size_t count_odd_depth_impl(upo_bst_node_t* node, size_t depth);
size_t count_leaves_impl(upo_bst_node_t* node);
size_t count_internal_impl(upo_bst_node_t* node);
size_t count_left_only_impl(upo_bst_node_t* node);
size_t count_right_only_impl(upo_bst_node_t* node);
size_t count_full_impl(upo_bst_node_t* node);
size_t count_at_depth_impl(upo_bst_node_t* node, size_t current_depth, size_t target_depth);
size_t count_greater_impl(upo_bst_node_t* node, const void *threshold, upo_bst_comparator_t key_cmp);
size_t count_smaller_impl(upo_bst_node_t* node, const void *threshold, upo_bst_comparator_t key_cmp);
size_t count_range_impl(upo_bst_node_t* node, const void *min_key, const void *max_key, upo_bst_comparator_t key_cmp);
size_t count_depth_multiple_impl(upo_bst_node_t* node, size_t depth, size_t divisor);
size_t count_height_impl(upo_bst_node_t* node, size_t target_height);
size_t calculate_height(upo_bst_node_t* node);
void upo_ht_sepchain_odelete(upo_ht_sepchain_t ht, const void *key, int destroy_data);
void upo_ht_sepchain_oinsert(upo_ht_sepchain_t ht, const void *key, const void *value);
void upo_ht_sepchain_remove_first_all(upo_ht_sepchain_t ht, int destroy_data);


/**** BEGIN of EXERCISE #1 ****/

size_t upo_bst_subtree_count_even(const upo_bst_t bst, const void *key) {
    if(upo_bst_is_empty(bst)|| key==NULL) return 0;

    size_t depth=0;
    upo_bst_node_t* node=findNode(bst->root,key,bst->key_cmp,&depth);
    if(node==NULL) return 0;
    return upo_bst_subtree_count_even_impl(node,depth);
}

size_t upo_bst_subtree_count_even_impl(upo_bst_node_t *node, size_t depth){
    if(node==NULL) return 0;
    size_t count=0;
    if(depth %2 ==0){
        count=1;
    }
    return count+ upo_bst_subtree_count_even_impl(node->left,depth+1)+upo_bst_subtree_count_even_impl(node->right,depth+1);
}

upo_bst_node_t* findNode(upo_bst_node_t *node, const void *key,upo_bst_comparator_t key_cmp,size_t *depth){
    if(node==NULL) return NULL;

    int cmp=key_cmp(key,node->key);

    if(cmp==0){
        return node;
    }else if(cmp<0){
        (*depth)++;
        return findNode(node->left,key,key_cmp,depth);
    }
    else{
        (*depth)++;
        return findNode(node->right,key,key_cmp,depth);
    }
}
// Count nodes at odd depths in a subtree
size_t upo_bst_subtree_count_odd(const upo_bst_t bst, const void *key) {
    if (upo_bst_is_empty(bst) || key==NULL ) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_odd_depth_impl(node, depth);
}

size_t count_odd_depth_impl(upo_bst_node_t* node, size_t depth) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    if ((depth % 2) == 1) {
        count = 1;
    }
    
    return count + count_odd_depth_impl(node->left, depth + 1) + count_odd_depth_impl(node->right, depth + 1);
}

// La funzione upo_bst_subtree_count_leaves serve a
// contare il numero di foglie nel sottoalbero radicato nel nodo con chiave key all'interno di un albero binario di ricerca (BST).
size_t upo_bst_subtree_count_leaves(const upo_bst_t bst, const void *key) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_leaves_impl(node);
}

size_t count_leaves_impl(upo_bst_node_t* node) {
    if (node == NULL) return 0;
    
    if (node->left == NULL && node->right == NULL) {
        return 1;
    }
    
    return count_leaves_impl(node->left) + count_leaves_impl(node->right);
}

//Restituisce il numero di nodi interni (cioè non foglie) del sottoalbero il cui nodo radice ha chiave key, in un BST (Binary Search Tree).
size_t upo_bst_subtree_count_internal(const upo_bst_t bst, const void *key) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_internal_impl(node);
}

size_t count_internal_impl(upo_bst_node_t* node) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    // If it has at least one child, it's an internal node
    if (node->left != NULL || node->right != NULL) {
        count = 1;
    }
    
    return count + count_internal_impl(node->left) + count_internal_impl(node->right);
}

// La funzione upo_bst_subtree_count_left_only serve a contare quanti nodi,
// in un sottoalbero con radice data, hanno solo il figlio sinistro (cioè left child ma nessun right child)
size_t upo_bst_subtree_count_left_only(const upo_bst_t bst, const void *key) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_left_only_impl(node);
}

size_t count_left_only_impl(upo_bst_node_t* node) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    // If it has only left child
    if (node->left != NULL && node->right == NULL) {
        count = 1;
    }
    
    return count + count_left_only_impl(node->left) + count_left_only_impl(node->right);
} 

// La funzione upo_bst_subtree_count_right_only serve a contare quanti nodi,
// in un sottoalbero con radice data, hanno solo il figlio Destro (cioè Right child ma nessun left child)
size_t upo_bst_subtree_count_right_only(const upo_bst_t bst, const void *key) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_right_only_impl(node);
}

size_t count_right_only_impl(upo_bst_node_t* node) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    // If it has only right child 
    if (node->left == NULL && node->right != NULL) {
        count = 1;
    }
    
    return count + count_right_only_impl(node->left) + count_right_only_impl(node->right);
}

// Count nodes with both children
size_t upo_bst_subtree_count_full(const upo_bst_t bst, const void *key) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_full_impl(node);
}

size_t count_full_impl(upo_bst_node_t* node) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    // If it has both children
    if (node->left != NULL && node->right != NULL) {
        count = 1;
    }
    
    return count + count_full_impl(node->left) + count_full_impl(node->right);
}

//la funzione upo_bst_subtree_count_at_depth serve a contare il numero di nodi a 
// una profondità specifica all'interno del sottoalbero radicato nel nodo con chiave key.

size_t upo_bst_subtree_count_at_depth(const upo_bst_t bst, const void *key, size_t target_depth) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_at_depth_impl(node, 0, target_depth);
}

size_t count_at_depth_impl(upo_bst_node_t* node, size_t current_depth, size_t target_depth) {
    if (node == NULL) return 0;
    
    if (current_depth == target_depth) {
        return 1;
    }

    if (current_depth > target_depth) {
        return 0;
    }

    return count_at_depth_impl(node->left, current_depth + 1, target_depth)+ count_at_depth_impl(node->right, current_depth + 1, target_depth);
}


// La funzione upo_bst_subtree_count_greater è progettata
// per contare quanti nodi in un sottoalbero hanno chiavi maggiori di una soglia specifica (threshold).
size_t upo_bst_subtree_count_greater(const upo_bst_t bst, const void *key, const void *threshold) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_greater_impl(node, threshold, bst->key_cmp);
}

size_t count_greater_impl(upo_bst_node_t* node, const void *threshold, upo_bst_comparator_t key_cmp) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    // If node's key is greater than threshold
    if (key_cmp(node->key, threshold) > 0) {
        count = 1;
    }
    
    return count + count_greater_impl(node->left, threshold, key_cmp) +count_greater_impl(node->right, threshold, key_cmp);
}

// Conta quanti nodi in un sottoalbero (radicato in subtree_key) hanno chiavi strettamente minori del valore threshold, usando il comparatore key_cmp.
size_t upo_bst_subtree_count_smaller(const upo_bst_t bst, const void *subtree_key, const void *threshold) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, subtree_key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_smaller_impl(node, threshold, bst->key_cmp);
}

size_t count_smaller_impl(upo_bst_node_t* node, const void *threshold, upo_bst_comparator_t key_cmp) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    // If node's key is smaller than threshold
    if (key_cmp(node->key, threshold) < 0) {
        count = 1;
    }
    
    return count + count_smaller_impl(node->left, threshold, key_cmp) +count_smaller_impl(node->right, threshold, key_cmp);
}

// Count nodes in key range
size_t upo_bst_subtree_count_range(const upo_bst_t bst, const void *subtree_key, const void *min_key, const void *max_key) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, subtree_key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_range_impl(node, min_key, max_key, bst->key_cmp);
}

size_t count_range_impl(upo_bst_node_t* node, const void *min_key, const void *max_key, upo_bst_comparator_t key_cmp) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    // If key is in range [min_key, max_key]
    if (key_cmp(node->key, min_key) >= 0 && key_cmp(node->key, max_key) <= 0) {
        count = 1;
    }
    
    return count + count_range_impl(node->left, min_key, max_key, key_cmp) +count_range_impl(node->right, min_key, max_key, key_cmp);
}

// La funzione upo_bst_subtree_count_depth_multiple conta quanti nodi nel sottoalbero radicato
// nel nodo con chiave key si trovano a una profondità che è multipla di un certo divisor.
size_t upo_bst_subtree_count_depth_multiple(const upo_bst_t bst, const void *key, size_t divisor) {
    if (bst == NULL || bst->root == NULL || divisor == 0) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    // Passo 0 per fare la profondità relativa al nodo 'key'
    return count_depth_multiple_impl(node, 0, divisor);
}

size_t count_depth_multiple_impl(upo_bst_node_t* node, size_t depth, size_t divisor) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    if (depth % divisor == 0) {
        count = 1;
    }
    
    return count + count_depth_multiple_impl(node->left, depth + 1, divisor)+ count_depth_multiple_impl(node->right, depth + 1, divisor);
}


// La funzione conta quanti nodi nel sottoalbero radicato nel nodo con chiave key hanno altezza
//(height) esattamente uguale a target_height.
size_t upo_bst_subtree_count_height(const upo_bst_t bst, const void *key, size_t target_height) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return count_height_impl(node, target_height);
}

size_t count_height_impl(upo_bst_node_t* node, size_t target_height) {
    if (node == NULL) return 0;  
    
    size_t height = calculate_height(node);
    size_t count = 0;
    
    if (height == target_height) {
        count = 1;
    }
    
    return count + count_height_impl(node->left, target_height) +count_height_impl(node->right, target_height);
}

size_t calculate_height(upo_bst_node_t* node) {
    if (node == NULL) return 0;
    
    size_t left_height = calculate_height(node->left);
    size_t right_height = calculate_height(node->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

/**** END of EXERCISE #1 ****/

/**** BEGIN of EXERCISE #2 ****/
// Rimuove un elemento specifico dalla hash table cercando la chiave nella lista collegata ordinata del bucket corrispondente. 
// Se trova la chiave,rimuove il nodo aggiornando i collegamenti e opzionalmente libera la memoria di chiave e valore.
void upo_ht_sepchain_odelete(upo_ht_sepchain_t ht, const void *key, int destroy_data) {
    if (ht == NULL || upo_ht_sepchain_is_empty(ht)|| key==NULL) {
        return;
    }
    
    size_t hash = ht->key_hash(key, ht->capacity);
    upo_ht_sepchain_list_node_t* node = ht->slots[hash].head;
    upo_ht_sepchain_list_node_t* pred = NULL;
    
    while (node != NULL && ht->key_cmp(key, node->key) > 0) {
        pred = node;
        node = node->next;
    }
    
    if (node != NULL && ht->key_cmp(key, node->key) == 0) {
        if (pred == NULL) {
            ht->slots[hash].head = node->next;
        } else {
            pred->next = node->next;
        }
        
        if (destroy_data) {
            free(node->key);
            free(node->value);
        }
        free(node);
        ht->size--;
    }  
    
    // If key not found, do nothing (correct behavior)
}

// Inserisce un nuovo elemento nella hash table mantenendo l'ordine crescente nella lista collegata del bucket.
// Se la chiave esiste già aggiorna il valore, altrimenti crea un nuovo nodo e lo inserisce nella posizione corretta.
void upo_ht_sepchain_oinsert(upo_ht_sepchain_t ht, const void *key, const void *value) {
    if (ht == NULL) return;
    
    size_t hash = ht->key_hash(key, ht->capacity);
    upo_ht_sepchain_list_node_t* node = ht->slots[hash].head;
    upo_ht_sepchain_list_node_t* pred = NULL;
    
    while (node != NULL && ht->key_cmp(key, node->key) > 0) {
        pred = node;
        node = node->next;
    }
    
    if (node != NULL && ht->key_cmp(key, node->key) == 0) {
        node->value = (void*)value;
        return;
    }
    
    upo_ht_sepchain_list_node_t* new_node = malloc(sizeof(upo_ht_sepchain_list_node_t));
    if (new_node == NULL) return; // Memory allocation failed
    
    new_node->key = (void*)key;
    new_node->value = (void*)value;
    new_node->next = node;
    
    if (pred == NULL) {
        ht->slots[hash].head = new_node;
    } else {
        pred->next = new_node;
    }
    
    ht->size++;
}

// Rimuove il primo elemento da tutte le liste non vuote della hash table, iterando su tutti i bucket.
// Per ogni bucket con elementi, elimina il primo nodo e opzionalmente libera la memoria associata.
void upo_ht_sepchain_remove_first_all(upo_ht_sepchain_t ht, int destroy_data) {
    if (ht == NULL || upo_ht_sepchain_is_empty(ht)) return;
    
    for (size_t i = 0; i < ht->capacity; i++) {
        if (ht->slots[i].head != NULL) {
            upo_ht_sepchain_list_node_t* to_remove = ht->slots[i].head;
            ht->slots[i].head = to_remove->next;
            
            if (destroy_data) {
                free(to_remove->key);
                free(to_remove->value);
            }
            free(to_remove);
            ht->size--;
        }
    }
}

// Rimuove tutti gli elementi le cui chiavi sono comprese nell'intervallo [min_key, max_key] da tutta la hash table. 
// Itera su tutti i bucket e per ogni lista rimuove i nodi che soddisfano la condizione di range, restituendo il numero di elementi rimossi.
size_t upo_ht_sepchain_remove_range(upo_ht_sepchain_t ht, const void *min_key, const void *max_key, int destroy_data) {
    if (ht == NULL || upo_ht_sepchain_is_empty(ht)) return 0;
    
    size_t removed_count = 0;
    
    for (size_t i = 0; i < ht->capacity; i++) {
        upo_ht_sepchain_list_node_t* node = ht->slots[i].head;
        upo_ht_sepchain_list_node_t* pred = NULL;
        
        while (node != NULL) {
            if (ht->key_cmp(node->key, min_key) >= 0 && ht->key_cmp(node->key, max_key) <= 0) {
                if (pred == NULL) {
                    ht->slots[i].head = node->next;
                } else {
                    pred->next = node->next;
                }
                
                upo_ht_sepchain_list_node_t* to_remove = node;
                node = node->next;
                
                if (destroy_data) {
                    free(to_remove->key);
                    free(to_remove->value);
                }
                free(to_remove);
                
                ht->size--;
                removed_count++;
            } 
            else {
                pred = node;
                node = node->next;
            }
        }
    }
    
    return removed_count;
}

// Restituisce il valore associato alla chiave `key` nella hash table `ht`.
// Se la chiave non è presente ritorna NULL.
void* upo_ht_sepchain_get(const upo_ht_sepchain_t ht, const void *key) {
    if (ht == NULL || upo_ht_sepchain_is_empty(ht) || key == NULL) return NULL;

    size_t hash = ht->key_hash(key, ht->capacity);
    upo_ht_sepchain_list_node_t* node = ht->slots[hash].head;

    while (node != NULL && ht->key_cmp(key, node->key) > 0) {
        node = node->next;
    } 

    if (node != NULL && ht->key_cmp(key, node->key) == 0) {
        return node->value;
    }

    return NULL;
}

/**** END of EXERCISE #2 ****/

