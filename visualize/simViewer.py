#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jun 28 09:18:10 2025

@author: hazel
"""

import pandas as pd

vendor_states = ['Idle', 'Requesting_Money', 'Checking_Money', 'Vending', 'Checking_Stock', 'Sending_Product', 'invalid']
customer_states = ['Sending_Request', 'Acknowleged', 'Send_Money', 'invalid']


filepathBase = '../simulation_results/'

#filepathRemainder = input("Enter the csv file name: ")

filepath = filepathBase + 'results.csv'

numVCs = int(input("Enter the number of VC pairs: "))

simulation_results = pd.read_csv(filepath, header=1)

AllVCSimResults = {}

for i in range(numVCs):
    VCSimResults = simulation_results.loc[(simulation_results['model_name'] == "vendor"+str(i+1))]
    AllVCSimResults.update({"V"+str(i+1):VCSimResults})
    VCSimResults = simulation_results.loc[(simulation_results['model_name'] == "customer"+str(i+1))]
    AllVCSimResults.update({"C"+str(i+1):VCSimResults})
