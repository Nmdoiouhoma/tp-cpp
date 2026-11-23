export module exo7;
import std;

export namespace exo7 {

    class Resource {
    public:
        Resource() {
            std::cout << "Resource() constructor called\n";
        }

        ~Resource() {
            std::cout << "~Resource() destructor called\n";
        }

        void DoSomething() const {
            std::cout << "Doing something\n";
        }
    };

    class Application {
    public:
        Application() {
            UniquePtr();
            SharedPtr();
        }

    private:
        void UniquePtr() {
            const auto resource = std::make_unique<Resource>();
            resource->DoSomething();
        }


        void UseSharedPtr(const std::shared_ptr<Resource> res) {
            std::cout << "resource use count: " << res.use_count() << '\n';
            res->DoSomething();

            if (res.use_count() < 5) {
                UseSharedPtr(res);
            }
        }

        void SharedPtr() {
            const auto resource = std::make_shared<Resource>();

            std::cout << "resource use count: " << resource.use_count() << '\n';
            UseSharedPtr(resource);
            std::cout << "resource use count: " << resource.use_count() << '\n';
        }
    };

}
