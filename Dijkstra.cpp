#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int INF = numeric_limits<int>::max();

void dijkstraMatrix(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF); //odl do wierzcholka start
    vector<int> prev(n, -1); //poprzednicy na najkr sciezce
    vector<bool> visited(n, false); 

    dist[start] = 0;

    for (int i = 0; i < n; ++i) {
        int u = -1; //wierzcholek o najm. odlg. 
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) // sprawdzenie, czy wierzchołek nie został odwiedzony, najl. odlg  
                u = j;
        }

        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != 0 && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) { //sprawdzenie istnienia krawędzi, suma odlg jest mniejsza niz obecna
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    cout << "Koszty dojscia (macierz sasiedztwa):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Wierzcholek " << i << ": ";
        if (dist[i] == INF)
            cout << "Brak połaczenia";
        else
            cout << dist[i] << " (poprzednik: " << prev[i] << ")";
        cout << "\n";
    }
}

void dijkstraList(const vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //przechowuje odlg, wierzch. +
    pq.push(make_pair(dist[start], start));

    while (!pq.empty()) {
        int u = pq.top().second; // wierzch najmniejsza odlg z kolejki
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;

        for (const auto& neighbor : graph[u]) { //sasiedzi wierzcholka
            int v = neighbor.first; //indeks wierz
            int weight = neighbor.second; 

            if (dist[u] != INF && dist[u] + weight < dist[v]) { //suma odlg niz akt
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "\nKoszty dojscia (lista sasiedztwa):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Wierzcholek " << i << ": ";
        if (dist[i] == INF)
            cout << "Brak połaczenia";
        else
            cout << dist[i] << " (poprzednik: " << prev[i] << ")";
        cout << "\n";
    }
}

int main() {
    int n = 6;

    vector<vector<int>> graphMatrix = {
        {0, 2, 4, 0, 0, 0},
        {2, 0, 1, 4, 2, 0},
        {4, 1, 0, 0, 3, 0},
        {0, 4, 0, 0, 3, 1},
        {0, 2, 3, 3, 0, 2},
        {0, 0, 0, 1, 2, 0}
    };

    vector<vector<pair<int, int>>> graphList = {
        {{1, 2}, {2, 4}},
        {{0, 2}, {2, 1}, {3, 4}, {4, 2}},
        {{0, 4}, {1, 1}, {4, 3}},
        {{1, 4}, {4, 3}, {5, 1}},
        {{1, 2}, {2, 3}, {3, 3}, {4, 2}},
        {{3, 1}, {4, 2}}
    };

    int startVertex = 0;  // wierzchołek startowy

    auto startTime = high_resolution_clock::now();

    dijkstraMatrix(graphMatrix, startVertex);

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);

    cout << "Czas wykonania (Macierz sasiedztwa): " << duration.count() << " mikrosekund\n";

    startTime = high_resolution_clock::now();

    dijkstraList(graphList, startVertex);

    endTime = high_resolution_clock::now();
    duration = duration_cast<microseconds>(endTime - startTime);

    cout << "Czas wykonania (Lista sasiedztwa): " << duration.count() << " mikrosekund\n";

    return 0;
}