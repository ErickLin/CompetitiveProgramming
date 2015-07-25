import java.io.*;
import java.util.*;

public class exchange {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        ArrayList<HashSet<Integer>> neighbors = new ArrayList<HashSet<Integer>>(n);
        for (int i = 0; i < n; i++)
            neighbors.add(new HashSet<Integer>());
        int k = Integer.parseInt(line.nextToken());
        for (int i = 0; i < k; i++) {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken());
            int b = Integer.parseInt(line.nextToken());
            neighbors.get(a).add(b);
            neighbors.get(b).add(a);
        }
        in.close();
        long ans = 1;
        boolean[] visited = new boolean[n];
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int groupSize = 1;
                Stack<Integer> nodes = new Stack<Integer>();
                nodes.add(i);
                visited[i] = true;
                while (!nodes.isEmpty()) {
                    int node = nodes.pop();
                    for (int neighbor : neighbors.get(node)) {
                        if (!visited[neighbor]) {
                            nodes.add(neighbor);
                            visited[neighbor] = true;
                            groupSize++;
                        }
                    }
                }
                for (int r = 2; r <= groupSize; r++) {
                    ans *= (r % 1000000007);
                    ans %= 1000000007;
                }
            }
        }
        System.out.println(ans);
        System.exit(0);
    }
}
