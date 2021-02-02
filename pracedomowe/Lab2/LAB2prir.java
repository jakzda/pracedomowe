import java.util.function.Function;



/**
 *
 * @author User
 */
public class LAB2prir {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Function<Double, Double> funkcja = (Double x) -> Math.sin(x);

        double w1 = MetodaProstokatow.metoda(0, Math.PI, 10, funkcja);
        
        System.out.println("Metoda prostokątów: " + w1);

        double w2 = MetodaTrapezow.metoda(0, Math.PI, 10, funkcja);
        
        System.out.println("Metoda trapezów: " + w2);

        double w3 = MetodaSimpsona.metoda(0, Math.PI, 10, funkcja);
        
        System.out.println("Metoda Simpsona: " + w3);

	System.out.println("Suma = " + (w1 + w2 + w3));
 
    }
    }
    

