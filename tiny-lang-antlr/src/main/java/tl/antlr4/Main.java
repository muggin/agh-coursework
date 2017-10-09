package tl.antlr4;

import java.util.HashMap;
import java.util.Map;

import org.antlr.v4.runtime.ANTLRFileStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;


public class Main {
    public static void main(String[] args) {
        try {
            // Klasy TLLexer oraz TLParser są generowane na podstawie wprowadzonej gramatyki (TL.g4)

            // Iniciujemy LEXER podajac mu plik na ktorym przeprowadzi ANALIZE LEKSYKALNA
            TLLexer lexer = new TLLexer(new ANTLRFileStream("src/main/tl/test.tl"));

            // Inicjujemy PARSER wykorzystujac stworzony LEXER
            TLParser parser = new TLParser(new CommonTokenStream(lexer));

            // Tworzymy drzewo parsowania
            parser.setBuildParseTree(true);
            ParseTree tree = parser.parse();

            // Tworzymy globalny Scope
            Scope scope = new Scope();

            // Przechodzimy drzewo parsowania w poszukiwaniu funkcji
            Map<String, Function> functions = new HashMap<String, Function>();
            SymbolVisitor symbolVisitor = new SymbolVisitor(functions);
            symbolVisitor.visit(tree);

            // Ewalujemy drzewo parsowania wykorzystując znalezione funkcje
            EvalVisitor visitor = new EvalVisitor(scope, functions);
            visitor.visit(tree);

        } catch (Exception e) {
            if ( e.getMessage() != null) {
                System.err.println(e.getMessage());
            } else {
                e.printStackTrace();
            }
        }
    }
}
