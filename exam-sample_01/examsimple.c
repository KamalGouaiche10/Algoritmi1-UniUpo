/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */


/******************************************************************************/
/*** NOME:KAMAL                                                             ***/
/*** COGNOME: GOUAICHE                                                      ***/
/*** MATRICOLA: 20054145                                                    ***/
/******************************************************************************/


#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/sort.h>


/**** BEGIN of EXERCISE #1 ****/

const void* upo_bst_predecessor(const upo_bst_t bst, const void *key) {
    if(key==NULL ||upo_bst_is_empty(bst))return NULL;

    upo_bst_node_t*node=bst->root;
    upo_bst_node_t*pred=NULL;

    upo_bst_comparator_t cmp=bst->key_cmp;

    while(node!=NULL){
        int cmp1=cmp(key,node->key);
        if(cmp1>0){
            pred=node;
            node=node->right;
        }
        else{node=node->left;}
    }
    return pred ? pred->key : NULL;
}


const void* upo_bst_successor(const upo_bst_t bst, const void *key) {
    if (key == NULL || upo_bst_is_empty(bst)) {
        return NULL;
    }
    
    upo_bst_node_t *current = bst->root;
    upo_bst_node_t *successor = NULL;
    
    while (current != NULL) {
        int cmp_result = bst->key_cmp(key, current->key);
        
        if (cmp_result < 0) {
            successor = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return successor ? successor->key : NULL;
}

/**
 * @brief Check function to find successor - reference implementation for testing
 */
const void* upo_bst_check_successor(const upo_bst_t bst, const void *key)
{
    if (bst == NULL || key == NULL || upo_bst_is_empty(bst)) {
        return NULL;
    }
    
    upo_bst_node_t *current = bst->root;
    upo_bst_node_t *successor = NULL;
    
    while (current != NULL) {
        int cmp = bst->key_cmp(key, current->key);
        
        if (cmp < 0) {
            successor = current;
            current = current->left;
        } else if (cmp > 0) {
            current = current->right;
        } else {
            if (current->right != NULL) {
                current = current->right;
                while (current->left != NULL) {
                    current = current->left;
                }
                return current->key;
            }
            break;
        }
    }
    
    return successor ? successor->key : NULL;
}

/**** END of EXERCISE #1 ****/


/**** BEGIN of EXERCISE #2 ****/
void upo_swap(void *p1, void *p2, size_t size);
void upo_bidi_bubble_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if(base==NULL || n<=1){
        fprintf(stderr,"Errore: la base dell'array non puo essere NULL");
        return;
    }
    unsigned char*pc=base;
    size_t left=0;
    size_t right=n-1;
    int swapped=1;

    while(left <right && swapped){
        swapped=0;
        for(size_t i=left;i<right;i++){
            if(cmp(pc+i*size,pc+(i+1)*size)>0){
                upo_swap(pc+i*size,pc+(i+1)*size,size);
                swapped=1;
            }
        }
        right--;
        if(!swapped) break;

         for(size_t i=right;i>left;i--){
            if(cmp(pc+i*size,pc+(i-1)*size)<0){
                upo_swap(pc+(i-1)*size,pc+i*size,size);
                swapped=1;
            }
        }
        left++;
    }

}

// Implementazione corretta di Insertion Sort Bidirezionale
void upo_bidi_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if(base == NULL || n <= 1) {
        if(base == NULL) {
            fprintf(stderr, "The base of array can't be NULL");
        }
        return;
    }

    unsigned char *pc = base;
    size_t left = 0;
    size_t right = n - 1;

    while(left < right) {
        for(size_t i = left + 1; i <= right; i++) {
            unsigned char temp[size];
            memcpy(temp, pc + i * size, size);
            
            size_t j = i;
            while(j > left && cmp(temp,pc + (j - 1) * size) < 0) {
                memcpy(pc + j * size, pc + (j - 1) * size, size);
                j--;
            }
            memcpy(pc + j * size, temp, size);
        }
        left++; 

        if(left < right) {
            for(size_t i = right; i > left; i--) {
                unsigned char temp[size];
                memcpy(temp, pc + (i - 1) * size, size);
                
                size_t j = i - 1;
                while(j < right && cmp(temp, pc + (j + 1) * size) > 0) {
                    memcpy(pc + j * size, pc + (j + 1) * size, size);
                    j++;
                }
                memcpy(pc + j * size, temp, size);
            }
            right--;
        }
    }
}

void upo_bidi_selection_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if(base==NULL || n<=1){
        return;
    }

    unsigned char *pc=base;
    size_t left=0;
    size_t right=n-1;

    while(left<=right){
        size_t min_idx=left;
        size_t max_idx=left;

        for(size_t i=left;i<=right;i++){
            if(cmp(pc+i*size,pc+min_idx*size)<0){
                min_idx=i;
            }
            if(cmp(pc+i*size,pc+max_idx*size)>0){
                max_idx=i;
            }
        }

        if(max_idx==left){
              max_idx=min_idx;
        }
        if(min_idx!=left){
            upo_swap(pc+left*size,pc+min_idx*size,size);
        }
         if(max_idx!=right){
            upo_swap(pc+right*size,pc+max_idx*size,size);
        }

       left++;
       right--;

    }

}

void upo_swap(void *p1,void *p2,size_t size){
    unsigned char* pc1=p1;
    unsigned char* pc2=p2;

    while(size--){
        unsigned char temp=*pc1;
        *pc1=*pc2;
        *pc2=temp;

        pc1++;
        pc2++;
    }
}
/**** END of EXERCISE #2 ****/