import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import java.io.*;
import java.net.*;
import java.util.*;

//my auth token:  

public class Zadanie1 {

    private static HttpURLConnection con;
    private static int status = 200;

    public static void main(String[] args) {

        StringBuilder bandName = new StringBuilder();
        String getRequestResponse = "";
        String apiQuestion = "";

        if(args.length == 0) {
            System.out.println("Podaj NUMER ID zespołu lub NAZWĘ zespołu muzycznego, jako pierwsze argumenty wywołania programu!");
            System.exit(1);
        }

        for(int i = 0; i < args.length; i++) {
            bandName.append(args[i]);
            if(i != args.length-1) {
                bandName.append("+");
            }
        }

        boolean isNumeric = isNumeric(bandName.toString()); //check if argument is band id

        if(!isNumeric) {
            apiQuestion = "https://api.discogs.com/database/search?q=" + bandName + "&type=artist&token=sLJvCfbPJIFmPrcIklPOsdNNiuXPNHlOqxZrPyOv";
            getRequestResponse = getRequest(apiQuestion); //search bandName
        }

        //JSON
        JSONParser jsonParser = new JSONParser();
        if(status == 200) {
            try {
                JSONObject jsonObject;
                JSONArray array;
                long bandId;

                if(!isNumeric) {
                    jsonObject = (JSONObject) jsonParser.parse(getRequestResponse);
                    array = (JSONArray) jsonObject.get("results");
                    JSONObject objectResults0 = (JSONObject) array.get(0); //choose first bandName in the array
                    bandId = (long) objectResults0.get("id");
                } else {
                    bandId = Long.parseLong(bandName.toString());
                }

                apiQuestion = "https://api.discogs.com/artists/" + bandId; //find that bandName
                getRequestResponse = getRequest(apiQuestion);

                if(status == 200) {
                    jsonObject = (JSONObject) jsonParser.parse(getRequestResponse);
                    array = (JSONArray) jsonObject.get("members");
                    Bands bands = new Bands();
                    //przeszukaj "members"
                    for(int i = 0; i < array.size(); i++) {
                        JSONObject bandNameArtistObject = (JSONObject) array.get(i);
                        long artistId = (long) bandNameArtistObject.get("id");
                        apiQuestion = "https://api.discogs.com/artists/" + artistId; //search each bandName member
                        getRequestResponse = getRequest(apiQuestion);

                        if(status == 200) {
                            JSONObject artistObject = (JSONObject) jsonParser.parse(getRequestResponse);
                            String artistName = (String) artistObject.get("name");
                            JSONArray artistArray = (JSONArray) artistObject.get("groups");
                            for(int j = 0; j < artistArray.size(); j++) {
                                JSONObject groupsObj = (JSONObject) artistArray.get(j);
                                String artistBandName = (String) groupsObj.get("name");
                                bands.addBand(artistBandName);
                                bands.addBandMember(artistBandName, artistName);
                            }
                        }
                    }
                    bands.print();
                }
            } catch (ParseException e) {
                e.printStackTrace();
            }
        }
    }

    private static String getRequest(String urlRequest) {
        String responseContentString = "";

        try {
            BufferedReader reader;
            String line;
            StringBuilder responseContent = new StringBuilder();

            URL url = new URL(urlRequest);
            con = (HttpURLConnection) url.openConnection();

            //Request setup
            con.setRequestMethod("GET");
            con.setConnectTimeout(1000);
            con.setReadTimeout(1000);

            status = con.getResponseCode(); //200 - ok
            String type = con.getContentType(); //text/html

            if (status > 299 && !type.equals("text/html")) {
                //wystapil problem z zadaniem HTTP
                reader = new BufferedReader(new InputStreamReader(con.getErrorStream()));
                System.out.println("Status: " + status + " odpowiedzi http != 200");
                if(status == 429) {
                    System.out.println("Too many requests. Spróbuj ponownie później.");
                }
                while ((line = reader.readLine()) != null) {
                    responseContent.append(line); //dodaj error http do responseContent
                    responseContent.append(System.lineSeparator());
                }
                reader.close();

            } else {
                reader = new BufferedReader(new InputStreamReader(con.getInputStream()));
                while ((line = reader.readLine()) != null) {
                    responseContent.append(line);
                    responseContent.append(System.lineSeparator());
                }
                reader.close();
            }

            responseContentString = responseContent.toString();

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            con.disconnect();
        }

        return responseContentString;
    }

    public static boolean isNumeric(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    static class Bands {
        Map<String, ArrayList<String>> adjList = new TreeMap();

        public void addBandMember(String bandName, String bandMember) {
            if(!bandName.equals(bandMember)) {
                ArrayList<String> list;
                list = adjList.get(bandName);
                list.add(bandMember);
                adjList.put(bandName, list);
            }
        }

        public void addBand(String bandName) {
            if(!adjList.containsKey(bandName)) {
                ArrayList<String> list = new ArrayList<>();
                adjList.put(bandName, list);
            }
        }

        public void print() {
            System.out.println();
            adjList.entrySet().forEach(entry->{
                if(entry.getValue().size() > 1)
                    System.out.println(entry.getKey() + " " + entry.getValue());
            });
        }
    }
}