public class TestPagamenti{
  private Pagamenti pgm = new Pagamenti();
  private void initLista(){
    pgm.svuota();
    pgm.inserisci("321.01");
    pgm.inserisci("531.7");
    pgm.inserisci("1234.5");
  }

  public void testSomma(){
    initLista();
    pgm.calcolaSomma();
    if(pgm.getSomma() == 2087.21f)
      System.out.println("OK test somma");
    else System.out.println("FAILED test somma");
  }

  public void testMax(){
    initLista();
    pgm.calcolaMassimo();
    if(Math.abs(pgm.getMassimo() - 12345.5f) < 0.01)
      System.out.println("OK test massimo");
    else System.out.println("FAILED test massimo");
  }

  public void testLeggiFile(){
    try{
      pgm.leggiFile("csvfiles","importi.csv");
      System.out.println("OK test leggi file");
    }catch(IOException e){
      System.out.println("FAILED test leggi file");
    }
  }

  public static void main(String[] args){
    TestPagamenti t1 = new TestPagamenti();
    t1.testLeggiFile();
    t1.testSomma();
    t1.testMax();
  }
}
