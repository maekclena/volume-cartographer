#pragma once

#include <boost/filesystem.hpp>

#include "vc/core/types/Metadata.hpp"

namespace volcart
{
/**
 * @class DiskBasedObjectBaseClass
 * @author Seth Parker
 *
 * @brief Base class for objects stored on disk with an associated metadata file
 *
 * Disk-based objects are meant to be used for objects stored inside of a
 * VolumePkg that need to be unique and identifiable, like Segmentations,
 * Renders, and Volumes. The goal of such objects is to make it easier to access
 * data from within the complex structure of a VolumePkg.
 *
 * As its name implies, a disk-based object is associated with a specific
 * file or directory on disk from which it loads and into which it saves data.
 * Derived classes are responsible for the process of updating this information.
 */
class DiskBasedObjectBaseClass
{
public:
    /** Default constructor */
    DiskBasedObjectBaseClass() = delete;

    /** @brief Identifier type */
    using Identifier = std::string;

    /** @brief Get the "unique" ID for the object */
    Identifier id() const { return metadata_.get<std::string>("uuid"); }

    /** @brief Get the path to the object */
    boost::filesystem::path path() const { return path_; }

    /** @brief Get the human-readable name for the object */
    std::string name() const { return metadata_.get<std::string>("name"); }

    /** @brief Update metadata on disk */
    void saveMetadata() { metadata_.save(); }

protected:
    /** Load the object from file */
    explicit DiskBasedObjectBaseClass(boost::filesystem::path path);

    /** Make a new object */
    DiskBasedObjectBaseClass(
        boost::filesystem::path path, Identifier uuid, std::string name);

    /** Metadata */
    volcart::Metadata metadata_;

    /** Location for the object on disk */
    boost::filesystem::path path_;
};
}
