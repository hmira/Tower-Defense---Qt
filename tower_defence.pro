QT          += opengl

HEADERS     = glwidget.h \
              helper.h \
              widget.h \
              window.h \
    enemy.h \
    cannon.h
SOURCES     = glwidget.cpp \
              helper.cpp \
              main.cpp \
              widget.cpp \
              window.cpp \
    enemy.cpp \
    cannon.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/tower_defence
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS tower_defence.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/opengl/tower_defence
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
