
conf = configuration_data ()

conf.set ('version', '0.1.0')

compiler = meson.get_compiler ('c')

if compiler.has_function ('strnlen' , prefix : '#include <string.h>')
    conf.set10 ('HAS_STRNLEN', 1)
endif

if compiler.has_function ('strlen_s', prefix : '#include <string.h>')
    conf.set10 ('HAS_STRLEN_S', 1)
endif

if compiler.has_function ('strlcpy' , prefix : '#include <string.h>')
    conf.set10 ('HAS_STRLCPY', 1)
endif

if compiler.has_function ('strlcat' , prefix : '#include <string.h>')
    conf.set10 ('HAS_STRLCAT', 1)
endif

configure_file (input : 'config.h.in', output : 'config.h', configuration : conf)
