#include <functional>
#include <vector>
#include <any>

template<typename... Args>
class Event
{
public:
    using Listener = std::function<void(Args...)>;

    void Register(const Listener& listener)
    {
        listeners.push_back(listener);
    }

    void Trigger(Args... args) const //TODO: convert to a operator();?
    {
        for (const auto& listener : listeners)
        {
            listener(args...);
        }
    }; 

private:
    std::vector<Listener> listeners;
};
