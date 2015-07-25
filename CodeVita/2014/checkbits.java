import java.io.*;

public class checkbits {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int send = Integer.parseInt(in.readLine());
        int receive = Integer.parseInt(in.readLine());
        in.close();
        String sendBin = Integer.toBinaryString(send);
        while (sendBin.length() < 7)
            sendBin = "0" + sendBin;
        int[] d = new int[8];
        for (int i = 1; i <= 7; i++)
            d[i] = Integer.parseInt(sendBin.substring(i - 1, i));
        int p1, p2, p4, p8;
        p1 = (d[1] + d[2] + d[4] + d[5] + d[7]) % 2;
        p2 = (d[1] + d[3] + d[4] + d[6] + d[7]) % 2;
        p4 = (d[2] + d[3] + d[4]) % 2;
        p8 = (d[5] + d[6] + d[7]) % 2;
        sendBin = p1 + "" + p2 + d[1] + p4 + d[2] + d[3] + d[4] + p8 + d[5] + d[6] + d[7];
        String receiveBin = Integer.toBinaryString(receive);
        while (receiveBin.length() < 11)
            receiveBin = "0" + receiveBin;
        int errors = 0, errorPos = 0;
        for (int i = 0; i < 11; i++) {
            if (!sendBin.substring(i, i + 1).equals(receiveBin.substring(i, i + 1))) {
                errorPos = i + 1;
                errors++;
            }
        }
        if (errors == 0)
            System.out.println("No transmission Error");
        else if (errors == 1) {
            System.out.println("Transmission Error at bit " + errorPos);
            System.out.println("Correct integer at Receive-side should have been: " + Integer.parseInt(sendBin, 2));
        } else {
            System.out.println("Transmission Error");
        }
        System.exit(0);
    }
}
