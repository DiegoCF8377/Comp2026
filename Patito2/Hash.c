#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

void initializeHashMap(struct hashMap* mp) {

    mp->capacity = 100;
    mp->numOfElements = 0;

    mp->arr = calloc(
        mp->capacity,
        sizeof(struct node*)
    );
}
int hashFunction(struct hashMap* mp, char* key){
    int bucketIndex;
    int sum = 0, factor = 31; //factor es para agregar más rango al hash
    for (int i = 0; i<strlen(key);i++){
        sum = ((sum % mp->capacity) + 
            (((int)key[i])*factor) % mp->capacity) % mp->capacity;
        factor = ((factor % __INT16_MAX__)
                  * (31 % __INT16_MAX__))
                 % __INT16_MAX__;
    };
    bucketIndex = sum;

    return bucketIndex;
};

void delete(struct hashMap* mp, char* key){
    int bucketIndex = hashFunction(mp,key);
    struct node* prevNode = NULL;
    struct node* currNode = mp->arr[bucketIndex];
    while (currNode!=NULL){
        if(strcmp(key,currNode->key)==0){//string compare
            if(currNode == mp->arr[bucketIndex]){//for head node deletion
                mp->arr[bucketIndex] = currNode->next;
            }else{//for middle or last node
                prevNode->next = currNode->next;
            }
            free(currNode->key);
            free(currNode); //frees memory used by malloc
            
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
        mp->numOfElements--;
    }
    return;
}
// Function to determine if a node already exists
int contains(struct hashMap* mp, const char* key) {

    int index = hashFunction(mp, (char*)key);

    struct node* current = mp->arr[index];

    while (current != NULL) {

        if (strcmp(current->key, key) == 0) {
            return 1;
        }

        current = current->next;
    }

    return 0;
}
void* search(struct hashMap* mp, const char* key) {

    int index = hashFunction(mp, (char*)key);

    struct node* current = mp->arr[index];

    while (current != NULL) {

        if (strcmp(current->key, key) == 0) {
            return current->value;
        }

        current = current->next;
    }

    return NULL;
}
int insert(struct hashMap* mp, const char* key, void* value) {

    if (contains(mp, key)) {
        return 0;
    }

    int index = hashFunction(mp, (char*)key);

    struct node* newNode = malloc(sizeof(struct node));

    newNode->key = strdup(key);
    newNode->value = value;

    newNode->next = mp->arr[index];

    mp->arr[index] = newNode;

    mp->numOfElements++;

    return 1; //succesful = 1 if error then 0
}

void destroyHashMap(struct hashMap *mp) {
    if (!mp || !mp->arr) return;

    for (int i = 0; i < mp->capacity; i++) {
        struct node* current = mp->arr[i];

        while (current != NULL) {
            struct node *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }

    free(mp->arr);
    mp->arr = NULL;
    mp->numOfElements = 0;
    mp->capacity = 0;
}