#include "chip8.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// Public
/////////////////////////////////////////////////////////////////////////////////////////////
chip8::chip8() {}

chip8::~chip8() {}

void chip8:: initialize() {
	// Initialize registers and memory once
	pc = 0x200;  // Program counter starts at 0x200
	opcode = 0;      // Reset current opcode	
	I = 0;      // Reset index register
	sp = 0;      // Reset stack pointer

	// Clear display	
	// Clear stack
	// Clear registers V0-VF
	// Clear memory

	// Load fontset
	//for (int i = 0; i < 80; ++i)
	//	memory[i] = chip8_fontset[i];

	// Reset timers
}

void chip8::emulateCycle() {
	unsigned char MSNibble;
	// Fetch opcode
	opcode = memory[pc] << 8 | memory[pc + 1];

	// Decode opcode
	switch (opcode & 0xF000)
	{
		// Some opcodes //

	case 0x0000: // ANNN: Sets I to the address NNN
		opcode0(); 
		break;
	case 0x1000:
		opcode1();
		break; 
	case 0x2000:
		opcode2();
		break; 
	case 0x3000: 
		opcode3();
		break;
	case 0x4000:
		opcode4(); 
		break; 
	case 0x5000: 
		opcode5(); 
		break; 
	case 0x6000:
		opcode6(); 
		break; 
	case 0x7000:
		opcode7();
		break; 
	case 0x8000:
		opcode8();
		break; 
	case 0x9000:
		opcode9(); 
		break; 
	case 0xA000:
		opcodeA();
		break; 
	case 0xB000:
		opcodeB();
		break;
	case 0xC000:
		opcodeC();
		break; 
	case 0xD000:
		opcodeD();
		break; 
	case 0xE000:
		opcodeE();
		break; 
	case 0xF000:
		opcodeF();
	default:
		printf("Unknown opcode: 0x%X\n", opcode);
	}

	// Update timers
	if (delay_timer > 0)
		--delay_timer;

	if (sound_timer > 0)
	{
		if (sound_timer == 1)
			printf("BEEP!\n");
		--sound_timer;
	}
}

void chip8::loadGame() {
	//for (int i = 0; i < bufferSize; ++i)
	//	memory[i + 512] = buffer[i];
}

void chip8::setKeys() {}

/////////////////////////////////////////////////////////////////////////////////////////////
// Private 
/////////////////////////////////////////////////////////////////////////////////////////////

