/*Made by ac*/

#include <windows.h>
#include "susu.h"
#include "overlay.h"

void createSusuOverlay(HWND hWnd, int x, int y, int width, int height)
{
    // Create the susu overlay
    susu::SusuOverlay overlay(hWnd, x, y, width, height);

    // Create a loop to keep the overlay visible
    while (true)
    {
        // Draw the overlay
        overlay.draw();

        // Sleep for a short amount of time
        Sleep(100);
    }
}

int main()
{
    // Get the handle for the window
    HWND hWnd = GetActiveWindow();
    if (hWnd == NULL)
    {
        // Handle error
    }
    while (true)
    {
        // Create an instance of the SusuOverlay class
        SusuOverlay overlay(hWnd, 50, 50, 200, 100);

        // Draw the overlay
        overlay.draw();

        // Draw some text
        overlay.Text("Hello World!", 60, 60);

        // Draw a checkbox
        bool checked = true;
        overlay.Checkbox(&checked, 60, 80);

        // Draw a menu title
        overlay.MenuTitle("Menu", 60, 100);

        // Wait for user input
        getchar();
    }
    std::cin.ignore();
}
