#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

struct edge {
    size_t dest_vertex;
    double weight;
};

struct vertex {
    size_t value;
    std::list<edge> edges;
    double distance;
    size_t prev;
    vertex() : value(0), edges(), distance(-1), prev(0) {}
};

class Graph {
private:

    std::vector<vertex> vertices;

public:
    // Task 1
    Graph();

    Graph(const Graph &other);

    Graph &operator=(const Graph &other);

    ~Graph();

    size_t vertex_count() const;

    size_t edge_count() const;

    bool contains_vertex(size_t id) const;

    bool contains_edge(size_t src, size_t dest) const;

    double cost(size_t src, size_t dest) const;

    bool add_vertex(size_t id);

    bool add_edge(size_t src, size_t dest, double weight = 1);

    bool remove_vertex(size_t id);

    bool remove_edge(size_t src, size_t dest);

    size_t min_distance( std::list<size_t> q);

    size_t get_previous( size_t dest_id) const;

    // Task 2
//    void prim(size_t source_id);
//
//    bool is_path(size_t id) const;
//
//    void prsize_t_path(size_t dest_id, std::ostream &os = std::cout) const;

    // Task 3
    void dijkstra(size_t source_id);

   double distance(size_t id) const;

    void print_shortest_path(size_t dest_id, std::ostream &os = std::cout) const;
};

Graph::Graph() : vertices() {
}

Graph::Graph(const Graph &other) : vertices() {
    for (size_t itr_vtx = 0; itr_vtx < other.vertex_count(); itr_vtx++) {
        add_vertex(other.vertices[itr_vtx].value);
        for (edge itr_edge: other.vertices[itr_vtx].edges) {
            add_edge(vertices[itr_vtx].value, itr_edge.dest_vertex, itr_edge.weight);
        }
    }
}

Graph &Graph::operator=(const Graph &other) {
    for (size_t itr_vtx = 0; itr_vtx < other.vertex_count(); itr_vtx++) {
        add_vertex(other.vertices[itr_vtx].value);
        for (edge itr_edge: other.vertices[itr_vtx].edges) {
            add_edge(vertices[itr_vtx].value, itr_edge.dest_vertex, itr_edge.weight);
        }
    }
    return *this;
}

Graph::~Graph() {
    // Nothing to implement here
}

size_t Graph::vertex_count() const {
    return vertices.size();
}

size_t Graph::edge_count() const {
    size_t count = 0;
    size_t itr;
    for (itr = 0; itr < vertices.size(); ++itr) {
        count += vertices[itr].edges.size();
    }
    return count;
}

bool Graph::contains_vertex(size_t id) const {
    size_t itr;
    for (itr = 0; itr < vertices.size(); itr++) {
        if (vertices[itr].value == id) {
            return true;
        }
    }
    return false;
}

bool Graph::contains_edge(size_t src, size_t dest) const {
    size_t itr_vertex = 0;
    for (itr_vertex = 0; itr_vertex < vertices.size(); itr_vertex++) {
        if (vertices[itr_vertex].value == src) {
            for (edge itr_edge: vertices[itr_vertex].edges) {
                if (itr_edge.dest_vertex == dest) {
                    return true;
                }
            }
        }
    }
    return false;
}

double Graph::cost(size_t src, size_t dest) const {
    size_t itr_vertex = 0;
    for (itr_vertex = 0; itr_vertex < vertices.size(); itr_vertex++) {
        if (vertices[itr_vertex].value == src) {
            for (edge itr_edge: vertices[itr_vertex].edges) {
                if (itr_edge.dest_vertex == dest) {
                    return itr_edge.weight;
                }
            }
        }
    }
    return -1;
}

bool Graph::add_vertex(size_t id) {
    size_t itr;
    for (itr = 0; itr < vertices.size(); ++itr) {
        if (vertices[itr].value == id) {
            return false;
        }
    }
    vertex new_vertex;
    new_vertex.value = id;
    vertices.push_back(new_vertex);
    return true;
}

bool Graph::add_edge(size_t src, size_t dest, double weight) {
    std::list<edge>::iterator it;
    size_t itr_vertex = 0;
    for (itr_vertex = 0; itr_vertex < vertices.size(); itr_vertex++) {
        if (vertices[itr_vertex].value == src) {
            it = vertices[itr_vertex].edges.begin();
            size_t itr_edge;
            for (itr_edge = 0; itr_edge < vertices[itr_vertex].edges.size(); itr_edge++) {
                if (it->dest_vertex == dest) {
                    return false;
                }
                std::advance(it, 1);
            }
            edge new_edge;
            new_edge.dest_vertex = dest;
            new_edge.weight = weight;
            vertices[itr_vertex].edges.push_back(new_edge);
            return true;
        }
    }
    return false;
}

