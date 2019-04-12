import java.io.*;

public interface Posto{     //Product
  public String getPosizione();
  public int getCosto();
  public String getSettore();
}

public class Palco implements Posto{   //ConcreteProduct
  private int numero;

  public Palco(){
    numero = (int) (Math.random() * 20);
  }

  public int getCosto(){
    if(numero > 10) return 50;
    return 40;
  }

  public String getPosizione(){
    return Integer.toString(numero);
  }

  public String getSettore(){
    if(numero == 20) return "Centrale";
    if(numero > 10) return "Verde";
    return "Blu";
  }
}

public class Platea implements Posto{
  private String[] nomi = {"A", "B", "C", "D", "E", "F"};
  private int numero;
  private int riga;

  public Platea(){      //ConcreteProduct
    numero = (int) (Math.random() * 10);
    riga = (int) (Math.random() * 5);
  }

  public int getCosto(){
    if(numero > 5 && rigaMax()) return 100;
    if(numero > 5 && rigaMin()) return 80;
    return 60;
  }

  public String getPosizione(){
    return nomi[riga].concat(Integer.toString(numero));
  }

  public String getSettore(){
    if(riga == 0) return "Riservato";
    return "Normale";
  }

  public boolean rigaMax(){
    if(riga >= 1 && riga <= 4) return true;
    return false;
  }

  public boolean rigaMin(){
    if(riga == 0 || riga == 5) return true;
    return false;
  }
}

public abstract class GnrPosizioni{     //Creator
  private final int maxPosti = 100;
  private TreeSet< String > pst = new TreeSet< >();

  public Posto prendiNumero(int x){
    if(pst.size() == maxPosti) return null;

    Posto p;
    do{
      p = getPosto(x);
    }while(pst.contains(p.getPosizione()));
    pst.add(p.getPosizione());
    return p;
  }

  public void printPostiOccupati(){
    for(String s : pst) System.out.print(s + " ");
  }

  public abstract Posto getPosto(int tipo);
}

public class extends GnrPosizioni{    //ConcreteCreator
  public Posto getPosto(int tipo){
    if(tipo == 1) return new Palco();
    return new Platea();
  }
}

//Client del Product
public class Biglietto{
  private String nome;
  private Posto pos;

  public Biglietto(Posto p){
    pos = p;
  }

  public void intesta(String s){
    nome = s;
  }

  public String getDettagli(){
    return pos.getPosizione();
  }

  public String getNome(){
    return nome;
  }

  public int getCosto(){
    return pos.getCosto();
  }
}

//main
public class MainBiglietti{
  private static Posizioni cp = new Posizioni();

  public static void main(String[] args){
    Posto pos = cp.prendiNumero(0);
    Biglietto b = new Biglietto(pos);
    b.intesta("Marco");
    System.out.println("Costo" + b.getCosto());

    new Biglietto(cp.prendiNumero(0));
    new Biglietto(cp.prendiNumero(0));
    cp.printPostiOccupati();
  }
}
