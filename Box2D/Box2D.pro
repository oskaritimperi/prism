#-------------------------------------------------
#
# Project created by QtCreator 2010-10-12T20:44:51
#
#-------------------------------------------------

SHAPES_SRCS = \
    Collision/Shapes/b2PolygonShape.cpp \
    Collision/Shapes/b2CircleShape.cpp

SHAPES_HDRS = \
    Collision/Shapes/b2Shape.h \
    Collision/Shapes/b2PolygonShape.h \
    Collision/Shapes/b2CircleShape.h

COLLISION_HDRS += \
    Collision/b2TimeOfImpact.h \
    Collision/b2DynamicTree.h \
    Collision/b2Distance.h \
    Collision/b2Collision.h \
    Collision/b2BroadPhase.h

COLLISION_SRCS += \
    Collision/b2TimeOfImpact.cpp \
    Collision/b2DynamicTree.cpp \
    Collision/b2Distance.cpp \
    Collision/b2Collision.cpp \
    Collision/b2CollidePolygon.cpp \
    Collision/b2CollideCircle.cpp \
    Collision/b2BroadPhase.cpp

COMMON_HDRS += \
    Common/b2StackAllocator.h \
    Common/b2Settings.h \
    Common/b2Math.h \
    Common/b2BlockAllocator.h

COMMON_SRCS += \
    Common/b2StackAllocator.cpp \
    Common/b2Settings.cpp \
    Common/b2Math.cpp \
    Common/b2BlockAllocator.cpp

DYNAMICS_HDRS += \
    Dynamics/b2WorldCallbacks.h \
    Dynamics/b2World.h \
    Dynamics/b2TimeStep.h \
    Dynamics/b2Island.h \
    Dynamics/b2Fixture.h \
    Dynamics/b2ContactManager.h \
    Dynamics/b2Body.h

DYNAMICS_SRCS += \
    Dynamics/b2WorldCallbacks.cpp \
    Dynamics/b2World.cpp \
    Dynamics/b2Island.cpp \
    Dynamics/b2Fixture.cpp \
    Dynamics/b2ContactManager.cpp \
    Dynamics/b2Body.cpp

CONTACTS_HDRS += \
    Dynamics/Contacts/b2TOISolver.h \
    Dynamics/Contacts/b2PolygonContact.h \
    Dynamics/Contacts/b2PolygonAndCircleContact.h \
    Dynamics/Contacts/b2ContactSolver.h \
    Dynamics/Contacts/b2Contact.h \
    Dynamics/Contacts/b2CircleContact.h

CONTACTS_SRCS += \
    Dynamics/Contacts/b2TOISolver.cpp \
    Dynamics/Contacts/b2PolygonContact.cpp \
    Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    Dynamics/Contacts/b2ContactSolver.cpp \
    Dynamics/Contacts/b2Contact.cpp \
    Dynamics/Contacts/b2CircleContact.cpp

JOINTS_HDRS += \
    Dynamics/Joints/b2WeldJoint.h \
    Dynamics/Joints/b2RevoluteJoint.h \
    Dynamics/Joints/b2PulleyJoint.h \
    Dynamics/Joints/b2PrismaticJoint.h \
    Dynamics/Joints/b2MouseJoint.h \
    Dynamics/Joints/b2LineJoint.h \
    Dynamics/Joints/b2Joint.h \
    Dynamics/Joints/b2GearJoint.h \
    Dynamics/Joints/b2FrictionJoint.h \
    Dynamics/Joints/b2DistanceJoint.h

JOINTS_SRCS += \
    Dynamics/Joints/b2WeldJoint.cpp \
    Dynamics/Joints/b2RevoluteJoint.cpp \
    Dynamics/Joints/b2PulleyJoint.cpp \
    Dynamics/Joints/b2PrismaticJoint.cpp \
    Dynamics/Joints/b2MouseJoint.cpp \
    Dynamics/Joints/b2LineJoint.cpp \
    Dynamics/Joints/b2Joint.cpp \
    Dynamics/Joints/b2GearJoint.cpp \
    Dynamics/Joints/b2FrictionJoint.cpp \
    Dynamics/Joints/b2DistanceJoint.cpp

GENERAL_HDRS += \

SOURCES += $${COLLISION_SRCS} $${SHAPES_SRCS} $${COMMON_SRCS} \
    $${DYNAMICS_SRCS} $${CONTACTS_SRCS} $${JOINTS_SRCS}

HEADERS += $${COLLISION_HDRS} $${SHAPES_HDRS} $${COMMON_HDRS} \
    $${DYNAMICS_HDRS} $${CONTACTS_HDRS} $${JOINTS_HDRS} \
    $${GENERAL_HDRS}
