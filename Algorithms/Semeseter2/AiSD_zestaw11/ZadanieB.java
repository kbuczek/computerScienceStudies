import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;

public class ZadanieB {
    public static void main(String[] args) throws FileNotFoundException {
        ZadanieB zadanieB = new ZadanieB();
        Graph graph = zadanieB.new Graph(1);

        //zczytywanie z pliku czasy
        try {
            int index = 1;
            File czasy = new File("czasy.txt");
            Scanner s = new Scanner(czasy);
            while (s.hasNextLine()) {
                String data = s.nextLine();
                String[] splited = data.split("\\s+");
                String zero, one;
                int two;
                try {
                    zero = splited[0];
                    one =  splited[1];
                    two = Integer.parseInt(splited[2]);

                    int checkZero = graph.findStringInMap(zero);
                    if( checkZero < 0) {
                        graph.addVertex(index, zero);
                        checkZero = index;
                        index++;
                    }

                    int checkOne = graph.findStringInMap(one);
                    if( checkOne < 0) {
                        graph.addVertex(index, one);
                        checkOne = index;
                        index++;
                    }

                    graph.addEdge(checkZero, checkOne);
                    graph.setEdgeValue(checkZero, checkOne, two);

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

        //zczytywanie z pliku positions
        try {
            int index = 1;
            File positions = new File("positions.txt");
            Scanner s = new Scanner(positions);
            while (s.hasNextLine()) {
                String data = s.nextLine();
                String[] splited = data.split("\\s+");
                String zero;
                double one, two;
                try {
                    zero = splited[0];
                    one =  Double.parseDouble(splited[2]); //zamian, bo graphivz ma wspolrzedne na odwrot
                    two = Double.parseDouble(splited[1]);

                    int checkZero = graph.findStringInMap(zero);
                    graph.stringForVertexPositions.put(checkZero, one + "," + two);
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


//        graph.printGraph();
        graph.FloydWarshall();

    }

    public class Graph {
        ArrayList<ArrayList<Integer>> graphArray;
        Map<Integer, String> stringForVertex = new HashMap<>();
        Map<Integer, String> stringForVertexPositions = new HashMap<>();
        ArrayList<Integer>  fromPrintPathArray = new ArrayList<>();

        public int vertexCount = 0;

        public Graph(int vertexCount) {
            this.vertexCount = vertexCount;
            graphArray = new ArrayList<ArrayList<Integer>>(this.vertexCount);
            for (int i = 0; i <= this.vertexCount; i++) {
                graphArray.add(new ArrayList<>());
                for (int j = 0; j <= vertexCount; j++) {
                    graphArray.get(i).add(0);
                }
            }
        }

        public int findStringInMap(String string) {
            int index = -1;
            for (int i = 1; i <= stringForVertex.size(); i++) {
                if (stringForVertex.get(i).equals(string)) {
                    index = i;
                    break;
                }
            }
            return index;
        }

        public void addVertex(int x, String s) {
//            if(findStringInMap(s) < 0) {
            if (x > 0 && x < vertexCount) {
                graphArray.get(x).set(0, 1);
                stringForVertex.put(x, s);
            } else if (x > 0) {
                for (int i = 1; i <= vertexCount; i++) {
                    for (int j = vertexCount + 1; j <= x; j++) {
                        graphArray.get(i).add(0);
                    }
                }
                for (int i = vertexCount + 1; i <= x; i++) {
                    graphArray.add(new ArrayList<>());
                    for (int j = 0; j <= x; j++) {
                        graphArray.get(i).add(0);
                    }
                }
                graphArray.get(x).set(0, 1);
                stringForVertex.put(x, s);
                this.vertexCount = x;
            }
//            }
        }

        public void removeVertex(int x) {
            graphArray.get(x).set(0, 0);
        }

        public void setVertexValue(int x, int v) {
            if (graphArray.get(x).get(0) != 0 && v != 0) {
                graphArray.get(x).set(0, v);
            }
        }

        public void getVertexValue(int x) {
            if (x > 0) {
                System.out.println("Vertex " + x + " value = " + graphArray.get(x).get(0));
            }
        }

        public void addEdge(int x, int y) {
            if (x > 0 && y > 0) {
                if (graphArray.get(x).get(0) > 0 && graphArray.get(y).get(0) > 0) {
                    graphArray.get(x).set(y, 1);
                    graphArray.get(y).set(x, 1);
                }
            }
        }

        public void removeEdge(int x, int y) {
            if (x > 0 && y > 0) {
                graphArray.get(x).set(y, 0);
                graphArray.get(y).set(x, 0);
            }
        }

        public void setEdgeValue(int x, int y, int v) {
            if (x > 0 && y > 0 && graphArray.get(x).get(0) > 0 && graphArray.get(y).get(0) > 0) {
                if (graphArray.get(x).get(y) > 0) {
                    graphArray.get(x).set(y, v);
                    graphArray.get(y).set(x, v);
                } else {
//                    System.out.println("Edge doesn't exist");
                }
            }
        }

        public boolean adjacent(int x, int y) {
            if (graphArray.get(x).get(y) > 0) {
//                System.out.println("Edge " + x + " - " + y + " exists");
                return true;
            } else {
//                System.out.println("Edge " + x + " - " + y + " doesn't exist");
                return false;
            }
        }

        public int neighbours(int x, int print) {
            if (graphArray.get(x).get(0) > 0) {
//                if(print == 1)
//                    System.out.println("Vertex " + x + " neighbours: ");
                for (int i = 1; i < graphArray.get(x).size(); i++) {
                    if (graphArray.get(x).get(i) > 0) {
                        return graphArray.get(x).get(i);
//                        if(print == 1)
//                            System.out.print(i + ", ");
                    }
                }
                if (print == 1)
                    System.out.println();
            }
            return 0;
        }

        public void printGraph() {
            for (int i = 1; i < graphArray.size(); i++) {
                if (graphArray.get(i).get(0) > 0) {
//                    System.out.println("Vertex " + i + ": ");
                    System.out.println("Vertex " + stringForVertex.get(i) + ": ");
                    for (int j = 1; j < graphArray.get(i).size(); j++) {
                        if (graphArray.get(i).get(0) > 0) {
                            if (graphArray.get(i).get(j) != 0) {
//                                System.out.println(j + " value " + graphArray.get(i).get(j) + ", ");
                                System.out.println(stringForVertex.get(j) + " value " + graphArray.get(i).get(j) + ", ");
                            }
                        }
                    }
                    System.out.println();
                }
            }
        }

        public void FloydWarshall() {
            int[][] dist = new int[vertexCount + 1][vertexCount + 1];
            int[][] next = new int[vertexCount + 1][vertexCount + 1];

            int i, j, k;

            for (i = 1; i < vertexCount + 1; i++)
                for (j = 1; j < vertexCount + 1; j++) {
                    dist[i][j] = 99999;
                    if (graphArray.get(i).get(j) > 0) {
                        dist[i][j] = graphArray.get(i).get(j);
                    }
                    if (i == j) {
                        dist[i][j] = 0;
                        next[i][j] = 0;
                    } else if (dist[i][j] != 99999)
                        next[i][j] = i;
                    else
                        next[i][j] = -1;
                }

            for (k = 1; k < vertexCount + 1; k++) {
                for (i = 1; i < vertexCount + 1; i++) {
                    for (j = 1; j < vertexCount + 1; j++) {
                        if (dist[i][k] != 99999 && dist[k][j] != 99999 && (dist[i][k] + dist[k][j] < dist[i][j])) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next[i][j] = next[k][j];
                        }
                    }
                }
            }
            printSolution(dist, next);

        }

        private void printSolution(int[][] dist, int[][] next) {

            for (int v = 1; v < vertexCount + 1; v++) {
                for (int u = 1; u < vertexCount + 1; u++) {
                    if (u != v && next[v][u] != -1) {
                        System.out.printf("Shortest Path from %d -> %d is (%d ", v, u, v);
                        printPath(next, v, u);
                        System.out.println(u + ")");
                        try {
                            saveToGraphviz(v, u);
                        } catch (FileNotFoundException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }

        private void printPath(int[][] next, int v, int u) {
            if (next[v][u] == v)
                return;
            printPath(next, v, next[v][u]);
            System.out.print(next[v][u] + " ");
            fromPrintPathArray.add(next[v][u]);

        }

        public void saveToGraphviz(int start, int end) throws FileNotFoundException {

            PrintWriter writer_graphviz = new PrintWriter(polskieLitery(stringForVertex.get(start)) + polskieLitery(stringForVertex.get(end)));
            writer_graphviz.println("graph G {");

            //positions
            for(int i = 1; i < vertexCount+1; i++) {
                writer_graphviz.println(stringForVertex.get(i) + " [pos=\"" + stringForVertexPositions.get(i) + "!\"];");
            }
            writer_graphviz.println();

            //połączenia
//            System.out.println("size "+ stringForVertex.size() + " start " + start);
//            for (int name: stringForVertex.keySet()){
//                String key = Integer.toString(name);
//                String value = stringForVertex.get(name);
//                System.out.println(name + " " + value);
//            }
//
//            System.out.println("size " + fromPrintPathArray.size());
//            for(int i =0; i < fromPrintPathArray.size(); i++) {
//                System.out.println(fromPrintPathArray.get(i));
//            }
//            System.out.println("start "+ start + " end " + end);

            if(fromPrintPathArray.size() != 0) {
                writer_graphviz.println(stringForVertex.get(start) + " -- " + stringForVertex.get(fromPrintPathArray.get(0)));
            } else {
                writer_graphviz.println(stringForVertex.get(start) + " -- " + stringForVertex.get(end));
            }

            if(fromPrintPathArray.size() != 0)
            {
                for(int i=0; i < fromPrintPathArray.size()-1; i++) {
                    int currentVertex = fromPrintPathArray.get(i), nextVertex = fromPrintPathArray.get(i+1);
                    writer_graphviz.println(stringForVertex.get(currentVertex) + " -- " + stringForVertex.get(nextVertex));
                }
                writer_graphviz.println(stringForVertex.get(fromPrintPathArray.get(fromPrintPathArray.size()-1)) + " -- " + stringForVertex.get(end));
            }


            fromPrintPathArray.clear();
            writer_graphviz.println("}");
            writer_graphviz.close();
        }

        public String polskieLitery(String s) {
            s = s.replace('ą', 'a');
            s = s.replace('ć', 'c');
            s = s.replace('ę', 'e');
            s = s.replace('ł', 'l');
            s = s.replace('ń', 'n');
            s = s.replace('ó', 'o');
            s = s.replace('ś', 's');
            s = s.replace('ź', 'z');
            s = s.replace('ż', 'z');
            s = s.replace('Ą', 'a');
            s = s.replace('Ć', 'c');
            s = s.replace('Ę', 'e');
            s = s.replace('Ł', 'l');
            s = s.replace('Ń', 'n');
            s = s.replace('Ó', 'o');
            s = s.replace('Ś', 's');
            s = s.replace('Ź', 'z');
            s = s.replace('Ż', 'z');
            return s;
        }
    }
}