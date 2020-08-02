import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class json_ksiazka_tel {
    public static void main(String[] args) {
        JSONParser jsonParser = new JSONParser();
        JSONArray objIn = new JSONArray();

        try(FileReader reader = new FileReader("ksiazka.json")) {
            Object obj = jsonParser.parse(reader);
            objIn = (JSONArray) obj;
            System.out.println(objIn);
        } catch (IOException | ParseException e) {
            e.printStackTrace();
        }

        //dodawanie nowej osoby
        JSONObject nowaOsoba = new JSONObject();
        JSONObject daneNowejOsoby = new JSONObject();
        daneNowejOsoby.put("imie", "Jeremi");
        daneNowejOsoby.put("nazwisko", "Marzec");
        daneNowejOsoby.put("numer", 600780323);
        nowaOsoba.put("osoba", daneNowejOsoby);
        objIn.add(3, nowaOsoba);

        //wypisanie osob
        for(int i = 0; i < objIn.size(); i++) {
            JSONObject array = (JSONObject) objIn.get(i);
            JSONObject osoba = (JSONObject) array.get("osoba");
            String imie = (String) osoba.get("imie");
            String nazwisko = (String) osoba.get("nazwisko");
            long numer = ((Number) osoba.get("numer")).longValue();
            System.out.println(imie + " " + nazwisko + ": " + numer + ", ");
        }


        try(FileWriter writer = new FileWriter("wyniki.json")) {
            writer.write(objIn.toJSONString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
