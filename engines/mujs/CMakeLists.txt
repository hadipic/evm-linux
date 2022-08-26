set(MUJS_DIR ./mujs)

set(mujs_src
    ${MUJS_DIR}/one.c
)

idf_component_register(SRCS
                       evm.c
                       ${mujs_src}
                       INCLUDE_DIRS 
                       .
                       ./mujs
                       ../../include)

