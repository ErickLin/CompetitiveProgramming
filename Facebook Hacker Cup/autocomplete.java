import java.io.*;
import java.util.*;

class autocomplete {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("autocomplete.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("autocomplete.out")));
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) {
            Trie dictionary = new Trie();
            int n = Integer.parseInt(in.readLine());
            int minChars = 0;
            for (int j = 0; j < n; j++) {
                char[] word = in.readLine().toCharArray();
                dictionary.addWord(word);
                minChars += dictionary.findMinChars(word);
            }
            out.println("Case #" + i + ": " + minChars);
        }
        in.close();
        
        out.close();
        System.exit(0);
    }

    public static class Trie {
        Node root;
        
        public Trie() {
            root = new Node();
        }
        
        public void addWord(char[] word) {
            Node current = root;
            for (int i = 0; i < word.length; i++) {
                current.addChild(word[i]);
                current = current.getChild(word[i]);
            }
        }

        public int findMinChars(char[] word) {
            int ret = 0;
            Node current = root;
            for (int i = 0; i < word.length; i++) {
                current = current.getChild(word[i]);
                ret++;
                if (current.multiplicity == 1)
                    break;
            }
            return ret;
        }

        private class Node {
            int multiplicity;
            HashMap<Character, Node> children;

            public Node() {
                multiplicity = 1;
                children = new HashMap<>();
            }
            
            public Node getChild(char next) {
                if (children.containsKey(next))
                    return children.get(next);
                else
                    return null;
            }
            
            public void addChild(char next) {
                if (children.containsKey(next)) {
                    getChild(next).multiplicity++;
                } else
                    children.put(next, new Node());
            }
        }
    }
}
