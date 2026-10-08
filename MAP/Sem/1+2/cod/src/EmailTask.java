public class EmailTask extends Task {
    private String email;

    public EmailTask(String taskID, String description, String email){
        super(taskID, description);
        this.email = email;
    }

    @Override
    public void execute(){
        System.out.println(email);
    }
}
