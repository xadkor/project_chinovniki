#include "tree.h"

#include <iostream>
#include <limits>

// ===== Node =====
Node::Node(int node_id, int node_cost) {
  id = node_id;
  cost = node_cost;
  first_child = nullptr;
  next_brother = nullptr;
}

// Tree 
Tree::Tree() {
  root_ = nullptr;
}

Node* Tree::CreateNode(int id, int cost) {
  return new Node(id, cost);
}

void Tree::SetRoot(Node* node) {
  root_ = node;
}

Node* Tree::GetRoot() const {
  return root_;
}

void Tree::AddChild(Node* parent, Node* child) {
  if (!parent->first_child) {
    parent->first_child = child;
  } else {
    Node* current = parent->first_child;
    while (current->next_brother) {
      current = current->next_brother;
    }
    current->next_brother = child;
  }
}

// поиск минимальной суммы
int Tree::FindMinCost() {
  if (!root_) {
    return 0;
  }
  return FindMinCostRecursive(root_);
}

int Tree::FindMinCostRecursive(Node* node) {
  if (!node->first_child) {
    return node->cost;
  }

  int min_cost = std::numeric_limits<int>::max();

  Node* child = node->first_child;
  while (child) {
    int current = FindMinCostRecursive(child);
    if (current < min_cost) {
      min_cost = current;
    }
    child = child->next_brother;
  }

  return node->cost + min_cost;
}

// вывод пути 
void Tree::PrintPath() {
  if (!root_) {
    return;
  }
  PrintPathRecursive(root_);
}

void Tree::PrintPathRecursive(Node* node) {
  if (!node) {
    return;
  }

  std::cout << node->id;

  if (!node->first_child) {
    return;
  }

  int min_cost = std::numeric_limits<int>::max();
  Node* best_child = nullptr;

  Node* child = node->first_child;
  while (child) {
    int current = FindMinCostRecursive(child);
    if (current < min_cost) {
      min_cost = current;
      best_child = child;
    }
    child = child->next_brother;
  }

  if (best_child) {
    std::cout << " -> ";
    PrintPathRecursive(best_child);
  }
}