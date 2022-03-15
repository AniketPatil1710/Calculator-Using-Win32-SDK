#include <windows.h>

#define BUTTON_0 100
#define BUTTON_1 101
#define BUTTON_2 102
#define BUTTON_3 103
#define BUTTON_4 104
#define BUTTON_5 105
#define BUTTON_6 106
#define BUTTON_7 107
#define BUTTON_8 108
#define BUTTON_9 109
#define BUTTON_C 110
#define BUTTON_P 111
#define BUTTON_M 112
#define BUTTON_X 113
#define BUTTON_D 114
#define BUTTON_E 115

RECT rc;
PAINTSTRUCT ps;
HPEN pen, oldpen;
HDC hdc;
HBRUSH hBrush;
void GetText(HWND hWnd, char* cBuf, int nBufLen)
{

	SendMessage(hWnd, WM_GETTEXT, (long)nBufLen, (LPARAM)(LPCSTR)cBuf);
}

// Set text to any edit/hWnd
void SetText(HWND hWnd, char* cBuf) //1

{
	SendMessage(hWnd, WM_SETTEXT, NULL, (LPARAM)(LPCSTR)cBuf);
}
int Div(double dNum1, double dNum2)
{
	return (int)(dNum1 / dNum2);
}

// Get the remainder of an integer division of two numbers
double Mod(double dNum1, double dNum2)
{
	return (double)(dNum1 - (dNum2 * Div(dNum1, dNum2)));
}


// Define buttons

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg, WPARAM wParam, LPARAM lParam);
HWND SetUpWindow(char* cClass, char* cTitle, int nWidth, int nHeight, HINSTANCE hInstance);

HWND hWndMe,	// Window
	hB0,		// Buttons
	hB1,
	hB2,
	hB3,
	hB4,
	hB5,
	hB6,
	hB7,
	hB8,
	hB9,
	hBC,
	hBP,
	hBM,
	hBX,
	hBD,
	hBE,
	hE1;		// Edit

// Function in use:
// 0 = None
// 1 = Add
// 2 = Subtract
// 3 = Multiply
// 4 = Divide
int nFunc = 0;
int nNew = 1;	// New/continuing digits
long lTotal = 0;// Current buffer total
char cBuf[10];	// char buffer

