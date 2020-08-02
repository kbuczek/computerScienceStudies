import java.io.*;
import java.util.*;
import java.io.IOException;
import java.util.Properties;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class Zadanie3 {

    //funkcja wczytaj
    public void getPropValues(Properties prop) throws IOException {
        try {
            prop.load(new FileInputStream("ksiazka.txt"));
        } catch (FileNotFoundException ex) {
            System.out.println("Exception: " + ex);
        } catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {

        }
    }

    //funkcja dodaj
    public void addPropValue(Properties prop){
        String numer = "";
        String imie = "";

        Scanner sc1 = new Scanner(System.in);
        System.out.println("Wprowadz imie: ");
        imie = sc1.nextLine();

        Scanner sc = new Scanner(System.in);
        System.out.println("Wprowadz numer: ");
        numer = sc.nextLine();

        prop.put(imie, numer);
    }

    //funkcja usun
    public void deletePropValue(Properties prop) {
        String imie = "";
        Scanner sc = new Scanner(System.in);
        System.out.println("Wprowadz imie: ");
        imie = sc.nextLine();
        prop.remove(imie);
    }

    //funkcja wyszukaj
    public Object searchPropValue(Properties prop){
        String imie = "";
        Scanner sc = new Scanner(System.in);
        System.out.println("Wprowadz imie: ");
        imie = sc.nextLine();
        System.out.println(("Numer szukanej osoby: "));
        return prop.get(imie);
    }

    //funkcja zapisz
    public void savePropValue(Properties prop) throws IOException{
        try {
            prop.store(new FileOutputStream("ksiazka.txt"), null);
        } catch (FileNotFoundException ex) {
            System.out.println("Exception: " + ex);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } finally {

        }
    }

    public static void main(String[] args) throws IOException{
            Zadanie3 p = new Zadanie3();
            Properties prop = new Properties();
            p.getPropValues(prop);
            //instrukcja obslugi
            System.out.println("Wybierz opcje:");
            System.out.println("1 - Dodaj kontakt");
            System.out.println("2 - Usun kontakt");
            System.out.println("3 - Wyszukaj kontakt");
            System.out.println("4 - Zapisz i wyjdz");

            int choose;
            int n = 1;

            while(n > 0){
                Scanner S = new Scanner(System.in);
                choose = S.nextInt();
                
                switch(choose){
                case 1: //dodaj
                    p.addPropValue(prop);
                	break;
                case 2: //usun
                    p.deletePropValue(prop);
                	break;
                case 3: //wyszukaj
                	System.out.println(p.searchPropValue(prop));
                	break;
                case 4: //zapisz i wyjdź
                	n = 0;
                	p.savePropValue(prop);
                	break;
                default:
                	System.out.println("Niepoprawna opcja.");
                }
            }
    }
}
