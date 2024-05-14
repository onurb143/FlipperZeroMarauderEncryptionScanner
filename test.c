#include "unity.h"
#include "wifi_marauder_app_i.h"

// Mock funktioner og eksterne definitioner her

void setUp(void) {
    // Denne funktion køres før hver test
}

void tearDown(void) {
    // Denne funktion køres efter hver test
}

void test_encryption_types(void) {
    TEST_ASSERT_EQUAL_STRING("WPA2_PSK", get_encryption_type(3));  // Antag, at dette er funktionen, du tester
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_encryption_types);
    return UNITY_END();
}
