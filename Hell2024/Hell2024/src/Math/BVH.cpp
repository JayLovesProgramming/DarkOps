#include "BVH.hpp"
#include <bvh/v2/bvh.h>
#include <bvh/v2/vec.h>
#include <bvh/v2/ray.h>
#include <bvh/v2/node.h>
#include <bvh/v2/default_builder.h>
#include <bvh/v2/thread_pool.h>
#include <bvh/v2/executor.h>
#include <bvh/v2/stack.h>
#include <bvh/v2/tri.h>
#include <iostream>
#include "Timer.hpp"

// Type aliases for Bounding Volume Hierarchy (BVH) components
using Scalar = float;
using Vec3 = bvh::v2::Vec<Scalar, 3>;
using BBox = bvh::v2::BBox<Scalar, 3>;
using Tri = bvh::v2::Tri<Scalar, 3>;
using Node = bvh::v2::Node<Scalar, 3>;
using Bvh = bvh::v2::Bvh<Node>;
using BVHRay = bvh::v2::Ray<Scalar, 3>;
using PrecomputedTri = bvh::v2::PrecomputedTri<Scalar>;

namespace BVH
{
    // Global BVH and precomputed triangles to optimize ray intersection tests
    Bvh g_bvh;
    std::vector<PrecomputedTri> g_precomputed_tris;

    // Flag to enable primitive data permutation for faster traversal
    static constexpr bool should_permute = true;

    // Updates the Bounding Volume Hierarchy with new vertex data
    void UpdateBVH(std::vector<glm::vec3>& vertices)
    {
        // Performance timer for BVH construction
        Timer timer("bvh construction");

        // Convert input vertices to triangles
        std::vector<Tri> tris;
        tris.reserve(vertices.size());
        for (int i = 0; i < vertices.size(); i += 3)
        {
            tris.emplace_back(
                Vec3(vertices[i].x, vertices[i].y, vertices[i].z),
                Vec3(vertices[i + 1].x, vertices[i + 1].y, vertices[i + 1].z),
                Vec3(vertices[i + 2].x, vertices[i + 2].y, vertices[i + 2].z)
            );
        }

        // Set up multi-threaded execution for parallel processing
        bvh::v2::ThreadPool thread_pool;
        bvh::v2::ParallelExecutor executor(thread_pool);

        // Precompute bounding boxes and triangle centers in parallel
        std::vector<BBox> bboxes(tris.size());
        std::vector<Vec3> centers(tris.size());
        executor.for_each(0, tris.size(), [&](size_t begin, size_t end)
            {
                for (size_t i = begin; i < end; ++i)
                {
                    bboxes[i] = tris[i].get_bbox();
                    centers[i] = tris[i].get_center();
                }
            });

        // Configure BVH builder for high-quality acceleration structure
        typename bvh::v2::DefaultBuilder<Node>::Config config;
        config.quality = bvh::v2::DefaultBuilder<Node>::Quality::High;
        g_bvh = bvh::v2::DefaultBuilder<Node>::build(thread_pool, bboxes, centers, config);

        // Precompute triangles to optimize traversal
        g_precomputed_tris.resize(tris.size());
        executor.for_each(0, tris.size(), [&](size_t begin, size_t end)
            {
                for (size_t i = begin; i < end; ++i)
                {
                    // Optionally permute triangle order based on BVH structure
                    auto j = should_permute ? g_bvh.prim_ids[i] : i;
                    g_precomputed_tris[i] = tris[j];
                }
            });
    }

    // Performs ray intersection test against the entire geometry
    bool AnyHit(Ray& ray)
    {
        // Performance timer for ray traversal
        Timer timer("closest hit traversal");

        // Convert input ray to BVH ray representation
        BVHRay bvhRay = BVHRay{
            Vec3(ray.origin.x, ray.origin.y, ray.origin.z),          // Ray origin
            Vec3(ray.direction.x, ray.direction.y, ray.direction.z), // Ray direction
            ray.minDist,                                             // Minimum intersection distance
            ray.maxDist                                              // Maximum intersection distance
        };

        // Constants for ray intersection traversal
        static constexpr size_t invalid_id = std::numeric_limits<size_t>::max();
        static constexpr size_t stack_size = 64;
        static constexpr bool use_robust_traversal = false;

        // Variables to track intersection
        auto prim_id = invalid_id;
        Scalar u, v;

        // Traverse the BVH using a small stack-based approach
        bvh::v2::SmallStack<Bvh::Index, stack_size> stack;
        g_bvh.intersect<true, use_robust_traversal>(bvhRay, g_bvh.get_root().index, stack,
            [&](size_t begin, size_t end) {
                for (size_t i = begin; i < end; ++i)
                {
                    // Optionally use permuted primitive IDs
                    size_t j = should_permute ? i : g_bvh.prim_ids[i];
                    if (auto hit = g_precomputed_tris[j].intersect(bvhRay))
                    {
                        prim_id = i;
                        std::tie(u, v) = *hit;
                    }
                }
                return prim_id != invalid_id;
            });

        // Output intersection results
        if (prim_id != invalid_id)
        {
            std::cout
                << "Intersection found\n"
                << "  primitive: " << prim_id << "\n"
                << "  distance: " << bvhRay.tmax << "\n"
                << "  barycentric coords.: " << u << ", " << v << std::endl;
            return 0;
        }
        else
        {
            std::cout << "No intersection found" << std::endl;
            return 1;
        }
    }
}