#include <stdbool.h>
#include "linked_list.c"

/**
 * The struct HashTable work with some constant values
 * - STARTING_SIZE is a constant to initialize the HashTable with a certain
 * table length
 * - PRIME_NUMBER is a constant used in the hashing function
 * - MAX_LOAD_FACTOR is a constant to meassure if the HashTable is overload
 * so it will automatically resize to assure constant time of operation
*/
int const STARTING_SIZE = 2, PRIME_NUMBER = 47216891;
long const MAX_LOAD_FACTOR = 0.67;

/**
 * The Struct HashTable allows to create new dynamic Hash Tables
*/
typedef struct HashTable{
    int size, cardinality;
    struct LinkedList* table;
} HashTable;

/**
 * The function initHash creates a clean Hash Table
 * @return a pointer to the new Hash Table
*/
HashTable* initHash (){
    // Assigning the dynamic space for the Hash Table
    HashTable* newTable = malloc(sizeof(HashTable));

    // Initializing the values of the Hash Tables
    newTable -> table = (LinkedList*) calloc(STARTING_SIZE, sizeof(LinkedList*));
    newTable -> size = 0;
    newTable -> cardinality = STARTING_SIZE;

    //Returning the pointer
    return newTable;
}

/**
 * The function isEmpty help to determine if the Hash Table is empty or not
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @return true if the Hash Table is empty, false on the contrary
*/
bool isEmpty(struct HashTable* hash){
    return hash -> size == 0;
}

/**
 * The function size is used for counting the amount of nodes stored in the Hash Table
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @return the size of the Hash Table
*/
int size(struct HashTable* hash){
    return hash -> size;
}

/**
 * The function hashCode is used to hash a key and return the correct position into the
 * Hash Table
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @param key to be hashed
 * @return the hash code for the given key
*/
int hashCode(struct HashTable* hash, int key){
    int a = 56809, b = 15259;

    return abs((a * key + b) % PRIME_NUMBER) % hash -> cardinality;
}

/**
 * The function loadFactor is used to meassure if the Hash Table is overload
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @return a value to be compared with MAX_LOAD_FACTOR
*/
long loadFactor(struct HashTable* hash){
    return (long) hash -> size / (long) sizeof(hash -> table);
}

/**
 * The function addNode insert a new key and data into the Hash Table
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @param key used to hash and find the stored data
 * @param data to be stored in the new node
*/
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

/**
 * The function rehashInsert is used to relocate the data when the Hash Table needs
 * to rehash
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @param list stored in a specific hash code of the Hash Table
*/
void rehashInsert(struct HashTable* hash, struct LinkedList* list){
    if (list != NULL) {
        Node* temp = list -> head;
        while (temp != NULL) {
            addNode(hash, temp -> key, temp -> data[0]);
            temp = temp -> next;
        }
    }
} 

/**
 * The function rehash is used to change the size of the dynamic Hash Table
 * to the double of the current size and relocate all the data
 * @param hash is a pointer to the Hash table we want to apply the function to
*/
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

/**
 * The function insert is used to add a new node into the Hash Table
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @param key to be hashed and stored into the new node
 * @param data to be stored into the new node
*/
void insert(struct HashTable* hash, int key, int data){
    addNode(hash, key, data);

    if(loadFactor(hash) > MAX_LOAD_FACTOR)
        rehash(hash);
}

/**
 * The function deleteKey is used to delete a node from a Hash Table using the 
 * stored key
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @param key to be finded and deleted from the Hash Table
 * @return the data stored in the deleted node or -1 if error
*/
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

/**
 * The function get search a node with the given key and return the data stored
 * into it
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @param key to be hashed to find the needed node
 * @return the data stored in the node wich key corresponds to the given key
*/
int get(struct HashTable* hash, int key){
    int index = hashCode(hash, key);

    LinkedList* temp = &(hash -> table[index]);
    if (temp == NULL)
        return -1;

    if (exists(temp, key))
        return find(temp, key) -> data[0];

    return -1;
}

/**
 * The function update is used to change the data stored in a node with the given
 * key also stored in it
 * @param hash is a pointer to the Hash table we want to apply the function to
 * @param key of the node where the data is going to be updated
 * @param data to be stored in the finded node
*/
void update(struct HashTable* hash, int key, int data){
    int index = hashCode(hash, key);

    LinkedList* temp = &(hash -> table[index]);

    if (temp == NULL)
        return;
    
    if (exists(temp, key)){
        updateData(temp, key, data);
    }
}
