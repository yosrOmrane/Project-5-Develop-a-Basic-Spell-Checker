#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Dict_lib.h"

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

	// open dictionary file
	FILE* file = fopen("words.txt", "r");
	if (file == NULL) {
		unload();
		return false;
	}

	// buffer for each word
	char word[LENGTH + 1];
	int idx;

