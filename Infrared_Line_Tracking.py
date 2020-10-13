#!/usr/bin/python
# -*- coding:utf-8 -*-
from InfraredLineTracker import InfraredLineTracker

import argparse

# Simple example prints accel/mag data once per second:
if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Run Infrared_Line_Tracking')
    parser.add_argument('-s', '--usesim', dest='useSim', action='store_true', help='Run the tracker with simulator')

    args = parser.parse_args()

    tracker = InfraredLineTracker()

    useSim = False
    if args.useSim:
        useSim=True
        print("Running tracker with the simulator")
    else:
        print("Running tracker with the alphaBot")

    tracker.useSim(useSim)
    tracker.run()

