import java.util.function.Function;

public class MetodaTrapezow
{
    public static double metoda(double x1, double x2, int y, Function<Double, Double> ff)
    {
        Trapez[] tab = new Trapez[y+1];
        double result = 0;

        for (int i=0; i<y+1; i++)
        {
            Trapez f = new Trapez(x1, x2, y, i, ff);
            f.start();
            tab[i] = f;
        }

        for (int i=0; i<y+1; i++)
        {
            try
            {
                tab[i].join();
                result = result + tab[i].returnResult();
            }
            catch(InterruptedException e)
            {
                e.printStackTrace();
            }
        }
        
        return result;
    }
}
