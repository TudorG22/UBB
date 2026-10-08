public class QueueContainer extends AbstractContainer{
    @Override
    public Task remove(){
        if(this.empty())
            return null;
        Task t1 = tasks[0];
        for(int i = 0; i < size - 1; i++){
            tasks[i] = tasks[i + 1];
        }
        size--;
        return t1;
    }
}
