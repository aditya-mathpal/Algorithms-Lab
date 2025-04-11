# Q1. KMP (Knuth–Morris–Pratt) Pattern Searching Algorithm

Complete C Program Implementation:
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void computeLPSArray(char *pattern, int m, int *lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else { // mismatch after len matches
            if (len) len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int* lps = (int*)malloc(m * sizeof(int));
    
    computeLPSArray(pattern, m, lps);
    
    int i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    free(lps);
}

int main() {
    char text[1000], pattern[1000];
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    
    text[strcspn(text, "\n")] = 0;
    pattern[strcspn(pattern, "\n")] = 0;
    
    KMPSearch(text, pattern);
    return 0;
}
```

# Q2. Rabin–Karp String Matching Algorithm
Overview:
The Rabin–Karp algorithm is a string searching algorithm that uses hashing to find any one of a set of pattern strings in a text. The key idea is to compute a hash of the pattern and then a hash of substrings of the text. A match is only verified when the hash values match.

Pseudocode:
```
function RabinKarp(text, pattern, d, q):
    n = length(text)
    m = length(pattern)
    h = (d^(m-1)) mod q  // high order digit multiplier
    p = 0  // hash value for pattern
    t = 0  // hash value for text

    // Preprocessing: Calculate the hash for pattern and first window of text
    for i from 0 to m-1:
        p = (d * p + pattern[i]) mod q
        t = (d * t + text[i]) mod q

    // Slide the pattern over text one by one
    for i from 0 to n-m:
        if p == t: // check for spurious hit
            if text substring from i to i+m-1 equals pattern:
                print "Pattern found at index", i
        if i < n-m:
            t = (d * (t - text[i]*h) + text[i+m]) mod q
            if t < 0:
                t = t + q
```
Time Complexities:

Best-case: O(n + m) when spurious hits are rare

Worst-case: O(n*m) if many spurious hits occur (i.e., when the hash values match frequently but the strings do not)

# Q3. Aho–Corasick Algorithm
Overview:
The Aho–Corasick algorithm allows simultaneous searching of multiple patterns (dictionary) in a single pass over the text. It constructs a trie of all the patterns, then builds fail pointers to handle mismatches. When processing the text, the algorithm transitions through the trie and uses the fail pointers to efficiently find all occurrences of the dictionary patterns.

Pseudocode:
```
function BuildTrie(dictionary):
    create root node
    for each pattern in dictionary:
        current = root
        for each character c in pattern:
            if current has no child for c:
                create new node for c
            current = current.child[c]
        mark current as an output node (store pattern)

function BuildFailPointers(root):
    create a queue
    for each child node of root:
        child.fail = root
        enqueue(child)
    while queue is not empty:
        current = dequeue(queue)
        for each child c of current:
            temp = current.fail
            while temp is not root and temp has no child for c:
                temp = temp.fail
            if temp has child for c:
                c.fail = temp.child[c]
            else:
                c.fail = root
            // merge output of fail pointer to child node's output
            enqueue(c)

function AhoCorasickSearch(root, text):
    current = root
    for i from 0 to length(text)-1:
        while current is not root and no transition for text[i]:
            current = current.fail
        if current has transition for text[i]:
            current = current.child[text[i]]
        else:
            current = root
        if current is an output node:
            print "Match found for patterns:", current.output, "at index", i
```
Time Complexities:

Best-case: O(n + z) where z is the number of pattern matches, as transitions are followed in constant time

Worst-case: O(n*m) in highly contrived cases with many overlapping patterns; however, practically it behaves in linear time relative to the text

Complete C Program Implementation:

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 256

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    struct TrieNode *fail;
    int isEnd;
    int patternIndex;
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    node->fail = NULL;
    node->isEnd = 0;
    node->patternIndex = -1;
    return node;
}

void insert(TrieNode* root, const char* pattern, int index) {
    TrieNode* curr = root;
    for (int i = 0; pattern[i] != 0; i++) {
        unsigned char ch = pattern[i];
        if (!curr->children[ch]) curr->children[ch] = createNode();
        curr = curr->children[ch];
    }
    curr->isEnd = 1;
    curr->patternIndex = index;
}

void buildFailurePointers(TrieNode* root) {
    TrieNode **queue = (TrieNode**)malloc(10000 * sizeof(TrieNode*));
    int front = 0, rear = 0;
    
    root->fail = root;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            root->children[i]->fail = root;
            queue[rear++] = root->children[i];
        }
    }
    
    while (front < rear) {
        TrieNode* curr = queue[front++];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            TrieNode* child = curr->children[i];
            if (child) {
                TrieNode* f = curr->fail;
                while (f != root && !f->children[i])
                    f = f->fail;
                if (f->children[i] && f->children[i] != child)
                    child->fail = f->children[i];
                else child->fail = root;
                queue[rear++] = child;
            }
        }
    }
    free(queue);
}

void AhoCorasickSearch(TrieNode* root, const char* text, char patterns[][50], int numPatterns) {
    TrieNode* curr = root;
    for (int i = 0; text[i] != 0; i++) {
        unsigned char ch = text[i];
        while (curr != root && !curr->children[ch])
            curr = curr->fail;
        if (curr->children[ch])
            curr = curr->children[ch];
        else curr = root;
        
        TrieNode* temp = curr;
        while (temp != root) {
            if (temp->isEnd)
                printf("Pattern \"%s\" found at index %d\n", patterns[temp->patternIndex], i - strlen(patterns[temp->patternIndex]) + 1);
            temp = temp->fail;
        }
    }
}

void freeTrie(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            freeTrie(root->children[i]);
    free(root);
}

int main() {
    char patterns[][50] = {"he", "she", "his", "hers"};
    int numPatterns = 4;
    char text[1000];
    
    TrieNode* root = createNode();
    for (int i = 0; i < numPatterns; i++)
        insert(root, patterns[i], i);
    buildFailurePointers(root);
    
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    
    AhoCorasickSearch(root, text, patterns, numPatterns);
    freeTrie(root);
    return 0;
}
```

# Q4. Bitap Algorithm (Shift-Or/Shift-And Algorithm)
Overview:
The Bitap algorithm uses bitwise operations to perform pattern matching by representing the pattern as bit masks. The algorithm is especially effective when the pattern length is less than or equal to the machine word size. Using dynamic programming and bit masking, it shifts a bitmask across the text to update the state.

Pseudocode:
```
function BitapSearch(text, pattern):
    m = length(pattern)
    if m == 0: return
    // Initialize mask for each character in the alphabet
    for each character c in alphabet:
        mask[c] = ~0
    for i from 0 to m-1:
        mask[pattern[i]] &= ~(1 << i)
    state = ~0
    for i from 0 to length(text)-1:
        state = ((state << 1) | 1) & mask[text[i]]
        if (state & (1 << m)) == 0:
            print "Pattern found at index", i - m + 1
```
Time Complexities:

Best-case: O(n) when bit operations and comparisons are constant-time.

Worst-case: Still O(n) but limited by pattern length due to bitmask operations. For very large patterns (exceeding machine word size), additional handling is needed.

Complete C Program Implementation:
```
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define ALPHABET_SIZE 256

void BitapSearch(const char* text, const char* pattern) {
    int m = strlen(pattern);
    if (m == 0) {
        printf("Empty pattern.\n");
        return;
    }
    if(m > (int)(sizeof(unsigned int) * CHAR_BIT)) {
        printf("Pattern too long for Bitap algorithm.\n");
        return;
    }
    
    unsigned int mask[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++)
        mask[i] = ~0;
    
    for (int i = 0; i < m; i++)
        mask[(unsigned char)pattern[i]] &= ~(1 << i);
    
    unsigned int state = ~0;
    for (int i = 0; text[i] != '\0'; i++) {
        state = ((state << 1) | 1) & mask[(unsigned char)text[i]];
        if ((state & (1 << m)) == 0)
            printf("Pattern found at index %d\n", i - m + 1);
    }
}

int main() {
    char text[1000], pattern[100];
    
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    
    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = 0;
    
    BitapSearch(text, pattern);
    return 0;
}
```