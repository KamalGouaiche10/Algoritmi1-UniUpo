# Algoritmi - Raccolta di Esercizi e Progetti in C

Questo repository contiene una collezione di esercizi programmati in **C**, focalizzati su algoritmi, strutture dati e concetti avanzati di programmazione come puntatori, puntatori a funzioni e gestione della memoria.

## Struttura del Repository
### 📋 Progetti d'Esame

#### **exam-20250124/**
Progetto d'esame del 24 gennaio 2025.
- **Contenuti**:
  - `exam20250124.c`: Implementazione principale
  - `exam.pdf`: Specifiche del problema
  - `include/upo/`: Header files per strutture dati
    - `bst.h`: Binary Search Tree
    - `hashtable.h`: Hash Table
    - `test.h`: Utility per test
  - `test/`: Test cases
    - `bst_common_ancestor.c`: Trovare il Lowest Common Ancestor in un BST
    - `ht_linprob_avg_collisions.c`: Calcolare collisioni medie in hash table con linear probing
  - `lib/`: Directory per librerie compilate
  - `Makefile`: Build configuration
- **Compilazione**: `make`

#### **exam-sample_01/**
Primo progetto campione d'esame.
- **Contenuti**:
  - `examsimple.c`: Implementazione
  - `include/upo/`: Header files
    - `bst.h`: Binary Search Tree
    - `sort.h`: Algoritmi di ordinamento
    - `test.h`: Utility
  - `test/`: Test cases
    - `bidi_bubble_sort.c`: Bubble sort bidirezionale
    - `bst_predecessor.c`: Predecessore in BST
    - `bst_successor.c`: Successore in BST
    - `upo_bidi_insertion_sort.c`: Insertion sort bidirezionale
    - `upo_bidi_selection_sort.c`: Selection sort bidirezionale
  - `Makefile`: Build configuration
- **Compilazione**: `make`

#### **exam-sample_02/**
Secondo progetto campione d'esame.
- **Contenuti**:
  - `exam.c`: Implementazione
  - `include/upo/`: Header files
    - `bst.h`: Binary Search Tree
    - `hashtable.h`: Hash Table
    - `test.h`: Utility
  - `lib/`: Directory per librerie compilate
  - `Makefile`: Build configuration
- **Compilazione**: `make`

#### **exam-sample_03/**
Terzo progetto campione d'esame.
- **Contenuti**:
  - `exam.c`: Implementazione
  - `include/upo/`: Header files
    - `bst.h`: Binary Search Tree
    - `hashtable.h`: Hash Table
    - `test.h`: Utility
  - `test/`: Test cases
    - `bst_subtree_count_even.c`: Contare nodi con chiave pari in sottalbero
    - `ht_sepchain_odelete.c`: Deletion ordinata in hash table con chaining
  - `lib/`: Directory per librerie compilate
  - `Makefile`: Build configuration
- **Compilazione**: `make`

### ⏱️ Esercizi su Timer

#### **timer/**
Implementazione e utilizzo di timer per misurare il tempo di esecuzione.
- **Contenuti**:
  - `timer1.h`: Definizione di timer come array (start time, stop time)
  - `use_timer1.c`: Utilizzo di timer1 con funzione `time()` da `<time.h>`
  - `timer2.h`: Implementazione alternativa di timer
  - `use_timer2.c`: Utilizzo di timer2
- **Compilazione**: `gcc -g use_timer1.c -o use_timer1`

#### **timer_adt/**
Implementazione di timer come Abstract Data Type.
- **Contenuti**:
  - `timer3.h`: Header con dichiarazioni
  - `timer3.c`: Implementazione dettagliata
  - `timer3_private.h`: Definizioni private
  - `use_timer3.c`: Esempio di utilizzo
- **Compilazione**: 
  ```bash
  gcc -g timer3.c use_timer3.c -o use_timer3
  ```

### 🐛 Valgrind Code

#### **valgrind_code/**
Esercizi per imparare a debuggare con Valgrind.
- **Contenuti**:
  - `dangling_ptr.c`: Esempio di puntatore pendente (dangling pointer)
  - `memleak.c`: Esempio di memory leak
  - `wild_ptr.c`: Esempio di puntatore selvatico (wild pointer)
  - `Makefile`: Build configuration
- **Compilazione**: `make`
- **Analisi con Valgrind**: `valgrind --tool=memcheck --leak-check=full ./program`

## Strumenti Utilizzati

- **Compilatore**: GCC (GNU Compiler Collection)
- **Build**: GNU Make
- **Debugger**: Valgrind (per memory leak detection)
- **Linguaggio**: C (C99 standard)

## Compilazione Generale

Ogni progetto ha un proprio `Makefile`. Per compilare:

```bash
cd <cartella_progetto>
make clean all
./program_name
```

Oppure usa il task di build integrato in VS Code:
- **Keyboard Shortcut**: `Ctrl+Shift+B` (C/C++: gcc build active file)

## Best Practices

- ✅ Utilizza `Valgrind` per verificare memory leak
- ✅ Compila con flag `-g` per debug info complete
- ✅ Includi `-Wall -Wextra` per avvisi completi
- ✅ Assicurati di liberare tutta la memoria allocata dinamicamente
- ✅ Usa `assert()` per validare precondizioni

## Strutture Dati Utilizzate

- **Binary Search Tree (BST)**: Albero binario di ricerca con operazioni di inserimento, ricerca, cancellazione
- **Hash Table**: Tabella hash con risoluzione di collisioni (linear probing, separate chaining)
- **Array**: Array di tipo generico con puntatori `void*`

## Algoritmi Implementati

- **Ricerca Binaria**: Efficiente su array ordinati, O(log n)
- **Ordinamento**:
  - Bubble Sort bidirezionale
  - Insertion Sort bidirezionale
  - Selection Sort bidirezionale
- **Operazioni su Alberi**: LCA (Lowest Common Ancestor), predecessore, successore
- **Operazioni su Hash Table**: Calcolo collisioni medie, cancellazione ordinata

## Note Importanti

- Non usare `memcpy()` e `memmove()` negli esercizi `cptrs-ex01-any_copy`
- Gestire correttamente i puntatori generici (`void*`) con casting appropriato
- Testare sempre il codice con Valgrind per evitare memory leak
- Seguire lo standard C99 per portabilità

## Autore

Progetto per corso di **Algoritmi e Strutture Dati** (Università Degli Studi Del Piemonte Orientale?)
