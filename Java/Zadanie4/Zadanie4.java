import java.io.*;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.ArrayList;
import java.lang.String;

public class Zadanie4 {
    public static void main(String[] args) throws IOException {
        Scanner s = null;
        ArrayList<Integer> array = new ArrayList<Integer>();
        try {
            s = new Scanner(new BufferedReader(new FileReader("tekst.txt")));
            while (s.hasNext()) {
                String temp = s.next();
                int length = temp.length();

                if(temp.contains(";")) {
                    length--;
                }
                if(temp.equals("-")) {
                    length = 0;
                }
                if(temp.contains(".")) {
                    length--;
                }
                if(temp.contains("...")) {
                    length--;
                }
                if(temp.contains(",")) {
                    length--;
                }
                if(temp.contains("!")) {
                    length--;
                }
                if(temp.contains("?")) {
                    length--;
                }

                //stworz array
                if(length > 0) { //jezeli mamy znak "-" to wyraz ma ilosc liter = 0;
                   if(length > array.size())
                   {
                       int krok = length - array.size();
                       for(int i = 0; i < krok; i++) { // Dodawanie pustch komórek
                           array.add(0);
                       }
                   }
                   array.set(length - 1, array.get(length - 1) + 1);
                }
            }
        } catch (NoSuchElementException e) {
            e.printStackTrace();
        } finally {
            if(s != null) {
                s.close();
            }
        }

        //wypisz array od konca
        for(int i = array.size()-1; i >= 0; i--) {
            if(array.get(i) != 0) {
                System.out.println(i+1 + " " + array.get(i));
            }
        }
    }
}
