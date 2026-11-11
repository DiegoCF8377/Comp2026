#ifndef HASH_H
#define HASH_H

struct node {
    char* key;
    void* value;
    struct node* next;
};

struct hashMap {
    int numOfElements;
    int capacity;
    struct node** arr;
};

void initializeHashMap(struct hashMap* mp);

int contains(struct hashMap* mp, const char* key);

void* search(struct hashMap* mp, const char* key);

int insert(struct hashMap* mp, const char* key, void* value);

void delete(struct hashMap* mp, char* key);

void destroyHashMap(struct hashMap* mp);
#endif