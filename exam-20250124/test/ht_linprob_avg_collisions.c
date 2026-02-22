/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2020 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/hashtable.h>
#include <upo/test.h>


#define TEST_OK 1
#define TEST_FAIL 0


static int test_ht1(void);
static int test_ht2(void);
static int test_ht3(void);
static int test_ht4(void);
static int test_ht5(void);
static int test_ht6(void);
static int test_empty_ht(void);
static int test_int_ht(int *keys, int *values, size_t n, int *no_keys, size_t m);
static int test_str_ht(char **keys, int *values, size_t n, char **no_keys, size_t m);
static int test_ht(void *keys, size_t key_sz, void *values, size_t value_sz, size_t n, void *no_keys, size_t m, upo_ht_hasher_t key_hasher, upo_ht_comparator_t key_cmp, char* (*key_to_string)(const void*), char* (*value_to_string)(const void*));
extern void upo_ht_linprob_dump(const upo_ht_linprob_t, FILE *, char* (*)(const void*), int, char* (*)(const void*), int);
extern void *upo_ht_linprob_put(upo_ht_linprob_t ht, void *key, void *value);
extern upo_ht_key_list_t upo_ht_key_list_create(void *keys, size_t key_size, size_t n);
extern double upo_ht_linprob_xyz(const upo_ht_linprob_t ht, const upo_ht_key_list_t key_list);


int main(void)
{
    const size_t n = 6;
    size_t i = 0;
    int ret = TEST_FAIL;

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
                ret = test_ht1();
                break;
            case 2:
                ret = test_ht2();
                break;
            case 3:
                ret = test_ht3();
                break;
            case 4:
                ret = test_ht4();
                break;
            case 5:
                ret = test_ht5();
                break;
            case 6:
                ret = test_ht6();
                break;
            default:
                fprintf(stderr, "ERROR: Unexpected test case number");
                abort();
        }
        printf("Test HT #%lu => %s\n", i, (ret == TEST_OK) ? "[OK]" : "[FAIL]");
    }

    ret = test_empty_ht();
    printf("Test Empty HT => %s\n", (ret == TEST_OK) ? "[OK]" : "[FAIL]");

    return 0;
}

//all keys present
int test_ht1(void)
{
    int keys[] = {0,60,120,180,240,300,360,420,480,540,600,1200,1800,2400,3000,3600,4200,4260,8400};
    int values[] = {0,1,2,3,4,5,6,7,8,9,1000,2000,3000,4000,5000,6000,7000,8000,9000};
    int no_keys[] = {1200,1800,2400,3000,3600,4200,4260,8400};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_int_ht(keys, values, n, no_keys, m);
}

//overlapping keys
int test_ht2(void)
{
    int keys[] = {0,60,120,180,240,300,360,420,480,540,600,1200,1800,2400,3000,3600,4200,4260,8400};
    int values[] = {0,1,2,3,4,5,6,7,8,9,1000,2000,3000,4000,5000,6000,7000,8000,9000};
    int no_keys[] = {1,22,10,20,30,40,307,508,709,1200,1800,2400,3000,3600,4200,4260,8400};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_int_ht(keys, values, n, no_keys, m);
}

//non overlapping keys
int test_ht3(void)
{
    int keys[] = {0,60,120,180,240,300,360,420,480,540,600,1200,1800,2400,3000,3600,4200,4260,8400};
    int values[] = {0,1,2,3,4,5,6,7,8,9,1000,2000,3000,4000,5000,6000,7000,8000,9000};
    int no_keys[] = {1,2,3,4,10,11,12,13,14,1000,2000,5000,6000,7000,8000,9000};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_int_ht(keys, values, n, no_keys, m);
}

int test_ht4(void)
{
    char *keys[] = {"AA","AB","AQ","Aa","Aq","Ba","Ca","Da","Ea","Fa","AAA", "Ab"};
    int values[] = {0,1,2,3,4,5,6,7,8,9,10,11};
    char *no_keys[] = {"Da","Ea","Fa","AAA", "Ab"};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_str_ht(keys, values, n, no_keys, m);
}

