#include <iostream>
#include <limits>
#include <string>
#include <windows.h>

#include "tree.h"

// ввод 
int ReadInt() {
  int value;
  while (!(std::cin >> value)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ошибка! Повторите: ";
  }
  return value;
}

//  вывод дерева
void PrintTree(const Node* node,
                     const std::string& prefix = "",
                     bool is_last = true) {
  if (!node) {
    return;
  }

  std::cout << prefix;

  if (!prefix.empty()) {
    std::cout << (is_last ? "└── " : "├── ");
  }

  if (prefix.empty()) {
    std::cout << "[ГЛАВНЫЙ] ";
  }

  std::cout << "[" << node->id << ":" << node->cost << "]\n";

  int count = 0;
  const Node* child = node->first_child;
  while (child) {
    count++;
    child = child->next_brother;
  }

  child = node->first_child;
  int index = 0;

  while (child) {
    index++;

    PrintTree(child,
                    prefix + (is_last ? "    " : "│   "),
                    index == count);

    child = child->next_brother;
  }
}

// готовый пример 
void CreateExample(Tree& tree, Node**& nodes) {
  const int n = 5;
  nodes = new Node*[n + 1];

  nodes[1] = tree.CreateNode(1, 10);
  nodes[2] = tree.CreateNode(2, 5);
  nodes[3] = tree.CreateNode(3, 3);
  nodes[4] = tree.CreateNode(4, 8);
  nodes[5] = tree.CreateNode(5, 2);

  tree.SetRoot(nodes[1]);

  tree.AddChild(nodes[1], nodes[2]);
  tree.AddChild(nodes[1], nodes[3]);
  tree.AddChild(nodes[2], nodes[4]);
  tree.AddChild(nodes[2], nodes[5]);

  std::cout << "\nПример министерства загружен!\n";
}

// создание своего дерева 
void CreateCustom(Tree& tree, Node**& nodes) {
  std::cout << "Введите количество чиновников: ";
  int n = ReadInt();

  if (n <= 0) {
    std::cout << "Ошибка: число должно быть > 0\n";
    return;
  }

  nodes = new Node*[n + 1];

  std::cout << "\nФормат: [начальник] [взятка]\n";
  std::cout << "Главный чиновник: начальник = -1\n\n";

  for (int i = 1; i <= n; i++) {
    std::cout << "Чиновник " << i << ": ";

    int parent = ReadInt();
    int cost = ReadInt();

    nodes[i] = tree.CreateNode(i, cost);

    if (parent == -1) {
      tree.SetRoot(nodes[i]);
    } else {
      if (parent < 1 || parent > n) {
        std::cout << "Ошибка: неверный начальник!\n";
        i--;
        continue;
      }
      tree.AddChild(nodes[parent], nodes[i]);
    }
  }

  std::cout << "\nМинистерство успешно создано!\n";
}

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  Tree tree;
  Node** nodes = nullptr;

  while (true) {
    std::cout << "\n===== СИСТЕМА ЧИНОВНИКОВ =====\n";
    std::cout << "1. Загрузить пример\n";
    std::cout << "2. Создать своё министерство\n";
    std::cout << "3. Показать структуру\n";
    std::cout << "4. Минимальная взятка\n";
    std::cout << "5. Путь документа\n";
    std::cout << "0. Выход\n";
    std::cout << "Выбор: ";

    int choice = ReadInt();

    if (choice == 1) {
      CreateExample(tree, nodes);
    } else if (choice == 2) {
      CreateCustom(tree, nodes);
    } else if (choice == 3) {
      if (!tree.GetRoot()) {
        std::cout << "Сначала создайте министерство!\n";
      } else {
        std::cout << "\nСТРУКТУРА МИНИСТЕРСТВА:\n\n";
        PrintTree(tree.GetRoot());

        std::cout << "\nПояснение:\n";
        std::cout << "- [id:стоимость]\n";
        std::cout << "- Верхний элемент — главный чиновник\n";
        std::cout << "- Ветви показывают подчинённых\n";
      }
    } else if (choice == 4) {
      if (!tree.GetRoot()) {
        std::cout << "Сначала создайте министерство!\n";
      } else {
        std::cout << "\nМинимальная сумма взяток: "
                  << tree.FindMinCost() << std::endl;
      }
    } else if (choice == 5) {
      if (!tree.GetRoot()) {
        std::cout << "Сначала создайте министерство!\n";
      } else {
        std::cout << "\nОптимальный путь: ";
        tree.PrintPath();
        std::cout << std::endl;
      }
    } else if (choice == 0) {
      std::cout << "Выход...\n";
      break;
    } else {
      std::cout << "Неверный пункт меню!\n";
    }
  }

  delete[] nodes;
  return 0;
}