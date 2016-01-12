#!/bin/sh
v4l2-ctl --set-ctrl white_balance_temperature_auto=0
v4l2-ctl --set-ctrl exposure_auto=1
v4l2-ctl --set-ctrl exposure_auto_priority=0
v4l2-ctl --set-ctrl white_balance_temperature=3000
v4l2-ctl --set-ctrl saturation=50
v4l2-ctl --set-ctrl exposure_absolute=25
v4l2-ctl --set-ctrl contrast=15
v4l2-ctl --set-ctrl hue=4000
v4l2-ctl --set-ctrl gamma=110
v4l2-ctl --set-ctrl sharpness=35

# H_MIN=4
# H_MAX=11
# S_MIN=212
# S_MAX=256
# V_MIN=92
# V_MAX=256

