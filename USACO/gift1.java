/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: gift1
*/
import java.io.*;
import java.util.*;

class gift1
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("gift1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("gift1.out")));
        int numberOfGivers = Integer.parseInt(in.readLine());
        LinkedHashMap<String, Giver> givers = new LinkedHashMap<String, Giver>(numberOfGivers);
        //gets all the givers and puts them into the hash map
        for (int i = 0; i < numberOfGivers; i++)
        {
            String name = in.readLine();
            givers.put(name, new Giver(name));
        }
        //the actual gift giving part
        for (int i = 0; i < numberOfGivers; i++)
        {
            Giver giver = givers.get(in.readLine());
            StringTokenizer currentLine = new StringTokenizer(in.readLine());
            int moneyGiven = Integer.parseInt(currentLine.nextToken());
            int numberOfRecipients = Integer.parseInt(currentLine.nextToken());
            giver.setMoneyGiven(moneyGiven);
            for (int j = 0; j < numberOfRecipients; j++)
                {
                    giver.addRecipient(givers.get(in.readLine()));
                }
            if (moneyGiven > 0 && numberOfRecipients > 0)
                giver.divide();
        }
        for (Map.Entry<String, Giver> entry : givers.entrySet())
        {
            //name followed by a space, then followed by the net gain/loss of money
            out.println(entry.getKey() + " " + entry.getValue().getNet());
        }
        in.close();
        out.close();
        System.exit(0);
    }
    
    static class Giver
    {
        private String name;
        private int moneyGiven, moneyReceived;
        private ArrayList<Giver> recipients;
        
        public Giver(String name)
        {
            this.name = name;
            recipients = new ArrayList<Giver>();
            moneyReceived = 0;
        }
        
        public String getName()
        {
            return name;
        }
        
        public void setMoneyGiven(int amount)
        {
            moneyGiven = amount;
        }
        
        public void addRecipient(Giver recipient)
        {
            recipients.add(recipient);
        }
        
        public void divide()
        {
            //each recipient receives his/her share (a whole number)
            
            for (Giver recipient : recipients)
            {
                recipient.addMoney(moneyGiven / recipients.size());
            }
            //the giver keeps the remainder
            addMoney(moneyGiven % recipients.size());
        }
        
        public void addMoney(int amount)
        {
            moneyReceived += amount;
        }
        
        public int getNet()
        {
            return moneyReceived - moneyGiven;
        }
    }
}
