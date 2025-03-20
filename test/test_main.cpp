#include <Arduino.h>
#include <unity.h>

// Fonction à tester (exemple simple)
int addition(int a, int b) {
    return a + b;
}

// ⚡ Test 1 : Vérifier que 2 + 3 = 5
void test_addition() {
    TEST_ASSERT_EQUAL(5, addition(2, 3));
}

// ⚡ Test 2 : Vérifier que -1 + 1 = 0
void test_addition_negatif() {
    TEST_ASSERT_EQUAL(0, addition(-1, 1));
}

// ⚡ Setup pour PlatformIO
void setup() {
    UNITY_BEGIN(); // Démarrer Unity
    RUN_TEST(test_addition);
    RUN_TEST(test_addition_negatif);
    UNITY_END(); // Terminer Unity
}

// ⚡ Boucle vide pour ESP32
void loop() {}
