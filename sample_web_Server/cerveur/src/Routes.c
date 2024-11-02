#include "E:\downloads_29_10_24\sample_web_Server\cerveur\include\Routes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//below function is to initialize the route(its structure is defined in the Routes.h header file)
struct Route * initRoute(char* key, char* value) {
	struct Route * temp = (struct Route *) malloc(sizeof(struct Route));

	temp->key = key;
	temp->value = value;

	temp->left = temp->right = NULL;
	return temp;
}

//get the routes in the ascending order
void inorder(struct Route* root)
{

    if (root != NULL) {
        inorder(root->left);
        printf("%s -> %s \n", root->key, root->value);
        inorder(root->right);
    }
}
//addRoute -- equivalent to insert a node into BST
struct Route * addRoute(struct Route * root, char* key, char* value) {
	if (root == NULL) {
		return initRoute(key, value); //if tree is empty create a newRoute
	}

	if (strcmp(key, root->key) == 0) { //lexigraphically compare given url/route name and existing route-> key to avoid redudnant routes
		printf("============ WARNING ============\n");
		printf("A Route For \"%s\" Already Exists\n", key);
	}else if (strcmp(key, root->key) > 0) { //create a new route in the right if route name is alphabetically greater than key
		root->right = addRoute(root->right, key, value);
	}else { //else create route  in the left node
		root->left = addRoute(root->left, key, value);
	}
}

//function to search for a route/node int the BST
struct Route * search(struct Route * root, char* key) {
	if (root == NULL) {
		return NULL;
	} 

	if (strcmp(key, root->key) == 0){
		return root;
	}else if (strcmp(key, root->key) > 0) {
		return search(root->right, key);
	}else if (strcmp(key, root->key) < 0) {
		return search(root->left, key);
	}  

}

