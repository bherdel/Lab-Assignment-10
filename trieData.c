#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    struct Trie *children[26];
    int count;
};

void insert(struct Trie **ppTrie, char *word) {
    if (*ppTrie == NULL) {
        *ppTrie = malloc(sizeof(struct Trie));
        memset((*ppTrie)->children, 0, sizeof((*ppTrie)->children));
        (*ppTrie)->count = 0;
    }
    if (*word == '\0') {
        (*ppTrie)->count++;
        return;
    }
    int index = *word - 'a';
    insert(&((*ppTrie)->children[index]), word + 1);
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
    }
    return pTrie->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->children[i] != NULL) {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
    return NULL;
}

int main(void) {
    int n;
    scanf("%d", &n);

    struct Trie *trie = NULL;
    char word[101];
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        insert(&trie, word);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }

    return 0;
}