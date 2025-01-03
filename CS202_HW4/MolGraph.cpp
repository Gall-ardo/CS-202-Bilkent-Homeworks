/**
* Title: Graphs
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 4
* Description : MolGraph class implementation
*/


#include "MolGraph.h"

MolGraph::MolGraph(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    file >> numAtoms;
    graph = new int*[numAtoms];
    for (int i = 0; i < numAtoms; i++) {
        graph[i] = new int[numAtoms];
        for (int j = 0; j < numAtoms; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < numAtoms; i++) {
        int atomId, degree;
        file >> atomId >> degree;
        for (int j = 0; j < degree; j++) {
            int neighborId;
            file >> neighborId;
            graph[atomId][neighborId] = 1;
        }
    }
    file.close();
}

MolGraph::~MolGraph() {
    for(int i = 0; i < numAtoms; i++) {
        delete[] graph[i];
    }
    delete[] graph;
}

void MolGraph::minBondPath(int source, int destination) {
    bool* visited = new bool[numAtoms];
    int* whereFrom = new int[numAtoms];
    int* distance = new int[numAtoms];
    for (int i = 0; i < numAtoms; i++) {
        visited[i] = false;
        whereFrom[i] = -1;
        distance[i] = 10000009;
    }
    visited[source] = true;
    distance[source] = 0;
    Queue<int> q;
    q.push(source);
    while (!q.isEmpty()) {
        int curr = q.getFront();
        q.pop();
        for (int i = 0; i < numAtoms; i++) {
            if (graph[curr][i] == 1 && !visited[i]) {
                visited[i] = true;
                whereFrom[i] = curr;
                distance[i] = distance[curr] + 1;
                q.push(i);

                if(i == destination) {
                    cout << "Minimum number of bonds to traverse from atom " << source  << " to atom " << destination << ": " << distance[i] << endl;
                    cout << "Path: ";
                    // put to a linkedlist to use as a stack
                    LinkedList<int> path;
                    int curr = i;
                    while (curr != -1) {
                        path.push_front(curr);
                        curr = whereFrom[curr];
                    }
                    LinkedListNode<int> *currNode = path.head;
                    while (currNode != nullptr) {
                        cout << currNode->data;
                        if(currNode->next != nullptr) {
                            cout << " -> ";
                        }
                        currNode = currNode->next;
                    }
                    cout << endl;
                    delete[] visited;
                    delete[] whereFrom;
                    delete[] distance;
                    return;
                }
            }
        }
    }
    delete[] visited;
    delete[] distance;
    delete[] whereFrom;
}

void mergeSortHelper(int** edges, int l, int r, int** temp) {
    if(l >= r) return;

    int m = l + (r - l) / 2;
    mergeSortHelper(edges, l, m, temp);
    mergeSortHelper(edges, m + 1, r, temp);

    int i = l, j = m + 1, k = l;
    while(i <= m && j <= r) {
        if(edges[i][0] < edges[j][0] || (edges[i][0] == edges[j][0] && edges[i][1] <= edges[j][1])) {
            temp[k][0] = edges[i][0];
            temp[k][1] = edges[i][1];
            i++;
        } else {
            temp[k][0] = edges[j][0];
            temp[k][1] = edges[j][1];
            j++;
        }
        k++;
    }
    while(i <= m) {
        temp[k][0] = edges[i][0];
        temp[k][1] = edges[i][1];
        i++; k++;
    }
    while(j <= r) {
        temp[k][0] = edges[j][0];
        temp[k][1] = edges[j][1];
        j++; k++;
    }
    for(i = l; i <= r; i++) {
        edges[i][0] = temp[i][0];
        edges[i][1] = temp[i][1];
    }
}

void mergeSort(int** edges, int n) {
    int** temp = new int*[n];
    for(int i = 0; i < n; i++) {
        temp[i] = new int[2];
    }
    mergeSortHelper(edges, 0, n-1, temp);
    for(int i = 0; i < n; i++) {
        delete[] temp[i];
    }
    delete[] temp;
}

void MolGraph::getMST() {
    int* parent = new int[numAtoms];
    bool *inMST = new bool[numAtoms];
    int remaining = numAtoms;
    for (int i = 0; i < numAtoms; i++) {
        parent[i] = -1;
        inMST[i] = false;
    }
    parent[0] = 0;
    inMST[0] = true;
    remaining--;
    Queue<int> q;
    q.push(0);
    while (remaining > 0) {
        int curr = q.getFront();
        q.pop();
        for (int i = 0; i < numAtoms; i++) {
            if (graph[curr][i] == 1 && !inMST[i]) {
                inMST[i] = true;
                parent[i] = curr;
                q.push(i);
                remaining--;
            }
        }
    }

    // Store edges in array
    int** edges = new int*[numAtoms - 1];
    for(int i = 0; i < numAtoms - 1; i++) {
        edges[i] = new int[2];
        edges[i][0] = min(parent[i + 1], i + 1);
        edges[i][1] = max(parent[i + 1], i + 1);
    }

    mergeSort(edges, numAtoms - 1);

    cout << "Minimum Spanning Tree:" << endl;
    cout << "Cost: " << numAtoms - 1 << endl;
    cout << "Edges:" << endl;
    for(int i = 0; i < numAtoms - 1; i++) {
        cout << edges[i][0] << " - " << edges[i][1] << endl;
    }

    // Cleanup
    for(int i = 0; i < numAtoms - 1; i++) {
        delete[] edges[i];
    }
    delete[] edges;
    delete[] parent;
    delete[] inMST;
}

void MolGraph::getDiameter() {
    int** distance = new int*[numAtoms];
    for (int i = 0; i < numAtoms; i++) {
        distance[i] = new int[numAtoms];
        for (int j = 0; j < numAtoms; j++) {
            if (i == j) {
                distance[i][j] = 0;
            } else if (graph[i][j] == 1) {
                distance[i][j] = 1;
            } else {
                distance[i][j] = 100009; // a value which is grate than the maximum distance. but smaller to avoid overflow
            }
        }
    }

    for (int k = 0; k < numAtoms; k++) {
        for (int i = 0; i < numAtoms; i++) {
            for (int j = 0; j < numAtoms; j++) {
                if (distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
    int diameter = 0;
    for (int i = 0; i < numAtoms; i++) {
        for (int j = 0; j < numAtoms; j++) {
            if (distance[i][j] > diameter) {
                diameter = distance[i][j];
            }
        }
    }

    cout << "Diameter of the molecule: " << diameter << endl;
    for (int i = 0; i < numAtoms; i++) {
        delete[] distance[i];
    }
    delete[] distance;
}

