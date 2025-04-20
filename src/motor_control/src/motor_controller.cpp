#include "rclcpp/rclcpp.hpp"
#include <gpiod.h>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

class MotorController : public rclcpp::Node
{
public:
    MotorController() : Node("motor_controller_node")
    {
        RCLCPP_INFO(this->get_logger(), "Motor Controller Node Starting");

        // get gpio chip
        chip_ = gpiod_chip_open_by_name("gpiochip0");
        if (!chip_)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open GPIO chip");
            return;
        }

        // get line for right motor GPIO pin
        motor_right_line_ = gpiod_chip_get_line(chip_, MOTOR_RIGHT_GPIO_PIN);
        if (!motor_right_line_)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to get motor right GPIO line");
            return;
        }

        // get line for left motor GPIO pin
        motor_left_line_ = gpiod_chip_get_line(chip_, MOTOR_LEFT_GPIO_PIN);
        if (!motor_left_line_)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to get motor left GPIO line");
            return;
        }

        // reserve lines for the GPIO outputs
        gpiod_line_request_output(motor_right_line_, "motor_controller", 0);
        gpiod_line_request_output(motor_left_line_, "motor_controller", 0);

        // Start right motor
        gpiod_line_set_value(motor_right_line_, 1);
        RCLCPP_INFO(this->get_logger(), "Motor right ON");

        // Wait 2 seconds
        std::this_thread::sleep_for(2s);

        // Stop right motor
        gpiod_line_set_value(motor_right_line_, 0);
        RCLCPP_INFO(this->get_logger(), "Motor right OFF");

        // Wait 1 second
        std::this_thread::sleep_for(1s);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // Start left motor
        gpiod_line_set_value(motor_left_line_, 1);
        RCLCPP_INFO(this->get_logger(), "Motor left ON");

        // Wait 2 seconds
        std::this_thread::sleep_for(2s);

        // Stop left motor
        gpiod_line_set_value(motor_left_line_, 0);
        RCLCPP_INFO(this->get_logger(), "Motor left OFF");

        // Wait 1 second
        std::this_thread::sleep_for(1s);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // Start both motors
        gpiod_line_set_value(motor_left_line_, 1);
        gpiod_line_set_value(motor_right_line_, 1);
        RCLCPP_INFO(this->get_logger(), "Motor both ON");

        // Wait 2 seconds
        std::this_thread::sleep_for(2s);

        // Stop left motor
        gpiod_line_set_value(motor_left_line_, 0);
        gpiod_line_set_value(motor_right_line_, 0);
        RCLCPP_INFO(this->get_logger(), "Motor both OFF");
    }

    ~MotorController()
    {
        if (motor_right_line_)
        {
            gpiod_line_release(motor_right_line_);
        }
        if (motor_left_line_)
        {
            gpiod_line_release(motor_left_line_);
        }
        if (chip_)
        {
            gpiod_chip_close(chip_);
        }
    }

private:
    gpiod_chip *chip_;
    gpiod_line *motor_right_line_;
    gpiod_line *motor_left_line_;
    const int MOTOR_RIGHT_GPIO_PIN = 17;
    const int MOTOR_LEFT_GPIO_PIN = 22;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MotorController>());
    rclcpp::shutdown();
    return 0;
}