#include <windows.h>
#include <cstdlib>
#include <cstdio>

HWND mytext, button1 , input1, input2, button2, button3, button4;
char firstinput[100], secondinput[100];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE: {
			mytext = CreateWindowEx(0, "STATIC",
				"Please input two numbers",
				WS_CHILD | WS_VISIBLE,
				30, 20, 200, 25,
				hwnd, NULL, NULL, NULL
			);
			button1 = CreateWindowEx(0, "BUTTON",
				"+",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				70, 105, 20, 20,
				hwnd, (HMENU) 1, NULL, NULL
			);
			button2 = CreateWindowEx(0, "BUTTON",
				"-",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				95, 105, 20, 20,
				hwnd, (HMENU) 2, NULL, NULL
			);
			button3 = CreateWindowEx(0, "BUTTON",
				"*",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				120, 105, 20, 20,
				hwnd, (HMENU) 3, NULL, NULL
			);
			button4 = CreateWindowEx(0, "BUTTON",
				"/",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				145, 105, 20, 20,
				hwnd, (HMENU) 4, NULL, NULL
			);
			input1 = CreateWindowEx(0, "EDIT",
				"",
				WS_CHILD | WS_VISIBLE,
				40, 50, 160, 20,
				hwnd, NULL, NULL, NULL
			);
			input2 = CreateWindowEx(0, "EDIT",
				"",
				WS_CHILD | WS_VISIBLE,
				40, 75, 160, 20,
				hwnd, NULL, NULL, NULL
			);
			
			break;
		}
		
		case WM_COMMAND: {
			switch(LOWORD(wParam)) {
				case 1: {
					
					GetWindowText(input1, firstinput, 100);
					GetWindowText(input2, secondinput, 100);
					// plus 5
					float firstnum = std::atof(firstinput);
					float secondnum = std::atof(secondinput);
					float result = firstnum + secondnum;
					char resulttext[100];
					std::sprintf(resulttext, "%f", result);
					
					::MessageBox(hwnd, resulttext, "Result", MB_OK);
					break;
				}
				case 2: {
					
					GetWindowText(input1, firstinput, 100);
					GetWindowText(input2, secondinput, 100);
					// minus 5
					float firstnum = std::atof(firstinput);
					float secondnum = std::atof(secondinput);
					float result = firstnum - secondnum;
					char resulttext[100];
					std::sprintf(resulttext, "%f", result);
					
					::MessageBox(hwnd, resulttext, "Result", MB_OK);
					break;
				}
				
				case 3: {
					
					GetWindowText(input1, firstinput, 100);
					GetWindowText(input2, secondinput, 100);
					// times 5
					float firstnum = std::atof(firstinput);
					float secondnum = std::atof(secondinput);
					float result = firstnum * secondnum;
					char resulttext[100];
					std::sprintf(resulttext, "%f", result);
					
					::MessageBox(hwnd, resulttext, "Result", MB_OK);
					break;
				}
				
				case 4: {
					
					GetWindowText(input1, firstinput, 100);
					GetWindowText(input2, secondinput, 100);
					// divide 5
					float firstnum = std::atof(firstinput);
					float secondnum = std::atof(secondinput);
					if (secondnum == 0) {
						::MessageBox(hwnd, "Cannot divide by zero!", "Result", MB_OK | MB_ICONERROR);
						break;
					}
					float result = firstnum / secondnum;
					char resulttext[100];
					std::sprintf(resulttext, "%f", result);
					
					::MessageBox(hwnd, resulttext, "Result", MB_OK);
					break;
					
				}
			}

			break;
			
			
		}
		
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(120, 120, 240));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
