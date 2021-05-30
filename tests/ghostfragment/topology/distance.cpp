#include "ghostfragment/topology/distance.hpp"
#include <catch2/catch.hpp>

using namespace ghostfragment::topology;

using value_type      = typename Distance::value_type;
using reference_type  = typename Distance::reference_type;
using const_reference = typename Distance::const_reference;

TEST_CASE("Distance") {
    SECTION("Typedefs") {
        STATIC_REQUIRE(std::is_same_v<value_type, double>);
        STATIC_REQUIRE(std::is_same_v<reference_type, double&>);
        STATIC_REQUIRE(std::is_same_v<const_reference, const double&>);
    }

    SECTION("Default CTor") {
        Distance d;
        REQUIRE(d.value() == value_type{0.0});
    }

    Distance d(1.23);

    SECTION("Value CTor") { REQUIRE(d.value() == value_type{1.23}); }

    SECTION("Copy CTor") {
        Distance CopyOfd(d);
        REQUIRE(CopyOfd.value() == value_type{1.23});
    }

    SECTION("hash") {
        REQUIRE(sde::hash_objects(d) == sde::hash_objects(Distance{1.23}));
        REQUIRE(sde::hash_objects(d) != sde::hash_objects(Distance{}));
    }

    SECTION("Comparisons") {
        SECTION("LHS == RHS") {
            Distance d2(1.23);
            REQUIRE(d == d2);
            REQUIRE_FALSE(d != d2);
        }
        SECTION("LHS != RHS") {
            Distance d2;
            REQUIRE_FALSE(d == d2);
            REQUIRE(d != d2);
        }
    }

    SECTION("Printing") {
        std::stringstream ss;
        ss << d;
        REQUIRE(ss.str() == "1.2300000000000000 (a.u.)");
    }
}