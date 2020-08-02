import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class ZadanieA {
    public static void main(String[] args) throws FileNotFoundException {
        ZadanieA zadanieA = new ZadanieA();
        Graph graph = zadanieA.new Graph(1);

        //zczytywanie z pliku
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

//        graph.printGraph();
        graph.FloydWarshall();

    }

    public class Graph {
        ArrayList<ArrayList<Integer>> graphArray;
        Map<Integer, String> stringForVertex = new HashMap<>();
        public int vertexCount = 0;

        public Graph(int vertexCount) {
            this.vertexCount = vertexCount;
            graphArray = new ArrayList<ArrayList<Integer>>(this.vertexCount);
            for(int i = 0; i <= this.vertexCount; i++) {
                graphArray.add(new ArrayList<>());
                for(int j = 0; j <= vertexCount; j++) {
                    graphArray.get(i).add(0);
                }
            }
        }

        public int findStringInMap(String string) {
            int index = -1;
            for(int i = 1; i <= stringForVertex.size(); i++) {
                if(stringForVertex.get(i).equals(string)) {
                    index = i;
                    break;
                }
            }
            return index;
        }

        public void addVertex(int x, String s) {
//            if(findStringInMap(s) < 0) {
                if(x > 0 && x < vertexCount) {
                    graphArray.get(x).set(0, 1);
                    stringForVertex.put(x, s);
                } else if(x > 0) {
                    for(int i = 1; i <= vertexCount; i++) {
                        for(int j = vertexCount+1; j <= x; j++) {
                            graphArray.get(i).add(0);
                        }
                    }
                    for(int i = vertexCount+1; i <= x; i++) {
                        graphArray.add(new ArrayList<>());
                        for(int j = 0; j <= x; j++) {
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
            if(graphArray.get(x).get(0) != 0 && v != 0) {
                graphArray.get(x).set(0, v);
            }
        }

        public void getVertexValue(int x) {
            if(x > 0) {
                System.out.println("Vertex " + x + " value = " + graphArray.get(x).get(0));
            }
        }

        public void addEdge(int x, int y) {
            if(x > 0 && y > 0) {
                if(graphArray.get(x).get(0) > 0 && graphArray.get(y).get(0) > 0) {
                    graphArray.get(x).set(y, 1);
                    graphArray.get(y).set(x, 1);
                }
            }
        }

        public void removeEdge(int x, int y) {
            if(x > 0 && y > 0) {
                graphArray.get(x).set(y, 0);
                graphArray.get(y).set(x, 0);
            }
        }

        public void setEdgeValue(int x, int y, int v) {
            if(x > 0 && y > 0 && graphArray.get(x).get(0) > 0 && graphArray.get(y).get(0) > 0) {
                if(graphArray.get(x).get(y) > 0) {
                    graphArray.get(x).set(y, v);
                    graphArray.get(y).set(x, v);
                } else {
//                    System.out.println("Edge doesn't exist");
                }
            }
        }

        public boolean adjacent(int x, int y) {
            if(graphArray.get(x).get(y) > 0) {
//                System.out.println("Edge " + x + " - " + y + " exists");
                return true;
            } else {
//                System.out.println("Edge " + x + " - " + y + " doesn't exist");
                return false;
            }
        }

        public int neighbours(int x, int print) {
            if(graphArray.get(x).get(0) > 0) {
//                if(print == 1)
//                    System.out.println("Vertex " + x + " neighbours: ");
                for (int i = 1; i < graphArray.get(x).size(); i++) {
                    if(graphArray.get(x).get(i) > 0) {
                        return graphArray.get(x).get(i);
//                        if(print == 1)
//                            System.out.print(i + ", ");
                    }
                }
                if(print == 1)
                    System.out.println();
            }
            return 0;
        }

        public void printGraph() {
            for(int i = 1; i < graphArray.size(); i++) {
                if(graphArray.get(i).get(0) > 0) {
//                    System.out.println("Vertex " + i + ": ");
                    System.out.println("Vertex " + stringForVertex.get(i) + ": ");
                    for (int j = 1; j < graphArray.get(i).size(); j++) {
                        if (graphArray.get(i).get(0) > 0) {
                            if (graphArray.get(i).get(j) != 0) {
//                                System.out.println(j + " value " + graphArray.get(i).get(j) + ", ");
                                System.out.println(stringForVertex.get(j) + " value " + graphArray.get(i).get(j) +", ");
                            }
                        }
                    }
                    System.out.println();
                }
            }
        }

        public void FloydWarshall() {
            int[][] dist = new int[vertexCount+1][vertexCount+1];
            int i, j, k;

            for (i = 1; i < vertexCount+1; i++)
                for (j = 1; j < vertexCount+1; j++) {
                    dist[i][j] = 99999;
                    if(graphArray.get(i).get(j) > 0) {
                        dist[i][j] = graphArray.get(i).get(j);
                    }
                    if(i == j) {
                        dist[i][j] = 0;
                    }
                }

            for (k = 1; k < vertexCount+1; k++)
            {
                for (i = 1; i < vertexCount+1; i++)
                {
                    for (j = 1; j < vertexCount+1; j++)
                    {
                        if (dist[i][k] + dist[k][j] < dist[i][j])
                            dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
            printSolution(dist);

        }

        void printSolution(int[][] dist)
        {
            System.out.print("                     ");
            for(int k = 1; k<vertexCount+1; k++) {
                System.out.print(stringForVertex.get(k));
                int numOfSpaces = 21 - stringForVertex.get(k).length();
                for(int s = 0; s < numOfSpaces; s++) {
                    System.out.print(" ");
                }
            }
            System.out.println();

            for (int i=1; i<vertexCount+1; ++i)
            {
                System.out.print(stringForVertex.get(i));
                int numOfSpaces = 21 - stringForVertex.get(i).length();
                for(int s = 0; s < numOfSpaces; s++) {
                    System.out.print(" ");
                }

                for (int j=1; j<vertexCount+1; ++j)
                {
                    if (dist[i][j] > 99)
                        System.out.print(dist[i][j]+"                  ");
                    else if(dist[i][j] > 9)
                        System.out.print(dist[i][j]+"                   ");
                    else
                        System.out.print(dist[i][j]+ "                    ");

                }
                System.out.println();
            }
        }
    }
}