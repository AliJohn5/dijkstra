#include <iostream>
#include <vector>
#include <queue>

using std::priority_queue;
using std::vector;

class Dijkstra
{
private:
    int _numberOfNodes;
    vector<vector<std::pair<int, int>>> _adj;
    vector<long long> _distance;
    priority_queue<std::pair<long long, int>> _q;
    vector<bool> _processed;
    vector<int> _parent;
    int root;

public:
    Dijkstra(int numberOfNodes);
    ~Dijkstra();
    void connect(int a, int b, int w);
    void run(int x);
    vector<int> path(int x);
};

Dijkstra::Dijkstra(int numberOfNodes)
{
    _numberOfNodes = numberOfNodes;
    _adj.resize(_numberOfNodes + 1);
    root = -1;
}

Dijkstra::~Dijkstra()
{
}

void Dijkstra::connect(int a, int b, int w)
{
    if (a == 0 || b == 0)
    {
        throw std::invalid_argument("don't use 0 as a Node");
    }
    _adj[a].push_back({b, w});
    _adj[b].push_back({a, w});
}

void Dijkstra::run(int x)
{
    _distance = vector<long long>(_numberOfNodes + 1, INT_MAX);
    _q = priority_queue<std::pair<long long, int>>();
    _processed = vector<bool>(_numberOfNodes + 1, 0);
    _parent = vector<int>(_numberOfNodes + 1, -1);
    root = x;

    _distance[x] = 0;
    _parent[x] = x;
    _q.push({0, x});

    while (!_q.empty())
    {
        int a = _q.top().second;
        _q.pop();

        if (_processed[a])
            continue;
        _processed[a] = 1;

        for (const auto u : _adj[a])
        {
            int b = u.first, w = u.second;

            if (_distance[a] + w < _distance[b])
            {
                _distance[b] = _distance[a] + w;
                _q.push({-_distance[b], b});
                _parent[b] = a;
            }
        }
    }
}

vector<int> Dijkstra::path(int x)
{

    std::vector<int> myPath;
    myPath.push_back(x);
    if (_parent[x] == -1)
    {
        throw std::invalid_argument("please run object.run() function before.");
    }

    while (_parent[x] != x)
    {
        myPath.push_back(_parent[x]);
        x = _parent[x];
    }

    vector<int> ans(myPath.size());
    int i = myPath.size() - 1;

    for (auto &e : ans)
    {
        e = myPath[i];
        --i;
    }

    return ans;
}

int main()
{
    int numberOfNodes = 5;
    Dijkstra dijkstra(numberOfNodes);

    // connect nodes
    // first arg is first node
    // second arg is second node
    // third arg is weight

    // Note : a -> b is same as b -> a
    dijkstra.connect(0, 3, 2);
    dijkstra.connect(2, 1, 5);
    dijkstra.connect(4, 3, 6);
    dijkstra.connect(1, 4, 9);
    dijkstra.connect(4, 5, 2);
    dijkstra.connect(1, 5, 1);

    // run the algorith using run function
    // root is the starting point
    // Note: every time you change the root run this function
    int root = 2;
    dijkstra.run(root);

    // then you can get the shortest path from root to any Node:
    // 2 -> 5
    int target = 5;
    vector<int> path = dijkstra.path(target);

    std::cout << "Your Path From " << root << " to " << target << " is:\n";

    for (int i = 0; i < path.size(); ++i)
    {
        std::cout << path[i];
        if (i != path.size() - 1)
            std::cout << " -> ";
        else
            std::cout << '\n';
    }

    return 0;
}