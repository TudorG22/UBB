public class StackContainer extends AbstractContainer {
    @Override
    public Task remove(){
        if(this.empty())
            return null;
        return tasks[--size];
    }
}
