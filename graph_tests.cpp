#include <iostream>
#include <sstream>
#include "graph.h"

//using std::cout, std::endl;

int main() {
    std::cout << "make an empty digraph" << std::endl;
    Graph G;

    std::cout << "add vertices" << std::endl;
    for (size_t n = 1; n <= 7; n++) {
        G.add_vertex(n);
    }

    std::cout << "add directed edges" << std::endl;
    G.add_edge(1, 2, 5);  // 1 ->{5} 2; (edge from 1 to 2 with weight 5)
    G.add_edge(1, 3, 3);
    G.add_edge(2, 3, 2);
    G.add_edge(2, 5, 3);
    G.add_edge(2, 7, 1);
    G.add_edge(3, 4, 7);
    G.add_edge(3, 5, 7);
    G.add_edge(4, 1, 2);
    G.add_edge(4, 6, 6);
    G.add_edge(5, 4, 2);
    G.add_edge(5, 6, 1);

    std::cout << "Result of adding edge to none existing vertex is " << G.add_edge(7, 5, 1) << std::endl;
    std::cout << "Result of adding already existing edge to the graph is " << G.add_edge(7, 5, 1) << std::endl;
    std::cout << "Result of adding edge to none existing vertex is " << G.add_edge(9, 8, 5) << std::endl;

    std::cout << "G has " << G.vertex_count() << " vertices" << std::endl;
    std::cout << "G has " << G.edge_count() << " edges" << std::endl;
    std::cout << std::endl;

    std::cout << "Testing for = operator" << std::endl;
    Graph new_G;
    new_G = G;
    std::cout << "new_G has " << new_G.vertex_count() << " vertices" << std::endl;
    std::cout << "new_G has " << new_G.edge_count() << " edges" << std::endl;
    std::cout << std::endl;

    std::cout << "Testing for creating new graph with new Graph(G)" << std::endl;
    Graph *new_ptr_G = new Graph(G);
    std::cout << "new_ptr_G has " << new_ptr_G->vertex_count() << " vertices" << std::endl;
    std::cout << "new_ptr_G has " << new_ptr_G->edge_count() << " edges" << std::endl;
    std::cout << std::endl;

    std::cout << "Testing for contains edges" << std::endl;
    std::cout << "Result of containing edge " << new_G.contains_edge(4, 1) << std::endl;
    std::cout << "Result of non containing edge " << new_G.contains_edge(1, 5) << std::endl;
    std::cout << std::endl;

    std::cout << "Testing for cost edges" << std::endl;
    std::cout << "Result of containing edge " << new_G.cost(4, 1) << std::endl;
    std::cout << "Result of non containing edge " << new_G.contains_edge(1, 5) << std::endl;
    std::cout << std::endl;

    std::cout << "Remove vertex test" << std::endl;
    std::cout << "Result of containing vertex " << new_G.remove_vertex(4) << std::endl;
    std::cout << "Result of non containing vertex " << new_G.remove_vertex(10) << std::endl;

    std::cout << "new_G has " << new_G.vertex_count() << " vertices" << std::endl;
    std::cout << "new_G has " << new_G.edge_count() << " edges" << std::endl;
    std::cout << std::endl;

    std::cout << "Remove edge test" << std::endl;
    std::cout << "Result of containing edge " << new_G.remove_edge(5, 4) << std::endl;
    std::cout << "Result of non containing edge " << new_G.remove_edge(5, 3) << std::endl;

    std::cout << "new_G has " << new_G.vertex_count() << " vertices" << std::endl;
    std::cout << "new_G has " << new_G.edge_count() << " edges" << std::endl;

    delete new_ptr_G;

//    std::cout << "compute mst path from 2" << std::endl;
//    G.prim(2);
//
//    std::cout << "print minimum spanning paths" << std::endl;
//    for (size_t n = 1; n <= 7; n++) {
//        std::cout << "minimum spanning path from 2 to " << n << std::endl;
//        std::cout << "  ";
//        G.print_path(n);
//    }
//    std::cout << std::endl;
//
//    std::cout << "compute shortest path from 2" << std::endl;
    G.dijkstra(2);
//
    std::cout << "print shortest paths" << std::endl;
    for (size_t n = 0; n <= 7; n++) {
        std::cout << "shortest path from 2 to " << n << std::endl;
        std::cout << "  ";
        G.print_shortest_path(n);
    }
    G.dijkstra(1);
    for (size_t n = 0; n <= 7; n++) {
        std::cout << "shortest path from 1 to " << n << std::endl;
        std::cout << "  ";
        G.print_shortest_path(n);
    }

    return 0;
}


