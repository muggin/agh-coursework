package Adapter;

import Adapter.Figura;

/**
 * Created by Wojtek on 19/12/14.
 */
public class KwadratAdapted extends Figura {
    private Kwadrat kwadrat;

    KwadratAdapted() {
        this.kwadrat = new Kwadrat();
    }

    KwadratAdapted(Kwadrat kwadratRef) {
        this.kwadrat = kwadratRef;
    }

    @Override
    public void draw() {
        this.kwadrat.rysuj();
    }
}