int test_ht5(void)
{
    char *keys[] = {"aaa","aba","aca","ada","aea","afa","aga","aha","aia","aja"};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    char *no_keys[] = {"a1a","a2a","a3a","a4a","a5a","a6a","aga","aha","aia","aja"};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_str_ht(keys, values, n, no_keys, m);
}

int test_ht6(void)
{
    char *keys[] = {"aaa","aab","aac","aad","aba","abb","abc","abd","abe","abf"};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    char *no_keys[] = {"AAA","AAX","AAC","AAY","ABA","ABZ"};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_str_ht(keys, values, n, no_keys, m);
}

int test_empty_ht(void)
{
    int dummy1 = 0;
    int dummy2 = 1;

    return test_int_ht(&dummy1, &dummy1, 0, &dummy2, 1);
}

int test_int_ht(int *keys, int *values, size_t n, int *no_keys, size_t m)
{
    assert( keys );
    assert( values );
    assert( no_keys );

    return test_ht(keys, sizeof keys[0], values, sizeof values[0], n, no_keys, m, upo_ht_hash_int_div, upo_test_int_cmp, upo_test_int_to_string, upo_test_int_to_string);
}

int test_str_ht(char **keys, int *values, size_t n, char **no_keys, size_t m)
{
    assert( keys );
    assert( values );
    assert( no_keys );

    return test_ht(keys, sizeof keys[0], values, sizeof values[0], n, no_keys, m, upo_ht_hash_str_kr2e, upo_test_str_cmp, upo_test_str_to_string, upo_test_int_to_string);
}

int test_ht(void *keys, size_t key_sz, void *values, size_t value_sz, size_t n, void *no_keys, size_t m, upo_ht_hasher_t key_hasher, upo_ht_comparator_t key_cmp, char* (*key_to_string)(const void*), char* (*value_to_string)(const void*))
{
    upo_ht_linprob_t ht = NULL;
    size_t base_cap = 3;
    size_t caps[4];
    size_t nc;
    unsigned char *pck = keys;
    unsigned char *pcv = values;
    int ret = TEST_OK;

/*
    caps[0] = 2*n+UPO_HT_SEPCHAIN_DEFAULT_CAPACITY;
    caps[1] = n*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY;
    caps[2] = UPO_HT_SEPCHAIN_DEFAULT_CAPACITY;
*/

    caps[0] = 3*n+base_cap;
    caps[1] = 2*n+base_cap;
    caps[2] = n*base_cap;
    caps[3] = base_cap;
    nc = sizeof caps/sizeof caps[0];

    upo_ht_key_list_t key_list = upo_ht_key_list_create(no_keys,key_sz,m);
    //upo_ht_key_list_node_t *ln;

    for (size_t k = 0; k < nc && ret == TEST_OK; ++k) 
    {
        ht = upo_ht_linprob_create(caps[k], key_hasher, key_cmp);

        assert( ht != NULL );

        if (n > 0)
        {
            // Non-empty HT

            // Populate the source HT
            for (size_t i = 0; i < n; ++i)
            {
                upo_ht_linprob_put(ht, pck + i*key_sz, pcv + i*value_sz);
            }
            
            // Check the average number of collisions of keys in list
            
            double avg = -2;
            double check_avg = -2;

            avg = upo_ht_linprob_avg_collisions(ht, key_list);
            check_avg = upo_ht_linprob_xyz(ht, key_list);

            if (avg != check_avg)
            {
                fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %lu -> Expected %.2f, got %.2f.\n", __FILE__, __LINE__, k, check_avg, avg);
                fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                upo_ht_linprob_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
            }
            
        }
        else {
            double avg = -2;
            double check_avg = -2;

            avg = upo_ht_linprob_avg_collisions(ht, key_list);
            check_avg = upo_ht_linprob_xyz(ht, key_list);
            
            if (avg != check_avg)
            {
                fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %lu -> Expected %.2f, got %.2f.\n", __FILE__, __LINE__, k, check_avg, avg);
                fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                upo_ht_linprob_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
            }        
        }

        upo_ht_linprob_destroy(ht, 0);
    }

    return ret;
}
