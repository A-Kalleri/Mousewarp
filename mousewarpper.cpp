#include <windows.h>

// Structure to hold screen dimensions
struct dimensions {
    int width;
    int height;
};

// Function to get the width and height of the primary display
dimensions getDimensions() {
    int width = GetSystemMetrics(SM_CXSCREEN);   // Get screen width
    int height = GetSystemMetrics(SM_CYSCREEN); // Get screen height

    return {width, height};
}

// Function to "warp" the mouse cursor to the opposite edge if it reaches the screen border
void warp(const dimensions& dim) {

    while (true) {

        POINT p;

        if (!GetCursorPos(&p)) {// Get current cursor position; skip if failed
            continue;
        }

        // If cursor is not at any edge, do nothing
        if (p.x > 0 && p.x < dim.width - 1 && p.y > 0 && p.y < dim.height - 1) {
            continue;
        }

        // If cursor is at the top edge, move it to the bottom
        if (p.y <= 0)
            SetCursorPos(p.x, dim.height - 1);
        // If cursor is at the bottom edge, move it to the top
        else if (p.y >= dim.height - 1)
            SetCursorPos(p.x, 0);
        // If cursor is at the left edge, move it to the right
        else if (p.x <= 0)
            SetCursorPos(dim.width - 1, p.y);
        // If cursor is at the right edge, move it to the left
        else if (p.x >= dim.width - 1)
            SetCursorPos(0, p.y);

        Sleep(50); // Sleep for 50 milliseconds to reduce CPU usage
    }
}

int main() {
    dimensions dim = getDimensions();   // Get screen dimensions
    warp(dim);                         // Start the mouse warp loop
    return 0;
}
