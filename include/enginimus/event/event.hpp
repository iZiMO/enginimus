//
// Created by Joel Schmidt on 8/10/2016.
//

#ifndef ENGINIMUS_EVENT_HPP
#define ENGINIMUS_EVENT_HPP

#include <vector>
#include <type_traits>

// Event
class BaseEvent {
protected:
    static size_t nextId;
};
size_t BaseEvent::nextId = 0;

template<typename T>
class Event : BaseEvent {
public:
    static size_t getId() { return id; }
private:
    static size_t id;
};

template<typename T>
size_t Event<T>::id = BaseEvent::nextId++;

#endif //ENGINIMUS_EVENT_HPP
