#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/hashtable.h> 


// 1. MASSIMO NUMERO DI COLLISIONI

// Calcola il massimo numero di collisioni tra le chiavi di una lista in una hash table con linear probing
// Ritorna -1 se la tabella è vuota, la lista è NULL, o nessuna chiave della lista è presente nella tabella
int upo_ht_linprob_max_collisions(const upo_ht_linprob_t ht, const upo_ht_key_list_t key_list)
{
    if (upo_ht_is_empty(ht) || key_list == NULL) return -1;

    int max_collision = -1;
    upo_ht_key_list_node_t *current = key_list;

    while (current != NULL)
    {
        size_t hash = ht->key_hash(current->key, ht->capacity);
        int collision = 0;

        for (int i = 0; i < ht->capacity; i++)
        {
            size_t pos = (hash + i) % ht->capacity;
            if(ht->slots[pos].key==NULL && !ht->slots[pos].tombstone){
                break;
            }
            else if(ht->slots[pos].key!=NULL && ht->key_cmp(current->key,ht->slots[pos].key)==0){
                if(max_collision<collision){
                    max_collision=collision;
                }
            }
            else{
                collision++;
            }
        }
        current=current->next;
    }

    return max_collision;
}

// Calcola la media delle collisioni per le chiavi di una lista presenti nella hash table
// Ritorna -1 se la tabella è vuota, la lista è NULL, o nessuna chiave della lista è presente nella tabella
double upo_ht_linprob_count_collisions(const upo_ht_linprob_t ht, void *key)
{
    double count = -1;

    if (ht != NULL && ht->slots != NULL && key != NULL)
    {
        size_t hash = ht->key_hash(key, ht->capacity);

        count = 0;
        while ((ht->slots[hash].key != NULL && ht->key_cmp(key, ht->slots[hash].key) != 0) || ht->slots[hash].tombstone != 0) 
        {
            hash = (hash+1) % ht->capacity;
            ++count;
        }
 
        if (ht->slots[hash].key == NULL)
        {
            count = -1;
        }
    }
    return count;
}
double upo_ht_linprob_avg_collisions(const upo_ht_linprob_t ht, const upo_ht_key_list_t key_list){
	if (key_list==NULL){
		return -1;
	}

	double sum = 0, nkeys=0;
	for (upo_ht_key_list_node_t *node=key_list;node!=NULL;node=node->next){
		double tmp = upo_ht_linprob_count_collisions(ht,node->key);

		if (tmp!=-1){
			nkeys++;
			sum = sum + tmp;
		}	
	} 

	if (nkeys==0){
		return -1;
	}
	return sum/nkeys;
}

// 2. CHIAVI SALVATE

// Restituisce la lista delle chiavi salvate in una hash table con separate chaining
// Scorre tutti gli slot e concatena le chiavi di tutte le liste di collisione
upo_ht_key_list_t upo_ht_sepchain_keys(const upo_ht_sepchain_t ht)
{
    if (upo_ht_is_empty(ht)) return NULL;

    upo_ht_key_list_t list = NULL;

    for (int i = 0; i < ht->capacity; i++){
        if (ht->slots[i].head != NULL) {
            for (upo_ht_sepchain_node_t *node = ht->slots[i].head; node != NULL; node = node->next)
            {
                upo_ht_key_list_node_t *list_node = malloc(sizeof(upo_ht_key_list_node_t));
                list_node->key = node->key;
                list_node->next = list;
                list = list_node;
            }
        }
    }
    return list;
}
// Restituisce la lista delle chiavi salvate in una hash table con linear probing
// Scorre tutti gli slot e raccoglie le chiavi non-NULL (escludendo i tombstone)
upo_ht_key_list_t upo_ht_linprob_keys(const upo_ht_linprob_t ht)
{
    if (upo_ht_linprob_is_empty(ht)) return NULL;

    upo_ht_key_list_t list = NULL;

    for (int i = 0; i < ht->capacity; i++)
    {
        if (ht->slots[i].keys != NULL)
        {
            upo_ht_key_list_node_t *node = malloc(sizeof(upo_ht_key_list_node_t));
            node->key = ht->slots[i].keys;
            node->next = list;
            list = node;
        }
    }
    return list;
}


// 3. PREDECESSORE

// Trova il predecessore di una chiave k in un BST (la più grande chiave minore di k)
// Ritorna NULL se il predecessore non esiste o se il BST è vuoto
const void *upo_bst_predecessor(const upo_bst_t bst, const void *key)
{
    if (bst == NULL || key == NULL) return NULL;
    return upo_bst_predecessor_impl(bst->root, key, bst->key_cmp);
}

