#!/bin/bash

sudo cpupower frequency-set -g performance
sudo nice -n -20 RelWithDebInfo/hashtest
sudo RelWithDebInfo/hashtest
sensors # get CPU temperature
