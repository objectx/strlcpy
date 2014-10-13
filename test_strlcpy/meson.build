
test_strlcpy = executable ('test_strlcpy',
                           [ 'main.cpp'
                           , 'strlcpy.cpp'
                           , 'strlcat.cpp'],
                           include_directories : incs,
                           link_with : libstrlcpy)
test ('Run strlcpy test', test_strlcpy)
