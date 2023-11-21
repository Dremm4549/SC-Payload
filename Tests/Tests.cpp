#include <gtest/gtest.h>
#include "../source code/ImageData.h"
#include "../source code/Payload.h"
#include "../source code/Packet.h"
#include "../source code/Telem.h"

TEST(TelemTest, ConstructorSetLat) {
    Telem telem(1, 2, 3);
    ASSERT_EQ(telem.getLat(), 2);
}

TEST(TelemTest, ConstructorSetLong) {
    Telem telem(1, 2, 3);
    ASSERT_EQ(telem.getLong(), 1);
}

TEST(TelemTest, ConstructorSetTime) {
    Telem telem(1, 2, 3);
    ASSERT_EQ(telem.getTime(), 3);
}

TEST(TelemTest, TelemetrySetLat) {
    Telem telem;
    telem.setLat(118);
    ASSERT_EQ(telem.getLat(), 118);
}

TEST(TelemTest, TelemetrySetLong) {
    Telem telem;
    telem.setLong(55);
    ASSERT_EQ(telem.getLong(), 55);
}

TEST(TelemTest, TelemetrySetTime) {
    Telem telem;
    auto time = std::chrono::system_clock::now();
    telem.setTime(std::chrono::system_clock::to_time_t(time));
    ASSERT_EQ(telem.getTime(), std::chrono::system_clock::to_time_t(time));
}

TEST(PayloadTest, ConstructorPayloadStateTrue) {
    Payload payload(true);
    ASSERT_EQ(payload.GetPowerState(), true);
}

TEST(PayloadTest, ConstructorPayloadStateFalse) {
    Payload payload(false);
    ASSERT_EQ(payload.GetPowerState(), false);
}

TEST(PayloadTest, SetPayloadStateTrue) {
    Payload payload(false);
    payload.SetPowerState(true);
    ASSERT_EQ(payload.GetPowerState(), true);
}

TEST(PayloadTest, SetPayloadStateFalse) {
    Payload payload(true);
    payload.SetPowerState(false);
    ASSERT_EQ(payload.GetPowerState(), false);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}