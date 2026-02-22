/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */
/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2016 University of Piemonte Orientale, Computer Science Institute
 */

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/test.h>

#define TEST_OK 1
#define TEST_FAIL 0

// Implementazioni delle funzioni di esercizio (copiate da exam-sample_02/exam.c)
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

size_t upo_bst_subtree_count_even(const upo_bst_t bst, const void *key) {
    if (upo_bst_is_empty(bst) || key ==NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if (node == NULL) return 0;
    
    return upo_bst_subtree_count_even_impl(node, depth);
}

size_t upo_bst_subtree_count_even_impl(upo_bst_node_t* node, size_t depth) {
    if (node == NULL) return 0;
    
    size_t count = 0;
    
    if ((depth % 2) == 0) {
        count = 1;
    }
    return count+ upo_bst_subtree_count_even_impl(node->left, depth + 1)+ upo_bst_subtree_count_even_impl(node->right, depth + 1);;
}

// Helper function to find a node and track depth
upo_bst_node_t* findNode(upo_bst_node_t* node, const void* key, upo_bst_comparator_t key_cmp, size_t *depth) {
    if (node == NULL) return NULL;
    
    int cmp = key_cmp(key, node->key);
    
    if (cmp == 0) {
        return node;  // Found
    }
    else if (cmp < 0) {
        (*depth)++;
        return findNode(node->left, key, key_cmp, depth);
    }
    else {
        (*depth)++;
        return findNode(node->right, key, key_cmp, depth);
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
size_t upo_bst_subtree_count_greater(const upo_bst_t bst, const void *subtree_key, const void *threshold) {
    if (bst == NULL || bst->root == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, subtree_key, bst->key_cmp, &depth);
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


// La funzione conta quanti nodi nel sottoalbero radicato nel nodo con chiave key hanno altezza (height) esattamente uguale a target_height.
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

// Helper per creare BST
upo_bst_t create_test_bst1() {
    /*
     * BST:
     *       8
     *     /   \
     *    3     10
     *   / \     \
     *  1   6     14
     *     / \   /
     *    4   7 13
     */
    int *keys[] = {malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int)), 
                   malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int)),
                   malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int))};
    int *values[] = {malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int)),
                     malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int)),
                     malloc(sizeof(int)), malloc(sizeof(int)), malloc(sizeof(int))};
    
    *keys[0] = 8; *keys[1] = 3; *keys[2] = 1; *keys[3] = 6;
    *keys[4] = 4; *keys[5] = 7; *keys[6] = 10; *keys[7] = 14; *keys[8] = 13;
    
    for (int i = 0; i < 9; i++) *values[i] = i;
    
    upo_bst_t bst = upo_bst_create(upo_test_int_cmp);
    for (int i = 0; i < 9; i++) {
        upo_bst_put(bst, keys[i], values[i]);
    }
    
    return bst;
}

