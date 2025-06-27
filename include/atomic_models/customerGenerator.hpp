#ifndef __CUSTOMER_GENERATOR_HPP__
#define __CUSTOMER_GENERATOR_HPP__

// This is an atomic model, meaning it has its' own internal logic/computation
// So, it is necessary to include atomic.hpp
#include "cadmium/modeling/devs/atomic.hpp"
#include <iostream>
#include <limits>
#include <assert.h>

using namespace std;

namespace cadmium::vendor_Space {
	
	//enum for representing the states
	enum class Customer_States {    
	Sending_Request,
	Acknowledged,
	Send_Money
	}; //end of the enum


	// Function to convert the enum for states to an enum to the corresponding string
	std::string enumToString(Customer_States state) {
		switch (state) {
			case Customer_States::Sending_Request:
				return "Sending_Request" ;

			case Customer_States::Acknowledged:
				return "Acknowledged" ;

			case Customer_States::Send_Money:
				return "Send_Money" ;

			default:
				return "invalid";
		}
	}

	struct CustomerState {

		// sigma is a mandatory variable, used to advance the time of the simulation
		double sigma;
		Customer_States ___current_state___;

		int product_bought;

		// Set the default values for the state constructor for this specific model
		CustomerState(): sigma(0), ___current_state___(Customer_States::Sending_Request), product_bought(0){};
	};

	std::ostream& operator<<(std::ostream &out, const CustomerState& state) {
		out << "[-|name|-]" << "Customer" << "[-|name|-]";
    	out << "[-|state|-]" << enumToString(state.___current_state___) << "[-|state|-]";
    	out << "[-|sigma|-]" << state.sigma << "[-|sigma|-]";
		out << "[-|product_bought|-]" << state.product_bought << "[-|product_bought|-]";
    	return out;
	}

	// Atomic model of Customer
	class Customer: public Atomic<CustomerState> {
		private:

		public:

			// Declare ports for the model

			Port<string> Vendor_Message;
        	Port<int> Product_Received;
        	Port<int> Money_Sent;

			// Declare variables for the model's behaviour

			/**
			 * Constructor function for this atomic model, and its respective state object.
			 *
			 * For this model, both a Customer object and a Customer object
			 * are created, using the same id.
			 *
			 * @param id ID of the new Customer model object, will be used to identify results on the output file
			 */
			Customer(const string& id, int initial_stock): Atomic<CustomerState>(id, CustomerState()) {

				// Initialize ports for the model
				Vendor_Message = addInPort<string>("Vendor_Message");
				Product_Received = addInPort<int>("Product_Received");

				Money_Sent = addOutPort<int>("Money_Sent");

				// Initialize variables for the model's behaviour
				state.___current_state___ = Customer_States::Sending_Request; //Initial state is Idle

				state.sigma = 5;
				
			}

			/**
			 * The transition function is invoked each time the value of
			 * state.sigma reaches 0.
			 *
			 * In this model, the value of state.lightOn is toggled.
			 *
			 * @param state reference to the current state of the model.
			 */
			void internalTransition(CustomerState& state) const override {
				state.sigma = 5;
				switch(state.___current_state___){
					case Customer_States::Sending_Request:
					// DOES NOT TRANSITION
						break;
					case Customer_States::Acknowledged:
						state.___current_state___ = Customer_States::Send_Money;
						break;
					case Customer_States::Send_Money:
					// DOES NOT TRANSITION
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
			void externalTransition(CustomerState& state, double e) const override {
				
				// First check if there are un-handled inputs for the "Customer_Request" port
				if(!Vendor_Message->empty()){

					// The variable x is created to handle the external input values in sequence.
					// The getBag() function is used to get the next input value.
					for( const auto x : Vendor_Message->getBag()){
						string msg_received = x;
						if (msg_received.compare("More Money Required") == 0){

						} else if (msg_received.compare("Enough Money Received") == 0){

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
			void output(const CustomerState& state) const override {
				switch(state.___current_state___){
					case Customer_States::Checking_Money:
						break;
					case Customer_States::Vending:
						Message_Customer->addMessage("Enough Money Received");
						break;
					case Customer_States::Checking_Stock:
						if (state.Customer_or_customer){
							Product_to_Customer->addMessage(1);
						} else {
							Product_to_Customer->addMessage(1);
						}
						break;
					case Customer_States::Sending_Product:
						break;
					case Customer_States::Idle:
						if (state.stock <= check_stock){
							Message_Customer->addMessage("Please Send Products");
						}
						break;
					case Customer_States::Requesting_Money:
						Message_Customer->addMessage("More Money Please");
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
			[[nodiscard]] double timeAdvance(const CustomerState& state) const override {
				return state.sigma;
			}
	};
};
#endif // __CUSTOMER_GENERATOR_HPP__