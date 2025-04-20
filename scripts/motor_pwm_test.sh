#!/bin/bash

# Set up PWM0 (Motor 1)
echo 0 | sudo tee /sys/class/pwm/pwmchip0/export
sleep 0.1
echo 50000 | sudo tee /sys/class/pwm/pwmchip0/pwm0/period

# Set up PWM1 (Motor 2)
echo 1 | sudo tee /sys/class/pwm/pwmchip0/export
sleep 0.1
echo 50000 | sudo tee /sys/class/pwm/pwmchip0/pwm1/period

# Function to set duty cycle for both motors
set_duty_cycle() {
    local duty_cycle=$1
    echo $duty_cycle | sudo tee /sys/class/pwm/pwmchip0/pwm0/duty_cycle
    echo $duty_cycle | sudo tee /sys/class/pwm/pwmchip0/pwm1/duty_cycle
}

# Enable both motors
echo 1 | sudo tee /sys/class/pwm/pwmchip0/pwm0/enable
echo 1 | sudo tee /sys/class/pwm/pwmchip0/pwm1/enable

# Set duty cycles and hold for 2 seconds each
echo "Running at 20%"
set_duty_cycle 10000
sleep 2

echo "Running at 50%"
set_duty_cycle 25000
sleep 2

echo "Running at 80%"
set_duty_cycle 40000
sleep 2

echo "Running at 100%"
set_duty_cycle 50000
sleep 2

# Turn off both motors
echo 0 | sudo tee /sys/class/pwm/pwmchip0/pwm0/enable
echo 0 | sudo tee /sys/class/pwm/pwmchip0/pwm1/enable

# Unexport (optional cleanup)
echo 0 | sudo tee /sys/class/pwm/pwmchip0/unexport
echo 1 | sudo tee /sys/class/pwm/pwmchip0/unexport

echo "Motors stopped and cleaned up."
