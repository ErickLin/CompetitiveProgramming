import java.io.*;
import java.util.*;

class dices {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        HashMap<HashSet<Long>, Long> dp = new HashMap<>();
        for (int i = 0; i < n; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int m = Integer.parseInt(line.nextToken());
            HashMap<HashSet<Long>, Long> newDp = new HashMap<>();
            for (HashSet<Long> element : dp.keySet()) {
                newDp.put(new HashSet<>(element), dp.get(element));
            }
            for (int j = 0; j < m; j++) {
                long u = Long.parseLong(line.nextToken());
                long c = Long.parseLong(line.nextToken());
                HashSet<Long> setOne = new HashSet<>();
                setOne.add(u);
                if (dp.containsKey(setOne)) {
                    if (c < dp.get(setOne)) {
                        newDp.put(setOne, c);
                    }
                } else {
                    newDp.put(setOne, c);
                }
                for (HashSet<Long> set : dp.keySet()) {
                    HashSet<Long> newSet = new HashSet<>(set);
                    newSet.add(u);
                    if (dp.containsKey(newSet)) {
                        if (dp.get(set) + c < dp.get(newSet)) {
                            newDp.put(newSet, dp.get(set) + c);
                        }
                    } else {
                        newDp.put(newSet, dp.get(set) + c);
                    }
                }
            }
            dp = newDp;
        }
        System.out.println(dp);
        int q = Integer.parseInt(in.readLine());
        for (int i = 0; i < q; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            HashSet<Long> querySet = new HashSet<>();
            for (int j = 0; j < n; j++) {
                querySet.add(Long.parseLong(line.nextToken()));
            }
            System.out.println(querySet);
            if (dp.containsKey(querySet)) {
                System.out.println(dp.get(querySet));
            } else {
                System.out.println("-1");
            }
        }
        in.close();
        System.exit(0);
    }
}
