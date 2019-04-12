import java.io.*;

public interface ILabel { // target
    public String getNextLabel();
}

//adapter
public class Label implements ILabel{
  private LabelServer ls;
  private String p;
  public Label(String prefix){
    p = prefix;
  }
  public String getNextLabel(){
    if(ls == null)
      ls = new LabelServer(p);
    return ls.serveNextLabel();
  }
}

public class Client{

}

public class LabelServer{ // adaptee
  private int labelNum = 1;
  private String labePrefix;
  public LabelServer(String prefix){
    labelPrefix = prefix;
  }
  public String serveNextLabel(){
    return labelPrefix + labelNum++;
  }
}
