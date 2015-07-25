import java.io.*;
import java.util.*;

public class image {
    public static int h, w;
    public static boolean[][] lit, visited;
    public static int numLit;
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            h = Integer.parseInt(line.nextToken());
            w = Integer.parseInt(line.nextToken());
            lit = new boolean[h][w];
            for (int r = 0; r < h; r++) {
                String row = in.readLine();
                for (int c = 0; c < w; c++) {
                    lit[r][c] = row.substring(c, c + 1).equals("#");
                }
            }
            visited = new boolean[h][w];
            ArrayList<Integer> numLitInBlob = new ArrayList<Integer>();
            for (int r = 0; r < h; r++) {
                for (int c = 0; c < w; c++) {
                    if (lit[r][c] && !visited[r][c]) {
                        numLit = 0;
                        dfs(r, c);
                        numLitInBlob.add(numLit);
                    }
                }
            }
            System.out.println(numLitInBlob.size());
            Collections.sort(numLitInBlob);
            System.out.print(numLitInBlob.get(0));
            for (int a = 1; a < numLitInBlob.size(); a++)
                System.out.print(" " + numLitInBlob.get(a));
            System.out.println();
        }
        
        in.close();
        System.exit(0);
    }
    
    public static void dfs(int r, int c) {
        visited[r][c] = true;
        numLit++;
        for (int r2 = r - 1; r2 <= r + 1; r2++) {
            if (r2 < 0 || r2 >= h)
                continue;
            for (int c2 = c - 1; c2 <= c + 1; c2++) {
                if (c2 < 0 || c2 >= w)
                    continue;
                if (r == r2 && c == c2)
                    continue;
                if (lit[r2][c2] && !visited[r2][c2])
                    dfs(r2, c2);
            }
        }
    }
}
