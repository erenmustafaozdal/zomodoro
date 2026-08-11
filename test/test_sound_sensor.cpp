#include <unity.h>
#include "SoundSensor.hpp"

void setUp(void) {
    // Test oncesi hazirlik
}

void tearDown(void) {
    // Test sonrasi temizlik
}

void test_sound_sensor_initialization(void) {
    EMO::SoundSensor sensor(A1, 10, 450);
    TEST_ASSERT_EQUAL(450, sensor.GetThreshold());
    TEST_ASSERT_EQUAL(0, sensor.GetNoiseFloor());
    TEST_ASSERT_EQUAL(0, sensor.GetLastSampleCount());
    TEST_ASSERT_FALSE(sensor.IsSoundDetected());
}

void test_sound_sensor_threshold_change(void) {
    EMO::SoundSensor sensor(A1, 10, 450);
    sensor.SetThreshold(600);
    TEST_ASSERT_EQUAL(600, sensor.GetThreshold());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_sound_sensor_initialization);
    RUN_TEST(test_sound_sensor_threshold_change);
    return UNITY_END();
}
