#include "cadmium/simulation/root_coordinator.hpp"
#include <limits>
#include "cadmium/simulation/logger/csv.hpp"
#include <iostream>
#include <string>

#include "include/coupled_models/top_model.hpp"

using namespace cadmium::vendor_Space;

int main(int argc,char* argv[]){

    int depth = 2;
    int initial_stock_all = 10;
    

    if (argc > 3){
        assert((false, "Too many arguments"));
    } else if (argc == 3){
        std::string arg1(argv[1]);
        std::string arg2(argv[2]);

        try{
            depth = std::stoi(arg1);
        } catch(out_of_range e){
            assert(("Both arguments must be integers", false));
        }

        try{
            initial_stock_all = std::stoi(arg2);
        } catch(out_of_range e){
            assert(("Both arguments must be integers", false));
        }


    } else if (argc == 2){

        std::string arg1(argv[1]);
        try{
            depth = std::stoi(arg1);
        } catch(out_of_range e){
            assert(("Both arguments must be integers", false));
        }
        
    }

    // Declare and initialize the top model
    auto model = std::make_shared<Top_model>("top_model", initial_stock_all, depth);
    auto rootCoordinator = cadmium::RootCoordinator(model);
	
    //set the name of the output file
	rootCoordinator.setLogger<cadmium::CSVLogger>("simulation_results/results.csv",",");

    rootCoordinator.start();

    rootCoordinator.simulate(500.0);

    rootCoordinator.stop();
    return 0;
}
