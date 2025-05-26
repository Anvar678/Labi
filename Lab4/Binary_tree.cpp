#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

template <typename T>
class Tree
{
private:
    struct Node
    {
        T value;
        Node* left; //левый сын
        Node* right; //правый сын

        Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t count_nodes; //size_t можно расширять а инт нет

    void deleteSubtree(Node* p)
    {
        if (!p) return;
        deleteSubtree(p->left);
        deleteSubtree(p->right);
        delete p;
    }

public:
    //Конструкторы
    Tree(const vector<T*>& arr) : root(nullptr), count_nodes(0)
    {
        const size_t n = arr.size();
        if (n == 0 || arr[0] == nullptr) return;

        vector<Node*> nodes(n, nullptr); // вектор указателй на узлы
        for (size_t i = 0; i < n; i++)
        {
            if (arr[i])
            {
                nodes[i] = new Node(*arr[i]);
                count_nodes++;
            }
        }

        // Связываю детей :)
        for (size_t i = 0; i < n; i++)
        {
            if (!nodes[i]) continue;
            size_t l = 2 * i + 1, r = 2 * i + 2; //индексы левого и правого потомка 

            if (l < n) nodes[i]->left = nodes[l];
            if (r < n) nodes[i]->right = nodes[r];
        }
        root = nodes[0];
    }

    Tree() : root(nullptr), count_nodes(0) {}

    ~Tree() { deleteSubtree(root); }

    size_t size() const { return count_nodes; }

    //Обходы
    void Show() //просто BFS который вывожу 
    {
        cout << endl;
        if (!root) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            size_t level_size = q.size(); //кол-во вершин на уровне

            for (size_t i = 0; i < level_size; i++)
            {
                Node* current = q.front();
                q.pop();

                cout << current->value << " ";

                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            cout << endl;
        }
    }

    void RootLeftRight()
    {
        RootLeftRight_pr(root);
        cout << endl;
    }

    void RootRightLeft()
    {
        RootRightLeft_pr(root);
        cout << endl;
    }

    void LeftRightRoot()
    {
        LeftRightRoot_pr(root);
        cout << endl;
    }

    void RightLeftRoot()
    {
        RightLeftRoot_pr(root);
        cout << endl;
    }

    void LeftRootRight()
    {
        LeftRootRight_pr(root);
        cout << endl;
    }

    void RightRootLeft()
    {
        RightRootLeft_pr(root);
        cout << endl;
    }

    // Функции
    void Map(T(*func)(T))
    {
        map_pr(root, func);
    }

    Tree<T> Where(bool (*pred)(const T&)) const
    {
        Tree<T> result;
        result.root = where_pr(root, pred, result.count_nodes);
        return result;
    }

    Tree<T> Merge(T(*sum_func)(T, T), Tree<T>* tree1, Tree<T>* tree2)
    {
        Tree<T> result;
        result.root = Merge_pr(tree1->root, tree2->root, sum_func, result.count_nodes);
        return result;
    }

    Tree<T> Subtree(int number_node)
    {
        Tree<T> result;
        if (!root) return result;

        queue<Node*> q;
        q.push(root);
        int idx = 0;
        Node* found = nullptr;

        while (!q.empty())
        {
            Node* cur = q.front(); q.pop();
            if (idx == number_node)
            {
                found = cur;
                break;
            }
            idx++;
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }

        result.root = Subtree_pr(found, result.count_nodes);
        return result;
    }

