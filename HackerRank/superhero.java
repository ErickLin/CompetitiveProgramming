import java.io.*;
import java.util.*;

public class superhero {
    static int[][] dists;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(line.nextToken());
            int m = Integer.parseInt(line.nextToken());
            int[][] p = new int[n][m];
            for (int level = 0; level < n; level++) {
                line = new StringTokenizer(in.readLine());
                for (int enemy = 0; enemy < m; enemy++) {
                    int health = Integer.parseInt(line.nextToken());
                    p[level][enemy] = health;
                }
            }
            int[][] b = new int[n][m];
            for (int level = 0; level < n; level++) {
                line = new StringTokenizer(in.readLine());
                for (int enemy = 0; enemy < m; enemy++) {
                    int bullets = Integer.parseInt(line.nextToken());
                    b[level][enemy] = bullets;
                }
            }
            dists = new int[n][m];
            boolean[][] visited = new boolean[n][m];
            //PriorityQueue<Enemy> q = new PriorityQueue<Enemy>();
            for (int enemy = 0; enemy < m; enemy++) {
                dists[0][enemy] = p[0][enemy];
                //q.add(new Enemy(0, enemy));
            }
            for (int level = 0; level < n - 1; level++) {
                for (int enemy = 0; enemy < m; enemy++) {
                    //Lucky that this runs in time.
                    //You can code this more intelligently, making it 1000 instead of m
                    //Because if two enemies have the same health, then you can ignore
                    //the one that gives less bullets.
                    for (int nextEnemy = 0; nextEnemy < m; nextEnemy++) {
                        int newDist = dists[level][enemy] + Math.max(p[level + 1][nextEnemy] - b[level][enemy], 0);
                        if (dists[level + 1][nextEnemy] == 0 || dists[level + 1][nextEnemy] > newDist)
                            dists[level + 1][nextEnemy] = newDist;
                    }
                }
            }
            int min = Integer.MAX_VALUE;
            for (int enemy = 0; enemy < m; enemy++) {
                if (dists[n - 1][enemy] < min)
                    min = dists[n - 1][enemy];
            }
            /*
            while (!q.isEmpty()) {
                Enemy node = q.poll();
                if (visited[node.level][node.num])
                    continue;
                visited[node.level][node.num] = true;
                if (node.level == n - 1) {
                    if (dists[node.level][node.num] < min)
                        min = dists[node.level][node.num];
                } else for (int enemy = 0; enemy < m; enemy++) {
                    if (!visited[node.level + 1][enemy]) {
                        int newDist = dists[node.level][node.num] + Math.max(p[node.level + 1][enemy] - b[node.level][node.num], 0);
                        if (dists[node.level + 1][enemy] == 0 || dists[node.level + 1][enemy] > newDist) {
                            dists[node.level + 1][enemy] = newDist;
                            q.add(new Enemy(node.level + 1, enemy));
                        }
                    }
                }
            }
                    */
            System.out.println(min);
        }
        in.close();
        System.exit(0);
    }
    
    private static class Enemy implements Comparable<Enemy> {
        int level;
        int num;

        public Enemy(int a, int b) {
            this.level = a;
            this.num = b;
        }
        
        @Override
        public boolean equals(Object other) {
            if (other == null)
                return false;
            if (other instanceof Enemy) {
                return level == ((Enemy) other).level && num == ((Enemy) other).num;
            }
            return false;
        }

        @Override
        public int hashCode() {
            int hash = 7;
            hash = 41 * hash + this.level;
            hash = 41 * hash + this.num;
            return hash;
        }
        
        @Override
        public int compareTo(Enemy other) {
            return new Integer(dists[level][num]).compareTo(dists[other.level][other.num]);
        }
    }
}
