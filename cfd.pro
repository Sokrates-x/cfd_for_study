TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        boundary_condtions.cpp \
        equation.cpp \
        field.cpp \
        fluid.cpp \
        main.cpp \
        mesh.cpp \
        node.cpp \
        rho_equation.cpp \
        time_cfd.cpp \
        u_equation.cpp \
        unit.cpp

HEADERS += \
    boundary_condtions.h \
    constant.h \
    equation.h \
    field.h \
    fluid.h \
    initial_tags.h \
    initialize.h \
    mesh.h \
    node.h \
    rho_equation.h \
    time_cfd.h \
    u_equation.h \
    unit.h
