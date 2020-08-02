import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

//wersja 2 działa tylko w java 11+
public class zadanie1_HttpClient {
    public static void main(String[] args) throws IOException, InterruptedException {
        //GET REQUEST
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder().uri(URI.create("http://th.if.uj.edu.pl/")).build();
        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
        System.out.println(response.body());

        //POST REQUEST
        HttpClient client2 = HttpClient.newBuilder().build();
        HttpRequest request2 = HttpRequest.newBuilder()
                .uri(URI.create("https://jsonplaceholder.typicode.com/posts"))
                .POST(HttpRequest.BodyPublishers.ofString("name=Krzysztof&occupation=programmer"))
                .build();

        HttpResponse<?> response2 = client.send(request2, HttpResponse.BodyHandlers.discarding());
        System.out.println(response2.toString());
    }
}
