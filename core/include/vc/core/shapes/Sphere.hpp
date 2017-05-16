#pragma once

#include <string>
#include <unordered_map>

#include "ShapePrimitive.hpp"
#include "vc/core/vc_defines.hpp"

namespace volcart
{
namespace shapes
{
// clang-format off
/**
 * @author Melissa Shankle
 * @date 12/03/15
 *
 * @brief Icosphere shape
 *
 * This class generates an approximation of a sphere as a polyhedron by
 * recursively subdividing the triangles of an icosahedron.
 *
 * The recursion level defines the "smoothness" of the sphere. An icosphere with
 * recursion = 0 will have 20 triangular faces. Each additional level results in
 * a 4x increase in the number of faces over the previous level. For a recursion
 * level \f$r\f$, the number of faces in the sphere will be \f$ 20 * 4^{r}\f$.
 *
 * The radius parameter is not currently used.
 *
 * The shape will have a number of points equal to the number of faces in the
 * sphere (see above) plus two. The points generated by this class are
 * unordered.
 *
 * This implementation is an adaptation of
 * <a href="http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html">
 * an implementation by Andreas Kahler</a>.
 *
 * @ingroup Shapes
 */
// clang-format on
class Sphere : public ShapePrimitive
{
public:
    explicit Sphere(float radius = 5, int recursion = 2);

private:
    /** @brief Compute and cache the midpoint between two vertices */
    int midpoint_(int p1, int p2);

    /** @brief Vertex index cache
     *
     * Keeps track of vertices that have already been created by subdividing an
     * existing edge. Used to avoid creating duplicate vertices.
     */
    std::unordered_map<std::string, int> indexCache_;

};  // Sphere
}
}
