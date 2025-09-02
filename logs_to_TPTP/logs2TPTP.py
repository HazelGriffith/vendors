#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep  1 10:00:34 2025

@author: hazel
"""
from state_transition import StateTransition
import pandas as pd
import re

vendor_states = ['Idle', 'Requesting_Money', 'Checking_Money', 'Vending', 'Checking_Stock', 'Sending_Product', 'invalid']
customer_states = ['Sending_Request', 'Acknowleged', 'Send_Money', 'invalid']
variable_names = ['state', 'sigma', 'stock', 'products_requested', 'money_received', 'vendor1_or_vendor2']

filepathBase = 'simulation_results/'

#filepathRemainder = input("Enter the csv file name: ")

filepath = filepathBase + 'results.csv'

numVCs = int(input("Enter the number of VC pairs: "))

# ----------- Step 1: Parse the DEVS Log File -----------
def extract_variable(data_str, varName):
    """Extract the DEVS variables from a data field."""
    match = re.search(r'\[-\|'+varName+'\|\-\](.*?)\[-\|'+varName+'\|\-\]', str(data_str))
    if match:
        return match.group(1).strip('_')
    return None

def parse_log(filepath):
    """Read and parse DEVS log file."""
    df = pd.read_csv(filepath, sep=',', header=1)
    for name in variable_names:
        df[name] = df['data'].apply(extract_variable, varName = name)
    return df

def build_state_transitions(modeldf):
    """initialize list of state transition objects for the given model"""
    times = list(set(map(int, modeldf['time'].tolist())))
    times.sort()
    state_transitions = []
    for i in range(len(times)-1):
        currdf = modeldf.loc[df['time'] == times[i]]
        assert(len(currdf)<=2)
        currStateDict = {'time': currdf['time'].tolist()[0]}
        if (len(currdf) > 0):
            currState = currdf.loc[currdf['port_name'].isnull()].head(1)
            for name in variable_names:
                currStateDict.update({name: currState[name].tolist()[0]})
        if (len(currdf) == 2):
            currExt = currdf.loc[currdf['port_name'].isnull() == False].head(1)
            if (len(currExt)>0):
                currStateDict.update({'port_name': currExt['port_name'].tolist()[0]})
                currStateDict.update({'data': currExt['data'].tolist()[0]})

        nextdf = modeldf.loc[df['time'] == times[i+1]]
        assert(len(nextdf)<=2)
        nextStateDict = {'time': nextdf['time'].tolist()[0]}
        if (len(nextdf) > 0):
            nextState = nextdf.loc[nextdf['port_name'].isnull()].head(1)
            for name in variable_names:
                nextStateDict.update({name: nextState[name].tolist()[0]})
        if (len(nextdf) == 2):
            nextExt = nextdf.loc[nextdf['port_name'].isnull() == False].head(1)
            if (len(nextExt) > 0):
                nextStateDict.update({'port_name': nextExt['port_name'].tolist()[0]})
                nextStateDict.update({'data': nextExt['data'].tolist()[0]})
        state_transitions.append(StateTransition(currStateDict, nextStateDict))

    return state_transitions

df = parse_log(filepath)

vendor1 = df.loc[df['model_name'] == 'vendor1']

state_transitions_v1 = build_state_transitions(vendor1)
