import java.util.function.Function;

public class Prostokat extends Thread
{
    private double result;
    private double x1;
    private double x2;
    private int y;
    private int yn;
    private Function<Double, Double> f;
    
    public Prostokat(double x1, double x2, int y, int yn, Function<Double, Double> f)
    {
        this.x1 = x1;
        this.x2 = x2;
        this.y = y;
        this.yn = yn;
        this.f = f;
    } 

    public void run()
    {
        double dx = (x2 - x1) / y;
        double xi = dx*(yn+1);
        double fxi = f.apply(xi);
        result = fxi * dx;
    }

    public double returnResult()
    {
        return result;
    }
}
