struct node{
    int data;
    struct node* next;
};

struct linked_list{
    struct node *head = NULL;
    struct node *tstruct linked_list *listail = NULL;
    int size = 0;
}

bool isEmpty(struct linked_list *list){
    return list.head == NULL;
}

int length(struct linked_list *list){
    return list.size;
}

void addFront(struct linked_list *list, int data){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode.data = data;
        
    if (size == 0){
        list.head = newNode;
        list.tail = newNode;
    }
    else{
        newNode -> next = list.head;
        list.head = newNode;
    }

    list.size += 1;
}

void addBack(struct linked_list *list, int data){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode.data = data;
        
    if (list.size == 0){
        list.head = newNode;
        list.tail = newNode;
    }
    else{
        list.tail.next = newNode;
        list.tail = newNode; 
    }

    list.size ++;
}














// /**

// package classes.data_structures;

// interface LinkedListInterface<T>{
//     public void AddBefore(DoubleListNode<T> node, T value);
//     public void AddAfter(DoubleListNode<T> node, T value);
//     public T Delete(DoubleListNode<T> eraseNode);
//     public T Show(DoubleListNode<T> node);
//     public DoubleListNode<T> Find(T findKey);
//     public boolean Exists(T findKey);
//     public boolean IsEmpty();
//     public void Empty();
// }

// /**
//  * @param <T> that define the data type
//  */
// class DoubleListNode<T>{
//     private T key;
//     private DoubleListNode<T> next, last;
    
//     DoubleListNode(T key){
//         this.key = key;
//         this.next = null;
//         this.last = null;
//     }

//     /**
//      * key is the data that is stored in the ListNode
//      * 
//      * @Has Getter
//      * @Has Setter
//      * @return key stored
//      */
//     public T getKey() {
//         return key;
//     }

//     public void setKey(T key) {
//         this.key = key;
//     }

//     /**
//      * next is the pointer to the next ListNode in the DoubleLinkedList
//      * 
//      * @HasGetter
//      * @HasSetter
//      * @return next pointer
//      */
//     public DoubleListNode<T> getNext() {
//         return next;
//     }

//     public void setNext(DoubleListNode<T> next) {
//         this.next = next;
//     }

//     /**
//      * last is the pointer to the last ListNode in the DoubleLinkedList
//      * 
//      * @HasGetter
//      * @HasSetter
//      * @return last pointer
//      */
//     public DoubleListNode<T> getLast() {
//         return last;
//     }

//     public void setLast(DoubleListNode<T> last) {
//         this.last = last;
//     }  
// }

// /**
//  * @param <T> that define the data type
//  */
// public class DoubleLinkedList<T> implements LinkedListInterface<T>{
    
//     private DoubleListNode<T> head, tail;
//     private int size;

//     /**
//      * Constructor of thFe class DoubleLinkedList
//      */
//     public DoubleLinkedList() {
//         this.head = null;
//         this.tail = null;
//         this.size = 0;
//     }
    
//     /**
//      * Constructor of the class DoubleLinkedList
//      * 
//      * @param head of the DoubleLinkedList to be reconstructed
//      */
//     public DoubleLinkedList (DoubleListNode<T> head){
//         this.head = head;
//         this.size = 0;
//         StablishDoubleLinkedList();
//     }
    
//     /**
//      * Function that reconstruct a DoubleLinkedList given a DoubleListNode
//      */
//     private void StablishDoubleLinkedList(){
//         DoubleListNode<T> stablishNode = this.head;
        
//         //Checking if the head is really the head
//         if(stablishNode.getLast() != null){
//             while (stablishNode.getLast() != null){
//                 stablishNode = stablishNode.getLast();
//             }
//             this.head = stablishNode;
//         }
        
//         //Identifiying the DoubleLinkedList body and placing the tail
//         if (this.head == null) this.tail = null;
//         else if (stablishNode.getNext() == null){
//             this.size = 1;
//             this.tail = this.head;
//         }
//         else{
//             while(stablishNode.getNext() != null){
//                 stablishNode = stablishNode.getNext();
//                 this.size++;
//             }
//             this.size++;
//             this.tail = stablishNode;
//         }
//     }
    
//     /**
//      * Function that say if the DoubleLinkedList is empty
//      * 
//      * @return if the DoubleLinkedList is empty or not
//      */
//     @Override
//     public boolean IsEmpty(){
//         return this.head == null;
//     }
    
//     /**
//      * Function that empties the DoubleLinkedList
//      */
//     @Override
//     public void Empty(){
//         this.head = null;
//         this.tail = null;
//         this.size = 0;
//     }
    
//     /**
//      * Function that add a new node after a given node
//      * 
//      * @param node where new node is going to be added after
//      * @param newKey to be stored in the new node
//      */
//     @Override
//     public void AddAfter(DoubleListNode<T> node, T newKey){
//         DoubleListNode<T> newNode = new DoubleListNode<>(newKey);
        
