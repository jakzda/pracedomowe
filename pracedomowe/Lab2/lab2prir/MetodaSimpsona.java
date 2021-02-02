import java.util.ArrayList;
import java.util.function.Function;

public class MetodaSimpsona
{
    public static double metoda(double x1, double x2, int y, Function<Double, Double> ff)
    {
        ArrayList <Simpson> tab = new ArrayList<Simpson>();        
        
        Simpson f0 = new Simpson(x1, x2, y, 0, 1, ff);
        Simpson fn = new Simpson(x1, x2, y, y, 1, ff);
        f0.start();
        fn.start();
        tab.add(f0);
        tab.add(fn);

        for (int i=1; i<=y; i++)
        {
            Simpson f = new Simpson(x1, x2, y, i, 2, ff);
            f.start();
            tab.add(f);
        }
        
        for (int i=1; i<=y; i++)
        {
            Simpson f = new Simpson(x1, x2, y, i, 3, ff);
            f.start();
            tab.add(f);
        }
        
        double result = 0;
        try
        {
            for (int i=0; i<tab.size(); i++)
            {
                Simpson f = tab.get(i);
                f.join();
                result = result + f.returnResult();
            }
        }
        catch(InterruptedException e)
        {
            e.printStackTrace();
        }

        return result;
    }
}
