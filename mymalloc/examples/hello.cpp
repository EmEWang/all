// #include <stdio.h>
// #include <stdlib.h>

// #include <iostream>
// #include <cstddef>
// #include <bits/c++config.h>
// #include <ostream>
// #include <istream>

// #include <ios>
// #include <bits/ostream_insert.h>

// #include <iosfwd>
// #include <exception> 		// For ios_base::failure
// #include <bits/char_traits.h> 	// For char_traits, streamoff, streamsize, fpos
// #include <bits/localefwd.h>	// For class locale
// #include <bits/ios_base.h>	// For ios_base declarations.
// #include <streambuf>
// #include <bits/basic_ios.h>

// #include <bits/localefwd.h>
// #include <bits/locale_classes.h>
// #include <bits/locale_facets.h>
// #include <bits/streambuf_iterator.h>
// #include <bits/move.h>

// #include <streambuf>
// #include <debug/debug.h>

// #include <bits/c++config.h>
// #include <iosfwd>
// #include <bits/localefwd.h>
// #include <bits/ios_base.h>
// #include <bits/cpp_type_traits.h>
// #include <ext/type_traits.h>

// #include <ext/atomicity.h>
// #include <bits/localefwd.h>
// #include <bits/locale_classes.h>

// #include <bits/localefwd.h>
// #include <string>
// #include <ext/atomicity.h>

// #include <bits/c++config.h>
// #include <bits/stringfwd.h>
// #include <bits/char_traits.h>  // NB: In turn includes stl_algobase.h
// #include <bits/allocator.h>
// #include <bits/cpp_type_traits.h>
// #include <bits/localefwd.h>    // For operators >>, <<, and getline.
// #include <bits/ostream_insert.h>
// #include <bits/stl_iterator_base_types.h>
// #include <bits/stl_iterator_base_funcs.h>
// #include <bits/stl_iterator.h>
// #include <bits/stl_function.h> // For less
// #include <ext/numeric_traits.h>
// #include <bits/stl_algobase.h>
// #include <bits/range_access.h>
// #include <bits/basic_string.h>
// #include <bits/basic_string.tcc>


// #include <ext/atomicity.h>
// #include <ext/alloc_traits.h>
// #include <debug/debug.h>

#include <malloc.h>
// #include <sys/malloc.h>
// #include <mm_malloc.h>
// #include <stdlib.h>

struct st
{
    int i;
    float f;
};

int main() {

    int size = 12801;

    unsigned int count = 10000;
    for (size_t i = 0; i < count; i++)
    {
        char *ptr = (char*) malloc(size);
        free(ptr);
    }

    st* pst = new st;

    // printf("--------- size %d count %u\n", size, count);
    return 0;
}