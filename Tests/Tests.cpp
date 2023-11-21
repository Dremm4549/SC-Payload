#include <gtest/gtest.h>
#include "../source code/ImageData.h"
#include "../source code/Payload.h"
#include "../source code/Packet.h"
#include "../source code/Telem.h"

TEST(TelemTest, SetTelemDataCheckLat) {
    Telem telem(1, 2, 3);
    ASSERT_EQ(telem.getLat(), 2);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}