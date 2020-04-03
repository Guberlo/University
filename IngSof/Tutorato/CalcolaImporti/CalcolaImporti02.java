import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.util.ArrayList;
import java.util.List;

public class CalcolaImporti{
  private List<String> importi = new ArrayList<>();
  private float totale, massimo;

  public float calcola(String n, String c){
    LineNumberReader f = new LineNumberReader(new FileReader(new File(n,c)));
    String riga;

    while(true){
      riga = f.readLine();
      if(null == riga) break;
      if(!importi.contains(riga))
        importi.add(riga);
    }
    f.close();
    // calcola totale
    totale = 0;
    for(int i=0; i<importi.size(); i++)
      totale += Float.parseFloat(importi.get(i));
    //calcola massimo
    massimo = importi.get(0);
    for(int i=1; i<importi.size(); i++)
      if(massimo < importi.get(i))
        massimo = Float.parseFloat(importi.get(i));
    return totale;
  }
}
