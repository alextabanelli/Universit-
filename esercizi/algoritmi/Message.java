package message;

/**
 * Class for storing and printing a message.
 */
public class Message {
    private final String msg;

    /**
     * Creates an empty message.
     */
    public Message() {
        this.msg = "";
    }
    
    /**
     * Stores the <code>msg</code> string parameter
     * @param msg message to be stored
     */
    public Message(String msg) {
        this.msg = msg;
    }


    /**
     * Prints the stored message
     */
    public void print() {
        System.out.println(msg);
    }

}
