import java.time.LocalDateTime;

public class Message {
    private String taskID;
    private String description;
    private String message;
    private String from;
    private String to;
    private LocalDateTime date;

    public Message(String taskID, String description, String message, String from,
                   String to, LocalDateTime date) {
        this.taskID = taskID;
        this.description = description;
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    public String getTaskID() {
        return taskID;
    }

    public String getDescription() {
        return description;
    }

    @Override
    public String toString() {
        return "id=" + taskID + "|description=" + description + "|message=" + message
                + "|from=" + from + "|to=" + to
                + "|date=" + date.format(MessageTask.DATE_TIME_FORMATTER);
    }
}
