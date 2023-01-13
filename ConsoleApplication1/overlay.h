#include <d3d9.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include "C:/Users/ac/source/repos/ConsoleApplication1/ConsoleApplication1/d3dx9.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// Struct used for the overlay
struct Overlay
{
    IDirect3DDevice9* device;
    ID3DXFont* font;
    ID3DXSprite* sprite;
    int x;
    int y;
    int width;
    int height;
    HWND hWnd;
};

// Class used for creating the overlay
class SusuOverlay
{
public:
    // Constructor
    SusuOverlay(HWND hWnd, int x, int y, int width, int height);
    // Destructor
    ~SusuOverlay();
    // Draw the overlay
    void draw();
    // Draw a text
    void Text(std::string text, int x, int y);
    // Draw a checkbox
    void Checkbox(bool* checked, int x, int y);
    // Draw a menu title
    void MenuTitle(std::string text, int x, int y);
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

    IDirect3DDevice9* device;

    // Initialize Direct3D
    if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, (IDirect3D9Ex**)&device)))
    {
        MessageBox(NULL, "Error initializing Direct3D", "Error", MB_OK);
        exit(1);
    }

    // Create the device
  //  D3DPRESENT_PARAMETERS d3dpp;
    //ZeroMemory(&d3dpp, sizeof(d3dpp));
    //d3dpp.Windowed = TRUE;
    //d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    //d3dpp.hDeviceWindow = overlay.hWnd;
    //if (FAILED(CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, overlay.hWnd,
      //  D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &overlay.device)))
    //{
      //  MessageBox(NULL, "Error creating the device", "Error", MB_OK);
       // exit(1);
    //}

    // Create the font
   // D3DXCreateFont(overlay.device, 14, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
     //   ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &overlay.font);

    // Create the sprite
   // D3DXCreateSprite(overlay.device, &overlay.sprite);
}

// Destructor
SusuOverlay::~SusuOverlay()
{
    // Release the objects
    overlay.font->Release();
    overlay.sprite->Release();
    overlay.device->Release();
}

// Draw the overlay
void SusuOverlay::draw()
{
    // Begin the scene
    overlay.device->BeginScene();

    // Set the current viewport
    D3DVIEWPORT9 viewport;
    viewport.X = 0;
    viewport.Y = 0;
    viewport.Width = overlay.width;
    viewport.Height = overlay.height;
    viewport.MinZ = 0.0f;
    viewport.MaxZ = 1.0f;
    overlay.device->SetViewport(&viewport);

    // Set the projection matrix
    D3DXMATRIX projection;
   // D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, (float)overlay.width, 0.0f, (float)overlay.height, 0.0f, 1.0f);
    overlay.device->SetTransform(D3DTS_PROJECTION, &projection);

    // Begin the sprite
    overlay.sprite->Begin(D3DXSPRITE_ALPHABLEND);

    // Draw the overlay
    RECT rect;
    SetRect(&rect, overlay.x, overlay.y, overlay.x + overlay.width, overlay.y + overlay.height);
    D3DXVECTOR3 position(0.0f, 0.0f, 0.0f);
    D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 0, 0);
    overlay.sprite->Draw(NULL, &rect, NULL, &position, color);

    // End the sprite
    overlay.sprite->End();

    // End the scene
    overlay.device->EndScene();

    // Present the back buffer
    overlay.device->Present(NULL, NULL, NULL, NULL);
}

// Draw a text
void SusuOverlay::Text(std::string text, int x, int y)
{
    // Convert the text to a wstring
    std::wstring wText(text.begin(), text.end());

    // Set the font color
    D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

    // Draw the text
    RECT rect;
    SetRect(&rect, x, y, overlay.width, overlay.height);
    overlay.font->DrawTextW(overlay.sprite, wText.c_str(), -1, &rect, DT_NOCLIP, fontColor);
}

// Draw a checkbox
void SusuOverlay::Checkbox(bool* checked, int x, int y)
{
    // Create variables for the checkbox locations
    int checkboxX = x;
    int checkboxY = y;
    int checkboxSize = 20;

    // Draw the checkbox
    RECT rect;
    SetRect(&rect, checkboxX, checkboxY, checkboxX + checkboxSize, checkboxY + checkboxSize);
    D3DXVECTOR3 position(0.0f, 0.0f, 0.0f);
    D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
    overlay.sprite->Draw(NULL, &rect, NULL, &position, color);

    // If the checkbox is checked, draw a checkmark
    if (*checked)
    {
        D3DXVECTOR2 lines[2];
        lines[0].x = (float)checkboxX;
        lines[0].y = (float)checkboxY;
        lines[1].x = (float)checkboxX + checkboxSize;
        lines[1].y = (float)checkboxY + checkboxSize;
        overlay.device->DrawPrimitiveUP(D3DPT_LINELIST, 1, lines, sizeof(D3DXVECTOR2));
    }
}

// Draw a menu title
void SusuOverlay::MenuTitle(std::string text, int x, int y)
{
    // Convert the text to a wstring
    std::wstring wText(text.begin(), text.end());

    // Set the font
    ID3DXFont* font;
  //  D3DXCreateFont(overlay.device, 18, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
    //    ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &font);

    // Set the font color
    D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

    // Draw the text
    RECT rect;
    SetRect(&rect, x, y, overlay.width, overlay.height);
//    font->DrawTextW(overlay.sprite, wText.c_str(), -1, &rect, DT_NOCLIP, fontColor);

    // Delete the font
  //  font->Release();
}