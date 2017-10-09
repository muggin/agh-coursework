package Adapter;
import Adapter.Figura;

/**
 * Created by Wojtek on 19/12/14.
 */
public class MainClass {
    public static void main(String [] args) {

        Figura figury [] = new Figura[2];

        figury[0] = new LiniaAdapted(new Linia());
        figury[1] = new KwadratAdapted(new Kwadrat());

        for(Figura element : figury) {
            element.draw();
        }

    }
}
