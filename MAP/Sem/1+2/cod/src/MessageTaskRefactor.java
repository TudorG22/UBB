public class MessageTaskRefactor extends Task{
    private final Message message;

    public MessageTaskRefactor(Message message){
        super(message.getId(), message.getSubject());
        this.message = message;
    }

    @Override
    public void execute(){
        System.out.println("id=" + message.getId() + "|subject=" + message.getSubject() +"|message=" +
                message.getBody() + "|from=" + message.getFrom() + "|to=" + message.getTo() + "|date="
                + message.getDate().format(MessageTask.DATE_TIME_FORMATTER));
    }
}
