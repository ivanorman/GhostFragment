#pragma once
#include <libchemist/chemical_system/chemical_system.hpp>
#include <libchemist/set_theory/set_theory.hpp>
#include <property_types/types.hpp>

namespace ghostfragment::type {

/// Type used to model the nuclear framework of a system
using molecule = property_types::type::molecule;

/// Type used to model a nucleus in the molecule
using atom = typename molecule::value_type;

/// Type used for connectivity tables
using connectivity_table = property_types::type::connectivity_table;

/// Type used for describing the entire chemical system
using chem_system = libchemist::ChemicalSystem;

/// Type used to denote tags/labels per fragment
using tag = std::string;

/// Type resulting from partitioning an object of type @p T
template<typename T>
using partition = libchemist::set_theory::FamilyOfSets<T>;

/// Type of a partitioned molecule
using fragmented_molecule = partition<molecule>;

/// Type of the nmers
using nmers = partition<fragmented_molecule>;

/// Type of a partitioned system
using fragmented_system = partition<chem_system>;

} // namespace ghostfragment::type
