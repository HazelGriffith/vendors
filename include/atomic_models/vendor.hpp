#ifndef __VENDOR_HPP__
#define __VENDOR_HPP__

// This is an atomic model, meaning it has its' own internal logic/computation
// So, it is necessary to include atomic.hpp
#include "cadmium/modeling/devs/atomic.hpp"
#include <iostream>
#include <limits>
#include <assert.h>

using namespace std;

namespace cadmium::vendor_Space {
	
	//enum for representing the states
	enum class Vendor_States {    
	Idle, 
	Requesting_Money, 
	Checking_Money, 
	Vending, 
	Checking_Stock,
	Sending_Product

	}; //end of the enum


	// Function to convert the enum for states to an enum to the corresponding string
	std::string enumToString(Vendor_States state) {
		switch (state) {
			case Vendor_States::Idle:
				return "Idle" ;

			case Vendor_States::Requesting_Money:
				return "Requesting_Money" ;

			case Vendor_States::Checking_Money:
				return "Checking_Money" ;

			case Vendor_States::Vending:
				return "Vending" ;

			case Vendor_States::Checking_Stock:
				return "Checking_Stock" ;

			case Vendor_States::Sending_Product:
				return "Sending_Product" ;

			default:
				return "invalid";
		}
	}

	struct VendorState {

		// sigma is a mandatory variable, used to advance the time of the simulation
		double sigma;
		Vendor_States ___current_state___;

		int stock;
		int money_received;
		int products_requested;
		bool vendor_or_customer;

		// Set the default values for the state constructor for this specific model
		VendorState(): sigma(0), ___current_state___(Vendor_States::Idle), stock(0), money_received(0), products_requested(0), vendor_or_customer(false){};
	};

	std::ostream& operator<<(std::ostream &out, const VendorState& state) {
		out << "[-|name|-]" << "Vendor" << "[-|name|-]";
    	out << "[-|state|-]" << enumToString(state.___current_state___) << "[-|state|-]";
    	out << "[-|sigma|-]" << state.sigma << "[-|sigma|-]";
    	out << "[-|~:stock:~|-]" << state.stock << "[-|~:stock:~|-]";
		out << "[-|~:products_requested:~|-]" << state.products_requested << "[-|~:products_requested:~|-]";
    	out << "[-|~:money_received:~|-]" << state.money_received << "[-|~:money_received:~|-]";
		out << "[-|~:vendor_or_customer~|-]" << state.vendor_or_customer << "[-|~:vendor_or_customer:~|-]";

    	return out;
	}

	// Atomic model of Vendor
	class Vendor: public Atomic<VendorState> {
		private:

		public:

			// Declare ports for the model

			Port<int> Customer_Request;
        	Port<int> Vendor_Request;
        	Port<int> Money_Input;
			Port<int> Product_Input;
        	Port<string> Message_Customer;
       	 	Port<string> Message_Vendor;
       	 	Port<int> Product_to_Customer;
        	Port<int> Product_to_Vendor;

			// Declare variables for the model's behaviour
			int check_stock = 5;
			int cost = 1;

			/**
			 * Constructor function for this atomic model, and its respective state object.
			 *
			 * For this model, both a Vendor object and a Vendor object
			 * are created, using the same id.
			 *
			 * @param id ID of the new Vendor model object, will be used to identify results on the output file
			 */
			Vendor(const string& id, int initial_stock): Atomic<VendorState>(id, VendorState()) {

				// Initialize ports for the model
				Customer_Request = addInPort<int>("Customer_Request");
				Vendor_Request = addInPort<int>("Vendor_Request");
				Money_Input = addInPort<int>("Money_Input");
				Product_Input = addInPort<int>("Product_Input");
				Message_Customer = addOutPort<string>("Message_Customer");
				Message_Vendor = addOutPort<string>("Message_Vendor");
				Product_to_Customer = addOutPort<int>("Product_to_Customer");
				Product_to_Vendor = addOutPort<int>("Product_to_Vendor");

				// Initialize variables for the model's behaviour
				state.___current_state___ = Vendor_States::Idle; //Initial state is Idle
				state.stock = initial_stock;

				state.sigma = numeric_limits<double>::infinity();
				
			}

