set(COMPONENT_ADD_INCLUDEDIRS "esp32-fft/components/fft/include")
file(GLOB COMPONENT_SRCS esp32-fft/components/fft/fft.c)


set(COMPONENT_PRIV_REQUIRES)

register_component()


