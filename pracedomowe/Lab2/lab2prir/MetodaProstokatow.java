import java.util.function.Function;

public class MetodaProstokatow
{
    public static double metoda(double x1, double x2, int y, Function<Double, Double> ff)
    {
        Prostokat[] tab = new Prostokat[y];
        for (int i=0; i<y; i++)
        {
            tab[i] = new Prostokat(x1, x2, y, i, ff);
            tab[i].start();
        }

        double result = 0;
        for (int i=0; i<y; i++)
        {
            try
            {
                tab[i].join();
            }
            catch(InterruptedException e)
            {
                e.printStackTrace();
            }
            result = result + tab[i].returnResult();
        }
        return result;
    }
}