// Implementazione ricorsiva del predecessore: cerca a sinistra se nodo >= key, altrimenti a destra
// Mantiene il miglior candidato trovato finora durante la ricerca
void *upo_bst_predecessor_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t key_cmp)
{
    if (node == NULL) return NULL;

    if (key_cmp(node->key, key) >= 0)
        return upo_bst_predecessor_impl(node->left, key, key_cmp);

    void *pred = upo_bst_predecessor_impl(node->right, key, key_cmp);
    if (pred == NULL)
        return node->key;
    else
        return pred;
}

// 4. RANGO
// Calcola il rango di una chiave k (numero di chiavi minori di k nel BST)
// Attraversa l'albero in-order contando le chiavi minori della chiave data
size_t upo_bst_rank(const upo_bst_t bst, const void *key)
{
    if (bst == NULL || key == NULL) return 0;

    size_t result = 0;
    upo_bst_rank_impl(bst->root, key, &result, bst->key_cmp);
    return result;
}

// Implementazione ricorsiva del rango: visita in-order e conta le chiavi minori
// Incrementa il contatore quando trova una chiave minore della chiave target
void upo_bst_rank_impl(upo_bst_node_t *node, const void *key, size_t *result, upo_bst_comparator_t key_cmp)
{
    if (node == NULL) return;

    upo_bst_rank_impl(node->left, key, result, key_cmp);

    if (key_cmp(key,node->key)  > 0)
        (*result)++;

    upo_bst_rank_impl(node->right, key, result, key_cmp);
}

// 5. NUMERO DI FOGLIE DEL SOTTO-ALBERO RADICATO IN K

// Conta le foglie nel sotto-albero radicato in k che si trovano a profondità d
// Prima trova il nodo con chiave k, poi conta le foglie alla profondità specificata
size_t upo_bst_subtree_count_leaves_depth(const upo_bst_t bst, const void *key, size_t d)
{
    if (bst == NULL || key == NULL || d < 0) return 0;

    upo_bst_node_t *node = upo_bst_find_node(bst->root, key, bst->key_cmp);
    if (node == NULL) return 0;

    return upo_bst_subtree_count_leaves_depth_impl(node, d);
}

// Implementazione ricorsiva: conta i nodi foglia alla profondità d dal nodo corrente
// Una foglia è un nodo senza figli; conta solo se si trova alla profondità target
size_t upo_bst_subtree_count_leaves_depth_impl(upo_bst_node_t *node, size_t depth)
{
    if (node == NULL) return 0;
    
    int count = 0;
    if (depth == 0 && node->left == NULL && node->right == NULL) 
        count = 1;

    return count + upo_bst_subtree_count_leaves_depth_impl(node->left, depth - 1) + upo_bst_subtree_count_leaves_depth_impl(node->right, depth - 1);
}

// 6. CHIAVI MINORI O UGUALI A UNA CHIAVE K

// Restituisce la lista delle chiavi nel BST che sono minori o uguali a k
// Utilizza un attraversamento in-order per raccogliere le chiavi in ordine
upo_bst_key_list_t upo_bst_keys_le(const upo_bst_t bst, const void *key)
{
    if (bst == NULL || key == NULL) return NULL;
    
    upo_bst_key_list_t list = NULL;
    upo_bst_keys_le_impl(bst->root, key, bst->key_cmp, &list);
    return list;
}

// Implementazione ricorsiva: attraversa in-order e aggiunge le chiavi <= k alla lista
// Costruisce la lista in ordine inverso per efficienza (inserimento in testa)
void upo_bst_keys_le_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t key_cmp, upo_bst_key_list_t *list)
{
    if (node != NULL)
    {
        upo_bst_keys_le_impl(node->left, key, key_cmp, list);

        if (key_cmp(node->key, key) <= 0)
        {
            upo_bst_key_list_node_t *list_node = malloc(sizeof(upo_bst_key_list_node_t));
            list_node->key = node->key;
            list_node->next = *list;
            *list = list_node;
        }

        upo_bst_keys_le_impl(node->right, key, key_cmp, list);
    }
}

// 7. SOMMA DEI VALORI CON CHIAVE COMPRESA

// Calcola la somma dei valori le cui chiavi sono comprese nell'intervallo [low, high]
// Ottimizza la ricerca visitando solo i sotto-alberi necessari
void *upo_bst_sum_in_range(const upo_bst_t tree, const void *low, const void *high)
{
    if (tree == NULL || low == NULL || high == NULL) return 0;
    return upo_bst_sum_in_range_impl(tree->root, low, high, tree->key_cmp);
}

