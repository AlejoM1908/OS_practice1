













/**
package classes.data_structures;

/**
 * 
 * @param <K> key
 * @param <V>
 */
interface HashTablesInterface<K extends Comparable<K>, V extends Comparable<V>> {
    int STARTING_SIZE = 10, PRIME_NUMBER = 1000003;
    double MAX_LOAD_FACTOR = 0.67;

    public void Add(K key, V value);

    public HashNode<K, V> Remove(K key, V value);

    public HashNode<K, V> Get(K key, V value);
}

class HashNode<K extends Comparable<K>, V extends Comparable<V>> {
    private K key;
    private V value;
    private HashNode<K, V> next;

    public HashNode(K key, V value, HashNode<K, V> next) {
        this.key = key;
        this.value = value;
        this.next = next;
    }

    public K getKey() {
        return key;
    }

    public void setKey(K key) {
        this.key = key;
    }

    public V getValue() {
        return this.value;
    }

    public void setValue(V value) {
        this.value = value;
    }

    public HashNode<K, V> getNext() {
        return this.next;
    }

    public void setNext(HashNode<K, V> next) {
        this.next = next;
    }
}

public class HashTable<K extends Comparable<K>, V extends Comparable<V>> implements HashTablesInterface<K, V> {
    private HashNode<K, V>[] table;
    private int size, cardinality;

    public HashTable() {
        Start();
    }

    public boolean IsEmpty() {
        return size == 0;
    }

    public void Empty() {
        Start();
    }

    @Override
    public void Add(K key, V value) {
        if (key == null || value == null)
            return;

        int index = HashCode(key);

        if (index == -1)
            return;

        HashNode<K, V> current = this.table[index];

        if (current == null) {
            this.table[index] = new HashNode<K, V>(key, value, null);
            size++;
        } else {
            while (current != null) {
                if (current.getKey().compareTo(key) == 0)
                    return;
                else if (current.getNext() == null) {
                    HashNode<K, V> insertNode = new HashNode<K, V>(key, value, null);
                    current.setNext(insertNode);
                    size++;
                }

                current = current.getNext();
            }
        }

        if (LoadFactor() > MAX_LOAD_FACTOR)
            Rehash();
    }

    @Override
    public HashNode<K, V> Remove(K key, V value) {
        int index = HashCode(key);

        if (index == -1)
            return null;

        HashNode<K, V> current = this.table[index];

        if (current == null)
            return null;

        while (current != null) {
            if (current.getNext() != null && current.getNext().getValue().compareTo(value) == 0) {
                HashNode<K, V> temporal = current.getNext();

                if (current.getNext().getNext() != null)
                    current.setNext(current.getNext().getNext());

                else
                    current.setNext(null);

                this.size--;
                return temporal;
            } else if (current.getValue().compareTo(value) == 0) {
                HashNode<K, V> temporal = current;

                if (current.getNext() != null)
                    this.table[index] = current.getNext();
                else
                    this.table[index] = null;

                this.size--;
                return temporal;

            }

            current = current.getNext();
        }

        return current;
    }

    @Override
    public HashNode<K, V> Get(K key, V value) {
        int index = HashCode(key);

        if (index == -1)
            return null;

        HashNode<K, V> current = this.table[index];

        if (current == null)
            return null;

        while (current != null) {
            if (current.getValue().compareTo(value) == 0) {
                return current;
            }

            current = current.getNext();
        }

        return null;
    }

    public boolean Update(HashNode<K, V> node, V value) {
        if (node == null || value == null)
            return false;

        node.setValue(value);
        return true;
    }

    public boolean Exists(K key, V value) {
        int index = HashCode(key);

        if (index == -1)
            return false;

        HashNode<K, V> current = this.table[index];

        if (current == null)
            return false;

        while (current != null) {
            if (current.getValue().compareTo(value) == 0) {
                return true;
            }

            current = current.getNext();
        }

        return false;
    }

    @SuppressWarnings("unchecked")
    private void Start() {
        this.table = (HashNode<K, V>[]) new HashNode[STARTING_SIZE];
        this.size = 0;
        this.cardinality = STARTING_SIZE;
    }

    private double LoadFactor() {
        return (double) this.size / (double) this.table.length;
    }

    @SuppressWarnings("unchecked")
    private void Rehash() {
        HashNode<K, V>[] temporal = this.table;
        this.table = (HashNode<K, V>[]) new HashNode[temporal.length * 2];
        this.size = 0;
        this.cardinality = temporal.length * 2;

        for (int i = 0; i < temporal.length; i++) {
            HashNode<K, V> node = temporal[i];
            if (node != null) {
                while (node != null) {
                    Add(node.getKey(), node.getValue());

                    node = node.getNext();
                }
            }
        }
    }

    private int HashCode(K key) {
        if (key instanceof Integer) {
            int a = 56809, b = 15259;

            return Math.abs((a * (Integer) key + b) % PRIME_NUMBER) % this.cardinality;
        }

        if (key instanceof String) {
            String hash = (String) key;
            int x = 60589, result = 0;

            for (int i = 0; i < hash.length(); i++)
                result += ((int) hash.charAt(i) * (x ^ i)) % PRIME_NUMBER;

            return result % this.cardinality;
        }

        if (key instanceof Double) {
            double a = 45263, b = 73361;

            return (int) Math.abs((a * (Double) key + b) % PRIME_NUMBER) % this.cardinality;
        }

        if (key instanceof Long) {
            long a = 364433, b = 581557;

            return (int) Math.abs((a * (Long) key + b) % PRIME_NUMBER) % this.cardinality;
        }

        return -1;
    }

    public Queue<V> traverseHash() {
        Queue<V> queue = new Queue<>();
        HashNode<K, V> current;

        for (int i = 0; i < cardinality; i++) {
            current = this.table[i];

            while (current != null) {
                queue.Enqueue(current.getValue());
                current = current.getNext();
            }
        }

        return queue;
    }

    public int getSize() {
        return this.size;
    }

    public V getValue(HashNode<K, V> node) {
        if (node != null)
            return node.getValue();
        return null;
    }
}