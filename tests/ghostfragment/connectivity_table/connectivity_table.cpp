#include "ghostfragment/connectivity_table.hpp"
#include <catch2/catch.hpp>

using namespace ghostfragment;

using pimpl_type     = typename ConnectivityTable::pimpl_type;
using pimpl_ptr      = typename ConnectivityTable::pimpl_ptr;
using size_type      = typename ConnectivityTable::size_type;
using pair_type      = typename ConnectivityTable::pair_type;
using bond_list_type = typename ConnectivityTable::bond_list_type;

TEST_CASE("ConnectivityTable") {
    SECTION("Typedefs") {
        using corr_pimpl = detail_::ConnectivityTablePIMPL;
        STATIC_REQUIRE(std::is_same_v<pimpl_type, corr_pimpl>);

        using corr_pimpl_ptr = std::unique_ptr<corr_pimpl>;
        STATIC_REQUIRE(std::is_same_v<pimpl_ptr, corr_pimpl_ptr>);

        using corr_size_type = std::size_t;
        STATIC_REQUIRE(std::is_same_v<size_type, corr_size_type>);

        using corr_pair_type = std::array<corr_size_type, 2>;
        STATIC_REQUIRE(std::is_same_v<pair_type, corr_pair_type>);

        using corr_bond_list = std::vector<corr_pair_type>;
        STATIC_REQUIRE(std::is_same_v<bond_list_type, corr_bond_list>);
    }

    ConnectivityTable t;

    SECTION("Default Ctor") {
        REQUIRE(t.natoms() == 0);
        REQUIRE(t.nbonds() == 0);
        REQUIRE(t.bonds() == bond_list_type{});
    }

    ConnectivityTable t0(0);
    ConnectivityTable t1(1);
    ConnectivityTable t2(2);
    ConnectivityTable t3(3);

    SECTION("Allocating CTor") {
        SECTION("0 Atoms") {
            REQUIRE(t0.natoms() == 0);
            REQUIRE(t0.nbonds() == 0);
            REQUIRE(t0.bonds() == bond_list_type{});
        }

        SECTION("1 Atom") {
            REQUIRE(t1.natoms() == 1);
            REQUIRE(t1.nbonds() == 0);
            REQUIRE(t1.bonds() == bond_list_type{});
        }

        SECTION("2 Atom") {
            REQUIRE(t2.natoms() == 2);
            REQUIRE(t2.nbonds() == 0);
            REQUIRE(t2.bonds() == bond_list_type{});
        }

        SECTION("3 Atom") {
            REQUIRE(t3.natoms() == 3);
            REQUIRE(t3.nbonds() == 0);
            REQUIRE(t3.bonds() == bond_list_type{});
        }
    }

    SECTION("Copy CTor") {
        ConnectivityTable CopyOft3(t3);
        REQUIRE(CopyOft3.natoms() == 3);
        REQUIRE(CopyOft3.nbonds() == 0);
        REQUIRE(CopyOft3.bonds() == bond_list_type{});
    }

    SECTION("Move CTor") {
        ConnectivityTable Newt3(std::move(t3));
        REQUIRE(Newt3.natoms() == 3);
        REQUIRE(Newt3.nbonds() == 0);
        REQUIRE(Newt3.bonds() == bond_list_type{});
        REQUIRE(t3.natoms() == 0);
        REQUIRE(t3.nbonds() == 0);
        REQUIRE(t3.bonds() == bond_list_type{});
    }

    SECTION("Comparisons") {
        SECTION("LHS == default") {
            SECTION("RHS == default") {
                REQUIRE(t == ConnectivityTable{});
                REQUIRE_FALSE(t != ConnectivityTable{});
            }

            SECTION("RHS == 0 Atoms") {
                REQUIRE(t == t0);
                REQUIRE_FALSE(t != t0);
            }

            SECTION("RHS has different number of atoms") {
                REQUIRE_FALSE(t == t1);
                REQUIRE(t != t1);
            }

            // No way for RHS have to only a different bonds or number of bonds
        }

        SECTION("LHS has natoms set") {
            SECTION("RHS == default") {
                REQUIRE_FALSE(t3 == t);
                REQUIRE(t3 != t);
            }

            SECTION("RHS is equal") {
                REQUIRE(t3 == ConnectivityTable{3});
                REQUIRE_FALSE(t3 != ConnectivityTable{3});
            }

            SECTION("RHS has different number of atoms") {
                REQUIRE_FALSE(t3 == t2);
                REQUIRE(t3 != t2);
            }

            SECTION("RHS has different number of bonds") {
                ConnectivityTable t3_2(3);
                t3_2.add_bond(0, 1);
                REQUIRE_FALSE(t3 == t3_2);
                REQUIRE(t3 != t3_2);
            }
        }

        SECTION("LHS has bonds") {
            t3.add_bond(0, 1);

            SECTION("RHS is equal") {
                ConnectivityTable t3_2(3);
                t3_2.add_bond(0, 1);
                REQUIRE(t3 == t3_2);
                REQUIRE_FALSE(t3 != t3_2);
            }

            SECTION("RHS has a different bond") {
                ConnectivityTable t3_2(3);
                t3_2.add_bond(1, 2);
                REQUIRE_FALSE(t3 == t3_2);
                REQUIRE(t3 != t3_2);
            }
        }
    }
}