void chip8::opcode0() {
	//possible opcodes 3 - 0NNN, 00E0, 00EE
	switch (opcode)
	{
		case 0x00E0:
			cout << "00E0 clear screen" << endl;
			//clear the screen 
			break;
		case 0x00EE:
			cout << "0x00EE Return from subroutine" << endl; 
			//return from subroutine
			--sp;			// 16 levels of stack, decrease stack pointer to prevent overwrite
			pc = stack[sp];	// Put the stored return address from the stack back into the program counter					
			pc += 2;		// Don't forget to increase the program counter!
			break;
		default :
				cout << "0x0NNN" << endl; 
	}

};
void chip8::opcode1() {
	//possible opcodes 1 - 1NNN
	pc = opcode & 0x0FFF;
	cout << "1NNN" << endl; 

};
void chip8::opcode2() {
	//possible opcodes 1 - 2NNN, subroutine at  adress NNN
	stack[sp] = pc;
	++sp;
	pc = opcode & 0x0FFF;
	cout << "2NNN" << endl; 
};
void chip8::opcode3() {
	//possible opcodes 1 - 3XNN 
	if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
		pc += 4;
	else
		pc += 2;
	cout << "3XNN" << endl; 
};
void chip8::opcode4() {
	//possible opcodes 4 - 4XNN 
	if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
		pc += 4;
	else
		pc += 2;
	cout << "4XNN" << endl;
};
void chip8::opcode5() {
	//possible opcodes 1 - 5XY0 
	if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
		pc += 4;
	else
		pc += 2;
	cout << "5XY0" << endl;
};
void chip8::opcode6() {
	//possible opcodes 1 - 6XNN 
	V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF);
	pc += 2;
	cout << "6XNN" << endl;
};
void chip8::opcode7() {
	//possible opcodes 1 - 7XNN
	V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
	pc += 2;
	cout << "7XNN" << endl;
};
void chip8::opcode8() {
	/*possible opcodes 9 - 8XY0, 8XY1, 8XY2
						 - 8XY3, 8XY4, 8XY5 
						 - 8XY6, 8XY7, 8XYE
	
	*/
	switch (opcode & 0x000F)
	{
		case 0x0000:
			V[opcode & 0x0F00 >> 8] = V[opcode & 0x00F0 >> 4];
			pc += 2; 
			cout << "8XY0" << endl;
			break;
		case 0x0001:
			V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
			pc += 2;
			cout << "8XY1" << endl;
			break; 
		case 0x0002:
			V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
			pc += 2;
			cout << "8XY2" << endl;
			break;
		case 0x0003:
			V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
			pc += 2;
			cout << "8XY3" << endl;
			break;
		case 0x0004: // check
			if (V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8]))
				V[0xF] = 1; //carry
			else
				V[0xF] = 0;
			V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
			pc += 2;
			cout << "8XY4" << endl;
			break; 
		case 0x0005:
			if (V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8])
				V[0xF] = 0; // there is a borrow
			else
				V[0xF] = 1;
			V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
			pc += 2;
			cout << "8XY5" << endl;
			break; 
		case 0x0006:
			V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
			V[(opcode & 0x0F00) >> 8] >>= 1;
			pc += 2;
			cout << "8XY6" << endl;
			break;
		case 0x0007:
			if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4])	// VY-VX
				V[0xF] = 0; // there is a borrow
			else
				V[0xF] = 1;
			V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
			pc += 2;
			cout << "8XY7" << endl;
			break; 
		case 0x000E:
			V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
			V[(opcode & 0x0F00) >> 8] <<= 1;
			pc += 2;
			cout << "8XYE" << endl;
			break; 
		default : 
			cout << "Unknown 8 opcode" << endl; 
	}
};
void chip8::opcode9() {
	//possible opcodes 1 - 9XY0
	if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
		pc += 4;
	else
		pc += 2;
	cout << "9XY0" << endl;

};
void chip8::opcodeA() {
	//possible opcodes 1 - ANNN
	I = opcode & 0x0FFF;
	pc += 2;
	cout << "ANNN" << endl;
};
void chip8::opcodeB() {
	//possible opcodes 1 - BNNN 
	pc = (opcode & 0x0FFF) + V[0];
	cout << "BNNN" << endl;
};
void chip8::opcodeC() {
	//possible opcodes 1 - CXNN 
	V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
	pc += 2;
	cout << "CXNN" << endl;
};
void chip8::opcodeD() {
	//possible opcodes 1 - DXYN 
	cout << "DXYN" << endl;
};
void chip8::opcodeE() {
	//possible opcodes 2 - EX9E, EXA1 
	switch (opcode & 0x00FF)
	{
		case 0x009E: 
			if (key[V[(opcode & 0x0F00) >> 8]] != 0)
				pc += 4;
			else
				pc += 2;
			cout << "EX9E" << endl; 
			break; 
		case 0x00A1: 
			if (key[V[(opcode & 0x0F00) >> 8]] == 0)
				pc += 4;
			else
				pc += 2;
			cout << "EXA1" << endl; 
			break; 
		default: 
			cout << "Unknown E opcode" << endl; 
	}
};
void chip8::opcodeF() {
	/*possible opcodes 9 - FX07, FX0A, FX15
						 - FX18, FX1E, FX29
						 - FX33, FX55, FX65

	*/
	switch (opcode & 0x00FF)
	{
	case 0x007:
		V[(opcode & 0x0F00) >> 8] = delay_timer;
		pc += 2;
		cout << "FX07" << endl;
		break;
	case 0x00A:
		bool keyPress = false;

		for (int i = 0; i < 16; ++i)
		{
			if (key[i] != 0)
			{
				V[(opcode & 0x0F00) >> 8] = i;
				keyPress = true;
			}
		}

		// If we didn't received a keypress, skip this cycle and try again.
		if (!keyPress)
			return;

		pc += 2;
		cout << "FX0A" << endl;
		break;
	case 0x0015:
		delay_timer = V[(opcode & 0x0F00) >> 8];
		pc += 2;
		cout << "FX15" << endl;
		break;
	case 0x0018:
		sound_timer = V[(opcode & 0x0F00) >> 8];
		pc += 2;
		cout << "FX18" << endl;
		break;
	case 0x001E:
		if (I + V[(opcode & 0x0F00) >> 8] > 0xFFF)	// VF is set to 1 when range overflow (I+VX>0xFFF), and 0 when there isn't.
			V[0xF] = 1;
		else
			V[0xF] = 0;
		I += V[(opcode & 0x0F00) >> 8];
		pc += 2;
		cout << "FX1E" << endl;
		break;
	case 0x029:
		memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
		memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
		memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
		pc += 2;
		cout << "FX29" << endl;
		break;
	case 0x0033:
		memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
		memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
		memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
		pc += 2;
		cout << "FX33" << endl;
		break;
	case 0x0055:
		for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
			memory[I + i] = V[i];

		// On the original interpreter, when the operation is done, I = I + X + 1.
		I += ((opcode & 0x0F00) >> 8) + 1;
		pc += 2;
		cout << "FX55" << endl;
		break;
	case 0x0065:
		for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
			V[i] = memory[I + i];

		// On the original interpreter, when the operation is done, I = I + X + 1.
		I += ((opcode & 0x0F00) >> 8) + 1;
		pc += 2;
		cout << "FX65" << endl;
		break;
	default:
		cout << "Unknown 8 opcode" << endl;
	}
};

