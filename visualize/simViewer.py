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

numVCs = int(input("Enter the number of VC pairs"))

simulation_results = pd.read_csv(filepath, header=1)

AllVCSimResults = {}
for i in range(numVCs):
    VCSimResults = simulation_results.loc[(simulation_results['model_name'] == 'Helo') &
                                      (simulation_results['port_name'].isnull())]
    AllVCSimResults.update({"VC"+str(i):VCSimResults})

print(AllVCSimResults)
'''
heloRows = simulation_results.loc[(simulation_results['model_name'] == 'Helo') &
                                  (simulation_results['port_name'].isnull())]
heloRows = heloRows.reset_index()

dataAndTime = heloRows[['time', 'data']]
states = dataAndTime['data'].str.extractall('(?P<states>[<].+[>])').reset_index(drop = True)

states = states['states'].str.replace('<', '').str.replace('>', '').str.split(";", expand = True)
states.columns = heloStates
statesAndTime = pd.concat([dataAndTime['time'], states], axis=1)
timeText = 'TIME = '
time = 0
'''