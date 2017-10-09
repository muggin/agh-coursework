package Decorator;

/**
 * Created by Wojtek on 19/12/14.
 */
public class OkragleOkno extends OknoDekorator {

    OkragleOkno(Okno oknoRef) {
        super = new OknoDekorator(oknoRef);
    }

    public void pokaz() {
        super.pokaz();
        System.out.println("Dekoruje okno.");
    }
}
