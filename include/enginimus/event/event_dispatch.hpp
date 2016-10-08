//
// Created by Joel Schmidt on 8/10/2016.
//

#ifndef ENGINIMUS_EVENT_DISPATCH_HPP
#define ENGINIMUS_EVENT_DISPATCH_HPP

#include <vector>
#include <type_traits>
#include <enginimus/event/event_listener.hpp>

class EventDispatch {
public:
    EventDispatch() {
        instance = this;
    }

    static EventDispatch* getInstance();

    template<typename EventType, typename ListenerType>
    void registerListener(ListenerType* listener) {
        size_t eventId = EventType::getId();
        size_t listenerId = ListenerType::getId();

        if (allListeners.size() <= eventId) {
            allListeners.resize(eventId + 1);
        }

        std::vector<BaseEventListener*>& listenersForEvent = allListeners[eventId];
        if (listenersForEvent.size() <= listenerId) {
            listenersForEvent.resize(listenerId + 1);
        }

        listenersForEvent[listenerId] = listener;
    }

    template<typename EventType, typename ListenerType>
    void deregisterListener(ListenerType* listener) {
        allListeners[EventType::getId()][ListenerType::getId()] = NULL;
    }
private:
    // eventId -> list of listeners
    std::vector<std::vector<BaseEventListener*>> allListeners;
    static EventDispatch* instance;
};

EventDispatch* EventDispatch::instance = NULL;
static EventDispatch* EventDispatch::getInstance() {
    return instance;
}


#endif //ENGINIMUS_EVENT_DISPATCH_HPP
