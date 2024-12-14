#include <iostream>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// Класс Graph
class Graph {
private:
    int numVertices;
    list<int>* adjLists;

public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int src, int dest);
    list<int> getNeighbors(int v);
};

Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new list<int>[vertices];
}

Graph::~Graph() {
    delete[] adjLists;
}

void Graph::addEdge(int src, int dest) {
    adjLists[src].push_back(dest);
}

list<int> Graph::getNeighbors(int v) {
    return adjLists[v];
}

// Абстрактный класс GraphTraversal
class GraphTraversal {
protected:
    Graph& graph;
public:
    GraphTraversal(Graph& g) : graph(g) {}
    virtual void traverse(int startVertex) = 0;
    virtual void startTraversal() {
        cout << "Начало обхода\n";
    }
    virtual void endTraversal() {
        cout << "Конец обхода\n";
    }
    virtual void visitVertex(int v) {
        cout << "Посещение узла " << v << "\n";
    }
    virtual void visitEdge(int v, int w) {
        cout << "Посещение ребра (" << v << ", " << w << ")\n";
    }
};

// Класс DFS, реализующий алгоритм поиска в глубину
class DFS : public GraphTraversal {
public:
    DFS(Graph& g) : GraphTraversal(g) {}
    void traverse(int startVertex) override;
};

void DFS::traverse(int startVertex) {
    startTraversal();
    bool* visited = new bool[graph.getNeighbors(startVertex).size()]();
    stack<int> stack;
    stack.push(startVertex);
    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();
        if (!visited[v]) {
            visitVertex(v);
            visited[v] = true;
            for (int neighbor : graph.getNeighbors(v)) {
                if (!visited[neighbor]) {
                    visitEdge(v, neighbor);
                    stack.push(neighbor);
                }
            }
        }
    }
    endTraversal();
    delete[] visited;
}

// Класс BFS, реализующий алгоритм поиска в ширину
class BFS : public GraphTraversal {
public:
    BFS(Graph& g) : GraphTraversal(g) {}
    void traverse(int startVertex) override;
};

void BFS::traverse(int startVertex) {
    startTraversal();
    bool* visited = new bool[graph.getNeighbors(startVertex).size()]();
    queue<int> queue;
    queue.push(startVertex);
    visited[startVertex] = true;
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        visitVertex(v);
        for (int neighbor : graph.getNeighbors(v)) {
            if (!visited[neighbor]) {
                visitEdge(v, neighbor);
                queue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
    endTraversal();
    delete[] visited;
}

// Основная функция
int main() {
    setlocale(LC_ALL, "RUS");

    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    DFS dfs(g);
    cout << "DFS traversal:\n";
    dfs.traverse(2);

    BFS bfs(g);
    cout << "BFS traversal:\n";
    bfs.traverse(2);

    return 0;
}