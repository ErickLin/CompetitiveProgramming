/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: stampede
*/

import java.io.*;
import java.util.*;

class stampede {
    public static void main(String[] args) throws IOException {
        /*
        System.out.println(50000);
        for (int i = 0; i < 50000; i++) {
            System.out.println("-" + (int) Math.ceil(Math.random() * 1000) + " "
                    + (int) Math.ceil(Math.random() * 1000000) + " "
                    + (int) Math.ceil(Math.random() * 1000000));
        }
        */
        BufferedReader in = new BufferedReader(new FileReader("stampede.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("stampede.out")));
        int n = Integer.parseInt(in.readLine());
        Cow[] cows = new Cow[n];
        for (int i = 0; i < n; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int absX = -Integer.parseInt(line.nextToken());
            int y = Integer.parseInt(line.nextToken());
            int r = Integer.parseInt(line.nextToken());
            cows[i] = new Cow(absX, y, r);
        }
        in.close();
        Arrays.sort(cows);
        HashSet<Interval> intervals = new HashSet<Interval>();
        int count = 0;
        for (Cow cow : cows) {
            boolean canSee = false;
            if (intervals.isEmpty()) {
                canSee = true;
                intervals.add(cow.interval);
            } else {
                HashSet<Interval> toMerge = new HashSet<Interval>();
                for (Interval i : intervals) {
                    if (cow.interval.startT < i.startT
                            || cow.interval.endT > i.endT) {
                        canSee = true;
                        if ((cow.interval.startT <= i.endT && cow.interval.endT > i.endT)
                                || (cow.interval.startT < i.startT && cow.interval.endT >= i.startT))
                            toMerge.add(i);
                    }
                    if (cow.interval.startT >= i.startT
                            && cow.interval.endT <= i.endT) {
                        canSee = false;
                        break;
                    }
                }
                if (canSee) {
                    for (Interval i : toMerge) {
                        cow.interval.startT = Math.min(cow.interval.startT, i.startT);
                        cow.interval.endT = Math.max(cow.interval.endT, i.endT);
                        intervals.remove(i);
                    }
                    intervals.add(cow.interval);
                }
            }
            //System.out.println(intervals + " " + canSee);
            if (canSee)
                count++;
        }
        out.println(count);
        out.close();
        System.exit(0);
    }

    private static class Cow implements Comparable<Cow>{
        int x;
        int y;
        int r;
        Interval interval;

        public Cow(int x, int y, int r) {
            this.x = x;
            this.y = y;
            this.r = r;
            interval = new Interval((x - 1) * r, x * r);
        }

        @Override
        public int compareTo(Cow other) {
            return new Integer(y).compareTo(other.y);
        }
    }
    
    private static class Interval {
        int startT;
        int endT;

        public Interval(int startT, int endT) {
            this.startT = startT;
            this.endT = endT;
        }
        
        @Override
        public String toString() {
            return "[" + startT + ", " + endT + "]";
        }
    }
}
