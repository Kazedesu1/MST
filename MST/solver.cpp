#include "solver.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <queue>
using namespace std;

Prim::Prim(const INSTANCE& instance) : instance(instance) {};

Kruskal::Kruskal(const INSTANCE& instance) : instance(instance) {};

void Prim::solve()
{
    auto start = chrono::high_resolution_clock::now();
    int n = instance.numnodes;
    // Khởi tạo vector kiểm tra xem đỉnh đã được thêm vào MST hay chưa
    vector<bool> inMST(n, false);

    // Xây dựng danh sách kề từ danh sách cạnh (chú ý chuyển đổi chỉ số: dữ liệu đầu vào có thể bắt đầu từ 1)
    vector<vector<pair<int, double>>> adj(n);
    for (const Edge& edge : instance.edges)
    {
        int u = edge.node1 - 1;
        int v = edge.node2 - 1;
        double w = edge.weight;
        // Giả sử đồ thị vô hướng
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }

    // Hàng đợi ưu tiên chứa các cạnh với cấu trúc: (trọng số, (u, v))
    typedef pair<double, pair<int, int>> EdgeInfo;
    priority_queue<EdgeInfo, vector<EdgeInfo>, greater<EdgeInfo>> pq;

    // Bắt đầu từ đỉnh 0
    inMST[0] = true;
    for (const auto& edge : adj[0])
    {
        pq.push({ edge.second, {0, edge.first} });
    }

    // Thuật toán Prim
    while (!pq.empty() && mstree.size() < n - 1)
    {
        auto top = pq.top();
        pq.pop();
        double weight = top.first;
        int u = top.second.first;
        int v = top.second.second;
        if (inMST[v])
            continue; // nếu đỉnh đã có trong MST thì bỏ qua

        // Thêm cạnh vào MST (chuyển chỉ số về 1-index)
        mstree.push_back({ u + 1, v + 1, weight });
        inMST[v] = true;

        // Thêm các cạnh nối từ đỉnh v vào hàng đợi
        for (const auto& edge : adj[v])
        {
            if (!inMST[edge.first])
            {
                pq.push({ edge.second, {v, edge.first} });
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    runtime = duration.count();
    total = 0.0;
    for (const Edge& e : mstree)
    {
        total += e.weight;
    }
}


void Prim::displaySolution() const
{
    cout << "Prim's algorithm" << endl;
    int totalWeight = 0;
    for (const Edge& e : mstree)
    {
        cout << e.node1 << " " << e.node2 << " " << e.weight << endl;
        totalWeight += e.weight;
    }
    cout << "Total weight: " << totalWeight << endl;
    
    cout << "Prim's algorithm runtime: " << runtime << "s" << endl;

}

void Kruskal::solve()
{

    vector<Edge> Sortededge;
    for (const Edge& edge : instance.edges)
    {
        // Kiểm tra và xử lý dữ liệu node đầu vào
        if (edge.node1 < 1 || edge.node1 > instance.numnodes ||
            edge.node2 < 1 || edge.node2 > instance.numnodes)
        {
            cerr << "Error: Node index out of range (" << edge.node1 << ", " << edge.node2 << ")\n";
            continue;
        }
        Sortededge.push_back({ edge.node1 - 1, edge.node2 - 1, edge.weight });
    }
    auto start = chrono::high_resolution_clock::now();

    // sắp xếp cạnh theo trọng số tăng dần
    sort(Sortededge.begin(), Sortededge.end(), [](const Edge& a, const Edge& b)
        { return a.weight < b.weight; });

    vector<int> parent(instance.numnodes);
    vector<int> rank(instance.numnodes, 0);
    for (int i = 0; i < instance.numnodes; i++)
        parent[i] = i;

    int edgesAdded = 0;
    for (const Edge& edge : Sortededge)
    {
        int u = find(parent, edge.node1);
        int v = find(parent, edge.node2);

        if (u != v)
        { // Nếu u và v không cùng tập cha thì thêm cạnh
            mstree.push_back({ edge.node1 + 1, edge.node2 + 1, edge.weight });
            total += edge.weight;
            unionSet(parent, rank, u, v);
            edgesAdded++;
            if (edgesAdded == instance.numnodes - 1)
                break; // kết thúc khi đủ n-1 cạnh
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    runtime = duration.count();
}

void Kruskal::displaySolution() const
{
    cout << "Kruskal's algorithm" << endl;
    for (const Edge& e : mstree)
    {
        cout << e.node1 << " " << e.node2 << " " << e.weight << endl;
    }
    cout << "Total weight: " << total << endl;
    cout << "Kruskal's algorithm runtime: " << runtime << "s" << endl;
}

// Hàm tìm tập cha của i
int Kruskal::find(vector<int>& parent, int i) const
{
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

// Hàm gộp 2 tập hợp chứa x và y
void Kruskal::unionSet(vector<int>& parent, vector<int>& rank, int x, int y) const
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX != rootY)
    {
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}
