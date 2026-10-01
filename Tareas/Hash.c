#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//linked list node for hash table 
struct node {
    char* key;
    char* value;
    struct node* next;
};

void setNode(struct node* node, char* key, char* value){
    node -> key = key;
    node -> value = value;
    node -> next = NULL;
    return;
}

struct hashMap{
    int numOfElements, capacity;
    struct node ** arr; //pointer to a pointer
};

void initializeHashMap(struct hashMap* mp){
    mp->capacity = 100;
    mp->numOfElements = 0;
    // reservar memoria de la cantidad de elementos por el tamaño de la estructura node
    mp->arr = (struct node**)   malloc  (sizeof(struct node*)* mp->capacity);
    return;
}; 
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

void insert (struct hashMap* mp, char* key, char* value){
    int bucketIndex = hashFunction(mp,key);
    struct node* newNode = (struct node*)malloc(
        sizeof(struct node));
    setNode(newNode, key, value);
    if (mp->arr[bucketIndex] == NULL){
        mp->arr[bucketIndex] = newNode;
    }else{ //hay colision
        newNode -> next = mp->arr[bucketIndex];
        mp->arr[bucketIndex] = newNode;
    }
    return;
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
            free(currNode); //frees memory used by malloc
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    return;
}

char* search(struct hashMap* mp, char* key){
    int bucketIndex = hashFunction(mp,key);
    struct node* bucketHead = mp->arr[bucketIndex];

    while(bucketHead!=NULL){
        if (bucketHead->key == key){
            return bucketHead->value;
        }
        bucketHead = bucketHead->next;
    }
    char* errorMssg = (char*)malloc(sizeof(char) * 25);
    errorMssg = "No data found\n";
    return errorMssg;
}


int main()
{
  struct hashMap* mp
        = (struct hashMap*)malloc(sizeof(struct hashMap));
    initializeHashMap(mp);

    insert(mp, "Key1", "Val1");
    insert(mp, "Key2", "Val2");
    insert(mp, "Key3", "Val3");
    insert(mp, "Key4", "Val4");
    insert(mp, "Key5", "Val5");

    printf("%s\n", search(mp, "Key1"));
    printf("%s\n", search(mp, "Key2"));
    
    
    printf("%s\n", search(mp, "LLave2"));
    printf("%s\n", search(mp, "key5"));


    printf("\nAfter deletion : \n");

    delete (mp, "Key1");
    printf("%s\n", search(mp, "Key1"));

    return 0;
}