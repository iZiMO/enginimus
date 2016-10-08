//
// Created by Joel Schmidt on 8/10/2016.
//

#ifndef ENGINIMUS_CAMERA_EVENTS_HPP
#define ENGINIMUS_CAMERA_EVENTS_HPP

#include <enginimus/enginimus.h>
#include <enginimus/event/event.hpp>

// concrete event data
struct AttachCamera : Event<AttachCamera> {
    EntityId id;
};

#endif //ENGINIMUS_CAMERA_EVENTS_HPP
