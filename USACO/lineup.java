/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: lineup
*/
import java.io.*;
import java.util.*;

class lineup
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("lineup.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lineup.out")));
        int numCows = Integer.parseInt(in.readLine());
		Cow[] cows = new Cow[numCows];
		ArrayList<Integer> breeds = new ArrayList<Integer>();
		for (int i = 0; i < numCows; i++)
		{
			StringTokenizer line = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(line.nextToken());
			int breed = Integer.parseInt(line.nextToken());
			cows[i] = new Cow(x, breed);
			if (!breeds.contains(breed))
				breeds.add(breed);
		}
        in.close();
		Arrays.sort(cows);
		/*{
			@Override
			public int compare(Object o1, Object o2)
			{
				Cow cow1 = (Cow)o1;
				Cow cow2 = (Cow)o2;
				return cow1.getX().compareTo(cow2.getX());
			}
		});*/
        int minCost = 999999999;
		for (int i = 0; i <= cows.length - breeds.size(); i++)
		{
			@SuppressWarnings("unchecked")
			ArrayList<Integer> breedsLeft = (ArrayList<Integer>)breeds.clone();
			//for (int k = 0; k < breedsLeft.size(); k++)
			//	System.out.println(breedsLeft.get(k));
			for (int j = i; j < cows.length; j++)
			{
				//System.out.println("index: " + j + "  breed: " + cows[j].getBreed());
				breedsLeft.remove(new Integer(cows[j].getBreed()));
				if (breedsLeft.size() < 1)
				{
					if (cows[j].getX() - cows[i].getX() < minCost)
						minCost = cows[j].getX() - cows[i].getX();
					break;
				}
			}
		}
        //System.out.println("Min cost: " + minCost);
        out.println(minCost);
        out.close();
        System.exit(0);
    }

	public static class Cow implements Comparable<Cow>
	{
		private int x, breed;

		public Cow(int a, int b)
		{
			x = a;
			breed = b;
		}

		public int getX()
		{
			return x;
		}

		public int getBreed()
		{
			return breed;
		}

        @Override
		public int compareTo(Cow other)
		{
			return this.getX() - other.getX();
		}
	}
}