//         if (this.size == 0){
//             this.head = newNode;
//             this.tail = newNode;
//         }
//         else if (node.getNext() == null){
//             newNode.setLast(node);
//             node.setNext(node);
//             this.tail = newNode;
//         }
//         else{
//             node.getNext().setLast(newNode);
//             newNode.setNext(node.getNext());
//             newNode.setLast(node);
//             node.setNext(newNode);
//         }
//         this.size++;
//     }
//     /**
//      * Function that add a new node before a given node
//      * 
//      * @param Node where new node is going to be added before
//      * @param newKey to be stored in the new node
//      */
//     @Override
//     public void AddBefore(DoubleListNode<T> Node, T newKey){
//         DoubleListNode<T> newNode = new DoubleListNode<>(newKey);
        
//         if (size == 0){
//             this.head = newNode;
//             this.tail = newNode;
//         }
//         else if (Node.getLast() == null){
//             newNode.setNext(Node);
//             Node.setLast(newNode);
//             this.head = newNode;
//         }
//         else{
//             Node.getLast().setNext(newNode);
//             newNode.setLast(Node.getLast());
//             newNode.setNext(Node);
//             Node.setLast(newNode);
//         }
//     }
    
//     /**
//      * Function that add a new node before the head node
//      * 
//      * @param newKey to be stored in the new node
//      */
//     public void AddFront(T newKey){
//         AddBefore(head, newKey);
//     }
    
//     /**
//      * Function that add a new node after the tail node
//      * 
//      * @param newKey to be stored in the new node
//      */
//     public void AddBack(T newKey){
//         AddAfter(tail, newKey);
//     }
    
//     /**
//      * Function that Delete a given node and return the data stored in it
//      * 
//      * @param eraseNode to be deleted
//      * @return the data of the deleted node
//      */
//     @Override
//     public T Delete(DoubleListNode<T> eraseNode){
//         if (this.size == 0) return null;
//         else if (this.size == 1){
//             T erasedKey = (T) eraseNode.getKey();
//             Empty();
//             return erasedKey;
//         }
//         else if (eraseNode.getNext() == null){
//             eraseNode.getLast().setNext(null);
//             this.tail = eraseNode.getLast();
//         }
//         else if(eraseNode.getLast() == null){
//             eraseNode.getNext().setLast(null);
//             this.head = eraseNode.getNext();
//         }
//         else{
//             eraseNode.getNext().setLast(eraseNode.getLast());
//             eraseNode.getLast().setNext(eraseNode.getNext());
//             eraseNode.setNext(null);
//             eraseNode.setLast(null);
//         }
//         size --;
//         return (T) eraseNode.getKey();
//     }
    
//     /**
//      * Function that delete the head of the DoubleLinkedList
//      * 
//      * @return the data stored in the deleted head
//      */
//     public T DeleteFront(){
//         return Delete(head);
//     }
    
//     /**
//      * Function that delete the tail of the DoubleLinkedList
//      * 
//      * @return the data stored in the deleted tail
//      */
//     public T DeleteBack(){
//         return Delete(tail);
//     }
    
//     /**
//      * Function that shows the data stored in a given DoubleListNode
//      * 
//      * @param node where we want to show the data
//      * @return the data stored in the given node
//      */
//     @Override
//     public T Show(DoubleListNode<T> node){
//         return node.getKey();
//     }

//     /**
//      * Function that shows the data stored in the head
//      * 
//      * @return the data stored in the head
//      */
//     public T ShowFront(){
//         return Show(this.head);
//     }
    
//     /**
//      * Function that shows the data stored in the tail
//      * 
//      * @return the data stored in the tail
//      */
//     public T ShowBack(){
//         return Show(this.tail);
//     }
    
//     /**
//      * Function that find if a data is already in the DoubleLinkedList
//      * 
//      * @param findKey to be found
//      * @return the node where the findKey was found
//      */
//     @Override
//     public DoubleListNode<T> Find(T findKey) {
//         DoubleListNode<T> current = this.head;
        
//         while (current != null){
//             if (current.getKey() == findKey) return current;
            
//             current = current.getNext();
//         }
//         return null;
//     }
    
//     /**
//      * Function that say if a given data already exists in the DoubleLinkedList
//      * 
//      * @param findKey to be finded
//      * @return if findKey is already added or not
//      */
//     @Override
//     public boolean Exists(T findKey){
//         DoubleListNode<T> current = this.head;

//         while (current != null){
//             if (current.getKey() == findKey) return true;
            
//             current = current.getNext();
//         }
//         return false;
//     }

//     /**
//      * size is the amount of DoubleListNode in the DoubleLinkedList
//      * 
//      * @HasGetter
//      * @HasSetter
//      * @return size of the DoubleLinkedList
//      */
//     public int getSize() {
//         return size;
//     }

//     public void setSize(int size) {
//         this.size = size;
//     }

//     /**
//      * Head is the first DoubleListNode in the DoubleLinkedList
//      * 
//      * @HasGetter
//      * @return head of the DoubleLinkedList
//      */
//     public DoubleListNode<T> getHead() {
//         return head;
//     }

//     /**
//      * Tail is the last DoubleListNode in the DoubleLinkedList
//      * 
//      * @HasGetter
//      * @return tail of the DoubleLinkedList
//      */
//     public DoubleListNode<T> getTail() {
//         return tail;
//     }
// }