			/**
			 * The transition function is invoked each time the value of
			 * state.sigma reaches 0.
			 *
			 * In this model, the value of state.lightOn is toggled.
			 *
			 * @param state reference to the current state of the model.
			 */
			void internalTransition(VendorState& state) const override {
				state.sigma = 0;
				switch(state.___current_state___){
					case Vendor_States::Checking_Money:
						if (state.money_received < cost){
							state.___current_state___ = Vendor_States::Requesting_Money;
							state.sigma = numeric_limits<double>::infinity();
							// DEADLOCK
						} else {
							state.___current_state___ = Vendor_States::Vending;
							state.money_received = 0;
						}
						break;
					case Vendor_States::Vending:
						if (state.stock > 0){
							state.stock--;
							state.___current_state___ = Vendor_States::Checking_Stock;
							state.vendor_or_customer = false;
						}
						// DEADLOCK
						break;
					case Vendor_States::Checking_Stock:
						state.___current_state___ = Vendor_States::Idle;
						state.sigma = numeric_limits<double>::infinity();
						break;
					case Vendor_States::Sending_Product:
						if (state.stock > 0){
							state.stock--;
							state.___current_state___ = Vendor_States::Checking_Stock;
							state.vendor_or_customer = true;
						}
						// DEADLOCK
						break;
					case Vendor_States::Idle:
						// Passive
						break;
					case Vendor_States::Requesting_Money:
						// sends request for money to customer after they requested a product
						break;
					default:
						assert(("Not a valid state", false));
						break;
				}
				
			}

			/**
			 * The external transition function is invoked each time external data
			 * is sent to an input port for this model.
			 *
			 * In this model, the value of state.fastToggle is toggled each time the
			 * button connected to the "in" port is pressed.
			 *
			 * The value of state.sigma is then updated depending on the value of
			 * state.fastToggle.  Sigma is not required to be updated in this function,
			 * but we are changing it based on our desired logic for the program.
			 *
			 * @param state reference to the current model state.
			 * @param e time elapsed since the last state transition function was triggered.
			 */
			void externalTransition(VendorState& state, double e) const override {

				if (state.___current_state___ == Vendor_States::Idle){
					// First check if there are un-handled inputs for the "Customer_Request" port
					if(!Customer_Request->empty()){

						// The variable x is created to handle the external input values in sequence.
						// The getBag() function is used to get the next input value.
						for( const auto x : Customer_Request->getBag()){
							if (x > 0){
								state.products_requested = x;
							} else {
								assert(("Must be greater than 0 products requested", false));
							}
							state.___current_state___ = Vendor_States::Requesting_Money;
						}

					}

					// First check if there are un-handled inputs for the "Customer_Request" port
					if(!Vendor_Request->empty()){

						// The variable x is created to handle the external input values in sequence.
						// The getBag() function is used to get the next input value.
						for( const auto x : Vendor_Request->getBag()){
							if (x > 0){
								state.products_requested = x;
							} else {
								assert(("Must be greater than 0 products requested", false));
							}
							state.___current_state___ = Vendor_States::Sending_Product;
						}

					}
				}

				if (state.___current_state___ == Vendor_States::Requesting_Money){
					// First check if there are un-handled inputs for the "Customer_Request" port
					if(!Money_Input->empty()){

						// The variable x is created to handle the external input values in sequence.
						// The getBag() function is used to get the next input value.
						for( const auto x : Money_Input->getBag()){
							if (x > 0){
								state.money_received += x;
							} else {
								assert(("Must be greater than 0 dollars received", false));
							}
							state.___current_state___ = Vendor_States::Checking_Money;
						}

					}
				}
				
				// First check if there are un-handled inputs for the "Customer_Request" port
				if(!Product_Input->empty()){

					// The variable x is created to handle the external input values in sequence.
					// The getBag() function is used to get the next input value.
					for( const auto x : Product_Input->getBag()){
						if (x > 0){
							state.stock += x;
						} else {
							assert(("Must be greater than 0 products received", false));
						}
						
					}
				}

			}

			/**
			 * This function outputs any desired state values to their associated ports.
			 *
			 * In this model, the value of state.lightOn is sent via the out port.  Once
			 * the value of state.ligthOn reaches the I/O model, that model will update
			 * the status of the LED.
			 *
			 * @param state reference to the current model state.
			 */
			void output(const VendorState& state) const override {
				switch(state.___current_state___){
					case Vendor_States::Checking_Money:
						break;
					case Vendor_States::Vending:
						Message_Customer->addMessage("Enough Money Received");
						break;
					case Vendor_States::Checking_Stock:
						if (state.vendor_or_customer){
							Product_to_Vendor->addMessage(1);
						} else {
							Product_to_Customer->addMessage(1);
						}
						break;
					case Vendor_States::Sending_Product:
						break;
					case Vendor_States::Idle:
						if (state.stock <= check_stock){
							Message_Vendor->addMessage("Please Send Products");
						}
						break;
					case Vendor_States::Requesting_Money:
						Message_Customer->addMessage("More Money Required");
						break;
					default:
						assert(("Not a valid state", false));
						break;
				}
			}

			/**
			 * It returns the value of state.sigma for this model.
			 *
			 * This function is the same for all models, and does not need to be changed.
			 *
			 * @param state reference to the current model state.
			 * @return the sigma value.
			 */
			[[nodiscard]] double timeAdvance(const VendorState& state) const override {
				return state.sigma;
			}
	};
};
#endif // __VENDOR_HPP__