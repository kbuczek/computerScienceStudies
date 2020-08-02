import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Zestaw4 {
    public static void main(String[] args) throws FileNotFoundException {
        PrintWriter writer_neighbours = new PrintWriter("neighbours.txt");
        Zestaw4 zestaw4 = new Zestaw4();

        Graph graph1 = zestaw4.new Graph(6);
        graph1.addVertex(1);
        graph1.addVertex(2);
        graph1.addVertex(4);
        graph1.addVertex(5);
        graph1.removeVertex(2);
        graph1.setVertexValue(1, 3);
        graph1.getVertexValue(1);
        graph1.addEdge(1, 4);
        graph1.addEdge(5, 4);
        graph1.removeEdge(4, 1);
        graph1.adjacent(5, 4);
        graph1.setEdgeValue(1, 4, 9);
        graph1.addEdge(1, 5);
        graph1.neighbours(5, 1);

        Graph graph2 = zestaw4.new Graph(1);
        for(int i = 1; i < 600; i++) {
            graph2.addVertex(i);
            graph2.addEdge(1, i);
            writer_neighbours.println(i + " " + graph2.neighbours(1, 0));
        }

        System.out.println();
        graph1.printGraph();

        writer_neighbours.close();
    }

    public class Graph {
        ArrayList<ArrayList<Integer>> graphArray;
        private int vertexCount = 0;

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

        public void addVertex(int x) {
            if(x > 0 && x < vertexCount) {
            graphArray.get(x).set(0, 1);
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
//                    graphArray.get(y).set(x, 1);
                }
            }
        }

        public void removeEdge(int x, int y) {
            if(x > 0 && y > 0) {
                graphArray.get(x).set(y, 0);
//                graphArray.get(y).set(x, 0);
            }
        }

        public void setEdgeValue(int x, int y, int v) {
            if(x > 0 && y > 0 && graphArray.get(x).get(0) > 0 && graphArray.get(y).get(0) > 0) {
                if(graphArray.get(x).get(y) > 0) {
                    graphArray.get(x).set(y, v);
//                    graphArray.get(y).set(x, v);
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
    }
}
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Zestaw4 {
    public static void main(String[] args) throws FileNotFoundException {
        PrintWriter writer_neighbours = new PrintWriter("neighbours.txt");
        Zestaw4 zestaw4 = new Zestaw4();

        Graph graph1 = zestaw4.new Graph(6);
        graph1.addVertex(1);
        graph1.addVertex(2);
        graph1.addVertex(4);
        graph1.addVertex(5);
        graph1.removeVertex(2);
        graph1.setVertexValue(1, 3);
        graph1.getVertexValue(1);
        graph1.addEdge(1, 4);
        graph1.addEdge(5, 4);
        graph1.removeEdge(4, 1);
        graph1.adjacent(5, 4);
        graph1.setEdgeValue(1, 4, 9);
        graph1.addEdge(1, 5);
        graph1.neighbours(5, 1);

        Graph graph2 = zestaw4.new Graph(1);
        for(int i = 1; i < 600; i++) {
            graph2.addVertex(i);
            graph2.addEdge(1, i);
            writer_neighbours.println(i + " " + graph2.neighbours(1, 0));
        }

        System.out.println();
        graph1.printGraph();

        writer_neighbours.close();
    }

    public class Graph {
        ArrayList<ArrayList<Integer>> graphArray;
        private int vertexCount = 0;

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

        public void addVertex(int x) {
            if(x > 0 && x < vertexCount) {
            graphArray.get(x).set(0, 1);
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
//                    graphArray.get(y).set(x, 1);
                }
            }
        }

        public void removeEdge(int x, int y) {
            if(x > 0 && y > 0) {
                graphArray.get(x).set(y, 0);
//                graphArray.get(y).set(x, 0);
            }
        }

        public void setEdgeValue(int x, int y, int v) {
            if(x > 0 && y > 0 && graphArray.get(x).get(0) > 0 && graphArray.get(y).get(0) > 0) {
                if(graphArray.get(x).get(y) > 0) {
                    graphArray.get(x).set(y, v);
//                    graphArray.get(y).set(x, v);
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
    }
}
