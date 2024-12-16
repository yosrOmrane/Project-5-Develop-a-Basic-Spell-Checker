#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

#define N 26

typedef struct node {
	bool isWord;
	struct node* children[N];
} node;

node* root;
int _size = 0;

bool load() {
	// initialize trie
	root = malloc(sizeof(node));
	if (root == NULL) {
		return false;
	}
	root->isWord = false;
	for (int i = 0; i < N; i++) {
		root->children[i] = NULL;
	}
