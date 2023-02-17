#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <iostream>
#include <set>
#include <string>
#include <memory>

//////////////////////////////////////////////////////////////////////////////////////
template <typename TSource, typename... TEventArgs>
class Observer
{
public:
    virtual void update(TSource&, TEventArgs... args) = 0; // model push-pull
    virtual ~Observer() = default;
};

//////////////////////////////////////////////////////////////////////////////////////
template <typename TSource, typename... TEventArgs>
struct Observable
{
    void subscribe(std::weak_ptr<Observer<TSource, TEventArgs...>> observer)
    {        
        observers_.insert(observer);
    }
    void unsubscribe(std::weak_ptr<Observer<TSource, TEventArgs...>> observer) { observers_.erase(observer); }

protected:
    void notify(TEventArgs... args)
    {
        for (auto&& observer : observers_)
        {
            if (std::shared_ptr living_observer = observer.lock())
                living_observer->update(static_cast<TSource&>(*this), std::move(args...));
        }
    }

private:
    using WeakPtrObserver = std::weak_ptr<Observer<TSource, TEventArgs...>>;
    std::set<WeakPtrObserver, std::owner_less<WeakPtrObserver>> observers_;
};

#endif /*OBSERVER_HPP_*/
