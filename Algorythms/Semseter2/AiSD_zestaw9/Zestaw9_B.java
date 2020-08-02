import java.util.*;

public class Zestaw9_B {
    public static void main(String[] args) {
        Graph graph = new Graph();
        graph.addVertex("3/4 cup milk");
        graph.addVertex("1 egg");
        graph.addVertex("1 Tbl Oil");
        graph.addVertex("1 cup mix");
        graph.addVertex("heat griddle");
        graph.addVertex("pour 1/4 cup");
        graph.addVertex("turn when bubbly");
        graph.addVertex("heat syrup");
        graph.addVertex("eat");

        graph.addEdge("3/4 cup milk", "1 cup mix");
        graph.addEdge("1 egg", "1 cup mix");
        graph.addEdge("1 Tbl Oil", "1 cup mix");
        graph.addEdge("1 cup mix", "pour 1/4 cup");
        graph.addEdge("1 cup mix", "heat syrup");
        graph.addEdge("heat griddle", "pour 1/4 cup");
        graph.addEdge("pour 1/4 cup", "turn when bubbly");
        graph.addEdge("turn when bubbly", "eat");
        graph.addEdge("heat syrup", "eat");

        DFS("3/4 cup milk", graph);

        System.out.println("Print Graph:");
        graph.printGraph();
    }

    public static void DFS(String start, Graph graph) {
        System.out.println("DFS:");
        Stack<String> stack = new Stack<String>();
        // Mark all the vertices as not visited
        List<String> visited = new ArrayList<String>();

        DFSRekurencja(start, visited, graph, stack);

        //dfs od wszystkich nieodwiedzonych wierzchołków
        for(Object key : graph.adjList.keySet()) {
//            System.out.println(key.toString());
            if(!searchVisited(key.toString(), visited)) {
                DFSRekurencja(key.toString(), visited, graph, stack);
            }
        }

        //wypisz stack
        while(!stack.empty()) {
            System.out.println(stack.pop() + " -> ");
        }

        System.out.println();
        System.out.println();
    }

    public static void DFSRekurencja(String start, List visited, Graph graph, Stack stack)
    {
        // Mark the current node as visited and print it
        visited.add(start);
        //odkomentuj zeby zobaczyć dfs
//        System.out.print(start + " -> ");

        // Recur for all the vertices adjacent to this vertex
        Iterator<Object> i = graph.adjList.get(start).descendingIterator();
        while (i.hasNext())
        {
            String unvisitedChild = i.next().toString();
            if (!searchVisited(unvisitedChild, visited)) {
                DFSRekurencja(unvisitedChild, visited, graph, stack);
            }
        }
        stack.push(start);
    }

    public static boolean searchVisited(String find, List array) {
        for (Object string : array) {
            if(string.equals(find)){
                return true;
            }
        }
        return false;
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
