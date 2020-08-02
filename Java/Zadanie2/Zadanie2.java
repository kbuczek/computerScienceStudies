public class Zadanie2 {

    public abstract class Abstract {
        public double a, b, h, temp, total = 0;
        public static final int n = 1000; //ilosc podzialow przedziału (a,b)
        public abstract double funkcja(double x);
        public double calculateIntegral() {
            h = (b - a)/n; //dlugosc przedzialow
            temp = a;
            for(int i = 1; i < n; i++) {
                total += funkcja(temp);
                temp += h;
            }
            total += (funkcja(a) + funkcja(b)) / 2;
            total = h * total;
            return total;
        }
    }

    public class funkcja1 extends Abstract {
        public double funkcja(double x) {
            return Math.sin(x);
        }
    }

    public class funkcja2 extends Abstract {
        public double funkcja(double x) {
            return Math.cos(x);
        }
    }

    public static void main(String[] args) {
        Zadanie2 zadanie = new Zadanie2();
        funkcja1 f1 =  zadanie.new funkcja1();
        funkcja2 f2 =  zadanie.new funkcja2();

        if(args.length < 2) {
            System.out.println("Brak argumentow");
        } else {
            f1.a = Double.parseDouble(args[0]);
            f1.b = Double.parseDouble(args[1]);
            System.out.println(f1.calculateIntegral());

            f2.a = Double.parseDouble(args[0]);
            f2.b = Double.parseDouble(args[1]);
            System.out.println(f2.calculateIntegral());
        }
    }

}
