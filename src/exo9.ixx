export module exo9;
import std;

export namespace exo9 {

    template <typename T>
    struct Node {
        T value{};
        std::unique_ptr<Node> left{};
        std::unique_ptr<Node> right{};
    };



    template <typename T>
    class BinaryTree {
    public:
        void Insert(const T value) {
            RecursiveInsert(root, value);
        }

        void Traversal(const std::function<void(T)>& visit) const {
            RecursiveTraversal(root, visit);
        }

    private:
        void RecursiveInsert(std::unique_ptr<Node <T>>& node, const T value) {
            if (node == nullptr) {
                node = std::make_unique<Node <T>>(value);
            } else if (value < node->value) {
                RecursiveInsert(node->left, value);
            } else {
                RecursiveInsert(node->right, value);
            }
        }

        void RecursiveTraversal(const std::unique_ptr<Node <T>>& node, const std::function<void(T)>& visit) const {
            if (node == nullptr) {
                return;
            }
            RecursiveTraversal(node->left, visit);
            visit(node->value);
            RecursiveTraversal(node->right, visit);
        }

        std::unique_ptr<Node <T>> root{nullptr};
    };

    class Application {
    public:
        Application() {
            auto tree =  BinaryTree<int>{};
            for (const int value : {10, 5, 15, 3, 7}) {
                tree.Insert(value);
            }
            tree.Traversal([](const int value) {
                std::cout << value << ' ';
            });
            std::cout << '\n';
        }
    };

}
