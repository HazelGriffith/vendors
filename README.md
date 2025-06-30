# Vendors model

## Description
This project uses the Cadmium v2 library to implement a DEVS model of multiple vendors selling products to customers while working in tandem to supply other vendors with products. It is intentionally designed to create deadlock problems where vendors are out of product and incapable of fullfilling customer orders, so they remain trapped in the vending state while customer's wait for a product that will never arrive.

## Installation
Follow the Cadmium V2 installation manual to setup the environment, then clone the repository and run "./build.sh" to create the "main.out" executable in the bin folder. 
If you run the executable with "./bin/main.out" it will run the default simulation with one vendor customer coupled model.
The results.csv file is stored in the simulation_results folder.

## Plans for the Future
-A python program to generate a graph mapping the state sequences of every simulation's model
