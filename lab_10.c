#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie *children[26];
    int isEndOfWord;
    int occurrences;
};

//Function Prototypes
void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createTrie();
int readDictionary(char *filename, char **pInWords);


// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *pCurrent = pTrie;

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        //printf("%d\n", index);
        if (index >= 0 && index <= 25) {
        if (pCurrent->children[index] == NULL) {
            pCurrent->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            memset(pCurrent->children[index], 0, sizeof(struct Trie)); // Initialize the new node
        }
        pCurrent = pCurrent->children[index];
        }
    }
    pCurrent->isEndOfWord = 1;
    pCurrent->occurrences += 1; // Increment the occurrences
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *pCurrent = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pCurrent->children[index] == NULL) {
            return 0;
        }
        pCurrent = pCurrent->children[index];
        //printf("%d\n", index);
        
    }
    return pCurrent->occurrences; // Return the count of occurrences
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    pTrie->isEndOfWord = 0;
    pTrie->occurrences = 0; // Initialize occurrences
    for (int i = 0; i < 26; i++) {
        pTrie->children[i] = NULL;
    }
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    int count = 0;
    char *word = (char *)malloc(sizeof(char) * 256);
    while (fscanf(file, "%s", word) == 1) {
        pInWords[count] = word;
        count++;
        word = (char *)malloc(sizeof(char) * 256);
    }
    fclose(file);
    return count;
}

int main(void)
{
char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}