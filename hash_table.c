#include <stdbool.h>
#include "linked_list.c"

int const STARTING_SIZE = 2, PRIME_NUMBER = 47216891;
long const MAX_LOAD_FACTOR = 0.67;

typedef struct HashTable{
    int size, cardinality;
    struct LinkedList* table;
} HashTable;

HashTable* initHash (){
    HashTable* newTable = malloc(sizeof(HashTable));

    newTable -> table = (LinkedList*) calloc(STARTING_SIZE, sizeof(LinkedList*));
    newTable -> size = 0;
    newTable -> cardinality = STARTING_SIZE;

    return newTable;
}

bool isEmpty(struct HashTable* hash){
    return hash -> size == 0;
}

int size(struct HashTable* hash){
    return hash -> size;
}

int hashCode(struct HashTable* hash, int key){
    int a = 56809, b = 15259;

    return abs((a * key + b) % PRIME_NUMBER) % hash -> cardinality;
}

long loadFactor(struct HashTable* hash){
    return (long) hash -> size / (long) sizeof(hash -> table);
}

void addNode(struct HashTable* hash, int key, int data){
    int index = hashCode(hash, key);

    LinkedList* current = &(hash -> table[index]);

    if (current == NULL){
        current = init();
        addFront(current,key,data);
    }
    else if (exists(current, key)){
        return;
    }
    else{
        addBack(current, key, data);
    }

    hash -> size ++;
}

void rehashInsert(struct HashTable* hash, struct LinkedList* list){
    if (list != NULL) {
        Node* temp = list -> head;
        while (temp != NULL) {
            addNode(hash, temp -> key, temp -> data[0]);
            temp = temp -> next;
        }
    }
} 

void rehash(struct HashTable* hash){
    LinkedList* temp = hash -> table;
    hash -> table = malloc(sizeof(LinkedList*) * (length(temp) * 2));
    hash -> size = 0;
    hash -> cardinality = length(temp) * 2;

    for (int i=0; i < sizeof(temp); i++){
        LinkedList* tempList = &temp[i];
        rehashInsert(hash, tempList);
    }
}

void insert(struct HashTable* hash, int key, int data){
    addNode(hash, key, data);

    if(loadFactor(hash) > MAX_LOAD_FACTOR)
        rehash(hash);
}

int deleteKey(struct HashTable* hash, int key){
    int index = hashCode(hash, key);
    LinkedList* list = &(hash -> table[index]);
    
    if (list == NULL)
        return -1;
    
    if (!exists(list, key))
        return -1;

    delete(list, find(list, key));
    if (isEmptyList(list)){
        freeList(list);
        LinkedList* temp = &(hash -> table[index]);
        temp = NULL;
    }

    hash -> size --;
}

int get(struct HashTable* hash, int key){
    int index = hashCode(hash, key);

    LinkedList* temp = &(hash -> table[index]);
    if (temp == NULL)
        return -1;

    if (exists(temp, key))
        return find(temp, key) -> data[0];

    return -1;
}

void update(struct HashTable* hash, int key, int data){
    int index = hashCode(hash, key);

    LinkedList* temp = &(hash -> table[index]);

    if (temp == NULL)
        return;
    
    if (exists(temp, key)){
        updateData(temp, key, data);
    }
}
