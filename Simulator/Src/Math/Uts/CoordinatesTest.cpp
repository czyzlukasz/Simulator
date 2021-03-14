#include <gtest/gtest.h>
#include <Coordinates.hpp>

TEST(CoordinatesTest, UserLiteralToCoordinates){
    EXPECT_EQ(12.3_N, 12.3);
    EXPECT_EQ(12.3_S, -12.3);
    EXPECT_EQ(-12.3_S, 12.3);
    EXPECT_EQ(-0._S, 0.);

    EXPECT_EQ(12.3_E, 12.3);
    EXPECT_EQ(12.3_W, -12.3);
    EXPECT_EQ(-12.3_W, 12.3);
    EXPECT_EQ(-0._W, 0.);
}

TEST(CoordinatesTest, DdToDmsZero){
    const auto [dLong, mLong, sLong, ew] = Coordinates().getHumanReadableLongitude();
    const auto [dLat, mLat, sLat, ns] = Coordinates().getHumanReadableLatitude();

    EXPECT_EQ(dLong, 0);
    EXPECT_EQ(dLat, 0);
    EXPECT_EQ(mLong, 0);
    EXPECT_EQ(mLat, 0);
    EXPECT_EQ(sLong, 0.f);
    EXPECT_EQ(sLat, 0.f);
}

TEST(CoordinatesTest, DdToDmsLatitudeN){
    const auto [d, m, s, ns] = Coordinates(1.1_N, 0._E).getHumanReadableLatitude();
    EXPECT_EQ(d, 1);
    EXPECT_EQ(m, 6);
    EXPECT_NEAR(s, 0.f, 1e-6);
    EXPECT_EQ(ns, 'N');
}

TEST(CoordinatesTest, DdToDmsLatitudeS){
    const auto [d, m, s, ns] = Coordinates(12.3456_S, 0._E).getHumanReadableLatitude();
    EXPECT_EQ(d, 12);
    EXPECT_EQ(m, 20);
    EXPECT_NEAR(s, 44.16f, 1e-6);
    EXPECT_EQ(ns, 'S');
}

TEST(CoordinatesTest, DdToDmsLongitudeE){
    const auto [d, m, s, ew] = Coordinates(0._N, 1.1_E).getHumanReadableLongitude();
    EXPECT_EQ(d, 1);
    EXPECT_EQ(m, 6);
    EXPECT_NEAR(s, 0.f, 1e-6);
    EXPECT_EQ(ew, 'E');
}

TEST(CoordinatesTest, DdToDmsLongitudeW){
    const auto [d, m, s, ew] = Coordinates(0._N, 12.3456_W).getHumanReadableLongitude();
    EXPECT_EQ(d, 12);
    EXPECT_EQ(m, 20);
    EXPECT_NEAR(s, 44.16f, 1e-6);
    EXPECT_EQ(ew, 'W');
}

TEST(CoordinatesTest, SmallDistanceBetweenCoordinates){
    const Coordinates first(12.3_N, 1.2_E);
    const Coordinates second(12.30004_N, 1.2_E);

    EXPECT_NEAR(Coordinates::distanceBetween(first, second), 4.448, 1e-3);
}

TEST(CoordinatesTest, LargeDistanceBetweenCoordinates){
    const Coordinates first(12.3_S, 1.2_E);
    const Coordinates second(52.4_N, 18.9_W);

    EXPECT_NEAR(Coordinates::distanceBetween(first, second), 7447856, 1.);
}

TEST(CoordinatesTest, SmallDistanceBearing){
    const Coordinates first(12.3_S, 1.2_E);
    const Coordinates second(12.4_S, 1.5_E);

    EXPECT_NEAR(first.initialBearing(second), 108.873, 1e-3);
}

TEST(CoordinatesTest, LargeDistanceBearing){
    const Coordinates first(12.3_S, 1.2_E);
    const Coordinates second(52.4_N, 18.9_W);

    EXPECT_NEAR(first.initialBearing(second), 346.831, 1e-3);
}
