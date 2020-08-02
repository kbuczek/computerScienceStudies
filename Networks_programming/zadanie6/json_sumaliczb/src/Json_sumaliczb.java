import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import org.json.simple.JSONArray;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class Json_sumaliczb {
    public static void main(String[] args) {
        JSONParser jsonParser = new JSONParser();
        JSONArray arrayIn = new JSONArray();
        JSONArray arrayOut = new JSONArray();
        long suma = 0;

        try(FileReader reader = new FileReader("liczby.json")) {
            Object obj = jsonParser.parse(reader);
            arrayIn = (JSONArray) obj;
            System.out.println(arrayIn);
        } catch (IOException | ParseException e) {
            e.printStackTrace();
        }

        for(int i = 0; i < arrayIn.size(); i++) {
            suma += (Long) arrayIn.get(i);
        }

        arrayOut.add(suma);

        try(FileWriter writer = new FileWriter("wynik.json")) {
            writer.write(arrayOut.toJSONString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
