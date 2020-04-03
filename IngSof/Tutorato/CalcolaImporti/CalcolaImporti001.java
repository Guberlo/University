import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.util.ArrayList;
import java.util.List;

public class CalcolaImporti{
  private List<String> importi = new ArrayList<>();
  private float totale;

  public float calcola(String c, String n) throws IOException{
    LineNumberReader f = new LineNumberReader(new FileReader(new File(c,n)));
    //lettura

    totale = 0;
    while(true){
      String riga = f.readLine();
      if(null == riga) break;
      importi.add(riga);
      totale += Float.parseFloat(riga);
    }
    f.close();
    return totale;
  }
}