// Implementazione ricorsiva: somma i valori nell'intervallo, pota i rami non necessari
// Visita il sotto-albero sinistro solo se necessario, idem per quello destro
void *upo_bst_sum_in_range_impl(upo_bst_node_t *node, const void *low, const void *high, upo_bst_comparator_t key_cmp)
{
    if (node == NULL) return 0;
    
    int sum = 0;
    size_t cmp_low = key_cmp(node->key, low);
    size_t cmp_high = key_cmp(node->key, high);

    if (cmp_low >= 0 && cmp_high <= 0)
        sum += *(int*)node->value;

    if (cmp_low > 0)
        sum += (int)upo_bst_sum_in_range_impl(node->left, low, high, key_cmp);
    if (cmp_high < 0)
        sum += (int)upo_bst_sum_in_range_impl(node->right, low, high, key_cmp);

    return sum;
}


// 9. N-ESIMA CHIAVE PIÙ PICCOLA

// Trova l'n-esima chiave più piccola nel sotto-albero radicato in k
// Prima trova il nodo con chiave k, poi esegue una visita in-order per trovare l'n-esima chiave
void *upo_bst_nmin(const upo_bst_t tree, const void *key, const int n)
{
    if (tree == NULL || key == NULL || n <= 0) return NULL;

    upo_bst_node_t *node = upo_bst_find_node(tree->root, key, tree->key_cmp);
    if (node == NULL) return NULL;

    int copyN = n;
    return upo_bst_nmin_impl(node, &copyN);
}

// Implementazione ricorsiva: visita in-order e decrementa n fino a raggiungere 0
// Quando n raggiunge 0, abbiamo trovato l'n-esima chiave più piccola
void *upo_bst_nmin_impl(upo_bst_node_t *node, int *n)
{
    if (node == NULL) return NULL;

    void *left = upo_bst_nmin_impl(node->left, n);
    if (left != NULL) return left;

    (*n)--;
    if (*n == 0) return node->key;

    return upo_bst_nmin_impl(node->right, n);
}

// 10. VALORE E PROFONDITÀ DI UNA CHIAVE

// Restituisce il valore di una chiave e la sua profondità nel BST
// Ritorna NULL e depth = -1 se la chiave non è trovata
void *upo_bst_get_value_depth(const upo_bst_t bst, const void *key, long *depth)
{
    if (bst == NULL || key == NULL || depth == NULL)
    {
        if (depth != NULL) *depth = -1;
        return NULL;
    }

    *depth = 0;
    return upo_bst_get_value_depth_impl(bst->root, key, depth, bst->key_cmp);
}

// Implementazione ricorsiva: cerca la chiave e tiene traccia della profondità
// Incrementa depth ad ogni livello di ricorsione, resetta a -1 se non trovata
void *upo_bst_get_value_depth_impl(upo_bst_node_t *node, const void *key, long *depth, upo_bst_comparator_t key_cmp)
{
    if (node == NULL)
    {
        *depth = -1;
        return NULL;
    }

    int cmp = key_cmp(node->key, key);

    if (cmp == 0)
        return node->value;
    else if (cmp > 0)
    {
        (*depth)++;
        return upo_bst_get_value_depth_impl(node->left, key, depth, key_cmp);
    }
    else
    {
        (*depth)++;
        return upo_bst_get_value_depth_impl(node->right, key, depth, key_cmp);
    }
}

// =============================================================================
// FUNZIONI AUSILIARIE
// =============================================================================

// Trova un nodo con una data chiave nel BST (versione base)
// Implementazione standard di ricerca in un BST
upo_bst_node_t *upo_bst_find_node(upo_bst_node_t *node, const void *key, upo_bst_comparator_t key_cmp)
{
    if (node == NULL) return NULL;

    int cmp = key_cmp(node->key, key);

    if (cmp == 0)
        return node;
    else if (cmp > 0)
        return upo_bst_find_node(node->left, key, key_cmp);
    else
        return upo_bst_find_node(node->right, key, key_cmp);
}

// Trova un nodo con una data chiave mantenendo traccia della profondità
// Versione estesa che calcola anche la profondità del nodo trovato
upo_bst_node_t *upo_bst_find_node_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t key_cmp, size_t *depth)
{
    if (node == NULL) return NULL;

    size_t cmp = key_cmp(node->key, key);

    if (cmp == 0) return node;
    else if (cmp > 0)
    {
        (*depth)++;
        return upo_bst_find_node_impl(node->left, key, key_cmp, depth);
    }
    else
    {
        (*depth)++;
        return upo_bst_find_node_impl(node->right, key, key_cmp, depth);
    }
}