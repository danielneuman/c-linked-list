/**
 * Takes input from stdin and prints out the lines in regular
 * and reversed order. EOF to end input.
 */


#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct item {
    struct item* prev;
    struct item* next;
    char* text;
};

int main()
{
    struct item* first_item = NULL;
    struct item* last_item = NULL;
    struct item* current_item;
    size_t item_size = sizeof(current_item);
    char buffer[42];
    char* result;
    printf("Input:\n");
    do {
        // Read max 41 chars + null
        result = fgets(buffer, 42, stdin);
        if (result) {
            // Get space for item
            current_item = malloc(item_size);
            current_item->next = current_item->prev = NULL;
            if (!current_item) {
                fputs("Could not allocate memory", stderr);
                return 1;
            }
            // Set current item as start of the list
            if (!first_item) {
                first_item = current_item;
            }
            // Link items (can be null)
            current_item->prev = last_item;
            if (last_item) {
                last_item->next = current_item;
            }
            // Set a reference to this item for next loop
            last_item = current_item;
            // Get space for text
            current_item->text = malloc(strlen(buffer));
            // Info
            fprintf(
                    stderr,
                    "Debug: Allocated string size %d\n",
                    (int) strlen(buffer)
            );
            // Set the text in the item
            strcpy(current_item->text, buffer);
        }
    } while (result != NULL);

    printf("Done. Printing text:\n");
    current_item = first_item;
    while(current_item) {
        printf("%s", current_item->text);
        current_item = current_item->next;
    }

    printf("Done. Printing text in reverse:\n");
    current_item = last_item;
    while (current_item) {
        printf("%s", current_item->text);
        current_item = current_item->prev;
    }
    return 0;
}
