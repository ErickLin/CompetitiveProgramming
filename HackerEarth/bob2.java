import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class bob2 {
    public static void main(String args[] ) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int[] boxes = new int[100000];
        for (int i = 0; i < 100000; i++)
            boxes[i] = i + 1;
        int N = Integer.parseInt(br.readLine());
        int[] L = new int[N];
        StringTokenizer line = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            L[i] = Integer.parseInt(line.nextToken());
            int count = 0;
            for (int j = 0; j < i; j++)
                if (L[j] < L[i])
                    count++;
            System.out.print(L[i] - count);
            if (i < N - 1)
                System.out.print(" ");
        }
        System.out.println();
    }
}