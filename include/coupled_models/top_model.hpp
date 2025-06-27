#ifndef __TOP_MODEL_HPP__
#define __TOP_MODEL_HPP__

// This is a coupled model, meaning it has no internal computation, and is
// used to connect atomic models.  So, it is necessary to include coupled.hpp
#include "cadmium/modeling/devs/coupled.hpp"
#include "cadmium/lib/iestream.hpp"
#include <iostream>
#include <string>
#include <cassert>

// We include any models that are directly contained within this coupled model
#include "VCCoupledModel.hpp"

// data structures

using namespace std;

namespace cadmium::vendor_Space {
    class Top_model : public Coupled {
        public:
        Top_model(const std::string& id): Coupled(id){

			// Declare the models
			shared_ptr<VCCoupled> VC = addComponent<VCCoupled>("vendor", 10);
			
            // Connect the models with coupling
			
        }
    };
} // namespace cadmium::vendor_Space

#endif // __TOP_MODEL_HPP__
