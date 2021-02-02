import java.util.function.Function;

public class Simpson extends Thread
{
    private double result;
    private double x1;
    private double x2;
    private int y;
    private int yn;
    private Function<Double, Double> f;
    private int type;
    
    public Simpson(double x1, double x2, int y, int yn, int type, Function<Double, Double> f)
    {
        this.x1 = x1;
        this.x2 = x2;
        this.y = y;
        this.yn = yn;
        this.f = f;
        this.type = type;
    } 

    public void run()
    {
        double dx = (x2 - x1) / y;
        double fti = 0;
        if (type==1)
        {
            double xi = 0;
            if(yn==0)
            {
                xi = x1;
            }
            else if(yn==y)
            {
                xi = x2;
            }
            fti = f.apply(xi);
        }
        else if (type==2)
        {
            double xi = x1 + yn * dx;
            fti = f.apply(xi) * 2;
        }
        else if (type==3)
        {
            double a = x1 + (yn-1) * dx;
            double b = x1 + (yn+1) * dx;
            double xi = (a + b) / 2;
            fti = f.apply(xi) * 4;
        }
        else
        {
            result = 0;
            return;
        }
        result = dx/6 * fti;
    }

    public double returnResult()
    {
        return result;
    }
}