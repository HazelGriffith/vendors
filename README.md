# Vendors model

## Description
This project uses the Cadmium v2 library to implement a DEVS model of multiple vendors selling products to customers while working in tandem to supply other vendors with products. It is intentionally designed to create deadlock problems where vendors are out of product and incapable of fullfilling customer orders, so they remain trapped in the vending state while customer's wait for a product that will never arrive.

## Installation
Follow the Cadmium V2 installation manual to setup the environment, then clone the repository and run "./build.sh" to create the "main.out" executable in the bin folder. 
If you run the executable with "./bin/main.out" it will run the default simulation with three vendor customer coupled models.
The results.csv file is stored in the simulation_results folder.

You can change the depth of the vendor network tree by providing it as the first integer argument when running the executable "main.out"
Ex: ./bin/main.out 3
The example will create a vendors tree of depth 3 with 7 total vendor and customer coupled models as shown below
Every vendor and customer coupled model (VC) is connected to the two other VCs directly above it such that every VC other than those at the top should have two VC models they can request products from.

                            VC      VC      VC
                                VC      VC
                                    VC

By adding a second integer argument to the executable you can specify the amount of stock every VC starts with.
Ex: ./bin/main.out 3 25
This example will create a vendors tree of depth 3 where each VC starts with 25 units in their stock.

## Plans for the Future
-A python program to generate a graph mapping the state sequences of every simulation's model
