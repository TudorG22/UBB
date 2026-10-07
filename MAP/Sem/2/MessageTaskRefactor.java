public class MessageTaskRefactor extends Task {
    private Message message;

    public MessageTaskRefactor(Message message) {
        super(message.getTaskID(), message.getDescription());
        this.message = message;
    }

    @Override
    public void execute() {
        System.out.println(message);
    }

    @Override
    public String toString() {
        return message.toString();
    }
}
