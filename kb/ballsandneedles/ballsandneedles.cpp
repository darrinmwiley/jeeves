/*
 * BEGIN ANNOTATION
 * PROBLEM URL: open.kattis.com/problems/ballsandneedles
 * TAGS: bfs
 * EXPLANATION:
 * bfs the 3d sculpture, then bfs the 2d shadow
 * END ANNOTATION
 */

#include <cstdio>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

class GraphNode {
public:

    GraphNode()=delete;

    GraphNode(string val) {
        this->val = val;
        this->predecessor = nullptr;
        this->wasVisited = false;
        this->adjacencySet = unordered_set<GraphNode*>();
    }

    ~GraphNode() {
        this->val = "";
        this->predecessor = nullptr;
        this->adjacencySet.clear();
    }

    void addNeighbor(GraphNode* other) {
        this->adjacencySet.insert(other);
    }

    void visit(GraphNode* other) {
        this->wasVisited = true;
        this->predecessor = other;
        if(other == nullptr) {
            return;
        }
        this->adjacencySet.erase(other);
    }

    string val;
    GraphNode* predecessor;
    bool wasVisited;
    unordered_set<GraphNode*> adjacencySet;
};

bool do_work(unordered_map<string, GraphNode*>& graph_orig) {
    unordered_map<string, GraphNode*> graph(graph_orig);
    while(!graph.empty()) {
        list<GraphNode*> queueOfNodes = list<GraphNode*>();
        GraphNode* startNode = graph.begin()->second;
        graph.erase(startNode->val);
        queueOfNodes.push_back(startNode);
        startNode->visit(nullptr);
        while (!queueOfNodes.empty()) {
            GraphNode* currNode = queueOfNodes.front();
            queueOfNodes.pop_front();
            for(GraphNode* neighbor : currNode->adjacencySet) {
                if(neighbor->wasVisited) {
                    return true;
                } else {
                    neighbor->visit(currNode);
                    graph.erase(currNode->val);
                    queueOfNodes.push_back(neighbor);
                }
            }
        }
    }
    return false;
}

int main() {

    int numNeedles;
    scanf("%d", &numNeedles);

    unordered_map<string, GraphNode*> ballMap = unordered_map<string, GraphNode*>();
    unordered_map<string, GraphNode*> ballShadowMap = unordered_map<string, GraphNode*>();

    for(int i = 0; i < numNeedles; i++) {
        int x1, y1, z1, x2, y2, z2;
        scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);

        string ball1 = "(" + to_string(x1) + ", " + to_string(y1) + ", " + to_string(z1) + ")";
        string ball2 = "(" + to_string(x2) + ", " + to_string(y2) + ", " + to_string(z2) + ")";
        string ballShadow1 = "(" + to_string(x1) + ", " + to_string(y1) + ")";
        string ballShadow2 = "(" + to_string(x2) + ", " + to_string(y2) + ")";

        if(ballMap.find(ball1) == ballMap.end()) {
            ballMap.insert({ball1, new GraphNode(ball1)});
        }

        if(ballMap.find(ball2) == ballMap.end()) {
            ballMap.insert({ball2, new GraphNode(ball2)});
        }

        if(ballShadowMap.find(ballShadow1) == ballShadowMap.end()) {
            ballShadowMap.insert({ballShadow1, new GraphNode(ballShadow1)});
        }

        if(ballShadowMap.find(ballShadow2) == ballShadowMap.end()) {
            ballShadowMap.insert({ballShadow2, new GraphNode(ballShadow2)});
        }

        GraphNode* b1 = ballMap.at(ball1);
        GraphNode* b2 = ballMap.at(ball2);
        GraphNode* bs1 = ballShadowMap.at(ballShadow1);
        GraphNode* bs2 = ballShadowMap.at(ballShadow2);

        b1->addNeighbor(b2);
        b2->addNeighbor(b1);
        if (bs1 == bs2) {
            continue;
        }
        bs1->addNeighbor(bs2);
        bs2->addNeighbor(bs1);
    }

    //now bfs - twice
    if(do_work(ballMap)) {
        printf("True closed chains\n");
    } else {
        printf("No true closed chains\n");
    }

    if(do_work(ballShadowMap)) {
        printf("Floor closed chains\n");
    } else {
        printf("No floor closed chains\n");
    }

    //memory safety
    while(!ballMap.empty()) {
        string k = ballMap.begin()->first;
        GraphNode* v = ballMap.at(k);
        ballMap.erase(k);
        delete v;
    }

    while(!ballShadowMap.empty()) {
        string k = ballShadowMap.begin()->first;
        GraphNode* v = ballShadowMap.at(k);
        ballShadowMap.erase(k);
        delete v;
    }

    return 0;
}
