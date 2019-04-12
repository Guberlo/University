import java.io.*;

public class Singleton {
  private static Singleton obj = new Singleton();
  private int i;
  private Singleton(){
    i = 3;
  }
  public static Singleton getInstance(){
    return obj;
  }
  public int getValue(){
    if(i<11) i++;
    return i;
  }
  public void reset(){
    i = 0;
  }
}
