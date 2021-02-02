/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab3prirz2;
import java.util.Scanner;
import java.util.Iterator;


import java.util.Scanner;

/**
 *
 * @author User
 */
public class LAB3prirZ2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        

        System.out.println("Podaj liczbe filozofów od 2 do 100: ");
        int ilosc = s.nextInt();

       
        System.out.println("1. Semafory");
        System.out.println("2. Niesymetryczne");
        System.out.println("3. Moneta");
 	System.out.println("Wybierz metode: ");

        Scanner s = new Scanner(System.in);
        int wybor = s.nextInt();

        if(wybor==1)
        {
            filozofowieSemafory sem = new filozofowieSemafory(ilosc);
        }

        else if(wybor==2)
        {
            filozofowieNiesymetryczne nies = new filozofowieNiesymetryczne(ilosc);
        }

        else
        {
            filozofowieMoneta mon = new filozofowieMoneta(ilosc);
        }
    }
    
}
