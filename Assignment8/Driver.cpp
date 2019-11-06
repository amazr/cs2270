#include "Graph.hpp"

//Currently being used to test basic graph creation functions
int main() {
    Graph graph;
    graph.addVertex("Boulder");
    graph.addVertex("Denver");
    graph.addVertex("Las Vegas");

    graph.addEdge("Boulder", "Denver");
    //graph.addEdge("Las Vegas", "Denver");
    std::cout << "Before BFS" << "\n";
    graph.displayEdges();
    graph.breadthFirstTraverse("Boulder");
    std::cout << "After BFS" << "\n";
    graph.displayEdges();
    std::cout << graph.getConnectedComponents() << "\n";

}