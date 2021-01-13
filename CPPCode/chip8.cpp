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
			cout << "00E0" << endl;
			break;
		case 0x00EE:
			cout << "0x00EE" << endl; 
			break;
		default :
				cout << "0x0NNN" << endl; 
	}

};
void chip8::opcode1() {
	//possible opcodes 1 - 1NNN
	cout << "1NNN" << endl; 
};
void chip8::opcode2() {
	//possible opcodes 1 - 2NNN
	cout << "2NNN" << endl; 
};
void chip8::opcode3() {
	//possible opcodes 1 - 3XNN 
	cout << "3XNN" << endl; 
};
void chip8::opcode4() {
	//possible opcodes 4 - 4XNN 
	cout << "4XNN" << endl;
};
void chip8::opcode5() {
	//possible opcodes 1 - 5XY0 
	cout << "5XY0" << endl;
};
void chip8::opcode6() {
	//possible opcodes 1 - 6XNN 
	cout << "6XNN" << endl;
};
void chip8::opcode7() {
	//possible opcodes 1 - 7XNN
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
			cout << "8XY0" << endl;
			break;
		case 0x0001:
			cout << "8XY1" << endl;
			break; 
		case 0x0002:
			cout << "8XY2" << endl;
			break;
		case 0x0003:
			cout << "8XY3" << endl;
			break;
		case 0x0004:
			cout << "8XY4" << endl;
			break; 
		case 0x0005:
			cout << "8XY5" << endl;
			break; 
		case 0x0006:
			cout << "8XY6" << endl;
			break;
		case 0x0007:
			cout << "8XY7" << endl;
			break; 
		case 0x000E:
			cout << "8XYE" << endl;
			break; 
		default : 
			cout << "Unknown 8 opcode" << endl; 
	}
};
void chip8::opcode9() {
	//possible opcodes 1 - 9XY0
	cout << "9XY0" << endl;

};
void chip8::opcodeA() {
	//possible opcodes 1 - ANNN
	cout << "ANNN" << endl;
};
void chip8::opcodeB() {
	//possible opcodes 1 - BNNN 
	cout << "BNNN" << endl;
};
void chip8::opcodeC() {
	//possible opcodes 1 - CXNN 
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
			cout << "EX9E" << endl; 
			break; 
		case 0x00A1: 
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
		cout << "FX07" << endl;
		break;
	case 0x00A:
		cout << "FX0A" << endl;
		break;
	case 0x0015:
		cout << "FX15" << endl;
		break;
	case 0x0018:
		cout << "FX18" << endl;
		break;
	case 0x001E:
		cout << "FX1E" << endl;
		break;
	case 0x029:
		cout << "FX29" << endl;
		break;
	case 0x0033:
		cout << "FX33" << endl;
		break;
	case 0x0055:
		cout << "FX55" << endl;
		break;
	case 0x0065:
		cout << "FX65" << endl;
		break;
	default:
		cout << "Unknown 8 opcode" << endl;
	}
};

