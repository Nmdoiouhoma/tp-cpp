export module exo8;
import std;

export namespace exo8 {

    struct Node {
        int value{};
        std::unique_ptr<Node> left{};
        std::unique_ptr<Node> right{};
    };

    class BinaryTree {
    public:
        void Insert(const int value) {
            RecursiveInsert(root, value);
        }

        void Traversal(const std::function<void(int)>& visit) const {
            RecursiveTraversal(root, visit);
        }

    private:
        void RecursiveInsert(std::unique_ptr<Node>& node, const int value) {
            if (node == nullptr) {
                node = std::make_unique<Node>(value);
            } else if (value < node->value) {
                RecursiveInsert(node->left, value);
            } else {
                RecursiveInsert(node->right, value);
            }
        }

        void RecursiveTraversal(const std::unique_ptr<Node>& node, const std::function<void(int)>& visit) const {
            if (node == nullptr) {
                return;
            }
            RecursiveTraversal(node->left, visit);
            visit(node->value);
            RecursiveTraversal(node->right, visit);
        }

        std::unique_ptr<Node> root{nullptr};
    };

    class Application {
    public:
        Application() {
            auto tree = BinaryTree{};
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
