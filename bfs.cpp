#include <iostream>
#include <limits.h>
using namespace std;
enum Color
{
    WHITE,
    GRAY,
    BLACK
};

struct node
{
    int data;
    node *link;
};

struct vtable
{
    char name[10];
    int d;
    enum Color color;
    int pi;
    node *Adj;
};
class Graph

{
    vtable vertex[10];
    int n;

public:
    void constructgraph(int);
    void initialize();
    void BFS(int s);
    void display();
    void printpath(int, int);
};

void Graph::constructgraph(int n)

{
    int m, adj;
    struct node *t;
    this->n = n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the name of the vertex ";
        cin >> vertex[i].name;
        vertex[i].Adj = NULL;
        cout << "Enter no. of adjacent vertices for " << vertex[i].name << " : ";
        cin >> m;
        for (int j = 0; j < m; j++)
        {
            cout << "Enter the index of the adjacent vertex: ";
            cin >> adj;
            t = new node;
            t->data = adj;
            t->link = NULL;
            if (vertex[i].Adj == NULL)
                vertex[i].Adj = t;
            else
            {
                t->link = vertex[i].Adj;
                vertex[i].Adj = t;
            }
        }
    }
}

void Graph::initialize()
{
    for (int i = 0; i < n; i++)
    {
        vertex[i].d = INT_MAX;
        vertex[i].color = WHITE;
        vertex[i].pi = -1;
    }
}

void Graph::display()
{
    cout << "No.\tName\td\t\tp\tAdjacent Node List " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << "\t" << vertex[i].name << "\t" << vertex[i].d << "\t\t" << vertex[i].pi << "\t";
        node *t = vertex[i].Adj;
        while (t != NULL)
        {
            cout << "-->" << t->data;
            t = t->link;
        }
        cout << endl;
    }
}
struct headnode
{
    node *front, *rear;
};

class Queue
{
    headnode *head;

public:
    Queue();
    bool empty();
    void enqueue(int x);
    int dequeue();
    ~Queue();
};

Queue::Queue()
{
    head = new headnode;
    head->front = NULL;
    head->rear = NULL;
}

Queue::~Queue()
{
    while (head->front != NULL)
    {
        node *t = head->front;
        head->front = t->link;
        delete t;
    }
    delete head;
}

bool Queue::empty()
{
    if (head->front == NULL)
        return true;
    else
        return false;
}

void Queue::enqueue(int x)
{
    node *nnode = new node;
    nnode->data = x;
    nnode->link = NULL;
    if (head->rear != NULL)
        head->rear->link = nnode;
    head->rear = nnode;
    if (head->front == NULL)
        head->front = nnode;
    return;
}

int Queue::dequeue()
{
    int x;
    if (head->front == NULL)
    {
        cout << "Queue Empty" << endl;
        return -1;
    }
    x = head->front->data;
    if (head->front == head->rear)
        head->front = head->rear = NULL;
    else
        head->front = head->front->link;
    return x;
}

void Graph::BFS(int s)

{
    Queue Q;
    node *t;
    int u, v;
    vertex[s].d = 0;
    vertex[s].color = GRAY;
    Q.enqueue(s);
    cout << "Edges used in the traversal are : " << endl;
    while (!Q.empty())
    {
        u = Q.dequeue();
        t = vertex[u].Adj;
        while (t != NULL)
        {
            v = t->data;
            if (vertex[v].color == WHITE)
            {
                vertex[v].d = vertex[u].d + 1;
                vertex[v].pi = u;
                vertex[v].color = GRAY;
                cout << vertex[u].name << "->" << vertex[v].name << endl;
                Q.enqueue(v);
            }
            t = t->link;
        }
        vertex[u].color = BLACK;
    }
}

void Graph::printpath(int i, int src)
{
    if (i == src)
        cout << vertex[i].name << "->";
    else if (vertex[i].pi == -1)
        cout << "no path from " << vertex[i].name << " to" << vertex[src].name << " exists";
    else
    {
        printpath(vertex[i].pi, src);
        cout << vertex[i].name << "->";
    }
}

int main()
{
    Graph g;
    int s, op, n;
    cout << "Enter no. of vertices : ";
    cin >> n;
    g.constructgraph(n);
    cout << "Enter the index of starting vertex ";
    cin >> s;
    g.initialize();
    g.BFS(s);
    g.display();
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        g.printpath(i, s);
        cout << endl;
    }
    return 0;
}