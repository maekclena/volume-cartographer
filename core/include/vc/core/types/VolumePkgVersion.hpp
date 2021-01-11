#pragma once

/**
  @file   VolumePkgVersion.hpp
  @author Seth Parker
  @date   April 2015

  @brief  VolumePkg metadata templates.

  The objects in this file define the keys that can be expected
  in a VolumePkg's metadata JSON file, based on the VolumePkg version
  number.

  A volcart::Dictionary defines a set of metadata keys and the associated types
  of the corresponding values (e.g. the key "version" should be interpreted as
  an `int`). A volcart::Library holds several such dictionaries: one dictionary
  for each unique version of VolumePkg.

  volcart::VERSION_LIBRARY holds the metadata keys and expected value-types for
  every version of VolumePkg. When creating a new VolumePkg, these dictionaries
  are used to define the default keys that populate the JSON file. In the
  future, applications that use VolumePkg will be able to query the Library in
  order to determine what information can be expected in a particular version
  of a VolumePkg. In this way, developers will be able to maintain backwards
  compatibility with older datasets.

  @ingroup Types
 */

#include <string>
#include <unordered_map>

namespace volcart
{
/** @brief %Volume Package version generated by this release */
static constexpr int VOLPKG_VERSION_LATEST = 6;

/** Dictionary entry */
using DictionaryEntryKey = std::string;

/** Possible types for Dictionary entries */
enum class DictionaryEntryType { String, Int, Double };

/**
 * Holds a set of key-value pairs that map JSON metadata keys to the expected
 * type of the value. A template for the structure of a VolumePkg's metadata.
 */
using Dictionary = std::unordered_map<DictionaryEntryKey, DictionaryEntryType>;

/**
 * Holds a set of key-value pairs that map version number keys to a specific
 * Dictionary of metadata mappings.
 */
using Library = std::unordered_map<int, Dictionary>;

// clang-format off
/** Metadata dictionary for VolumePkg v6. */
const Dictionary V6 =
        {
        {"name",             DictionaryEntryType::String},
        {"version",          DictionaryEntryType::Int},
        {"materialthickness",DictionaryEntryType::Double}
        };

/** Metadata dictionary for VolumePkg v5 */
const Dictionary V5 = V6;

/** Metadata dictionary for VolumePkg v4. */
const Dictionary V4 = V5;

/** Metadata dictionary for VolumePkg v3. */
const Dictionary V3 =
        {
        {"volumepkg name",   DictionaryEntryType::String},
        {"version",          DictionaryEntryType::Int},
        {"width",            DictionaryEntryType::Int},
        {"height",           DictionaryEntryType::Int},
        {"number of slices", DictionaryEntryType::Int},
        {"slice location",   DictionaryEntryType::String},
        {"min",              DictionaryEntryType::Double},
        {"max",              DictionaryEntryType::Double},
        {"voxelsize",        DictionaryEntryType::Double},
        {"materialthickness",DictionaryEntryType::Double}
        };

/** Metadata dictionary for VolumePkg v2. */
const Dictionary V2 =
        {
        {"volumepkg name",   DictionaryEntryType::String},
        {"version",          DictionaryEntryType::Int},
        {"width",            DictionaryEntryType::Int},
        {"height",           DictionaryEntryType::Int},
        {"number of slices", DictionaryEntryType::Int},
        {"slice location",   DictionaryEntryType::String},
        {"min",              DictionaryEntryType::Double},
        {"max",              DictionaryEntryType::Double},
        {"voxelsize",        DictionaryEntryType::Double},
        {"materialthickness",DictionaryEntryType::Double}
        };

/** Metadata dictionary for VolumePkg v1. */
const Dictionary V1 =
        {
        {"volumepkg name",   DictionaryEntryType::String},
        {"version",          DictionaryEntryType::Int},
        {"width",            DictionaryEntryType::Int},
        {"height",           DictionaryEntryType::Int},
        {"number of slices", DictionaryEntryType::Int},
        {"slice location",   DictionaryEntryType::String},
        {"min",              DictionaryEntryType::Double},
        {"max",              DictionaryEntryType::Double},
        {"voxelsize",        DictionaryEntryType::Double}
        };
// clang-format on

/**
 * Global Library used to store all template Dictionaries.
 */
const Library VERSION_LIBRARY = {{1, V1}, {2, V2}, {3, V3},
                                 {4, V4}, {5, V5}, {6, V6}};
}  // namespace volcart
