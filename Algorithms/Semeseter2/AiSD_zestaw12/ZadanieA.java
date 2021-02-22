import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class ZadanieA {

    public static void main(String[] args) throws FileNotFoundException {
        ZadanieA zadanieA = new ZadanieA();
        Graph graph = zadanieA.new Graph(1);

        for(int i = 1; i < 129; i++) {
            graph.addVertex(i);
        }

        //zczytywanie z pliku
        try {
            File randgraph = new File("randgraph.txt");
            Scanner s = new Scanner(randgraph);
            while (s.hasNextLine()) {
                String data = s.nextLine();
                String[] splited = data.split("\\s+");
                int zero, one;
                double two;
                try {
                    zero = Integer.parseInt(splited[0]);
                    one = Integer.parseInt(splited[1]);
                    two = Double.parseDouble(splited[2]);
                    graph.addEdge(zero, one);
                    graph.setEdgeValue(zero, one, two);
                }
                catch (NumberFormatException e)
                {
                    e.printStackTrace();
                }

            }
            s.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        //Przykład
//        graph.addVertex(1);
//        graph.addVertex(2);
//        graph.addVertex(2);
//        graph.addVertex(3);
//        graph.addVertex(4);
//        graph.addVertex(5);
//        graph.addEdge(1, 2);
//        graph.addEdge(1, 4);
//        graph.addEdge(3, 2);
//        graph.addEdge(3, 4);
//        graph.addEdge(1, 3);
//        graph.addEdge(2, 4);
//        graph.addEdge(4, 5);
//        graph.setEdgeValue(1, 2, 190);
//        graph.setEdgeValue(1, 4, 5);
//        graph.setEdgeValue(3, 2, 3);
//        graph.setEdgeValue(3, 4, 10);
//        graph.setEdgeValue(1, 3, 1);
//        graph.setEdgeValue(2, 4, 0.6);
//        graph.setEdgeValue(4, 5, 200);

//                graph.printGraph();
        graph.prim();
        System.out.println();
    }

    public class Graph {
        ArrayList<ArrayList<Double>> graphArray;
        private int vertexCount = 0;

        public Graph(int vertexCount) {
            this.vertexCount = vertexCount;
            graphArray = new ArrayList<ArrayList<Double>>(this.vertexCount);
            for(int i = 0; i <= this.vertexCount; i++) {
                graphArray.add(new ArrayList<>());
                for(int j = 0; j <= vertexCount; j++) {
                    graphArray.get(i).add(0.0);
                }
            }
        }

        public void addVertex(int x) {
            if(x > 0 && x < vertexCount) {
                graphArray.get(x).set(0, 1.0);
            } else if(x > 0) {
                for(int i = 1; i <= vertexCount; i++) {
                    for(int j = vertexCount+1; j <= x; j++) {
                        graphArray.get(i).add(0.0);
                    }
                }
                for(int i = vertexCount+1; i <= x; i++) {
                    graphArray.add(new ArrayList<>());
                    for(int j = 0; j <= x; j++) {
                        graphArray.get(i).add(0.0);
                    }
                }
                graphArray.get(x).set(0, 1.0);
                this.vertexCount = x;

            }
        }

        public void addEdge(int x, int y) {
            if(x > 0 && y > 0) {
                if(graphArray.get(x).get(0) > 0 && graphArray.get(y).get(0) > 0) {
                    graphArray.get(x).set(y, 1.0);
                    graphArray.get(y).set(x, 1.0);
                }
            }
        }

        public void setEdgeValue(int x, int y, double v) {
            if(x > 0 && y > 0 && graphArray.get(x).get(0) > 0 && graphArray.get(y).get(0) > 0) {
                if(graphArray.get(x).get(y) > 0) {
                    graphArray.get(x).set(y, v);
                    graphArray.get(y).set(x, v);
                } else {
//                    System.out.println("Edge doesn't exist");
                }
            }
        }

        public void adjacent(int x, int y) {
            if(graphArray.get(x).get(y) > 0) {
                System.out.println("Edge " + x + " - " + y + " exists");
            } else {
                System.out.println("Edge " + x + " - " + y + " doesn't exist");
            }
        }

        public long neighbours(int x, int print) {
            long startTime = System.nanoTime();
            if(graphArray.get(x).get(0) > 0) {
                if(print == 1)
                    System.out.println("Vertex " + x + " neighbours: ");
                for (int i = 1; i < graphArray.get(x).size(); i++) {
                    if(graphArray.get(x).get(i) > 0) {
                        if(print == 1)
                            System.out.print(i + ", ");
                    }
                }
                if(print == 1)
                    System.out.println();
            }
            long estimatedTime = System.nanoTime() - startTime;
            return estimatedTime;
        }

        public void printGraph() {
            for(int i = 1; i < graphArray.size(); i++) {
                if(graphArray.get(i).get(0) > 0) {
                    System.out.println("Vertex " + i + ": ");
                    for (int j = 1; j < graphArray.get(i).size(); j++) {
                        if (graphArray.get(i).get(0) > 0) {
                            if (graphArray.get(i).get(j) != 0) {
//                            System.out.println(graphArray.get(i).get(j) + ", ");
                                System.out.println(j + " value " + graphArray.get(i).get(j) + ", ");
                            }
                        }
                    }
                    System.out.println();
                }
            }
        }

        void prim() //szuka najmniejszego połączenia spośród wszystkich odwiedzonych wierzchołków
        {
            int[] parent = new int[vertexCount+1];
            double[] key = new double[vertexCount+1]; //wartosci powiazan
            Boolean[] visited = new Boolean[vertexCount+1]; //odwiedzone wieszchołki

            for (int i = 1; i < vertexCount+1; i++) {
                key[i] = Integer.MAX_VALUE;
                visited[i] = false;
            }

            //szukam wierzcholka z najmniejszym polaczeniem w całym grafie
            int minEdgeVertex = 1;
            double minEdgeValue = Integer.MAX_VALUE;
            for (int x = 1; x < vertexCount+1; x++) {
                for(int y = 1; y < vertexCount+1; y++) {
                    if(graphArray.get(x).get(y) < minEdgeValue) {
                        minEdgeValue = graphArray.get(x).get(y);
                        minEdgeVertex = x;
                    }
                }
            }

            key[minEdgeVertex] = 0;
            parent[minEdgeVertex] = 0;

            for (int j = 1; j < vertexCount+1; j++) {
                int u = primMinKey(key, visited); //szukanie najmniejszego połączenia, zwraca index do wierzchołka z najkrótszą ścieżką
                visited[u] = true;

                for (int v = 1; v < vertexCount+1; v++) {
                    if (graphArray.get(u).get(v) != 0 && !visited[v] && graphArray.get(u).get(v) < key[v]) { //przeszukaj sąsiadów wybranego wierzchołka
                        parent[v] = u; //zapisz jaki był poprzednik wierzchołka v
                        key[v] = graphArray.get(u).get(v); //zapisz wartość połączenia
                    }
                }
            }

            primPrint(parent, key);
        }

        int primMinKey(double[] key, Boolean[] visited)
        {
            double min = Integer.MAX_VALUE;
            int min_index = -1;

            for (int v = 1; v < vertexCount+1; v++)
                if (!visited[v] && key[v] < min) {
                    min = key[v];
                    min_index = v;
                }

            return min_index;
        }

        void primPrint(int[] parent, double[] key)
        {
            System.out.println("Prim's Spanning Tree:");
            System.out.println("Edge    Weight");
            double total = 0.0;
            for (int i = 2; i < vertexCount+1; i++) {
                System.out.println(parent[i] + " - " + i + "   " + key[i]);
                total += key[i];
            }

            System.out.println("Total sum of all Minimum Spanning Tree Edges: " + total);
        }

        //O(ilość wierzcholkóów * ilość połączeń) = O(n^2). Przeszukuje zawsze cały graf i wybiera najmniejsze połączenie, jeżeli nie tworzy ono cyklu
        //Jest inaczej jeżeli połączenia będziemy trzymać w Min Heap O(n * log(n))
        public void Kruskal() {

        }
    }
}