// Test per upo_bst_subtree_count_even
int test_count_even() {
    printf("\n=== Test di upo_bst_subtree_count_even ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, key3 = 3;
    size_t result;
    
    result = upo_bst_subtree_count_even(bst, &key8);
    printf("Nodi a profondità pari da chiave 8: %zu (atteso: 5)\n", result);
    
    result = upo_bst_subtree_count_even(bst, &key3);
    printf("Nodi a profondità pari da chiave 3: %zu (atteso: 3)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_odd
int test_count_odd() {
    printf("\n=== Test di upo_bst_subtree_count_odd ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, key3 = 3;
    size_t result;
    
    result = upo_bst_subtree_count_odd(bst, &key8);
    printf("Nodi a profondità dispari da chiave 8: %zu (atteso: 4)\n", result);
    
    result = upo_bst_subtree_count_odd(bst, &key3);
    printf("Nodi a profondità dispari da chiave 3: %zu (atteso: 2)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_leaves
int test_count_leaves() {
    printf("\n=== Test di upo_bst_subtree_count_leaves ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, key3 = 3, key6 = 6;
    size_t result;
    
    result = upo_bst_subtree_count_leaves(bst, &key8);
    printf("Foglie da chiave 8: %zu (atteso: 4)\n", result);
    
    result = upo_bst_subtree_count_leaves(bst, &key3);
    printf("Foglie da chiave 3: %zu (atteso: 3)\n", result);
    
    result = upo_bst_subtree_count_leaves(bst, &key6);
    printf("Foglie da chiave 6: %zu (atteso: 2)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_internal
int test_count_internal() {
    printf("\n=== Test di upo_bst_subtree_count_internal ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, key3 = 3;
    size_t result;
    
    result = upo_bst_subtree_count_internal(bst, &key8);
    printf("Nodi interni da chiave 8: %zu (atteso: 5)\n", result);
    
    result = upo_bst_subtree_count_internal(bst, &key3);
    printf("Nodi interni da chiave 3: %zu (atteso: 2)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_left_only
int test_count_left_only() {
    printf("\n=== Test di upo_bst_subtree_count_left_only ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, key10 = 10;
    size_t result;
    
    result = upo_bst_subtree_count_left_only(bst, &key8);
    printf("Nodi con solo figlio sinistro da chiave 8: %zu (atteso: 1)\n", result);
    
    result = upo_bst_subtree_count_left_only(bst, &key10);
    printf("Nodi con solo figlio sinistro da chiave 10: %zu (atteso: 1)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_right_only
int test_count_right_only() {
    printf("\n=== Test di upo_bst_subtree_count_right_only ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, key10 = 10;
    size_t result;
    
    result = upo_bst_subtree_count_right_only(bst, &key8);
    printf("Nodi con solo figlio destro da chiave 8: %zu (atteso: 1)\n", result);
    
    result = upo_bst_subtree_count_right_only(bst, &key10);
    printf("Nodi con solo figlio destro da chiave 10: %zu (atteso: 0)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_full
int test_count_full() {
    printf("\n=== Test di upo_bst_subtree_count_full ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, key3 = 3;
    size_t result;
    
    result = upo_bst_subtree_count_full(bst, &key8);
    printf("Nodi con entrambi i figli da chiave 8: %zu (atteso: 3)\n", result);
    
    result = upo_bst_subtree_count_full(bst, &key3);
    printf("Nodi con entrambi i figli da chiave 3: %zu (atteso: 1)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_at_depth
int test_count_at_depth() {
    printf("\n=== Test di upo_bst_subtree_count_at_depth ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8;
    size_t result;
    
    result = upo_bst_subtree_count_at_depth(bst, &key8, 0);
    printf("Nodi a profondità 0 da chiave 8: %zu (atteso: 1)\n", result);
    
    result = upo_bst_subtree_count_at_depth(bst, &key8, 1);
    printf("Nodi a profondità 1 da chiave 8: %zu (atteso: 2)\n", result);
    
    result = upo_bst_subtree_count_at_depth(bst, &key8, 2);
    printf("Nodi a profondità 2 da chiave 8: %zu (atteso: 3)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_greater
int test_count_greater() {
    printf("\n=== Test di upo_bst_subtree_count_greater ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, threshold5 = 5, threshold10 = 10;
    size_t result;
    
    result = upo_bst_subtree_count_greater(bst, &key8, &threshold5);
    printf("Nodi > 5 da chiave 8: %zu (atteso: 5)\n", result);
    
    result = upo_bst_subtree_count_greater(bst, &key8, &threshold10);
    printf("Nodi > 10 da chiave 8: %zu (atteso: 2)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_smaller
int test_count_smaller() {
    printf("\n=== Test di upo_bst_subtree_count_smaller ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, threshold5 = 5, threshold10 = 10;
    size_t result;
    
    result = upo_bst_subtree_count_smaller(bst, &key8, &threshold5);
    printf("Nodi < 5 da chiave 8: %zu (atteso: 2)\n", result);
    
    result = upo_bst_subtree_count_smaller(bst, &key8, &threshold10);
    printf("Nodi < 10 da chiave 8: %zu (atteso: 6)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_range
int test_count_range() {
    printf("\n=== Test di upo_bst_subtree_count_range ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, min3 = 3, max10 = 10, min5 = 5, max8 = 8;
    size_t result;
    
    result = upo_bst_subtree_count_range(bst, &key8, &min3, &max10);
    printf("Nodi in range [3,10] da chiave 8: %zu (atteso: 6)\n", result);
    
    result = upo_bst_subtree_count_range(bst, &key8, &min5, &max8);
    printf("Nodi in range [5,8] da chiave 8: %zu (atteso: 3)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_depth_multiple
int test_count_depth_multiple() {
    printf("\n=== Test di upo_bst_subtree_count_depth_multiple ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8;
    size_t result;
    
    result = upo_bst_subtree_count_depth_multiple(bst, &key8, 2);
    printf("Nodi a profondità multipla di 2 da chiave 8: %zu (atteso: 5)\n", result);
    
    result = upo_bst_subtree_count_depth_multiple(bst, &key8, 3);
    printf("Nodi a profondità multipla di 3 da chiave 8: %zu (atteso: 3)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

// Test per upo_bst_subtree_count_height
int test_count_height() {
    printf("\n=== Test di upo_bst_subtree_count_height ===\n");
    upo_bst_t bst = create_test_bst1();
    int key8 = 8, key3 = 3;
    size_t result;
    
    result = upo_bst_subtree_count_height(bst, &key8, 0);
    printf("Nodi con altezza 0 da chiave 8: %zu (atteso: 4 foglie)\n", result);
    
    result = upo_bst_subtree_count_height(bst, &key8, 1);
    printf("Nodi con altezza 1 da chiave 8: %zu\n", result);
    
    result = upo_bst_subtree_count_height(bst, &key3, 0);
    printf("Nodi con altezza 0 da chiave 3: %zu (atteso: 3 foglie)\n", result);
    
    upo_bst_destroy(bst, 1);
    printf("Test completato.\n");
    return TEST_OK;
}

int main() {
    printf("*** [DISCLAIMER] ***************************************************************\n");
    printf("The following tests are provided as is, to allow you to quickly test your code.\n");
    printf("However, passing these tests is a necessary but not sufficient condition,\n");
    printf("meaning that they do not guarantee that your code is correct.\n");
    printf("In fact, your code may be wrong even it passes all these tests\n");
    printf("********************************************************************************\n\n");

    test_count_even();
    test_count_odd();
    test_count_leaves();
    test_count_internal();
    test_count_left_only();
    test_count_right_only();
    test_count_full();
    test_count_at_depth();
    test_count_greater();
    test_count_smaller();
    test_count_range();
    test_count_depth_multiple();
    test_count_height();

    printf("\n=== TUTTI I TEST COMPLETATI ===\n");
    return 0;
}