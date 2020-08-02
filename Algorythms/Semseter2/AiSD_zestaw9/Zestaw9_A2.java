import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;

public class Zestaw9_A2 {
    public static void main(String[] args) throws FileNotFoundException {
        Zestaw9_A2 zestaw9_A = new Zestaw9_A2();
        ArrayList<String> arrayFromFile = new ArrayList<String>();
        Graph graph = new Graph();

        //zczytywanie z pliku
        try {
            File slowa = new File("slowa.txt");
            Scanner s = new Scanner(slowa);
            while (s.hasNextLine()) {
                String data = s.nextLine();
                if (data.length() == 4) {
                    arrayFromFile.add(data);
                    graph.addVertex(data);
                }
            }
            s.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        //słowo startowe
        System.out.println("Podaj 4 literowe słowo poczatkowe:");
        Scanner sc = new Scanner(System.in);
        String word_start = sc.nextLine();
        if (word_start.length() != 4) {
            System.out.println("Niepoprawna dlugosc slowa!");
            System.exit(1);
        }

        //słowo koncowe
        System.out.println("Podaj 4 literowe słowo koncowe:");
        Scanner sc2 = new Scanner(System.in);
        String word_end = sc2.nextLine();
        if (word_end.length() != 4) {
            System.out.println("Niepoprawna dlugosc slowa!");
            System.exit(1);
        }

        //tworzenie bucketów
        Graph buckets = new Graph();
        for(int i = 0; i < arrayFromFile.size(); i++) {
            for(int k = 0; k < 4; k++) {
                String bucket = charSwapAt(arrayFromFile.get(i), k, '_');
                buckets.addVertex(bucket);
                buckets.addEdge(bucket, arrayFromFile.get(i));
            }
        }

//        //tworzenie grafu slow na podstawie bucketow
            buckets.adjList.entrySet().forEach(entry->{
                 LinkedList list = entry.getValue();
//                 System.out.println(list);
                 for(int i = 0; i < list.size(); i++) {
                     for(int k = 0; k < list.size(); k++) {
                         if(list.get(i) != null && list.get(k) != null)
                         graph.addEdge(list.get(i).toString(), list.get(k).toString());
                     }
                 }
            });
//        graph.printGraph();

        //BFS
        BFS(word_start, word_end, graph);
    }

    public static void BFS(String start, String end, Graph graph) {
        boolean shortestPathFound = false;
        // Mark all the vertices as not visited
        List<String> visited = new ArrayList<String>();

        // Create a queue for BFS
        LinkedList<String> queue = new LinkedList<String>();

        // Store path
        Map<String, String> parentNodes = new HashMap<String, String>();

        // Mark the current node as visited and enqueue it
        queue.add(start);

        while (!queue.isEmpty()) {
            String next = queue.peek();
            visited.add(next);
            start = queue.poll();

            shortestPathFound = (next.equals(end));
            if(shortestPathFound)break;

            Iterator<Object> i = graph.adjList.get(start).descendingIterator();
            while (i.hasNext()) {
                String unvisitedChild = i.next().toString();
                if (!searchVisited(unvisitedChild, visited)) { //jezeli nie jest odwiedzony
                    visited.add(unvisitedChild);
                    queue.add(unvisitedChild);
                    parentNodes.put(unvisitedChild, next);

                    if(unvisitedChild.equals(end)) {
                        List<String> shortestPath = new ArrayList<>();
                        String node = end;
                        while(node != null) {
                            shortestPath.add(node);
                            node = parentNodes.get(node);
                        }
                        Collections.reverse(shortestPath);
                        for(Object string: shortestPath) {
                            if(!string.equals(end)) {
                                System.out.print(string + " -> ");
                            } else {
                                System.out.print(string);
                                System.out.println();
                            }
                        }
                    }
                }
            }
        }
    }

    public static boolean searchVisited(String find, List array) {
        for (Object string : array) {
            if(string.equals(find)){
                return true;
            }
        }
        return false;
    }

    public static String charSwapAt(String str, int index, char c) {
        return str.substring(0, index) + c + str.substring(index+1);
    }

    static class Graph {
        HashMap<Object, LinkedList<Object>> adjList = new HashMap();

        public void addEdge(Object source, Object destination) {
            //add forward edge
            if(!source.equals(destination)) {
                LinkedList<Object> list;
                list = adjList.get(source);
                list.addFirst(destination);
                adjList.put(source, list);
            }
        }

        public void addVertex(Object vertex) {
            if(!adjList.containsKey(vertex)) {
                LinkedList<Object> list = new LinkedList<>();
                adjList.put(vertex, list);
            }
        }

        public void printGraph() {
            adjList.entrySet().forEach(entry->{
                System.out.println(entry.getKey() + " " + entry.getValue());
            });
        }
    }
}

