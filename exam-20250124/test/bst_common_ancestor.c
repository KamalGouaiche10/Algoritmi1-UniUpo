/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2016 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib developed by Marco Guazzone, Università del Piemonte Orientale.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
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


static int test_bst1(void);
static int test_bst2(void);
static int test_bst3(void);
static int test_bst4(void);
static int test_bst5(void);
static int test_bst6(void);
static int test_bst7(void);
static int test_bst8(void);
static int test_bst9(void);
static int test_bst10(void);
static int test_bst11(void);
static int test_bst12(void);
static int test_bst13(void);
static int test_bst14(void);
static int test_bst15(void);
static int test_empty_bst(void);
static int test_int_bst(int *keys, int *values, size_t n, int *key1, int *key2);
static int test_str_bst(char **keys, int *values, size_t n, char **key1, char **key2);
static int test_bst(void *keys, size_t key_sz, void *values, size_t value_sz, size_t n, void *key1, void *key2, upo_bst_comparator_t key_cmp, char* (*key_to_string)(const void*), char* (*value_to_string)(const void*));
extern void* upo_bst_xyz(upo_bst_t, void*, void*);
extern void upo_bst_dump(const upo_bst_t, FILE *, char* (*)(const void*), int, char* (*)(const void*), int);
extern void* upo_bst_put(upo_bst_t, void*, void*);


int main(void)
{
    size_t n = 15;
    size_t i = 0;
    int ret = 0;

    printf("*** [DISCLAIMER] ***************************************************************\n");
    printf("The following tests are provided as is, to allow you to quickly test your code.\n");
    printf("However, passing these tests is a necessary but not sufficient condition,\n");
    printf("meaning that they do not guarantee that your code is correct.\n");
    printf("In fact, your code may be wrong even it passes all these tests\n");
    printf("********************************************************************************\n\n");

    for (i = 1; i <= n; ++i)
    {
        switch (i)
        {
            case 1:
                ret = test_bst1();
                break;
            case 2:
                ret = test_bst2();
                break;
            case 3:
                ret = test_bst3();
                break;
            case 4:
                ret = test_bst4();
                break;
            case 5:
                ret = test_bst5();
                break;
            case 6:
                ret = test_bst6();
                break;
            case 7:
                ret = test_bst7();
                break;
            case 8:
                ret = test_bst8();
                break;
            case 9:
                ret = test_bst9();
                break;
            case 10:
                ret = test_bst10();
                break;
            case 11:
                ret = test_bst11();
                break;
            case 12:
                ret = test_bst12();
                break;
            case 13:
                ret = test_bst13();
                break;
            case 14:
                ret = test_bst14();
                break;
            case 15:
                ret = test_bst15();
                break;
            default:
                fprintf(stderr, "[file: %s, line: %d] Unexpected test case number\n", __FILE__, __LINE__);
                abort();
        }
        printf("Test BST #%lu => %s\n", i, (ret == TEST_OK) ? "[OK]" : "[FAIL]");
    }

    ret = test_empty_bst();
    printf("Test Empty BST => %s\n", (ret == TEST_OK) ? "[OK]" : "[FAIL]");

    return 0;
}

