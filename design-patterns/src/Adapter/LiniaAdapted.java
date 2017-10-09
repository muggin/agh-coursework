package Adapter;

import Adapter.Figura;

/**
 * Created by Wojtek on 19/12/14.
 */
public class LiniaAdapted extends Figura {
    private Linia linia;

    LiniaAdapted() {
        this.linia = new Linia();
    }

    LiniaAdapted(Linia liniaRef) {
        this.linia = liniaRef;
    }

    @Override
    public void draw() {
        this.linia.rysuj();
    }
}
