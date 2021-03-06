/*
 * Copyright (C) 2020 The AXiG Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.

 * File: MouseTest.cpp
 * Version: 1.00
 * Author: Herbert H. <bgameapp@gmail.com>
 * Date: 2020/6/26
  */

#include <stdio.h>
#include <conio.h>
#include "SerialPort.h"
#include "CH9329.h"

#define DEFAULTSERIALPORT	"COM4"
#define BAUDRATE			115200

const char Help[] = { "\n\r--------------------------------------------------------------\n\rAIxG UART2HID Mouse Test\n\r\n\r? - Show help\n\rW - Move up\n\rS - Move down\n\rA - Move left\n\rD - Move right\n\r0 - Move to (1,1)\n\rESC - Quit\n\r--------------------------------------------------------------\n\r" };

int main(int argc, char** argv)
{
	HANDLE hcom = NULL;
	char c = 0;

	if (argc > 1)
		hcom = SerialPortOpen(argv[1], BAUDRATE);
	else
		hcom = SerialPortOpen(DEFAULTSERIALPORT, BAUDRATE);
	if (hcom == NULL)
		return -1;

	printf("%s\n", Help);

	while (c != 27) {
		c = _getch();
		switch (c) {
		case '?':
			printf("%s\n", Help);
			break;
		case 'w':
		case 'W':
			MouseRelative(hcom, 0, -20, 0, 0);
			break;
		case 's':
		case 'S':
			MouseRelative(hcom, 0, 20, 0, 0);
			break;
		case 'a':
		case 'A':
			MouseRelative(hcom, -20, 0, 0, 0);
			break;
		case 'd':
		case 'D':
			MouseRelative(hcom, 20, 0, 0, 0);
			break;
		case 'o':
		case 'O':
		case '0':
			MouseAbsolute(hcom, 1, 1, 0, 0);
			break;
		}
	}

	CloseHandle(hcom);
}
