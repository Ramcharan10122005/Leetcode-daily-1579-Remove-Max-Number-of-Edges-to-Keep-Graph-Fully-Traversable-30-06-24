int find(int* parent, int a) {
    if (parent[a] != a)
        parent[a] = find(parent, parent[a]);
    return parent[a];
}

int unionSet(int* connected, int a, int b) {
    a = find(connected, a);
    b = find(connected, b);

    if (a == b)
        return 1;
    if (a > b)
        connected[a] = connected[b];
    else
        connected[b] = connected[a];
    return 0;
}

int maxNumEdgesToRemove(int n, int** edges, int edgesSize, int* edgesColSize) {
    int counter = 0;
    int tmp = 0;
    int* connecteda = malloc((n) * sizeof(int));
    int* connectedb = malloc((n) * sizeof(int));

    for (int i = 0; i < n; i++) {
        connecteda[i] = connectedb[i] = i;
    }
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][0] == 3) {
            if (unionSet(connecteda, edges[i][1] - 1, edges[i][2] - 1))
                counter++;
            else
                unionSet(connectedb, edges[i][1] - 1, edges[i][2] - 1);
        }
    }
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][0] == 1)
            counter += unionSet(connecteda, edges[i][1] - 1, edges[i][2] - 1);
        else if (edges[i][0] == 2)
            counter += unionSet(connectedb, edges[i][1] - 1, edges[i][2] - 1);
    }
    for (int i = 1; i < n; i++) {
        if (find(connecteda, i) != find(connecteda, 0) ||
            find(connectedb, i) != find(connectedb, 0))
            return -1;
    }

    return counter;
}
