
test_strlcpy = executable ('test_strlcpy',
                           ['main.cpp', 'strlcpy.cpp', 'strlcat.cpp', 'strconcat.cpp'],
                           include_directories : incs,
                           cpp_pch : ['pch/common_pch.hpp'],
                           link_with : libstrlcpy)

test ('Run strlcpy test', test_strlcpy)
