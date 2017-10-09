package Decorator;

/**
 * Created by Wojtek on 19/12/14.
 */
public class OknoDekorator implements Okno {
    private Okno okno;

    // Konstruktor musi miec parametr do obiektu ktory implementuje.
    OknoDekorator(Okno oknoRef) {
        this.okno = oknoRef;
    }

    public void pokaz() {
        okno.pokaz();
    }
}