void CreateButton(HINSTANCE);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	
	MSG msg;
	TCHAR szAppName[] = TEXT("My Application");

	WNDCLASSEX wClass;
	HWND hWnd;

	wClass.cbSize = sizeof(wClass);
	wClass.style = CS_HREDRAW | CS_VREDRAW;
	wClass.lpfnWndProc = WndProc;				// Message Handler Procedure
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	wClass.hInstance = hInstance;
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = szAppName;
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wClass);

	hWndMe = CreateWindow(szAppName,
		TEXT("Calculator:-By Aniket") ,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		490,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);

	


	CreateButton( hInstance);

	/*hB0 = CreateWindow("button", "0", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 440, 100, 100, hWndMe, (HMENU)BUTTON0, hInstance, NULL);
	hB1 = CreateWindow("button", "1", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 340, 100, 100, hWndMe, (HMENU)BUTTON1, hInstance, NULL);
	hB2 = CreateWindow("button", "2", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 340, 100, 100, hWndMe, (HMENU)BUTTON2, hInstance, NULL);
	hB3 = CreateWindow("button", "3", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 220, 340, 100, 100, hWndMe, (HMENU)BUTTON3, hInstance, NULL);
	hB4 = CreateWindow("button", "4", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 240, 100, 100, hWndMe, (HMENU)BUTTON4, hInstance, NULL);
	hB5 = CreateWindow("button", "5", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 240, 100, 100, hWndMe, (HMENU)BUTTON5, hInstance, NULL);
	hB6 = CreateWindow("button", "6", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 220, 240, 100, 100, hWndMe, (HMENU)BUTTON6, hInstance, NULL);
	hB7 = CreateWindow("button", "7", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 140, 100, 100, hWndMe, (HMENU)BUTTON7, hInstance, NULL);
	hB8 = CreateWindow("button", "8", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 140, 100, 100, hWndMe, (HMENU)BUTTON8, hInstance, NULL);
	hB9 = CreateWindow("button", "9", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 220, 140, 100, 100, hWndMe, (HMENU)BUTTON9, hInstance, NULL);
	hBC = CreateWindow("button", "C", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 220, 440, 100, 100, hWndMe, (HMENU)BUTTONC, hInstance, NULL);
	hBP = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 140, 100, 100, hWndMe, (HMENU)BUTTONP, hInstance, NULL);
	hBM = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 240, 100, 100, hWndMe, (HMENU)BUTTONM, hInstance, NULL);
	hBX = CreateWindow("button", "X", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 340, 100, 100, hWndMe, (HMENU)BUTTONX, hInstance, NULL);
	hBD = CreateWindow("button", "/", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 440, 100, 100, hWndMe, (HMENU)BUTTOND, hInstance, NULL);
	hBE = CreateWindow("button", "=", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 440, 100, 100, hWndMe, (HMENU)BUTTONE, hInstance, NULL);
	hE1 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | ES_MULTILINE, 20, 20, 440, 100, hWndMe, NULL, hInstance, NULL);
	*/
	// Clear buffer and display 0
	cBuf[0] = 0;
	SetText(hE1, "0");

	// Show windows
	ShowWindow(hWndMe,iCmdShow);	// Window
	ShowWindow(hB0,iCmdShow);		// Buttons
	ShowWindow(hB1,iCmdShow);
	ShowWindow(hB2,iCmdShow);
	ShowWindow(hB3,iCmdShow);
	ShowWindow(hB4,iCmdShow);
	ShowWindow(hB5,iCmdShow);
	ShowWindow(hB6,iCmdShow);
	ShowWindow(hB7,iCmdShow);
	ShowWindow(hB8,iCmdShow);
	ShowWindow(hB9,iCmdShow);
	ShowWindow(hBC,iCmdShow);
	ShowWindow(hBP,iCmdShow);
	ShowWindow(hBM,iCmdShow);
	ShowWindow(hBX,iCmdShow);
	ShowWindow(hBD,iCmdShow);
	ShowWindow(hBE,iCmdShow);
	ShowWindow(hE1,iCmdShow);		// Edit

	UpdateWindow(hWndMe);				// Update window

	// Receive messages
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
		case WM_CREATE:
			
			break;
		case WM_DESTROY:				// Program closed
		{
			PostQuitMessage(0);
			return 0;
			break;
		}
		case WM_COMMAND:				// Object Messages
		{
			switch(LOWORD(wParam))
			{
				case BUTTON_0:			// BUTTON0 clicked
				{
					// If new digits
					// -Empty char buffer and clear edit
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					// If the length of the char buffer is greater than 0 and less than 5
					// -Add "0" to the end of the char buffer and display
					if ((strlen(cBuf) > 0) && (strlen(cBuf) < 5))
					{
						strcat(&cBuf[0], "0");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_1:			// BUTTON1 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					if (strlen(cBuf) < 5)
					{
						strcat(&cBuf[0], "1");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_2:			// BUTTON2 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					if (strlen(cBuf) < 5)
					{
						strcat(&cBuf[0], "2");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_3:			// BUTTON3 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					if (strlen(cBuf) < 5)
					{
						strcat(&cBuf[0], "3");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_4:			// BUTTON4 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					if (strlen(cBuf) < 5)
					{
						strcat(&cBuf[0], "4");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_5:			// BUTTON5 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					if (strlen(cBuf) < 5)
					{
						strcat(&cBuf[0], "5");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_6:			// BUTTON6 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					if (strlen(cBuf) < 5)
					{
						strcat(&cBuf[0], "6");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_7:			// BUTTON7 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					if (strlen(cBuf) < 5)
					{
						strcat(&cBuf[0], "7");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_8:			// BUTTON8 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					if (strlen(cBuf) < 5)
					{
						strcat(&cBuf[0], "8");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_9:			// BUTTON9 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetText(hE1, cBuf);
						nNew = 0;
					}

					if (strlen(cBuf) < 5)
					{
						strcat(&cBuf[0], "9");
						SetText(hE1, cBuf);
					}
					break;
				}
				case BUTTON_C:			// BUTTONC clicked
				{
					lTotal = 0;			// Clear total
					cBuf[0] = 0;		// Clear char buffer
					SetText(hE1, "0");	// Display zero
					nNew = 1;			// Set new digit
					nFunc = 0;			// set function to none
					break;
				}
				case BUTTON_P:			// BUTTONP clicked
				{
					switch (nFunc)
					{
						case 0:			// If function is set to none
						{
							// Fill buffer and set to total
							GetText(hE1, cBuf, 10);
							lTotal = atol(cBuf);
							break;
						}
						case 1:			// If function is set to add
						{
							// Fill buffer and add to total
							GetText(hE1, cBuf, 10);
							lTotal += atol(cBuf);
							break;
						}
						case 2:			// If function is set to subtract
						{
							// Fill buffer and subtract from total
							GetText(hE1, cBuf, 10);
							lTotal -= atol(cBuf);
							break;
						}
						case 3:			// If function is set to multiply
						{
							// Fill buffer and multiply total by the value of the char buffer
							GetText(hE1, cBuf, 10);
							lTotal = lTotal * atol(cBuf);
							break;
						}
						case 4:			// If function is set to divide
						{
							// Fill buffer and divide total by the value of the char buffer
							GetText(hE1, cBuf, 10);
							lTotal = (long) Div((double) lTotal, (double) atol(cBuf));
							break;
						}
					}
					cBuf[0] = 0;			// Empty char buffer
					_ltoa(lTotal, cBuf, 10);// Fill buffer with total
					SetText(hE1, cBuf);		// Display total from buffer
					nNew = 1;				// Set new digit
					nFunc = 1;				// Set function to add
					break;
				}
				case BUTTON_M:			// BUTTONM clicked
				{
					switch (nFunc)
					{
						case 0:
						{
							GetText(hE1, cBuf, 10);
							lTotal = atol(cBuf);
							break;
						}
						case 1:
						{
							GetText(hE1, cBuf, 10);
							lTotal += atol(cBuf);
							break;
						}
						case 2:
						{
							GetText(hE1, cBuf, 10);
							lTotal -= atol(cBuf);
							break;
						}
						case 3:
						{
							GetText(hE1, cBuf, 10);
							lTotal = lTotal * atol(cBuf);
							break;
						}
						case 4:
						{
							GetText(hE1, cBuf, 10);
							lTotal = (long) Div((double) lTotal, (double) atol(cBuf));
							break;
						}
					}
					cBuf[0] = 0;
					_ltoa(lTotal, cBuf, 10);
					SetText(hE1, cBuf);
					nNew = 1;
					nFunc = 2;				// Set functtion to subtract
					break;
				}
				case BUTTON_X:			// BUTTONX clicked
				{
					switch (nFunc)
					{
						case 0:
						{
							GetText(hE1, cBuf, 10);
							lTotal = atol(cBuf);
							break;
						}
						case 1:
						{
							GetText(hE1, cBuf, 10);
							lTotal += atol(cBuf);
							break;
						}
						case 2:
						{
							GetText(hE1, cBuf, 10);
							lTotal -= atol(cBuf);
							break;
						}
						case 3:
						{
							GetText(hE1, cBuf, 10);
							lTotal = lTotal * atol(cBuf);
							break;
						}
						case 4:
						{
							GetText(hE1, cBuf, 10);
							lTotal = (long) Div((double) lTotal, (double) atol(cBuf));
							break;
						}
					}
					cBuf[0] = 0;
					_ltoa(lTotal, cBuf, 10);
					SetText(hE1, cBuf);
					nNew = 1;
					nFunc = 3;				// Set function to multiply
					break;
				}
				case BUTTON_D:			// BUTTOND clicked
				{
					switch (nFunc)
					{
						case 0:
						{
							GetText(hE1, cBuf, 10);
							lTotal = atol(cBuf);
							break;
						}
						case 1:
						{
							GetText(hE1, cBuf, 10);
							lTotal += atol(cBuf);
							break;
						}
						case 2:
						{
							GetText(hE1, cBuf, 10);
							lTotal -= atol(cBuf);
							break;
						}
						case 3:
						{
							GetText(hE1, cBuf, 10);
							lTotal = lTotal * atol(cBuf);
							break;
						}
						case 4:
						{
							GetText(hE1, cBuf, 10);
							lTotal = (long) Div((double) lTotal, (double) atol(cBuf));
							break;
						}
					}
					cBuf[0] = 0;
					_ltoa(lTotal, cBuf, 10);
					SetText(hE1, cBuf);
					nNew = 1;
					nFunc = 4;				// Set function to divide
					break;
				}
				case BUTTON_E:			// BUTTONE clicked
				{
					switch (nFunc)
					{
						case 0:
						{
							GetText(hE1, cBuf, 10);
							lTotal = atol(cBuf);
							break;
						}
						case 1:
						{
							GetText(hE1, cBuf, 10);
							lTotal += atol(cBuf);
							break;
						}
						case 2:
						{
							GetText(hE1, cBuf, 10);
							lTotal -= atol(cBuf);
							break;
						}
						case 3:
						{
							GetText(hE1, cBuf, 10);
							lTotal = lTotal * atol(cBuf);
							break;
						}
						case 4:
						{
							GetText(hE1, cBuf, 10);
							lTotal = (long) Div((double) lTotal, (double) atol(cBuf));
							break;
						}
					}
					cBuf[0] = 0;
					_ltoa(lTotal, cBuf, 10);
					SetText(hE1, cBuf);
					nNew = 1;
					nFunc = 0;				// Set function to none
					break;
				}
			}
			break;
		}
	}
	// Return message
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

// Create the window
/*HWND SetUpWindow(char* cClass, char* cTitle, int nWidth, int nHeight, HINSTANCE hInstance)
{
	WNDCLASSEX wClass;
	HWND hWnd;

	wClass.cbSize = sizeof(wClass);
	wClass.style = CS_HREDRAW | CS_VREDRAW;
	wClass.lpfnWndProc = WndProc;				// Message Handler Procedure
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	wClass.hInstance = hInstance;
	wClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = cClass;
	wClass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);

	RegisterClassEx(&wClass);

	hWnd = CreateWindow(cClass, cTitle, WS_OVERLAPPEDWINDOW, 0, 0, nWidth, nHeight, NULL, NULL, hInstance, NULL);

	return hWnd;
}*/

void CreateButton(HINSTANCE hInstance)
{
	hB0 = CreateWindow("button", "0", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 440, 100, 100, hWndMe, (HMENU)BUTTON_0, hInstance, NULL);
	hB1 = CreateWindow("button", "1", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 340, 100, 100, hWndMe, (HMENU)BUTTON_1, hInstance, NULL);
	hB2 = CreateWindow("button", "2", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 340, 100, 100, hWndMe, (HMENU)BUTTON_2, hInstance, NULL);
	hB3 = CreateWindow("button", "3", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 220, 340, 100, 100, hWndMe, (HMENU)BUTTON_3, hInstance, NULL);
	hB4 = CreateWindow("button", "4", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 240, 100, 100, hWndMe, (HMENU)BUTTON_4, hInstance, NULL);
	hB5 = CreateWindow("button", "5", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 240, 100, 100, hWndMe, (HMENU)BUTTON_5, hInstance, NULL);
	hB6 = CreateWindow("button", "6", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 220, 240, 100, 100, hWndMe, (HMENU)BUTTON_6, hInstance, NULL);
	hB7 = CreateWindow("button", "7", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 140, 100, 100, hWndMe, (HMENU)BUTTON_7, hInstance, NULL);
	hB8 = CreateWindow("button", "8", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 140, 100, 100, hWndMe, (HMENU)BUTTON_8, hInstance, NULL);
	hB9 = CreateWindow("button", "9", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 220, 140, 100, 100, hWndMe, (HMENU)BUTTON_9, hInstance, NULL);
	hBC = CreateWindow("button", "C", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 220, 440, 100, 100, hWndMe, (HMENU)BUTTON_C, hInstance, NULL);
	hBP = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 140, 100, 100, hWndMe, (HMENU)BUTTON_P, hInstance, NULL);
	hBM = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 240, 100, 100, hWndMe, (HMENU)BUTTON_M, hInstance, NULL);
	hBX = CreateWindow("button", "X", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 340, 100, 100, hWndMe, (HMENU)BUTTON_X, hInstance, NULL);
	hBD = CreateWindow("button", "/", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 440, 100, 100, hWndMe, (HMENU)BUTTON_D, hInstance, NULL);
	hBE = CreateWindow("button", "=", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 440, 100, 100, hWndMe, (HMENU)BUTTON_E, hInstance, NULL);
	hE1 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | ES_MULTILINE, 20, 20, 440, 100, hWndMe, NULL, hInstance, NULL);

}
