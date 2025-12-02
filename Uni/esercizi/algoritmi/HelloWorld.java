import message.Message;

/**
 * OOP version of the <b>HelloWorld</b> program
 * @author Superpippo
 */
public class HelloWorld {
    /**
     * Main method of the class. Prints "Hello, World!"
     * @param args command line parameters (unused)
     */
    public static void main(String args[]) {
        Message msg = new Message("Hello, World!");
        msg.print();
    }
}