    bool Is_here(T val)
    {
        queue<Node*> q;
        q.push(root);
        while (!q.empty())
        {
            Node* cur = q.front(); q.pop();
            if (cur->value == val) return true;
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        return false;
    }

    string Tree_to_string(void(*)(Node*))
    {
        ostringstream ss;
        if (!root) return "";
        queue<Node*> q;
        q.push(root);
        while (!q.empty())
        {
            Node* cur = q.front(); 
            q.pop();
            ss << cur->value << " ";
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        return ss.str();
    }

    Tree<T>* String_to_tree(void(*)(Node*), string str)
    {
        std::istringstream iss(str);

        std::vector<T> values;
        T value;
        while (iss >> value) values.push_back(value);
        

        // Указатели на элементы
        std::vector<T*> pointers;
        for (std::size_t i = 0; i < values.size(); i++) pointers.push_back(&values[i]);
        
        return new Tree<T>(pointers);
    }

    Node* Route(string route) //LRRLR
    {
        Node* cur = root;
        for (char c : route)
        {
            if (!cur) return nullptr;
            if (c == 'L')      cur = cur->left;
            else if (c == 'R') cur = cur->right;
            else               return nullptr;
        }
        return cur;
    }

private:

    //Рекурсивные обходы
    void RootLeftRight_pr(Node* p)
    {
        if (!p) return;
        cout << p->value << ' ';
        RootLeftRight_pr(p->left);
        RootLeftRight_pr(p->right);
    }

    void RootRightLeft_pr(Node* p)
    {
        if (!p) return;
        cout << p->value << ' ';
        RootRightLeft_pr(p->right);
        RootRightLeft_pr(p->left);
    }

    void LeftRightRoot_pr(Node* p)
    {
        if (!p) return;
        if (p->left)  LeftRightRoot_pr(p->left);
        if (p->right) LeftRightRoot_pr(p->right);
        cout << p->value << " ";
    }

    void RightLeftRoot_pr(Node* p)
    {
        if (!p) return;
        if (p->right) RightLeftRoot_pr(p->right);
        if (p->left)  RightLeftRoot_pr(p->left);
        cout << p->value << " ";
    }

    void LeftRootRight_pr(Node* p)
    {
        if (!p) return;
        LeftRootRight_pr(p->left);
        cout << p->value << " ";
        LeftRootRight_pr(p->right);
    }

    void RightRootLeft_pr(Node* p)
    {
        if (!p) return;
        RightRootLeft_pr(p->right);
        cout << p->value << " ";
        RightRootLeft_pr(p->left);
    }

    //Функции рекурсивные
    void map_pr(Node* p, T(*func)(T))
    {
        if (!p) return;
        p->value = func(p->value);
        map_pr(p->left, func);
        map_pr(p->right, func);
    }

    Node* where_pr(Node* p, bool (*pred)(const T&), size_t& cnt) const
    {
        if (!p) return nullptr;
        Node* L = where_pr(p->left, pred, cnt);
        Node* R = where_pr(p->right, pred, cnt);
        if (pred(p->value))
        {
            Node* q = new Node(p->value);
            cnt++; //счетчик узлов в итоговом дереве
            q->left = L;
            q->right = R;
            return q;
        }
        return L ? L : R;
    }

    Node* Merge_pr(Node* p1, Node* p2, T(*sum_func)(T, T), size_t& cnt)
    {
        if (!p1 && !p2) return nullptr;
        T val;
        if (p1 && p2)      val = sum_func(p1->value, p2->value);
        else if (p1)       val = p1->value;
        else               val = p2->value;

        Node* q = new Node(val);
        cnt++;
        q->left = Merge_pr(p1 ? p1->left : nullptr, p2 ? p2->left : nullptr, sum_func, cnt);
        q->right = Merge_pr(p1 ? p1->right : nullptr, p2 ? p2->right : nullptr, sum_func, cnt);
        return q;
    }

    Node* Subtree_pr(Node* p, size_t& cnt)
    {
        if (!p) return nullptr;
        Node* q = new Node(p->value);
        cnt++;
        q->left = Subtree_pr(p->left, cnt);
        q->right = Subtree_pr(p->right, cnt);
        return q;
    }

};

int func(int x) { return x + 2; }

bool predic(const int& x) { return x % 2 == 0; }

int summ_for_int(int a, int b) { return a + b; }

int main()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    vector<int*> data = { &a, &b, &c, &d, &e, nullptr, nullptr, &f, &g };
    Tree<int> t(data);

    vector<int*> data1 = { &a, &b, &c, &d, &e, &f, &g };
    Tree<int> t1(data1);

    cout << t.size() << endl;

    //Обходы
    t.RootLeftRight();
    t.RootRightLeft();
    t.Show();
    t1.Show();
    t1.LeftRightRoot();
    t1.RightLeftRoot();
    t1.LeftRootRight();
    t1.RightRootLeft();

    t.Map(func);
    t.Show();

    Tree<int> t3 = t1.Where(predic);
    t3.Show();

    Tree<int> t4 = t.Merge(summ_for_int, &t1, &t1);
    t4.Show();

    Tree<int> t5 = t.Subtree(3);
    t5.Show();

    cout << endl << t5.Is_here(25);

    string s = t.Tree_to_string(nullptr);
    cout << endl << "Serialized: " << s;

    Tree<int>* t6 = t.String_to_tree(nullptr, s);
    t6->Show();

    auto node = t.Route("LR");
    if (node) cout << endl << "Route LR: " << node->value;
    else cout << endl << "Route LR: nullptr";

    return 0;
}
