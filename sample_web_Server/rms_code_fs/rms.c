#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Recipe structure
typedef struct Recipe { //used typedef for aliasing
    char name[50];
    char ingredients[200];
    char instructions[500];
    char imagePath[100];
    int timeRequired; // in minutes
    char cuisine[50];
    char dishType[50];
    struct Recipe* next; // Pointer to the next recipe
} Recipe;

// Function to create a new recipe
Recipe* createRecipe(char* name, char* ingredients, char* instructions, char* imagePath, int timeRequired, char* cuisine, char* dishType) {
    Recipe* newRecipe = (Recipe*)malloc(sizeof(Recipe));
    if (newRecipe == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strcpy(newRecipe->name, name);
    strcpy(newRecipe->ingredients, ingredients);
    strcpy(newRecipe->instructions, instructions);
    strcpy(newRecipe->imagePath, imagePath);
    newRecipe->timeRequired = timeRequired;
    strcpy(newRecipe->cuisine, cuisine);
    strcpy(newRecipe->dishType, dishType);
    newRecipe->next = NULL;
    return newRecipe;
}

// Function to add a recipe to the list (used double referencing because of scope of the function was giving some problem so made it global)
void addRecipe(Recipe** head, char* name, char* ingredients, char* instructions, char* imagePath, int timeRequired, char* cuisine, char* dishType) {
    Recipe* newRecipe = createRecipe(name, ingredients, instructions, imagePath, timeRequired, cuisine, dishType);
    newRecipe->next = *head; // Insert at the beginning
    *head = newRecipe;
}

// Function to display all recipes(Traversal)
void displayRecipes(Recipe* head) {
    Recipe* current = head;
    while (current != NULL) {
        printf("Recipe Name: %s\n", current->name);
        printf("Time Required: %d minutes\n", current->timeRequired);
        printf("Cuisine: %s\n", current->cuisine);
        printf("Dish Type: %s\n", current->dishType);
        printf("Ingredients: %s\n", current->ingredients);
        printf("Instructions: %s\n", current->instructions);
        printf("Image Path: %s\n\n", current->imagePath);
        current = current->next;
    }
}

// Function to delete a recipe by name(delete by node)
void deleteRecipe(Recipe** head, char* name) {
    Recipe* current = *head;
    Recipe* prev = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }

    // Recipe not found
    if (current == NULL) {
        printf("Recipe not found!\n");
        return;
    }

    // Recipe found
    if (prev == NULL) {
        *head = current->next; // Remove the head
    } else {
        prev->next = current->next; // Bypass the current recipe
    }
    free(current);
    printf("Recipe deleted: %s\n", name);
}
// Function to swap nodes in the linked list
void swapNodes(Recipe** head, Recipe* currX, Recipe* currY, Recipe* prevX, Recipe* prevY) {
    // If either node is head, update head
    if (prevX == NULL)
        *head = currY;
    else
        prevX->next = currY;

    if (prevY == NULL)
        *head = currX;
    else
        prevY->next = currX;

    // Swap next pointers
    Recipe* temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

// Function to search for a recipe by name
void searchRecipeByName(Recipe* head, char* name) {
    Recipe* current = head;
    int found = 0;

    while (current != NULL) {
        // Use strcasecmp for case-insensitive comparison on Unix/Linux
        // Use _stricmp for Windows
        #ifdef _WIN32
        if (_stricmp(current->name, name) == 0) {
        #else
        if (strcasecmp(current->name, name) == 0) {
        #endif
            found = 1;
            printf("Recipe Found:\n");
            printf("Recipe Name: %s\n", current->name);
            printf("Time Required: %d minutes\n", current->timeRequired);
            printf("Cuisine: %s\n", current->cuisine);
            printf("Dish Type: %s\n", current->dishType);
            printf("Ingredients: %s\n", current->ingredients);
            printf("Instructions: %s\n", current->instructions);
            printf("Image Path: %s\n\n", current->imagePath);
        }
        current = current->next;
    }
    if (!found) {
        printf("No recipe found with name: %s\n", name);
    }
}

// Function to sort recipes by time (ascending)
void sortRecipesByTimeAsc(Recipe** head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    int swapped;
    Recipe* current;
    Recipe* prev = NULL;
    Recipe* prevX;
    Recipe* prevY;

    do {
        swapped = 0;
        current = *head;
        prev = NULL;

        while (current->next != NULL) {
            if (current->timeRequired > current->next->timeRequired) {
                prevX = prev;
                prevY = current;
                swapNodes(head, current, current->next, prevX, prevY);
                swapped = 1;
                if (prev == NULL)
                    prev = *head;
                else
                    prev = prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);
}

// Function to sort recipes by time (descending)
void sortRecipesByTimeDesc(Recipe** head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    int swapped;
    Recipe* current;
    Recipe* prev = NULL;
    Recipe* prevX;
    Recipe* prevY;

    do {
        swapped = 0;
        current = *head;
        prev = NULL;

        while (current->next != NULL) {
            if (current->timeRequired < current->next->timeRequired) {
                prevX = prev;
                prevY = current;
                swapNodes(head, current, current->next, prevX, prevY);
                swapped = 1;
                if (prev == NULL)
                    prev = *head;
                else
                    prev = prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);
}

// Function to sort recipes by name (ascending)
void sortRecipesByNameAsc(Recipe** head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    int swapped;
    Recipe* current;
    Recipe* prev = NULL;
    Recipe* prevX;
    Recipe* prevY;

    do {
        swapped = 0;
        current = *head;
        prev = NULL;

        while (current->next != NULL) {
            if (strcmp(current->name, current->next->name) > 0) {
                prevX = prev;
                prevY = current;
                swapNodes(head, current, current->next, prevX, prevY);
                swapped = 1;
                if (prev == NULL)
                    prev = *head;
                else
                    prev = prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);
}

// Function to sort recipes by name (descending)
void sortRecipesByNameDesc(Recipe** head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    int swapped;
    Recipe* current;
    Recipe* prev = NULL;
    Recipe* prevX;
    Recipe* prevY;

    do {
        swapped = 0;
        current = *head;
        prev = NULL;

        while (current->next != NULL) {
            if (strcmp(current->name, current->next->name) < 0) {
                prevX = prev;
                prevY = current;
                swapNodes(head, current, current->next, prevX, prevY);
                swapped = 1;
                if (prev == NULL)
                    prev = *head;
                else
                    prev = prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);
}

// Function to filter recipes by cuisine
void filterRecipesByCuisine(Recipe* head, char* cuisine) {
    Recipe* current = head;
    int found = 0;

    while (current != NULL) {
 
        // Use _stricmp for Windows (case insensitive comparision)
        #ifdef _WIN32
        if (_stricmp(current->cuisine, cuisine) == 0) {
        #else
        if (strcasecmp(current->cuisine, cuisine) == 0) {
        #endif
            found = 1;
            printf("Recipe Name: %s\n", current->name);
            printf("Time Required: %d minutes\n", current->timeRequired);
            printf("Dish Type: %s\n", current->dishType);
            printf("Ingredients: %s\n", current->ingredients);
            printf("Instructions: %s\n", current->instructions);
            printf("Image Path: %s\n\n", current->imagePath);
        }
        current = current->next;
    }
    if (!found) {
        printf("No recipes found for cuisine: %s\n", cuisine);
    }
}

// Function to filter recipes by dish type
void filterRecipesByDishType(Recipe* head, char* dishType) {
    Recipe* current = head;
    int found = 0;

    while (current != NULL) {
        // Use strcasecmp for case-insensitive comparison on Unix/Linux
        // Use _stricmp for Windows
        #ifdef _WIN32 
        if (_stricmp(current->dishType, dishType) == 0) {
        #else
        if (strcasecmp(current->dishType, dishType) == 0) {
        #endif
            found = 1;
            printf("Recipe Name: %s\n", current->name);
            printf("Time Required: %d minutes\n", current->timeRequired);
            printf("Cuisine: %s\n", current->cuisine);
            printf("Ingredients: %s\n", current->ingredients);
            printf("Instructions: %s\n", current->instructions);
            printf("Image Path: %s\n\n", current->imagePath);
        }
        current = current->next;
    }
    if (!found) {
        printf("No recipes found for dish type: %s\n", dishType);
    }
}
// Function to save recipes to a file
void saveRecipesToFile(Recipe* head) {
    FILE* file = fopen("recipes.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    Recipe* current = head;
    while (current != NULL) {
        fprintf(file, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n", 
                current->name, 
                current->ingredients, 
                current->instructions, 
                current->imagePath, 
                current->timeRequired, 
                current->cuisine, 
                current->dishType);
        current = current->next;
    }

    fclose(file);
    printf("Recipes saved to file successfully.\n");
}

// Function to load recipes from a file
void loadRecipesFromFile(Recipe** head) {
    FILE* file = fopen("recipes.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    char name[50], ingredients[200], instructions[500], imagePath[100], cuisine[50], dishType[50]; //redeclare vars to store the vars after file is opened agen
    int timeRequired;

    while (fscanf(file, "%49[^\n]\n%199[^\n]\n%499[^\n]\n%99[^\n]\n%d\n%49[^\n]\n%49[^\n]\n", //scan the file and add the value till the max %specified character
                  name, ingredients, instructions, imagePath, &timeRequired, cuisine, dishType) == 7) {
        addRecipe(head, name, ingredients, instructions, imagePath, timeRequired, cuisine, dishType); //restart the linked list
    }
    fclose(file);
}

// Main function
int main() {
    Recipe* recipeList = NULL;
    loadRecipesFromFile(&recipeList); // Load recipes from file at the start(i.e from previous session)

    int choice;
    char name[50], ingredients[200], instructions[500], imagePath[100], cuisine[50], dishType[50];
    int timeRequired;

    while (1) { //while any case doesnt return 0
        printf("\nRecipe Management System\n");
        printf("1. Add Recipe\n");
        printf("2. Display Recipes\n");
        printf("3. Delete Recipe\n");
        printf("4. Search Recipe by Name\n");
        printf("5. Sort Recipes by Time (Ascending)\n");
        printf("6. Sort Recipes by Time (Descending)\n");
        printf("7. Sort Recipes by Name (Ascending)\n");
        printf("8. Sort Recipes by Name (Descending)\n");
        printf("9. Filter Recipes by Cuisine\n");
        printf("10. Filter Recipes by Dish Type\n");
        printf("11. Save Recipes to File\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter recipe name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline

                printf("Enter ingredients: ");
                fgets(ingredients, sizeof(ingredients), stdin);
                ingredients[strcspn(ingredients, "\n")] = 0;

                printf("Enter instructions: ");
                fgets(instructions, sizeof(instructions), stdin);
                instructions[strcspn(instructions, "\n")] = 0;

                printf("Enter image path: ");
                fgets(imagePath, sizeof(imagePath), stdin);
                imagePath[strcspn(imagePath, "\n")] = 0;

                printf("Enter time required (in minutes): ");
                scanf("%d", &timeRequired);
                getchar(); // Consume newline

                printf("Enter cuisine: ");
                fgets(cuisine, sizeof(cuisine), stdin);
                cuisine[strcspn(cuisine, "\n")] = 0;

                printf("Enter dish type: ");
                fgets(dishType, sizeof(dishType), stdin);
                dishType[strcspn(dishType, "\n")] = 0;

                addRecipe(&recipeList, name, ingredients, instructions, imagePath, timeRequired, cuisine, dishType);
                printf("Recipe added!\n");
                break;

            case 2:
                displayRecipes(recipeList);
                break;

            case 3:
                printf("Enter recipe name to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                deleteRecipe(&recipeList, name);
                break;

            case 4:
                printf("Enter recipe name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                searchRecipeByName(recipeList, name);
                break;

            case 5:
                sortRecipesByTimeAsc(&recipeList);
                printf("Recipes sorted by time (ascending).\n");
                displayRecipes(recipeList); // Display sorted recipes
                break;

            case 6:
                sortRecipesByTimeDesc(&recipeList);
                printf("Recipes sorted by time (descending).\n");
                displayRecipes(recipeList); // Display sorted recipes
                break;

            case 7:
                sortRecipesByNameAsc(&recipeList);
                printf("Recipes sorted by name (ascending).\n");
                displayRecipes(recipeList); // Display sorted recipes
                break;

            case 8:
                sortRecipesByNameDesc(&recipeList);
                printf("Recipes sorted by name (descending).\n");
                displayRecipes(recipeList); // Display sorted recipes
                break;

            case 9:
                printf("Enter cuisine to filter: ");
                fgets(cuisine, sizeof(cuisine), stdin);
                cuisine[strcspn(cuisine, "\n")] = 0;
                filterRecipesByCuisine(recipeList, cuisine);
                break;

            case 10:
                printf("Enter dish type to filter (e.g., breakfast, lunch, dinner, desserts): ");
                fgets(dishType, sizeof(dishType), stdin);
                dishType[strcspn(dishType, "\n")] = 0;
                filterRecipesByDishType(recipeList, dishType);
                break;

            case 11:
                saveRecipesToFile(recipeList);
                printf("Recipes saved to file.\n");
                break;

            case 12:
                printf("Exiting...\n");
                saveRecipesToFile(recipeList); // Save before exiting
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}