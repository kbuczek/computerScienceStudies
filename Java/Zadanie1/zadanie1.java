public class zadanie1 {
    public static void main(String[] args){

        double a = Double.parseDouble(args[0]); //liczba pierwiastkowana
        double n = Double.parseDouble(args[1]); //stopień pierwiatka
        double x = a;

        for(int i = 0; i < 100; i++){
            x = 1/n * ((n-1)*x + a/Math.pow(x, n-1));
        }

        System.out.println("Wynik: " + x);
    }
}
