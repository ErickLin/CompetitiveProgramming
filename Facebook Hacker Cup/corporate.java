import java.io.*;
import java.util.*;

class corporate {
    static int[] gifts;
    static int total;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("corporate_gifting.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("corporate.out")));
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(in.readLine());
            ArrayList<HashSet<Integer>> subordinates = new ArrayList<>();
            ArrayList<Integer> managers = new ArrayList<>(n);
            for (int j = 0; j < n; j++)
                subordinates.add(new HashSet<Integer>());
            int[] level = new int[n];
            level[0] = 0;
            HashMap<Integer, HashSet<Integer>> levelSet = new HashMap<>();
            levelSet.put(0, new HashSet<Integer>());
            levelSet.get(0).add(0);
            gifts = new int[n];
            total = 0;
            StringTokenizer line = new StringTokenizer(in.readLine());
            int maxLevel = 0;
            for (int j = 0; j < n; j++) {
                int manager = Integer.parseInt(line.nextToken()) - 1;
                managers.add(manager);
                if (j > 0) {
                    subordinates.get(manager).add(j);
                    level[j] = level[manager] + 1;
                    if (level[j] > maxLevel)
                        maxLevel = level[j];
                    if (levelSet.containsKey(level[manager] + 1)) {
                        levelSet.get(level[manager] + 1).add(j);
                    } else {
                        levelSet.put(level[manager] + 1, new HashSet<Integer>());
                        levelSet.get(level[manager] + 1).add(j);
                    }
                }
            }
            for (int node : levelSet.get(maxLevel)) {
                gifts[node] = 1;
                total++;
            }
            for (int lvl = maxLevel - 1; lvl >= 0; lvl--) {
                for (int node : levelSet.get(lvl)) {
                    TreeSet<Integer> choices = new TreeSet<>();
                    for (int sub = 1; sub <= subordinates.get(node).size(); sub++) {
                        choices.add(sub);
                    }
                    for (int subordinate : subordinates.get(node)) {
                        choices.remove(gifts[subordinate]);
                    }
                    if (choices.isEmpty())
                        gifts[node] = subordinates.get(node).size() + 1;
                    else
                        gifts[node] = choices.pollFirst();
                    total += gifts[node];
                }
            }
            out.println("Case #" + i + ": " + total);
        }
        in.close();
        out.close();
        System.exit(0);
    }

    /*
    public static void findBestGiftValue(ArrayList<HashSet<Integer>> subordinates, int node) {
        if (subordinates.get(node).isEmpty()) {
            gifts[node] = 1;
        } else {
            
        }
        total += gifts[node];
    }
    */
}