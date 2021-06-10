#include "gtest/gtest.h"
#include "../headers/Record.hpp"

TEST(RecordTest, Getters)
{
    Record rec("1234", "101", "20200101180000", "Live");
    ASSERT_EQ(rec.getStartTime(), "20200101180000");
    ASSERT_EQ(rec.getHomeId(), "1234");
    ASSERT_EQ(rec.getDuration(), 0);
    ASSERT_EQ(rec.info(), "1234|101|20200101180000|Live||0\n");
}
