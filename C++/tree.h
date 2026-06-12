#ifndef TREE_H_
#define TREE_H_

struct Node {
  int id;
  int cost;

  Node* first_child;
  Node* next_brother;

  Node(int node_id, int node_cost);
};

class Tree {
 public:
  Tree();

  Node* CreateNode(int id, int cost);
  void SetRoot(Node* node);
  Node* GetRoot() const;

  void AddChild(Node* parent, Node* child);

  int FindMinCost();
  void PrintPath();

 private:
  Node* root_;

  int FindMinCostRecursive(Node* node);
  void PrintPathRecursive(Node* node);
};

#endif  