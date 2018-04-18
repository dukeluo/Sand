/*
 * Binary Search Tree
 * Symbol table
 */

import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class BST<Key extends Comparable<Key>, Value> {
    private Node root;

    private class Node {
        private Key key;
        private Value val;
        private int n;
        private Node left;
        private Node right;

        public Node(Key key, Value val, int n) {
            this.key = key;
            this.val = val;
            this.n = n;
        }
    }

    public BST() {
    }

    public void put(Key key, Value val) {
        root = put(root, key, val);
    }

    private Node put(Node x, Key key, Value val) {
        if (x == null) {
            return new Node(key, val, 1);
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            x.left = put(x.left, key, val);
        } else if (cmp > 0) {
            x.right = put(x.right, key, val);
        } else {
            x.val = val;
        }
        x.n = size(x.left) + size(x.right) + 1;
        return x;
    }

    public Value get(Key key) {
        Node d = get(root, key);
        if (d == null) {
            return null;
        } else {
            return d.val;
        }
    }

    private Node get(Node x, Key key) {
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            return get(x.left, key);
        } else if (cmp > 0) {
            return get(x.right, key);
        } else {
            return x;
        }
    }

    public void delete(Key key) {
        root = delete(root, key);
    }

    private Node delete(Node x, Key key) {
        if (x == null) {
          return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            x.left = delete(x.left, key);
        } else if (cmp > 0) {
            x.right = delete(x.right, key);
        } else {
            if (x.left == null) {
                return x.right;
            } else if (x.right == null) {
                return x.left;
            } else {
                Node t = x;
                x = min(t.right);
                x.right = deleteMin(t.right);
                x.left = t.left;
            }
        }
        x.n = size(x.left) + size(x.right) + 1;
        return x;
    }

    public boolean contains(Key key) {
        return get(key) != null;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public int size() {
        return size(root);
    }

    private int size(Node x) {
        if (x == null) {
            return 0;
        } else {
            return x.n;
        }
    }

    public Key min() {
        Node d = min(root);
        if (d == null) {
            return null;
        } else {
            return d.key;
        }
    }

    private Node min(Node x) {
        if (x.left == null) {
            return x;
        }
        return min(x.left);
    }

    public Key max() {
        Node d = max(root);
        if (d == null) {
            return null;
        } else {
            return d.key;
        }
    }

    private Node max(Node x) {
        if (x.right == null) {
            return x;
        }
        return max(x.right);
    }

    public Key floor(Key key) {
        Node d = floor(root, key);
        if (d == null) {
            return null;
        } else {
            return d.key;
        }
    }

    private Node floor(Node x, Key key) {
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp == 0) {
            return x;
        }
        if (cmp < 0) {
            return floor(x.left, key);
        }
        Node d = floor(x.right, key);
        if (d != null) {
            return d;
        } else {
            return x;
        }
    }

    public Key ceiling(Key key) {
        Node d = ceiling(root, key);
        if (d == null) {
            return null;
        } else {
            return d.key;
        }
    }

    private Node ceiling(Node x, Key key) {
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp == 0) {
            return x;
        }
        if (cmp > 0) {
            return ceiling(x.right, key);
        }
        Node d = ceiling(x.left, key);
        if (d != null) {
            return d;
        } else {
            return x;
        }
    }

    public int rank(Key key) {
        return rank(root, key);
    }

    private int rank(Node x, Key key) {
        if (x == null) {
            return 0;
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            return rank(x.left, key);
        } else if (cmp > 0) {
            return size(x.left) + 1 +rank(x.right, key);
        } else {
            return size(x.left);
        }
    }

    public Key select(int k) {
        return select(root, k);
    }

    private Key select(Node x, int k) {
        if (x == null) {
            return null;
        }
        int n = size(x.left);
        if (k < n) {
            return select(x.left, k);
        } else if (k > n) {
            return select(x.right, k-n-1);
        } else {
            return x.key;
        }
    }

    public void deleteMin() {
        root = deleteMin(root);
    }

    private Node deleteMin(Node x) {
        if (x.left == null) {
            return x.right;
        }
        x.left = deleteMin(x.left);
        x.n = size(x.left) + size(x.right) + 1;
        return x;
    }

    public void deleteMax() {
        root = deleteMax(root);
    }

    private Node deleteMax(Node x) {
        if (x.right == null) {
            return x.left;
        }
        x.right = deleteMax(x.right);
        x.n = size(x.left) + size(x.right) + 1;
        return x;
    }

    public Iterable<Key> keys(Key lo, Key hi) {
        Queue<Key> q = new Queue<Key>();
        keys(root, q, lo, hi);
        return q;
    }

    private void keys(Node x, Queue<Key> q, Key lo, Key hi) {
        if (x == null) {
            return ;
        }
        int cmplo = lo.compareTo(x.key);
        int cmphi = hi.compareTo(x.key);
        if (cmplo < 0) {
            keys(x.left, q, lo, hi);
        }
        if (cmplo <= 0 && cmphi >= 0) {
            q.enqueue(x.key);
        }
        if (cmphi > 0) {
            keys(x.right, q, lo, hi);
        }
    }

    public Iterable<Key> keys() {
        return keys(min(), max());
    }

// Test case is badly written
    public static void main(String[] args) {
        BST<String, Integer> st;
        st = new BST<String, Integer>();

        for (int i = 0; !StdIn.isEmpty(); i++) {
            String key = StdIn.readString();
            st.put(key, i);
        }
        StdOut.println("size: " + st.size());
        for (String s : st.keys()) {
            StdOut.println(s + " " + st.get(s));
        }

        for (String s : st.keys()) {
            if (StdRandom.random() > 0.5) {
                st.delete(s);
            }
        }
        StdOut.println("size: " + st.size());
        for (String s : st.keys()) {
            StdOut.println(s + " " + st.get(s));
        }

        st.deleteMax();
        st.deleteMin();
        StdOut.println("size: " + st.size());
        for (String s : st.keys()) {
            StdOut.println(s + " " + st.get(s));
        }
        StdOut.println("floor 'G': " + st.floor("G"));
        StdOut.println("ceiling 'Q': " + st.ceiling("Q"));
    }
}
