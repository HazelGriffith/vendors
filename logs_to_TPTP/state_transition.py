#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep  1 10:38:59 2025

@author: hazel
"""

class StateTransition:
    
    def __init__(self, currState: dict, nextState: dict):
        self.currState = currState
        self.nextState = nextState


    def printToTPTP(self, filename: str):
        currentState = self.currState.get('state')
        with open(filename, "a") as f:
            if (currentState == "Idle"):
                f.write("\n%-----Current state is Idle")
                f.write("\nfof(curr_state_is_i,axiom,\n\tcurr(i)).")
                if (self.nextState.get('products_requested') > 0):
                    f.write("\n%-----rcvd input from port customer request")
                    f.write("\nfof(rcvd_input_cr,axiom,\n\trcvd(cr)).")
            elif (currentState == "Requesting_Money"):
                f.write("\n%-----Current state is Requesting Money")
                f.write("\nfof(curr_state_is_rm,axiom,\n\tcurr(rm)).")
            elif (currentState == "Checking_Money"):
                f.write("\n%-----Current state is Checking Money")
                f.write("\nfof(curr_state_is_cm,axiom,\n\tcurr(cm)).")
            elif (currentState == "Vending"):
                f.write("\n%-----Current state is Vending")
                f.write("\nfof(curr_state_is_v,axiom,\n\tcurr(v)).")
            elif (currentState == "Checking_Stock"):
                f.write("\n%-----Current state is Checking Stock")
                f.write("\nfof(curr_state_is_cs,axiom,\n\tcurr(cs)).")
            elif (currentState == "Sending_Product"):
                f.write("\n%-----Current state is Sending Product")
                f.write("\nfof(curr_state_is_sp,axiom,\n\tcurr(sp)).")
            
        