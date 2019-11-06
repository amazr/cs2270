#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <queue>

//This is a modified BFS that sets a vertex to a color, and then sets all of it's adj to a different color (red or green).
//If an two adjacent vertex's have the same color then this function will return false. If it makes it through the entire graph then it will return true!
bool bipartiteHelper(vertex *current) {
    queue <vertex*> BFSqueue;

    BFSqueue.push(current);
    current->color = "red";
    current->visited = true;

    while(!BFSqueue.empty()) {

        current = BFSqueue.front(); //Sets current to the first item in the queue
        BFSqueue.pop();             //removes the next item from the queue

        for (unsigned int i = 0; i < current->adj.size(); i++) {
            if (current->adj.at(i).v->visited == false) {   //If one of currents adj vertex's is unvisited
                current->adj.at(i).v->visited = true;       //Set the uvisited vertex to true
                if (current->adj.at(i).v->color == "") {    //If the color of the adj is blank, set it to the opposite of the parent vertex
                    if (current->color == "red") current->adj.at(i).v->color = "green";
                    else current->adj.at(i).v->color = "red";
                }
                BFSqueue.push(current->adj.at(i).v);        //Add the adj vertex to the queue
            }
            if (current->adj.at(i).v->color == current->color) return false;
        }
    }
    return true;
}

//This method runs a very simple BFS on the graph
void connectedCompHelper(vertex *current) {

    queue <vertex*> BFSqueue;
    BFSqueue.push(current);
    current->visited = true;

    while(!BFSqueue.empty()) {

        current = BFSqueue.front(); //Sets current to the first item in the queue
        BFSqueue.pop();             //removes the next item from the queue

        for (unsigned int i = 0; i < current->adj.size(); i++) {
            if (current->adj.at(i).v->visited == false) {   //If one of currents adj vertex's is unvisited
                current->adj.at(i).v->visited = true;       //Set the uvisited vertex to true
                BFSqueue.push(current->adj.at(i).v);        //Add the adj vertex to the queue
            }
        }
    }
}

//Connect vertex v1 and v2
void Graph::addEdge(std::string v1, std::string v2) {
    adjVertex vertex1;
    adjVertex vertex2;

    //Iterate through vertices vector and set the temp vertex pointers above to the vertex with the name v1 and v2
    for (int i = 0; i < vertices.size(); i++) {
        if (v1 == vertices.at(i)->name) {
            vertex1.v = vertices.at(i);
        }
        if (v2 == vertices.at(i)->name) {
            vertex2.v = vertices.at(i);
        }
    }

    //This will add each vertex to each vertex's adjacent vector list
    vertex1.v->adj.push_back(vertex2);
    vertex2.v->adj.push_back(vertex1);
}

//Adds a vertex to the graph. When a vertex is added it is NOT connected to any other vertex
//Creates a new vertex(struct) variable, sets the name, and adds it to the vector (vertices) of vertex's
void Graph::addVertex(std::string name) {
    vertex *newVertex = new vertex();
    newVertex->name = name;
    vertices.push_back(newVertex);
}

//Displays all of the edges in the form found on the pdf for A8
void Graph::displayEdges() {
    for (unsigned int i = 0; i < vertices.size(); i++) {
        std::cout << vertices.at(i)->name << " --> ";
        for (unsigned int j = 0; j < vertices.at(i)->adj.size(); j++) {  //j from 0 to the size of each vertex's adj vector
            std::cout << vertices.at(i)->adj.at(j).v->name << " ";     //displays the names of each vertex's adj vertex
        }
        std::cout << "\n";
    }
}

//Runs a BFS on the graph starting from sourceVertex
void Graph::breadthFirstTraverse(std::string sourceVertex) { 
    queue <vertex*> BFSqueue;
    vertex *source;
    
    //Set the source vertex to a temp pointer vertex
    for (unsigned int i = 0; i < vertices.size(); i++) {
        if (sourceVertex == vertices.at(i)->name) source = vertices.at(i);
    }
    
    source->visited = true;
    BFSqueue.push(source);
    vertex *current = source;
    current->distance = 0;
    std::cout << "Starting vertex (root): " << source->name << "-> ";

    while(!BFSqueue.empty()) {

        current = BFSqueue.front(); //Sets current to the first item in the queue
        BFSqueue.pop();             //removes the next item from the queue

        for (unsigned int i = 0; i < current->adj.size(); i++) {
            if (current->adj.at(i).v->visited == false) {   //If one of currents adj vertex's is unvisited
                current->adj.at(i).v->visited = true;       //Set the uvisited vertex to true
                current->adj.at(i).v->distance = current->distance + 1;
                BFSqueue.push(current->adj.at(i).v);        //Add the adj vertex to the queue
                std::cout << current->adj.at(i).v->name << "(" << current->adj.at(i).v->distance << ")"<< " ";
            }
        }
    }
}

//Returns the number of unconnected vertex's (?) wtf is this method name?
int Graph::getConnectedComponents() {
    int unconnectedComponents = 1;
    int indexToSearch = 0;
    bool unvisited = false;
    while (true) {
        unvisited = false;
        connectedCompHelper(vertices.at(indexToSearch)); //Run a BFS on an unvisited vertex
        for (unsigned int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i)->visited == false) { //If the vertex found is unvisited, that means that the BFS didn't reach it
                unconnectedComponents++;            //Increment the number of unconnected comps by one
                indexToSearch = i;                  //Set this unvisited vertex as a new comp and search it's connections
                unvisited = true;
                break;                          
            }
        }
        if (unvisited) continue;
        else break;
    }
    return unconnectedComponents;
}

//This function checks if a graph is bipartite. For a def on 'bipartite' see pdf for A8
bool Graph::checkBipartite() {
    bool result;
    int indexToSearch = 0;
    bool unvisited = false;
    while (true) {
        result = bipartiteHelper(vertices.at(indexToSearch)); //Runs a bipartite helped on the current unvisited vertex and returns a result
        if (result == false) break;
        unvisited = false;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i)->visited == false) { //If the vertex found is unvisited, that means that the BFS didn't reach it
                indexToSearch = i;                  //Set this unvisited vertex as a new comp and search it's connections
                unvisited = true;
                break;                           
            }
        }
        if (unvisited) continue;
        break;
    }
    return result;
}