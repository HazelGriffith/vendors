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
#include "../atomic_models/vendor.hpp"
// data structures

using namespace std;

namespace cadmium::vendor_Space {
    class Top_model : public Coupled {
        public:
        Top_model(const std::string& id): Coupled(id){

			// Declare the models


			shared_ptr<Vendor> vendor = addComponent<Vendor>("vendor", 10);
            // Connect the models with coupling
			


			for (int i = 0; i < evacueeCoupledModels.size(); i++){
				for (int j = 0; j < heloCoupledModels.size(); j++){
					addCoupling(heloCoupledModels[j]->outEvac,evacueeCoupledModels[i]->in);
					addCoupling(evacueeCoupledModels[i]->outHelo,heloCoupledModels[j]->inEvac);
				}
				addCoupling(evacueeCoupledModels[i]->outFOL,fol->in);
				addCoupling(evacueeCoupledModels[i]->outES,evacuationSite->inEvac);
				addCoupling(evacuationSite->outEvac,evacueeCoupledModels[i]->in);
			}
			
			for (int i = 0; i < heloCoupledModels.size(); i++){
				addCoupling(heloCoupledModels[i]->outES,evacuationSite->inHelo);
				addCoupling(evacuationSite->outHelo,heloCoupledModels[i]->inES);
			}
			
        }
    };
} // namespace cadmium::vendor_Space

#endif // __TOP_MODEL_HPP__
