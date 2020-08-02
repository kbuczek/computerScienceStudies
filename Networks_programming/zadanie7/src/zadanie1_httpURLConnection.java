import javax.xml.crypto.Data;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.Map;
import java.util.Optional;

public class zadanie1_httpURLConnection {

    private static HttpURLConnection con;
    public static void main(String[] args) {

        BufferedReader reader;
        String line;
        StringBuilder responseContent = new StringBuilder();

        //GET REQUEST
        try {
            URL url = new URL("http://th.if.uj.edu.pl/");
            con = (HttpURLConnection) url.openConnection();

            //Request setup
            con.setRequestMethod("GET");
            con.setConnectTimeout(5000);
            con.setReadTimeout(5000);

            int status = con.getResponseCode(); //200 - ok
            String type = con.getContentType(); //text/html

            if(status > 299 && !type.equals("text/html")) {
                //wystapil problem z zadaniem HTTP
                reader = new BufferedReader(new InputStreamReader(con.getErrorStream()));
                System.out.println("Status odpowiedzi http != 200");
                while((line = reader.readLine()) != null) {
                    responseContent.append(line); //dodaj error http do responseContent
                    responseContent.append(System.lineSeparator());
                }
                reader.close();

            } else {
                reader = new BufferedReader(new InputStreamReader(con.getInputStream()));
                while((line = reader.readLine()) != null) {
                    responseContent.append(line);
                    responseContent.append(System.lineSeparator());
                }

                if(!responseContent.toString().contains("Theorethical Physics Departments")) {
                    System.out.println("TO NIE JEST SPODZIEWNA STRONA");
                }
                reader.close();
            }
            System.out.println("HTTP request status: " + status);
            System.out.println(responseContent.toString());

            //Cookies
            CookieManager manager = new java.net.CookieManager();
            manager.setCookiePolicy(CookiePolicy.ACCEPT_ALL);
            CookieHandler.setDefault(manager);
            CookieStore cookieJar =  manager.getCookieStore();
            List <HttpCookie> cookies = cookieJar.getCookies();
            for (HttpCookie cookie: cookies) {
                System.out.println("CookieHandler retrieved cookie: " + cookie);
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            con.disconnect();
        }

        //POST REQUEST
        try {
            URL url = new URL("https://jsonplaceholder.typicode.com/posts");
            var urlParameters = "name=Krzysztof&occupation=programmer";
            byte[] postData = urlParameters.getBytes(StandardCharsets.UTF_8);

            con = (HttpURLConnection) url.openConnection();

            con.setDoOutput(true);
            con.setRequestMethod("POST");
            con.setRequestProperty("User-Agent", "Java client");
            con.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");

            try (DataOutputStream wr = new DataOutputStream(con.getOutputStream())) {
                wr.write(postData);
            }

            try (BufferedReader br = new BufferedReader(new InputStreamReader(con.getInputStream()))) {
                responseContent = new StringBuilder();
                while ((line = br.readLine()) != null) {
                    responseContent.append(line);
                    responseContent.append(System.lineSeparator());
                }
            }

            System.out.println(responseContent.toString());

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            con.disconnect();
        }
    }
}