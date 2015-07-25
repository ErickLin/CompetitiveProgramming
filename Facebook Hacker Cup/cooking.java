import java.io.*;
import java.util.*;

public class cooking {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("cooking_the_books.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cooking.out")));
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) {
            out.print("Case #" + i + ": ");
            char[] n = in.readLine().toCharArray();
            int max = 0;
            int maxPos = -1;
            int min = Integer.MAX_VALUE;
            int minPos = -1;
            for (int j = 0; j < n.length; j++) {
                if (n[j] > max) {
                    max = n[j];
                    maxPos = j;
                }
                if (n[j] < min && n[j] != '0') {
                    min = n[j];
                    minPos = j;
                }
            }
            if (minPos != -1) {
                char temp = n[0];
                n[0] = n[minPos];
                n[minPos] = temp;
            }
            for (int j = 0; j < n.length; j++)
                out.print(n[j]);
            out.print(" ");
            if (minPos != -1) {
                char temp = n[0];
                n[0] = n[minPos];
                n[minPos] = temp;
                temp = n[0];
                n[0] = n[maxPos];
                n[maxPos] = temp;
            }
            for (int j = 0; j < n.length; j++)
                out.print(n[j]);
            out.println();
        }
        in.close();
        out.close();
        System.exit(0);
    }
}
