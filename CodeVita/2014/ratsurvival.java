import java.io.*;
import java.util.*;

public class ratsurvival {
    public static int n;
    public static boolean[][] open, visited;
    public static double minProb;
    public static double[][] probs;
    public static int numOpen, numSafe;
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(in.readLine());
        open = new boolean[n][n];
        for (int i = 0; i < n; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            for (int j = 0; j < n; j++) {
                open[i][j] = line.nextToken().equals("O");
            }
        }
        minProb = Double.parseDouble(in.readLine());
        probs = new double[n][n];
        for (int i = 0; i < n; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            for (int j = 0; j < n; j++) {
                probs[i][j] = Double.parseDouble(line.nextToken());
            }
        }
        in.close();
        visited = new boolean[n][n];
        ArrayList<Integer> numSafeInRoom = new ArrayList<Integer>();
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (open[r][c] && !visited[r][c]) {
                    numOpen = 0;
                    numSafe = 0;
                    dfs(r, c);
                    numSafeInRoom.add(numSafe);
                }
            }
        }
        int possible = 1;
        for (int i = 0; i < numSafeInRoom.size(); i++)
            if (numSafeInRoom.get(i) > 0)
                possible = (possible * numSafeInRoom.get(i)) % 1000000007;
        System.out.println(possible);
        System.exit(0);
    }
    
    public static void dfs(int r, int c) {
        visited[r][c] = true;
        numOpen++;
        if (probs[r][c] >= minProb)
            numSafe++;
        if (r - 1 >= 0 && open[r - 1][c] && !visited[r - 1][c])
            dfs(r - 1, c);
        if (r + 1 < n && open[r + 1][c] && !visited[r + 1][c])
            dfs(r + 1, c);
        if (c - 1 >= 0 && open[r][c - 1] && !visited[r][c - 1])
            dfs(r, c - 1);
        if (c + 1 < n && open[r][c + 1] && !visited[r][c + 1])
            dfs(r, c + 1);
    }
}
