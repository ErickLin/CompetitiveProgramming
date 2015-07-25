import java.io.*;
import java.util.*;

public class bob {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(in.readLine());
        int[] L = new int[N];
        StringTokenizer line = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            L[i] = Integer.parseInt(line.nextToken());
        }
        Arrays.sort(L);
        for (int i = 0; i < N; i++) {
            System.out.print(L[i] - i);
            if (i < N - 1)
                System.out.print(" ");
        }
        System.out.println();
        in.close();
        System.exit(0);
    }
}
