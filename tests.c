#include <check.h>  // the test framework
#include <stdlib.h>

extern int chop(int needle, const int* haystack, int haystack_size);




// NOTES:
// couldn't face putting all these into their own individual tests,
// so grouped them into slightly artificial groups.
// What I really wanted was a way to define a test concisely in a single line.

START_TEST(test_empty)
{
    int data_empty[] = {};
    fail_unless( chop(3,data_empty,0) == -1); 
}
END_TEST

START_TEST(test_single)
{
    int data_single[] = {1};
    fail_unless( chop(3,data_single,1) == -1);
    fail_unless( chop(1,data_single,1) == 0);
}
END_TEST


START_TEST(test_odd_length)
{
    int data_three[] = {1,3,5};
    fail_unless( chop(1,data_three,3) == 0);
    fail_unless( chop(3,data_three,3) == 1);
    fail_unless( chop(5,data_three,3) == 2);
    fail_unless( chop(0,data_three,3) == -1);
    fail_unless( chop(2,data_three,3) == -1);
    fail_unless( chop(4,data_three,3) == -1);
    fail_unless( chop(6,data_three,3) == -1);
}
END_TEST


// NOTES:
// - these tests picked up a bug in their own implementation: originally
//   I pasted the haystack_size param as 3, so some of the tests were failing
START_TEST(test_even_length)
{
    int data_four[] = {1,3,5,7};
    fail_unless( chop(1,data_four,4) == 0);
    fail_unless( chop(3,data_four,4) == 1);
    fail_unless( chop(5,data_four,4) == 2);
    fail_unless( chop(7,data_four,4) == 3);
    fail_unless( chop(0,data_four,4) == -1);
    fail_unless( chop(2,data_four,4) == -1);
    fail_unless( chop(4,data_four,4) == -1);
    fail_unless( chop(6,data_four,4) == -1);
    fail_unless( chop(8,data_four,4) == -1);
}
END_TEST


// NOTE:
// the linear_chop reference version times out on this one ;-)
// (check has a sefault 4 sec timeout)
START_TEST(test_big)
{
    const int OFFSET = 42;
    const int N=100000;
    int data_big[N];
    int i;
    for(i=0;i<N;++i) {
        data_big[i] = OFFSET+i;
    }

    // check the values we know are there
    for(i=0;i<N;++i) {
        fail_unless( chop(OFFSET+i,data_big,N) == i);
    }

    // check some too-small values
    for(i=0;i<OFFSET;++i) {
        fail_unless( chop(i,data_big,N) == -1);
    }

    // check some too-big values
    for(i=0; i<10; ++i) {
        fail_unless( chop(OFFSET+N+i,data_big,N) == -1);
    }
}
END_TEST
 

int main (void)
{
    // ugh. too much boilerplate. Maybe check has some macros for such simple cases...
    int number_failed;
    Suite *s = suite_create ("KarateChop");

    TCase *tc_core = tcase_create ("Core");
    tcase_add_test (tc_core, test_empty);
    tcase_add_test (tc_core, test_single);
    tcase_add_test (tc_core, test_odd_length);
    tcase_add_test (tc_core, test_even_length);
    tcase_add_test (tc_core, test_big);
    suite_add_tcase (s, tc_core);

    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_NORMAL);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}


