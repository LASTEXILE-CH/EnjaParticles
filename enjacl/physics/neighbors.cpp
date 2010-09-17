#ifndef __NEIGHBORS_CL_K_
#define __NEIGHBORS_CL_K_

#include "cl_macros.h"
#include "cl_structures.h"

//----------------------------------------------------------------------
void ForNeighbor(__global float4*  var_sorted,
				__constant uint index_i,
				uint index_j,
				float4 r,
				float rlen,
				float rlen_sq,
	  			__constant struct GridParams* gp,
	  			__constant struct FluidParams* fp)
{
// the density sum using Wpoly6 kernel
//data.sum_density += SPH_Kernels::Wpoly6::Kernel_Variable(fp->smoothing_length_pow2, r, rlen_sq);	
// #include FILE to deal with collisions or other stuff
#include "cl_snippet_sphere_forces.h"
}
//--------------------------------------------------
void ForPossibleNeighbor(__global float4* var_sorted, 
						__constant uint numParticles, 
						__constant uint index_i, 
						uint index_j, 
						__constant float4 position_i,
	  					__constant struct GridParams* gp,
	  					__constant struct FluidParams* fp)
{
	// check not colliding with self
	if (index_j != index_i) {
		// get the particle info (in the current grid) to test against
		float4 position_j = FETCH_DENS(var_sorted, index_j); // uses numParticles

		// get the relative distance between the two particles, translate to simulation space
		float4 r = (position_i - position_j) * fp->scale_to_simulation;

		float rlen_sq = dot(r,r);
		// |r|
		float rlen;
		rlen = sqrt(rlen_sq);

		// is this particle within cutoff?
		if (rlen <= fp->smoothing_length) {
#if 1
			ForNeighbor(var_sorted, index_i, index_j, r, rlen, rlen_sq, gp, fp);
#endif
		}
	}
}
//--------------------------------------------------
#endif