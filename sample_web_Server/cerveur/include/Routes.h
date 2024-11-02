#include <stdlib.h>
#include <string.h>
/*creating a BST for the route which contains 2 elements and 2 referencing pointers
here key determines the route to be chosen like /,/about,/recipes,etc [ A pointer to a string representing the route (e.g., a URL)]
where as values:[A pointer to a string representing the handler or response associated with the route.]*/
struct Route { 
	char* key;
	char* value;

	struct Route *left, *right;
};

struct Route * initRoute(char* key, char* value);
//function to initialize the route
struct Route * addRoute(struct Route * root, char* key, char* value);
//function to add a new route
struct Route * search(struct Route * root, char * key);
//function to search for the route
void inorder(struct Route * root );
