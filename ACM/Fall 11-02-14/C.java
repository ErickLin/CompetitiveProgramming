package fall_11_02_14;

import java.io.*;
import java.util.*;

public class C {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        for (int t = 0; t < n; t++) {
            StringBuilder s1 = new StringBuilder(in.readLine());
            StringBuilder s2 = new StringBuilder(in.readLine());
            ArrayList<Character> key = new ArrayList<Character>();
            ArrayList<Character> text = new ArrayList<Character>();
            System.out.print("Case " + (t + 1) + ": ");
            for (int j = 0; j < s1.length(); j++)
                if (isAlphabetic(s1.charAt(j)))
                    key.add(Character.toUpperCase(s1.charAt(j)));
            for (int j = 0; j < s2.length(); j++)
                if (isAlphabetic(s2.charAt(j)))
                    text.add(Character.toUpperCase(s2.charAt(j)));
            TreeSet<Character> remaining = new TreeSet<Character>();
            for (int j = 65; j < 65 + 26; j++)
                remaining.add((char) j);
            char[][] grid = new char[5][5];
            int pos = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    while (pos < key.size() && !remaining.contains(key.get(pos))) {
                        pos++;
                    }
                    if (pos == key.size())
                        grid[i][j] = convert(remaining.pollFirst());
                    else
                        grid[i][j] = convert(key.get(pos));
                    remaining.remove(grid[i][j]);
                    if (grid[i][j] == 'I') {
                        remaining.remove('I');
                        remaining.remove('J');
                    }
                    //System.out.print(grid[i][j] + " ");
                }
                //System.out.println();
            }
            int ins = 65;
            for (int pos2 = 0; pos2 < text.size(); pos2++) {
                char[] digraph = new char[2];
                digraph[0] = convert(text.get(pos2));
                if (pos2 + 1 >= text.size() || text.get(pos2 + 1) == text.get(pos2)) {
                    if (((char) ins) == digraph[0]) {
                        ins++;
                        //check this part carefully!
                        if (ins == 74)
                            ins++;
                        if (ins >= 65 + 26)
                            ins = 65;
                    }
                    digraph[1] = (char) ins;
                    ins++;
                    //check this part carefully!
                    if (ins == 74)
                        ins++;
                    if (ins >= 65 + 26)
                        ins = 65;
                } else {
                    digraph[1] = convert(text.get(pos2 + 1));
                    pos2++;
                }
                int[] row = new int[2];
                int[] col = new int[2];
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 5; j++) {
                        for (int k = 0; k < 2; k++) {
                            if (digraph[k] == grid[i][j]) {
                                row[k] = i;
                                col[k] = j;
                            }
                        }
                    }
                //for (int i = 0; i < 2; i++) {
                //    System.out.println(digraph[i] + " " + row[i] + " " + col[i]);
                //}
                if (row[0] == row[1]) {
                    //Rule 1
                    System.out.print(grid[row[0]][(col[0] + 1) % 5]);
                    System.out.print(grid[row[1]][(col[1] + 1) % 5]);
                } else if (col[0] == col[1]) {
                    //Rule 2
                    System.out.print(grid[(row[0] + 1) % 5][col[0]]);
                    System.out.print(grid[(row[1] + 1) % 5][col[1]]);
                } else {
                    //Rule 3
                    System.out.print(grid[row[0]][col[1]]);
                    System.out.print(grid[row[1]][col[0]]);
                }
            }
            System.out.println();
        }
        in.close();
        System.exit(0);
    }
    
    public static char convert(char c) {
        int ret = ((int) c);
        if (ret == 74)
            ret--;
        return (char) ret;
    }
    
    public static boolean isAlphabetic(char c) {
        if (((int) c) >= 65 && ((int) c) < 65 + 26)
            return true;
        if (((int) c) >= 97 && ((int) c) < 97 + 26)
            return true;
        return false;
    }
}
