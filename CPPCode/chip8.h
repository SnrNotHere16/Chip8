#pragma once
#ifndef chip8_H
#define chip8_H
#include <iostream>
using namespace std;

class chip8 {
	public:
		chip8();
		~chip8();
		void initialize(); 
		void emulateCycle(); 
		void loadGame(); 
		void setKeys(); 



	private:
		unsigned short opcode;
		unsigned char memory[4096];
		//registers (15 general purpose register, 1 for carry flag (Register 0xF))
		unsigned char V[16];  
		
		//index (register) and program counter 
		unsigned short I;
		unsigned short pc;
/*
		0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
		0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
		0x200-0xFFF - Program ROM and work RAM
*/
		unsigned char gfx[64 * 32];
		unsigned char delay_timer;
		unsigned char sound_timer;
		unsigned short stack[16];
		unsigned short sp;
		unsigned char key[16];


};
#endif 
