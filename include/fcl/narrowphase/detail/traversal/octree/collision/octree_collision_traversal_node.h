/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011-2014, Willow Garage, Inc.
 *  Copyright (c) 2014-2016, Open Source Robotics Foundation
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Open Source Robotics Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/** @author Jia Pan */

#ifndef FCL_TRAVERSAL_OCTREE_OCTREECOLLISIONTRAVERSALNODE_H
#define FCL_TRAVERSAL_OCTREE_OCTREECOLLISIONTRAVERSALNODE_H

#include "fcl/config.h"
#if not(FCL_HAVE_OCTOMAP)
#error "This header requires fcl to be compiled with octomap support"
#endif

#include "fcl/geometry/octree/octree.h"
#include "fcl/narrowphase/detail/traversal/collision/collision_traversal_node_base.h"
#include "fcl/narrowphase/detail/traversal/octree/octree_solver.h"

namespace fcl
{

namespace detail
{

/// @brief Traversal node for octree collision
template <typename NarrowPhaseSolver>
class FCL_VISIBLE OcTreeCollisionTraversalNode
    : public CollisionTraversalNodeBase<typename NarrowPhaseSolver::S>
{
public:

  using S = typename NarrowPhaseSolver::S;

  OcTreeCollisionTraversalNode();

  bool BVTesting(int, int) const;

  void leafTesting(int, int) const;

  const OcTree<S>* model1;
  const OcTree<S>* model2;

  Transform3<S> tf1;
  Transform3<S> tf2;

  const OcTreeSolver<NarrowPhaseSolver>* otsolver;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

/// @brief Initialize traversal node for collision between two octrees, given
/// current object transform
template <typename NarrowPhaseSolver>
bool initialize(
    OcTreeCollisionTraversalNode<NarrowPhaseSolver>& node,
    const OcTree<typename NarrowPhaseSolver::S>& model1,
    const Transform3<typename NarrowPhaseSolver::S>& tf1,
    const OcTree<typename NarrowPhaseSolver::S>& model2,
    const Transform3<typename NarrowPhaseSolver::S>& tf2,
    const OcTreeSolver<NarrowPhaseSolver>* otsolver,
    const CollisionRequest<typename NarrowPhaseSolver::S>& request,
    CollisionResult<typename NarrowPhaseSolver::S>& result);

} // namespace detail
} // namespace fcl

#include "fcl/narrowphase/detail/traversal/octree/collision/octree_collision_traversal_node-inl.h"

#endif
