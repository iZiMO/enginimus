//
// Created by Joel Schmidt on 8/10/2016.
//

#ifndef ENGINIMUS_EVENT_DISPATCH_HPP
#define ENGINIMUS_EVENT_DISPATCH_HPP

#include <vector>
#include <type_traits>
#include <enginimus/event/event_listener.hpp>

using namespace std;

using ListenerInstances = vector<BaseEventListener*>;
using ListenerTypesForEvent = vector<ListenerInstances>;
using AllListeners = vector<ListenerTypesForEvent>;

class EventDispatch {
public:

    static EventDispatch* getInstance();

    template<typename EventType, typename ListenerType>
    void registerListener(ListenerType* listener) {
        size_t eventId = EventType::getId();
        size_t listenerTypeId = ListenerType::getId();

        if (allListeners.size() <= eventId) {
            allListeners.resize(eventId + 1);
        }

        ListenerTypesForEvent& listenersForType = allListeners[eventId];
        if (listenersForType.size() <= listenerTypeId) {
            listenersForType.resize(listenerTypeId + 1);
            numInstancesOfType.resize(listenerTypeId + 1);
        }

        ListenerInstances& listenerInstances = listenersForType[listenerTypeId];
        if (listenerInstances.size() <= MAX_LISTENER_INSTANCES) {
            listenerInstances.resize(MAX_LISTENER_INSTANCES);
        }

        addInstance(listenerTypeId, listenerInstances, listener);
    }

    template<typename EventType, typename ListenerType>
    void deregisterListener(ListenerType* listener) {
        removeInstance(ListenerType::getId(), allListeners[EventType::getId()][ListenerType::getId()], listener);
    }
private:
    AllListeners allListeners;
    vector<int> numInstancesOfType;
    static EventDispatch* instance;

    EventDispatch() {
        instance = this;
    }

    template<typename ListenerType>
    void addInstance(size_t listenerTypeId, ListenerInstances &instances, ListenerType *listener) {
        int numInstances = numInstancesOfType[listenerTypeId];
        listener->slot = numInstances++;
        instances[listener->slot] = listener;
        numInstancesOfType[numInstances];
    }

    template<typename ListenerType>
    void removeInstance(size_t listenerTypeId, ListenerInstances &instances, ListenerType *listener) {
        assert(listener->slot >= 0);
        int numInstances = numInstancesOfType[listenerTypeId];
        int lastSlot = numInstances - 1;
        auto lastListener = instances[lastSlot];
        lastListener->slot = listener->slot;
        listener->slot = -1;
        instances[numInstances--] = NULL;
        instances[lastListener->slot] = lastListener;
        numInstancesOfType[listenerTypeId] = numInstances;
    }
};

EventDispatch* EventDispatch::instance = NULL;
EventDispatch* EventDispatch::getInstance() {
    if (!instance) {
        instance = new EventDispatch();
    }
    return instance;
}


#endif //ENGINIMUS_EVENT_DISPATCH_HPP
