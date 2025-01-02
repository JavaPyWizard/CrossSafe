#include <stdio.h>
#include <unistd.h> // For sleep function
#include <stdlib.h> // For system calls
#include <signal.h> // For handling graceful exit

void displayTrafficLight(const char *red, const char *yellow, const char *green, int timeLeft);
void trafficLightController();
void clearConsole();
void setTextColor(int color);
void handleSignal(int signal);

// Flag to simulate pedestrian button
int pedestrianCrossing = 0;

#define RED_COLOR 31    // Red text
#define YELLOW_COLOR 33 // Yellow text
#define GREEN_COLOR 32  // Green text
#define BUTTON_GREEN 32 // Green text for button
#define BUTTON_RED 31   // Red text for button
#define REDTIME 10      // Red light time
#define YELLOWTIME 5    // Yellow light time
#define GREENTIME 6     // Green light time

int main() 
{
    // Register signal handler for graceful exit
    signal(SIGINT, handleSignal);
    // Start the traffic light controller
    trafficLightController();

    return 0;
}

// Function to display the current state of the traffic light with a timer
void displayTrafficLight(const char *red, const char *yellow, const char *green, int timeLeft) 
{
    clearConsole();  // Clear the console screen before every update
    printf("Time Left: %02d seconds\n", timeLeft);
    printf("-------------------\n");

    // Display the Red light
    if (red == "ON") 
    {
        setTextColor(RED_COLOR);
    } 
    else 
    {
        setTextColor(0); // Default color for inactive lights
    }
    printf("RED    : %s\n", red);

    // Display the Yellow light
    if (yellow == "ON") 
    {
        setTextColor(YELLOW_COLOR);
    } 
    else 
    {
        setTextColor(0); // Default color for inactive lights
    }
    printf("YELLOW : %s\n", yellow);

    // Display the Green light
    if (green == "ON") 
    {
        setTextColor(GREEN_COLOR);
    } 
    else 
    {
        setTextColor(0); // Default color for inactive lights
    }
    printf("GREEN  : %s\n", green);

    // Reset color to default
    setTextColor(0);
    printf("-------------------\n");

    // Display pedestrian button status with color
    if (pedestrianCrossing) 
    {
        setTextColor(BUTTON_GREEN);
        printf("PEDESTRIAN BUTTON: ACTIVE\n");
    } 
    else 
    {
        setTextColor(BUTTON_RED);
        printf("PEDESTRIAN BUTTON: INACTIVE\n");
    }
    
    // Reset color to default
    setTextColor(0);
}

// Function to clear the console screen
void clearConsole() 
{
    printf("\033[2J\033[H"); 
}

// Function to set text color
void setTextColor(int color) 
{
    if (color) 
    {
        printf("\033[1;%dm", color); // Apply the color
    } 
    else 
    {
        printf("\033[0m"); // Reset to default color
    }
}

// Signal handler for graceful exit
void handleSignal(int signal) 
{
    printf("\nGracefully exiting the program...\n");
    exit(0); // Exit the program
}

// Traffic light controller function
void trafficLightController() 
{
    while (1) 
    {
        // Red Light with pedestrian crossing active
        for (int t = REDTIME; t > 0; t--) 
        {
            pedestrianCrossing = 1; // Pedestrian crossing is active during red light
            displayTrafficLight("ON", "OFF", "OFF", t);
            sleep(1);
        }

        // Yellow Light 
        for (int t = YELLOWTIME; t > 0; t--) 
        {
            pedestrianCrossing = 0; // Pedestrian crossing is inactive during yellow light
            displayTrafficLight("OFF", "ON", "OFF", t);
            sleep(1);
        }

        // Green Light 
        for (int t = GREENTIME; t > 0; t--) 
        {
            pedestrianCrossing = 0; // Pedestrian crossing is inactive during green light
            displayTrafficLight("OFF", "OFF", "ON", t);
            sleep(1);
        }
    }
}