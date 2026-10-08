import java.time.LocalDate;
import java.time.LocalDateTime;

public class Message {
    private String id;
    private String subject;
    private String body;
    private String to;
    private String from;
    private LocalDateTime date;

    public Message(String id, String subject, String body, String to, String from, LocalDateTime date){
        this.id = id;
        this.subject = subject;
        this.body = body;
        this.to = to;
        this.from = from;
        this.date = date;
    }

    public String getId(){
        return id;
    }

    public String getSubject(){
        return subject;
    }

    public String getBody(){
        return body;
    }

    public String getTo(){
        return to;
    }

    public String getFrom(){
        return from;
    }

    public LocalDateTime getDate(){
        return date;
    }
}
