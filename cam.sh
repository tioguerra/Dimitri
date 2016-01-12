#!/bin/sh
v4l2-ctl --set-ctrl white_balance_temperature_auto=0
v4l2-ctl --set-ctrl contrast=10
v4l2-ctl --set-ctrl saturation=45
v4l2-ctl --set-ctrl exposure_auto=1
v4l2-ctl --set-ctrl exposure_auto_priority=0
v4l2-ctl --set-ctrl white_balance_temperature=2800
v4l2-ctl --set-ctrl exposure_absolute=35
v4l2-ctl --set-ctrl hue=350
v4l2-ctl --set-ctrl gamma=115
v4l2-ctl --set-ctrl sharpness=100

# H_MIN=4
# H_MAX=11
# S_MIN=212
# S_MAX=256
# V_MIN=92
# V_MAX=256