int test_bst1(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 8, key2 = 14;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst2(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 3, key2 = 13;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst3(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 1, key2 = 6;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst4(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 5, key2 = 10;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst5(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 6, key2 = 4;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst6(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 14, key2 = 19;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst7(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 10, key2 = 0;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst8(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 4, key2 = 7;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst9(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 7, key2 = 1;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst10(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 13, key2 = 15;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst11(void)
{
    /*
     * BST:
     *          8
     *         / \
     *        3   10
     *       / \    \
     *      1   6    14
     *         / \   /
     *        4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t n = sizeof keys/sizeof keys[0];
    int key1 = 9, key2 = 3;

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_int_bst(keys, values, n, &key1, &key2);
}

int test_bst12(void)
{
    /*
     * BST:
     *         "aae"
     *          / \
     *      "aac" "aaj"
     *       / \      \
     *   "aaa" "aad" "aak"
     */

    char* keys[] = {"aae", "aaj", "aac", "aad", "aaa", "aak"};
    int values[] = {-5, -10, -3, -4, -1, -11};
    size_t n = sizeof keys/sizeof keys[0];
    char *key1 = "aac", *key2 = "aad";

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_str_bst(keys, values, n, &key1, &key2);
}

int test_bst13(void)
{
    /*
     * BST:
     *         "aae"
     *          / \
     *      "aac" "aaj"
     *       / \      \
     *   "aaa" "aad" "aak"
     */

    char* keys[] = {"aae", "aaj", "aac", "aad", "aaa", "aak"};
    int values[] = {-5, -10, -3, -4, -1, -11};
    size_t n = sizeof keys/sizeof keys[0];
    char *key1 = "aaj", *key2 = "aak";

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_str_bst(keys, values, n, &key1, &key2);
}

int test_bst14(void)
{
    /*
     * BST:
     *         "aae"
     *          / \
     *      "aac" "aaj"
     *       / \      \
     *   "aaa" "aad" "aak"
     */

    char* keys[] = {"aae", "aaj", "aac", "aad", "aaa", "aak"};
    int values[] = {-5, -10, -3, -4, -1, -11};
    size_t n = sizeof keys/sizeof keys[0];
    char *key1 = "aaa", *key2 = "aak";

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_str_bst(keys, values, n, &key1, &key2);
}

int test_bst15(void)
{
    /*
     * BST:
     *         "aae"
     *          / \
     *      "aac" "aaj"
     *       / \      \
     *   "aaa" "aad" "aak"
     */

    char* keys[] = {"aae", "aaj", "aac", "aad", "aaa", "aak"};
    int values[] = {-5, -10, -3, -4, -1, -11};
    size_t n = sizeof keys/sizeof keys[0];
    char *key1 = "aak", *key2 = "aaf";

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );

    return test_str_bst(keys, values, n, &key1, &key2);
}

int test_empty_bst(void)
{
    return test_int_bst(NULL, NULL, 0, NULL, NULL);
}

int test_int_bst(int *keys, int *values, size_t n, int *key1, int *key2)
{
    return test_bst(keys, sizeof keys[0], values, sizeof values[0], n, key1, key2, upo_test_int_cmp, upo_test_int_to_string, upo_test_int_to_string);
}

int test_str_bst(char **keys, int *values, size_t n, char **key1, char **key2)
{
    return test_bst(keys, sizeof keys[0], values, sizeof values[0], n, key1, key2, upo_test_str_cmp, upo_test_str_to_string, upo_test_int_to_string);
}

int test_bst(void *keys, size_t key_sz, void *values, size_t value_sz, size_t n, void *key1, void *key2, upo_bst_comparator_t key_cmp, char* (*key_to_string)(const void*), char* (*value_to_string)(const void*))
{
    upo_bst_t bst = NULL;
    unsigned char *pck = keys;
    unsigned char *pcv = values;
    size_t i;
    int ret = TEST_OK;

    /* Creates BST */

    bst = upo_bst_create(key_cmp);

    assert( bst != NULL );

    if (n > 0)
    {
        // Non-empty BST

        // Populate BST

        for (i = 0; i < n; ++i)
        {
            upo_bst_put(bst, pck + i*key_sz, pcv + i*value_sz);
        }

        /* Find LCA */

        void *k = NULL;
        void *check_k = NULL; 

        k = upo_bst_lca(bst, key1, key2);
        check_k = upo_bst_xyz(bst, key1, key2);

        if ((k!=NULL) && (check_k!=NULL))
        {   
            if (key_cmp(k,check_k)!=0){
                char *key1_str = key_to_string(key1);
                char *key2_str = key_to_string(key2);
                char *check_str = key_to_string(check_k);
                char *key_str = key_to_string(k);

                fprintf(stderr, "[file: %s, line: %d] ERROR: Keys: '%s','%s' -> Expected '%s', got '%s'.\n", __FILE__, __LINE__, key1_str,key2_str,check_str,key_str);
                fprintf(stderr, "[file: %s, line: %d]: <BST>\n", __FILE__, __LINE__);
                upo_bst_dump(bst, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </BST>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
            }
        }
        else if ((k==NULL) && (check_k!=NULL)){
                char *key1_str = key_to_string(key1);
                char *key2_str = key_to_string(key2);
                char *check_str = key_to_string(check_k);

                fprintf(stderr, "[file: %s, line: %d] ERROR: Keys: '%s','%s' -> Expected ancestor '%s', got none.\n", __FILE__, __LINE__, key1_str, key2_str, check_str);
                fprintf(stderr, "[file: %s, line: %d]: <BST>\n", __FILE__, __LINE__);
                upo_bst_dump(bst, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </BST>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
        }
        else if ((k!=NULL) && (check_k==NULL)){
                char *key1_str = key_to_string(key1);
                char *key2_str = key_to_string(key2);
                char *k_str = key_to_string(k);
                fprintf(stderr, "[file: %s, line: %d] ERROR: Keys: '%s','%s' -> Expected no ancestor, got '%s'.\n", __FILE__, __LINE__, key1_str, key2_str, k_str);
                fprintf(stderr, "[file: %s, line: %d]: <BST>\n", __FILE__, __LINE__);
                upo_bst_dump(bst, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </BST>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
        }
    }
    else
    {
        // Empty BST

        void *k = upo_bst_lca(bst, key1, key2);

        if (k != NULL)
        {
            fprintf(stderr, "[file: %s, line: %d] ERROR: Empty BST -> Expected NULL, got %s.\n", __FILE__, __LINE__, key_to_string(k));
            ret = TEST_FAIL;
        }
    }

    /* Destroy */
 
    upo_bst_destroy(bst, 0);

    return ret;
}
