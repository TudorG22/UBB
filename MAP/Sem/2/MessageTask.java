import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task {
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;
    public static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd hh:mm");

    public MessageTask(String taskID, String description, String message, String from, String to, LocalDateTime date) {
        super(taskID, description);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public void execute() {
        System.out.println(message + "blabla" + date.format(DATE_TIME_FORMATTER));
    }

    @Override
    public String toString() {
        return super.toString() + ' ' + message + " blabla " + date.format(DATE_TIME_FORMATTER);
    }
}
