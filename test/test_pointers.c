#include <stdio.h>
#include <math.h>
#include "minunit.h"
#include "../src/structs/structs.h"

/* It is unwise to compare the equality of floats
 * As such, one defines a tolerance EPSILON that indicates
 * the smallest deviation between two floats that one will accept
 * before declaring the floats unequal
 */
#define EPSILON 1e-15

/* Note: structure of test file taken from minunit example at
 *   http://www.jera.com/techinfo/jtns/jtn002.html
 */

// Needed for minunit to function properly
int tests_run = 0;

/* Check equality between COMP values
 * The size of the absolute value of the difference indicates equality
 */
int is_equal(COMP x, COMP y) {
    return fabs(x - y) < EPSILON;
}

/* Notice return type of a string (i.e., char *)
 * The default value is 0, which is an empty (null) string
 * If the test fails, it replaces this return with an error string
 */
static char * test_pass_by_value() {
    /* This uses the macro defined in minunit.h
     * which performs the Boolean test, and returns the error
     * message string if it fails
     */
    COMP x = 0, y = 0, z = 0;
    VEC3 v = {x, y, z};
    VEC3 w = modifyVec3(v, 15.0);
    mu_assert("error, v.x != 0.0", is_equal(v.x, x));
    mu_assert("error, v.y != 0.0", is_equal(v.y, y));
    mu_assert("error, v.z != 0.0", is_equal(v.z, z));
    mu_assert("error, w.x != 15.0", is_equal(w.x, 15.0)); 
    return 0;
}




// Pass by reference test
static char * test_pass_by_reference() {
    COMP x = 0, y = 0;
    VEC2 r = {x, y};
    setVec2(&r, 6.0, 8.0);
	mu_assert("error, r.x != 6.0", is_equal(r.x, 6.0));
	mu_assert("error, r.y != 8.0", is_equal(r.y, 8.0));
    return 0;
}




/* all_tests collects a set of tests defined above, and runs them
 */
static char * all_tests() {
    mu_run_test(test_pass_by_value);
    mu_run_test(test_pass_by_reference); // Run the pass by reference test
    return 0;
}




/* A test file should be executable, so has a main function
 * Note that it runs all the tests above, and prints output accordingly
 */
int main(int argc, char **argv) {
    // String to store all test results
    char *result = all_tests();
    
    // If the result is not null, there is at least one error
    if (result != 0) {
        // print the errors
        printf("%s\n", result);
    }
    else {
        // or inform user that tests passed
        printf("ALL TESTS PASSED\n");
    }
    // Show count of run tests
    printf("Tests run: %d\n", tests_run);
    
    // The return code is the boolean of whether all tests passed
    return result != 0;
}
