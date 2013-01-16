
int linear_chop(int needle, const int* haystack, int haystack_size)
{
    int i;
    for(i=0;i<haystack_size;++i) {
        if(haystack[i]==needle)
            return i;
    }
    return -1;
}


// NOTES:
// - was surprised to see tests all pass before I'd 'mentally' finished
//   testing the code (which I guess is the whole point of tdd)
// - was simple to write
// - smells right: no corner cases.
int binary_chop(int needle, const int* haystack, int haystack_size)
{
    int begin=0;
    int end=haystack_size;

    while(begin<end) {
        int mid = begin + (end-begin)/2;
        if(needle == haystack[mid])
            return mid;
        if(needle > haystack[mid]) {
            begin = mid+1;
        } else {
            end = mid;
        }
    }
    return -1;
}


// NOTES:
// - my cheesy auto-update script was hiding a crucial compiler warning that
//   actually caused a segfault (I was using haystack where I should have
//   had haystack_size, so I was suddenly making the array _HUGE_!)
// - weird problem of test_odd and test_even failing, but test_big passing
// - had bug where adding mid to -1... needed to add specific check.
// - smells bad. too many corner cases. Do not like.

// - Extra:
//   I found an off-by-one error. It didn't break the function, and the tests
//   didn't fail... but the function was doing more work than it should've.
//   I would have found it if I _wasn't_ using tests - I'd have
//   had to think harder about the code. With the tests, I find my actual
//   implementation gets lazy.

int recursive_chop(int needle, const int* haystack, int haystack_size)
{
    if(haystack_size==0)
        return -1;

    int mid = haystack_size/2;
    if(needle==haystack[mid])
        return mid;

    if(needle > haystack[mid]) {
        int foo = recursive_chop(needle, haystack+mid+1, haystack_size-(mid+1));
        return foo==-1 ? -1 : mid+1+foo;
    } else {
        return recursive_chop(needle, haystack, mid);
    }
}


// NOTES:
// - uses helper function to remove some special cases
// - managed to grind my computer to a crawl with an unbounded recursion :-)
// - feels cleaner, but helper function messy in C
int _recursive_chop2_helper(int needle, const int* haystack, int begin, int end)
{
    if( begin==end)
        return -1;

    int mid = begin+(end-begin)/2;
    if(needle==haystack[mid])
        return mid;

    if(needle > haystack[mid]) {
        return _recursive_chop2_helper(needle, haystack, mid+1, end);
    } else {
        return _recursive_chop2_helper(needle, haystack, begin,mid);
    }
}

int recursive_chop2(int needle, const int* haystack, int haystack_size)
{
    return _recursive_chop2_helper(needle, haystack,0,haystack_size);
}


int chop(int needle, const int* haystack, int haystack_size)
{
//    return binary_chop(needle,haystack,haystack_size);
//    return recursive_chop(needle,haystack,haystack_size);
//    return recursive_chop2(needle,haystack,haystack_size);
    return linear_chop(needle,haystack,haystack_size);
}

