/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: heritage
*/

import java.io.*;
import java.util.*;

class heritage {
    static int[] left;
    static int[] right;
    static char[] preOrder;
    static int preOrderPos;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("heritage.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("heritage.out")));
        String inOrder = in.readLine();
        preOrder = in.readLine().toCharArray();
        in.close();
        left = new int[26];
        right = new int[26];
        preOrderPos = 0;
        int root = preOrder[preOrderPos] - 65;
        makeTree(inOrder, root);
        out.println(postOrder(root));
        out.close();
        System.exit(0);
    }

    public static void makeTree(String inOrder, int root) {
        int rootPos = inOrder.indexOf(root + 65);
        if (rootPos > 0) {
            left[root] = preOrder[++preOrderPos] - 65;
            makeTree(inOrder.substring(0, rootPos), left[root]);
        } else {
            left[root] = -1;
        }
        if (rootPos < inOrder.length() - 1) {
            right[root] = preOrder[++preOrderPos] - 65;
            makeTree(inOrder.substring(rootPos + 1), right[root]);
        } else {
            right[root] = -1;
        }
    }

    public static String postOrder(int root) {
        String ret = "";
        if (left[root] != -1)
            ret += postOrder(left[root]);
        if (right[root] != -1)
            ret += postOrder(right[root]);
        ret += (char) (root + 65);
        return ret;
    }
}
