//
// Created by Joel Schmidt on 8/10/2016.
//

#ifndef ENGINIMUS_EVENT_LISTENER_HPP
#define ENGINIMUS_EVENT_LISTENER_HPP

#include <vector>
#include <type_traits>

// Listener
class BaseEventListener {
protected:
    static size_t nextId;
};
size_t BaseEventListener::nextId = 0;

template<class EventType>
class EventListener : BaseEventListener {
public:
    virtual void handle(const EventType& event) = 0;
    static size_t getId() { return id; }
private:
    static size_t id;
};

template<typename EventType>
size_t EventListener<EventType>::id = BaseEventListener::nextId++;

#endif //ENGINIMUS_EVENT_LISTENER_HPP
