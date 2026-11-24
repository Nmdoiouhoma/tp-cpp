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

        T* Find(const T& value) {
            return RecursiveFind(root, value);
        }

    private:
        T* RecursiveFind(const std::unique_ptr<Node <T>>& node, const T& value) {
            if (node == nullptr) {
                return nullptr;
            }
            if (value == node->value) {
                return &node->value;
            }
            if (value < node->value) {
                return RecursiveFind(node->left, value);
            }
            return RecursiveFind(node->right, value);
        }

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


    template <typename K, typename V>
    struct MapEntry {
        K key;
        V value;
        bool operator<(const MapEntry& other) const {
            return key < other.key;
        }

        bool operator>(const MapEntry& other) const {
            return key > other.key;
        }

        bool operator<=(const MapEntry& other) const {
            return key <= other.key;
        }

        bool operator>=(const MapEntry& other) const {
            return key >= other.key;
        }

        bool operator==(const MapEntry& other) const {
            return key == other.key;
        }

        bool operator!=(const MapEntry& other) const {
            return key != other.key;
        }
    };


    template <typename K, typename V>
    class Map {
    public:
        void Clear() {
            tree = BinaryTree<MapEntry<K, V>>{};
        }

        std::size_t GetSize() const {
            std::size_t count{0};
            tree.Traversal([&count](const MapEntry<K, V>& entry) {++count; });
            return count;
        }

        bool Contains(const K& key) const {
            bool found{false};
            tree.Traversal([&found, key](const MapEntry<K, V>& entry) {
                if (entry.key == key) {
                    found = true;
                }

            });
            return found;
        }

        V& Get(const K& key) {
            MapEntry<K, V>* entry = tree.Find(MapEntry<K, V>{key, V{}});
            if (entry == nullptr) {
                throw std::out_of_range("Key not found");
            }
            return entry->value;
        }

        void Put(const K& key, const V& value) {
            MapEntry<K, V>* entry = tree.Find(MapEntry<K, V>{key, value});
            if (entry == nullptr) {
                tree.Insert(MapEntry<K, V>{key, value});
            } else {
                entry->value = value;
            }
        }

        std::optional<std::reference_wrapper<V>> Find(const K& key) {
            MapEntry<K, V>* entry = tree.Find(MapEntry<K, V>{key, V{}});
            if (entry == nullptr) {
                return std::nullopt;
            }
            return std::ref(entry->value);
        }

        std::expected<std::reference_wrapper<V>, std::string> FindExpected(const K& key) {
            MapEntry<K, V>* entry = tree.Find(MapEntry<K, V>{key, V{}});
            if (entry == nullptr) {
                return std::unexpected("Key not found");
            }
            return std::ref(entry->value);
        }

    private:
        BinaryTree<MapEntry<K, V>> tree;
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