bool Graph::remove_vertex(size_t id) {
    bool ret_val = false;
    std::vector<vertex>::iterator it_vtx;
    std::list<edge>::iterator it_edg;
    it_vtx = vertices.begin();
    size_t itr_vertex;
    for (itr_vertex = 0; itr_vertex < vertices.size(); itr_vertex++) {
        it_edg = vertices[itr_vertex].edges.begin();
        size_t itr_edge;
        for (itr_edge = 0; itr_edge < vertices[itr_vertex].edges.size(); itr_edge++) {
            if (it_edg->dest_vertex == id) {
                vertices[itr_vertex].edges.erase(it_edg);
                break;
            }
            std::advance(it_edg, 1);
        }
        if (vertices[itr_vertex].value == id) {
            vertices.erase(it_vtx);
            ret_val = true;
        }
        std::advance(it_vtx, 1);
    }
    return ret_val;
}

bool Graph::remove_edge(size_t src, size_t dest) {
    std::list<edge>::iterator it;
    size_t itr_vertex = 0;
    for (itr_vertex = 0; itr_vertex < vertices.size(); itr_vertex++) {
        if (vertices[itr_vertex].value == src) {
            it = vertices[itr_vertex].edges.begin();
            size_t itr_edge;
            for (itr_edge = 0; itr_edge < vertices[itr_vertex].edges.size(); itr_edge++) {
                if (it->dest_vertex == dest) {
                    vertices[itr_vertex].edges.erase(it);
                    return true;
                }
                std::advance(it, 1);
            }
        }
    }
    return false;
}

void Graph::dijkstra(size_t source_id){
    std::list<size_t> Q;
    size_t v = 0;
    size_t newdist = 0;
    size_t tempIndex = -1;
    
    //initalize source distance & prev
    if(contains_vertex(source_id)){
        size_t itr;
        for (itr = 0; itr < vertex_count(); itr++) {
            if (vertices[itr].value == source_id) {
               vertices[itr].distance = 0;
                vertices[itr].prev = -1;
            }
        }
    }
    
    for(size_t i = 0; i < vertex_count(); i++){ //set all distances (except source_id) to INFINITY
        if(!(vertices[i].value == source_id)){
            vertices[i].distance = std::numeric_limits<size_t>::max();
        }
        Q.push_back(vertices[i].value); // add to queue
       
    } 
    
    while(!Q.empty()){
         v = min_distance(Q); // get shortest distance
        Q.remove(vertices[v].value); //remove that from queue
    
        for(edge temp: vertices[v].edges){ //for each edge get the distance
            newdist = vertices[v].distance + temp.weight;
            for(size_t i = 0; i < vertices.size(); i++ ){
                if(vertices[i].value == temp.dest_vertex){
                    tempIndex = i;
                    break;
                }
            }
            if(newdist < vertices[tempIndex].distance){ //if new distance is shorter, make disatnce
                vertices[tempIndex].distance = newdist;
                vertices[tempIndex].prev = vertices[v].value;
            }
    
        }

    }

    
}

 void Graph::print_shortest_path(size_t dest_id, std::ostream &os) const{
    
    size_t prev = 0;
    size_t noprev = -1;
    std::list<size_t> previousQ;
    size_t temp = dest_id;

    if(!contains_vertex(dest_id)){ // if vertex does not exist
        os << "<no path>\n";
        return;
    }
    for(size_t i = 0; i < vertices.size(); i++ ){
        if(vertices[i].value == dest_id){

            if(vertices[i].distance == -1){ // if there is no path
                os << "<no path>\n";
                return;
            }
        }
    }

    while(prev != noprev){
        prev = get_previous(temp);
        if(prev == noprev){
            break;
        }
        previousQ.push_front(prev);
        temp = prev;
    }


    while(! previousQ.empty()){
        
        os << previousQ.front() << " --> ";
        previousQ.pop_front();
        
    }
    double tempDistance = distance(dest_id);
    os << dest_id << " distance: " <<  tempDistance << std::endl;
 }

//helper function for print_shortest_path
 size_t Graph::get_previous(size_t dest_id) const{
     size_t index = 0;
     for(size_t i = 0; i < vertices.size(); i++ ){
        if(vertices[i].value == dest_id){

            index = i;
        }
    }
    return vertices[index].prev;
 }

//get shortest distance for inputed id from the source_id in the alg
 double Graph::distance(size_t id) const{
      size_t index = 0;

    if(!contains_vertex(id)){ // if vertex does not exist
        return std::numeric_limits<size_t>::max();
    }
     for(size_t i = 0; i < vertices.size(); i++ ){
        if(vertices[i].value == id){

            index = i;
            if(vertices[i].distance == -1){ // if there is no path
                return std::numeric_limits<size_t>::max();
            }
        }
    }
    return vertices[index].distance;
 }

/*helper function to get the index of 
minimum distance of the values left in the queue
*/
size_t Graph::min_distance( std::list<size_t> q){

    size_t min = std::numeric_limits<size_t>::max();
    size_t minIndex = -1;
    std::list<size_t> temp = q;

    while(!temp.empty()) {
        for(size_t i = 0; i < vertex_count(); i++){
            if(temp.front() == vertices[i].value){
                if(vertices[i].distance  < min){
                    min = vertices[i].distance;
                    minIndex = i;
                }
            }

        }
        temp.pop_front();
    }
    
    return minIndex;
}

#endif  // GRAPH_H
