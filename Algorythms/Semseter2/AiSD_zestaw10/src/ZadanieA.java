import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class ZadanieA {
    public static void main(String[] args) {
        Graph graph = new Graph(1);
        graph.addVertex(1, "A");
        graph.addVertex(2, "B");
        graph.addVertex(3, "C");
        graph.addVertex(4, "D");
        graph.addVertex(5, "E");
        graph.addVertex(6, "F");
        graph.addVertex(7, "G");
        graph.addVertex(8, "H");
        graph.addVertex(9, "I");
        graph.addVertex(10, "J");

        graph.addEdge(1, 2); //AB
        graph.setEdgeValue(1, 2, 3);
        graph.addEdge(2, 3); //BC
        graph.setEdgeValue(2, 3, 2);
        graph.addEdge(2, 4); //BD
        graph.addEdge(4, 5); //DE
        graph.addEdge(5, 6); //EF
        graph.addEdge(6, 7); //FG
        graph.addEdge(6, 8); //FH
        graph.setEdgeValue(6, 8, 2);
        graph.addEdge(7, 8); //GH
        graph.addEdge(8, 3); //HC
        graph.setEdgeValue(8, 3, 2);
        graph.addEdge(8, 9); //HI
        graph.setEdgeValue(8, 9, 2);
        graph.addEdge(8, 10);

        graph.printGraph();

        //odległości Z każdego pomieszczenia do A oiaz do J
        graph.dijkstra(1, -1); //A
        graph.dijkstra(10, -1); //J
        //najkrótsza ścieżka z I do D
//        graph.dijkstra(9, -1);
        graph.dijkstra(9, 4);
    }

    public static class Graph {
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

        public void addVertex(int x, String s) {
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

        public void dijkstra(int source, int end) {
            int[] dist = new int[vertexCount+1];
            int[] previousVertex = new int[vertexCount+1];
            Boolean[] visited = new Boolean[vertexCount+1];
            int prev = 0;

            for(int i = 1; i <= vertexCount; i++) {
                dist[i] = Integer.MAX_VALUE;
                visited[i] = false;
            }
            dist[source] = 0;

            for(int j = 1; j <= vertexCount; j++) {
                int u = minimumDistance(dist, visited);
                visited[u] = true;

                for(int v = 1; v <= vertexCount; v++) {
                    if(!visited[v] && graphArray.get(u).get(v) != 0 && dist[u] + graphArray.get(u).get(v) < dist[v]) {
                        dist[v] = dist[u] + graphArray.get(u).get(v);
                        previousVertex[v] = u;
                    }
                }
            }

            if(end > 0) {
                printDijkstraPath(previousVertex, end);
            } else {
                printDijkstra(dist);
            }
        }

        public int minimumDistance(int[] dist, Boolean[] visited) {
            int min = Integer.MAX_VALUE;
            int min_index = -1;

            for(int v = 1; v <= vertexCount; v++) {
                if(!visited[v] && dist[v] <= min) {
                    min = dist[v];
                    min_index = v;
                }
            }

            return min_index;
        }

        public void printDijkstra(int[] dist) {
            System.out.println("Vertex  Distance");
            for(int i = 1; i <= vertexCount; i++) {
                System.out.println(stringForVertex.get(i) + ":      " + dist[i]);
            }
            System.out.println();
        }

        public void printDijkstraPath(int[] previousVertex, int end) {
            System.out.println("Shortest path");
            int v = end;
            while(v > 0) {
                System.out.println(stringForVertex.get(v));
                v = previousVertex[v];
            }
            System.out.println();
        }
    }
}
