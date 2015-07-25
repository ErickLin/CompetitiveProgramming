/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: shopping
*/

import java.io.*;
import java.util.*;

class shopping {
    static HashMap<Integer, HashMap<Integer, Integer>> fromHash;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("shopping.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("shopping.out")));
        HashSet<Offer> offers = new HashSet<Offer>();
        int numOffers = Integer.parseInt(in.readLine());
        for (int i = 0; i < numOffers; i++) {
            HashMap<Integer, Integer> products = new HashMap<Integer, Integer>();
            StringTokenizer line = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(line.nextToken());
            for (int j = 0; j < n; j++) {
                products.put(Integer.parseInt(line.nextToken()), Integer.parseInt(line.nextToken()));
            }
            offers.add(new Offer(products, Integer.parseInt(line.nextToken())));
        }
        int numProducts = Integer.parseInt(in.readLine());
        HashMap<Integer, Integer> indices = new HashMap<Integer, Integer>();
        int productCount = 0;
        ArrayList<Integer> numNeeded = new ArrayList<Integer>();
        ArrayList<Integer> regPrices = new ArrayList<Integer>();
        for (int i = 0; i < numProducts; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int c = Integer.parseInt(line.nextToken());
            int k = Integer.parseInt(line.nextToken());
            int p = Integer.parseInt(line.nextToken());
            indices.put(c, productCount);
            productCount++;
            numNeeded.add(k);
            regPrices.add(p);
        }
        in.close();
        fromHash = new HashMap<Integer, HashMap<Integer, Integer>>();
        for (Offer offer : offers) {
            offer.calcSavings(indices, regPrices);
            offer.calcHash(indices);
        }
        int maxSavings = 0;
        //assigns the maximum savings value to a hash that equals each set of
        //product quantities (capacity: 6^6)
        TreeMap<Integer, Integer> dp = new TreeMap<Integer, Integer>();
        dp.put(0, 0);
        HashMap<Integer, Integer> initMap = new HashMap<Integer, Integer>();
        for (Integer product : indices.keySet()) {
            initMap.put(product, 0);
        }
        fromHash.put(0, initMap);
        for (Offer offer : offers) {
            Set<Integer> products = offer.products.keySet();
            TreeSet<Integer> dp2 = new TreeSet<Integer>(dp.keySet());
            for (Integer hash : dp2.descendingSet()) {
                HashMap<Integer, Integer> quantities = new HashMap<Integer, Integer>(fromHash.get(hash));
                loop : for (int m = 1; m <= 5; m++) {
                    for (Integer product : products) {
                        if (quantities.get(product) + offer.products.get(product) <= numNeeded.get(indices.get(product)))
                            quantities.put(product, quantities.get(product) + offer.products.get(product));
                        else
                            break loop;
                    }
                    int savings = dp.get(hash) + offer.savings * m;
                    if (!dp.containsKey(hash + offer.hash * m) || savings > dp.get(hash + offer.hash * m)) {
                        dp.put(hash + offer.hash * m, savings);
                    }
                    if (savings > maxSavings) {
                        maxSavings = savings;
                    }
                    if (!fromHash.containsKey(hash + offer.hash * m)) {
                        fromHash.put(hash + offer.hash * m, new HashMap<Integer, Integer>(quantities));
                    }
                }
            }
        }
        int minPrice = -maxSavings;
        for (Integer product : indices.keySet()) {
            int index = indices.get(product);
            minPrice += regPrices.get(index) * numNeeded.get(index);
        }
        out.println(minPrice);
        out.close();
        System.exit(0);
    }

    private static class Offer {
        HashMap<Integer, Integer> products;
        int price;
        int hash;
        int savings;

        public Offer(HashMap<Integer, Integer> ck, int p) {
            products = ck;
            price = p;
        }

        public void calcHash(HashMap<Integer, Integer> indices) {
            for (Integer product : indices.keySet()) {
                if (!products.containsKey(product))
                    products.put(product, 0);
            }
            hash = 0;
            for (Integer product : products.keySet()) {
                hash += products.get(product) * (int) (Math.pow(6, indices.get(product)));
            }
            fromHash.put(hash, products);
        }

        public void calcSavings(HashMap<Integer, Integer> indices, ArrayList<Integer> regPrices) {
            savings = -price;
            for (Integer product : products.keySet()) {
                savings += regPrices.get(indices.get(product)) * products.get(product);
            }
        }
        
        @Override
        public String toString() {
            return products + " " + savings;
        }
    }
}
