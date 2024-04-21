#!/bin/bash

sudo cpupower frequency-set -g performance
sudo RelWithDebInfo/hashtest
sensors # get CPU temperature
