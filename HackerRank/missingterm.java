import java.io.*;
import java.util.*;

class missingterm {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] terms = new int[n];
        StringTokenizer line = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            terms[i] = Integer.parseInt(line.nextToken());
        }
        in.close();
        int diff = (terms[n - 1] - terms[0]) / terms.length;
        for (int i = 1; i < n; i++) {
            if (terms[i] - terms[i - 1] != diff) {
                System.out.println(terms[i] - diff);
                break;
            }
        }
        System.exit(0);
    }
}
