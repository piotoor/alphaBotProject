#!/usr/bin/python
# -*- coding:utf-8 -*-
from InfraredLineTracker import InfraredLineTracker

# Simple example prints accel/mag data once per second:
if __name__ == '__main__':

    tracker = InfraredLineTracker()
    tracker.useSim(True)
    tracker.run()

