import java.io.*;
import java.util.*;

class corporate2 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("corporate.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("corporate.out")));
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(in.readLine());
            ArrayList<HashSet<Integer>> subordinates = new ArrayList<>();
            for (int j = 0; j < n; j++)
                subordinates.add(new HashSet<Integer>());
            int[] level = new int[n];
            level[0] = 0;
            int evenCount = 1;
            int oddCount = 0;
            StringTokenizer line = new StringTokenizer(in.readLine());
            for (int j = 0; j < n; j++) {
                int manager = Integer.parseInt(line.nextToken()) - 1;
                if (j > 0) {
                    subordinates.get(manager).add(j);
                    level[j] = level[manager] + 1;
                    if (level[j] % 2 == 0) {
                        evenCount++;
                    } else {
                        oddCount++;
                    }
                }
            }
            if (evenCount > oddCount) {
                System.out.println("Case #" + i + ": " + (evenCount + oddCount * 2));
            } else {
                System.out.println("Case #" + i + ": " + (evenCount * 2 + oddCount));
            }
        }
        in.close();
        out.close();
        System.exit(0);
    }
}
