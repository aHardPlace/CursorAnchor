# CursorAnchor
Moves the cursor to an anchor point when a key is hit. Default is the center of the first screen.

## Usage
- **F2** records the current cursor position
- **F3** moves the cursor to the recorded position

Keys can be changed by modifying the GetAsyncKeyState() calls in CursorAnchor.cpp with any of the keycodes found here: [MSDN Virtual-Key Codes](https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731)

## Building
`$ make` includes an app icon.
`$ make simple` does not.
