#!/usr/bin/env bash

lscpu | grep -i 'byte' | awk 'END {print $(NF-1), $NF}' | sed 's/ //g'
