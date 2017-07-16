import java.io.*;
import java.util.*;

public class schedule {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        Test[] tests = new Test[n];
        for (int i = 0; i < n; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int t = Integer.parseInt(line.nextToken());
            double p = Double.parseDouble(line.nextToken());
            tests[i] = new Test(t, p);
        }
        Arrays.sort(tests);
        double expected = 0;
        int cumTime = 0;
        double cumProb = 1;
        for (int i = 0; i < n - 1; i++) {
            cumTime += tests[i].t;
            expected += cumTime * ((1 - tests[i].p) * cumProb);
            cumProb *= tests[i].p;
        }
        cumTime += tests[n - 1].t;
        expected += cumTime * cumProb;
        System.out.println(expected);
        in.close();
        System.exit(0);
    }
    
    private static class Test implements Comparable<Test> {
        int t;
        double p;
        
        public Test(int t, double p) {
            this.t = t;
            this.p = p;
        }
        
        @Override
        public int compareTo(Test other) {
            return new Double(t * (1 - p) + (t + other.t) * p * (1 - other.p))
                    .compareTo(other.t * (1 - other.p) + (other.t + t) * other.p * (1 - p));
        }
    }
}
