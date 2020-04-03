import java.io.*;

public class Logs{
  private static Logs obj;
  private List<String> l;

  private Logs(){
    empty();
  }
  public static getInstance(){
    if(obj == null) obj = new Logs();
    return obj;
  }
  public void record(String s){
    l.add(s);
  }
  public String dumpLast(){ //ritorna l'ultimo valore di l
    return l.getLast();
  }
  public String dumpAll(){
    String acc = "";
    for(String s : l) acc = acc.concat(s);
    return acc;
  }
  public void empty(){
    l = new ArrayList<String>();
  }
}
