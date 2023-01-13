/*Made by ac*/

/*every piece of code explaned*/

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

HDC hdc;
int x;
int y;
int width;
int height;
// susu namespace
namespace susu
{
    // susu struct used for drawing the overlay
    struct Overlay
    {
        int x;
        int y;
        int width;
        int height;
        HDC hdc;
        HWND hWnd;
    };

    // Class used for creating the susu overlay
    class SusuOverlay
    {
    public:
        // Constructor
        SusuOverlay(HWND hWnd, int x, int y, int width, int height);
        // Destructor
        ~SusuOverlay();
        // Draw the overlay
        void draw();  
    private:
        // Susu overlay struct
        Overlay overlay;
    };

    // Constructor
    SusuOverlay::SusuOverlay(HWND hWnd, int x, int y, int width, int height)
    {
        // Set the overlay properties
        overlay.x = x;
        overlay.y = y;
        overlay.width = width;
        overlay.height = height;
        overlay.hWnd = hWnd;

        // Get the device context for the window
        overlay.hdc = GetDC(overlay.hWnd);
        if (overlay.hdc == NULL)
        {
            // Handle error
        }
    }

    // Destructor
    SusuOverlay::~SusuOverlay()
    {
        // Release the device context
        if (!ReleaseDC(overlay.hWnd, overlay.hdc))
        {
            // Handle error
        }
    }

    // Draw the overlay
    void SusuOverlay::draw()
    {
        // Set the brush and pen colors
        HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
        if (brush == NULL)
        {
            // Handle error
        }
        HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        if (pen == NULL)
        {
            // Handle error
        }
        HGDIOBJ prevBrush = SelectObject(overlay.hdc, brush);
        if (prevBrush == NULL)
        {
            // Handle error
        }
        HGDIOBJ prevPen = SelectObject(overlay.hdc, pen);
        if (prevPen == NULL)
        {
            // Handle error
        }

        // Draw the rectangle
        if (!Rectangle(overlay.hdc, overlay.x, overlay.y, overlay.x + overlay.width, overlay.y + overlay.height))
        {
            // Handle error
        }

        // Restore the previous GDI objects
        if (!SelectObject(overlay.hdc, prevBrush))
        {
            // Handle error
        }
        if (!SelectObject(overlay.hdc, prevPen))
        {
            // Handle error
        }

        // Delete the GDI objects
        if (!DeleteObject(brush))
        {
            // Handle error
        }
        if (!DeleteObject(pen))
        {
            // Handle error
        }
    }
      

   
    
    
}


