
conf = configuration_data ()


conf.set ('version', '0.1.0')

compiler = meson.get_compiler ('c')

code = '''
#include <string.h>

int main (int argc, char **argv) {
    char tmp [128] ;
    int len ;
    len = strlcpy (tmp, "mokeke", sizeof (tmp)) ;
    if (len == 6) {
        return 0 ;
    }
    return 1 ;
}
'''

result = compiler.run (code, name : 'Check strlcpy')

conf.set10 ('TEST_ONLY', result.compiled ())

configure_file (input : 'config.h.in', output : 'config.h', configuration : conf)