/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab3zad3;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class Lab3zad3 extends Thread {

    final static int N = 4096;
    final static int CUTOFF = 100;

    static int[][] set = new int[N][N];
    public static void main(String a[]) throws IOException, InterruptedException {
        long startTime = System.currentTimeMillis();

        Scanner scan = new Scanner(System.in);
        System.out.println("Wpisz wartość części rzeczywistej stałej c: ");
        double cRe = scan.nextDouble();
        System.out.println("Wpisz wartość części urojonej stałej c: ");
        double cIm = scan.nextDouble();

        System.out.println("Wpisz wartość przybliżenia: ");
        double zoom = scan.nextDouble();
        System.out.println("Wpisz wartość o jakąc chcesz zmienić pozycję na osi X: ");
        double X = scan.nextDouble();
        System.out.println("Wpisz wartość o jakąc chcesz zmienić pozycję na osi Y: ");
        double Y = scan.nextDouble();

        Lab3zad3 thread0 = new Lab3zad3(0, cRe, cIm, zoom, X, Y);
        Lab3zad3 thread1 = new Lab3zad3(1, cRe, cIm, zoom, X, Y);
        Lab3zad3 thread2 = new Lab3zad3(2, cRe, cIm, zoom, X, Y);
        Lab3zad3 thread3 = new Lab3zad3(3, cRe, cIm, zoom, X, Y);

        thread0.start();
        thread1.start();
        thread2.start();
        thread3.start();

        thread0.join();
        thread1.join();
        thread2.join();
        thread3.join();

        long endTime = System.currentTimeMillis();

        System.out.println("Obliczenia zakonczone w czasie " + (endTime - startTime) + " milisekund");

        BufferedImage img = new BufferedImage(N, N, BufferedImage.TYPE_INT_ARGB);

        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                int k = set[i][j];

                float level;
                if(k < CUTOFF){
                    level = (float) k / CUTOFF;
                }else{
                    level = 0;
                }
                Color c = new Color(0, level, 0);
                img.setRGB(i, j, c.getRGB());
            }
        }

        ImageIO.write(img, "PNG", new File("Julia.png"));
    }

    int me;
    double cRe, cIm, zoom, X, Y;
    public Lab3zad3(int me, double cre, double cIm, double zoom, double X, double Y){
        
        this.me = me;
        this.cRe = cre;
        this.cIm = cIm;
        this.zoom = zoom;
        this.X = X;
        this.Y = Y;
    }

    public void run(){
        
        int begin = 0, end = 0;

        if(me == 0){
            begin = 0;
            end = (N/4) * 1;
        }
        else if (me == 1){
            begin = (N/ 4) * 1;
            end = (N / 4) * 2;
        }
        else if (me == 2){
            begin = (N/ 4) * 2;
            end = (N / 4) * 3;
        }
        else if (me == 3){
            begin = (N/ 4) * 3;
            end = N;
        }
 
        
        for (int i = begin; i < end; i++){
            for (int j = 0; j < N; j++){
                double cr = 1.5 * (i - N / 2) / (0.5 * zoom * N) + X;
                double ci = (j - N / 2) / (0.5 * zoom * N) + Y;
                double zr = cr, zi = ci;

                int k = 0;
                while(k < CUTOFF && zr * zr + zi * zi < 4.0){

                    double oldr = zr;
                    double oldi = zi;

                    zr = oldr * oldr - oldi * oldi + cRe;
                    zi = 2 * oldr * oldi + cIm;

                    k++;
                }
                set[i][j] = k;
            }
        }
    }
}
