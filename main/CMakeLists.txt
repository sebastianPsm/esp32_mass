# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c")
set(COMPONENT_ADD_INCLUDEDIRS "")

set(EXTRA_COMPONENT_DIRS "${EXTRA_COMPONENT_DIRS} ${CMAKE_SOURCE_DIR}/components/mass")

register_component()
