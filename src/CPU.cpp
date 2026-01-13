#include "CPU.h"
#include "Bus.h"

#include <iostream>

CPU::CPU()
{
	// Inizializza la lookup table.

	lookup = {
		{ "NOP", &CPU::NOP, &CPU::IMP, 1 },   { "LD", &CPU::LDIM, &CPU::REG, 3 },  { "LD", &CPU::LDA, &CPU::IMP, 2 },  { "INC", &CPU::IDO, &CPU::IMP, 2 }, { "INC", &CPU::INC, &CPU::IMP, 1 },   { "DEC", &CPU::DEC, &CPU::IMP, 1 }, { "LD", &CPU::LIR, &CPU::IMM, 2 },    { "RLCA", &CPU::RLCA, &CPU::IMP, 1 }, { "LD", &CPU::LSP, &CPU::REG, 5 },  { "ADD", &CPU::AHL, &CPU::IMP, 2 }, { "LD", &CPU::LAR, &CPU::IMP, 1 },  { "DEC", &CPU::DDO, &CPU::IMP, 2 }, { "INC", &CPU::INC, &CPU::IMP, 1 }, { "DEC", &CPU::DEC, &CPU::IMP, 1 }, { "LD", &CPU::LIR, &CPU::IMM, 2 },  { "RRCA", &CPU::RLCA, &CPU::IMP, 1 },
		{ "STOP", &CPU::STOP, &CPU::IMP, 1 }, { "LD", &CPU::LDIM, &CPU::REG, 3 },  { "LD", &CPU::LDA, &CPU::IMP, 2 },  { "INC", &CPU::IDO, &CPU::IMP, 2 }, { "INC", &CPU::INC, &CPU::IMP, 1 },   { "DEC", &CPU::DEC, &CPU::IMP, 1 }, { "LD", &CPU::LIR, &CPU::IMM, 2 },    { "RLA",&CPU::RLA, &CPU::IMP, 1 },    { "JR", &CPU::JR, &CPU::IMM, 3},    { "ADD", &CPU::AHL, &CPU::IMP, 2 }, { "LD", &CPU::LAR, &CPU::IMP, 1 },  { "DEC", &CPU::DDO, &CPU::IMP, 2 }, { "INC", &CPU::INC, &CPU::IMP, 1 }, { "DEC", &CPU::DEC, &CPU::IMP, 1 }, { "LD", &CPU::LIR, &CPU::IMM, 2 },  { "RRA", &CPU::RLCA, &CPU::IMP, 1 },
		{ "JR", &CPU::JR, &CPU::IMM, 3 },     { "LD", &CPU::LDIM, &CPU::REG, 3 },  { "LD", &CPU::LDA, &CPU::IMP, 2 },  { "INC", &CPU::IDO, &CPU::IMP, 2 }, { "INC", &CPU::INC, &CPU::IMP, 1 },   { "DEC", &CPU::DEC, &CPU::IMP, 1 }, { "LD", &CPU::LIR, &CPU::IMM, 2 },    { "DAA", &CPU::DAA, &CPU::IMP, 1 },   { "JR", &CPU::JR, &CPU::IMM, 3},    { "ADD", &CPU::AHL, &CPU::IMP, 2 }, { "LD", &CPU::LAR, &CPU::IMP, 1 },  { "DEC", &CPU::DDO, &CPU::IMP, 2 }, { "INC", &CPU::INC, &CPU::IMP, 1 }, { "DEC", &CPU::DEC, &CPU::IMP, 1 }, { "LD", &CPU::LIR, &CPU::IMM, 2 },  { "CPL", &CPU::CPL, &CPU::IMP, 1 },
		{ "JR", &CPU::JR, &CPU::IMM, 3 },     { "LD", &CPU::LDIM, &CPU::REG, 3 },  { "LD", &CPU::LDA, &CPU::IMP, 2 },  { "INC", &CPU::IDO, &CPU::IMP, 2 }, { "INC", &CPU::IHL, &CPU::IMP, 3 },   { "DEC", &CPU::DHL, &CPU::IMP, 3 }, { "LD", &CPU::LIR, &CPU::IMM, 2 },    { "SCF", &CPU::SCF, &CPU::IMP, 1 },   { "JR", &CPU::JR, &CPU::IMM, 3},    { "ADD", &CPU::AHL, &CPU::IMP, 2 }, { "LD", &CPU::LAR, &CPU::IMP, 1 },  { "DEC", &CPU::DDO, &CPU::IMP, 2 }, { "INC", &CPU::INC, &CPU::IMP, 1 }, { "DEC", &CPU::DEC, &CPU::IMP, 1 }, { "LD", &CPU::LIR, &CPU::IMM, 2 },  { "CCF", &CPU::CCF, &CPU::IMP, 1 },
		{ "LD", &CPU::LD, &CPU::IMP, 1 },     { "LD", &CPU::LD, &CPU::IMP, 1 },    { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },     { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 2 },     { "LD", &CPU::LD, &CPU::IMP, 1 },     { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 2 },   { "LD", &CPU::LD, &CPU::IMP, 1 },
		{ "LD", &CPU::LD, &CPU::IMP, 1 },     { "LD", &CPU::LD, &CPU::IMP, 1 },    { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },     { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 2 },     { "LD", &CPU::LD, &CPU::IMP, 1 },     { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 2 },   { "LD", &CPU::LD, &CPU::IMP, 1 },
		{ "LD", &CPU::LD, &CPU::IMP, 1 },     { "LD", &CPU::LD, &CPU::IMP, 1 },    { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },     { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 2 },     { "LD", &CPU::LD, &CPU::IMP, 1 },     { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 2 },   { "LD", &CPU::LD, &CPU::IMP, 1 },
		{ "LD", &CPU::LD, &CPU::IMP, 2 },     { "LD", &CPU::LD, &CPU::IMP, 2 },    { "LD", &CPU::LD, &CPU::IMP, 2 },   { "LD", &CPU::LD, &CPU::IMP, 2 },   { "LD", &CPU::LD, &CPU::IMP, 2 },     { "LD", &CPU::LD, &CPU::IMP, 2 },   { "HALT", &CPU::HALT, &CPU::IMP, 1 }, { "LD", &CPU::LD, &CPU::IMP, 2 },     { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 1 },   { "LD", &CPU::LD, &CPU::IMP, 2 },   { "LD", &CPU::LD, &CPU::IMP, 1 },
		{ "ADD", &CPU::ADD, &CPU::IMP, 1 },   { "ADD", &CPU::ADD, &CPU::IMP, 1 },  { "ADD", &CPU::ADD, &CPU::IMP, 1 }, { "ADD", &CPU::ADD, &CPU::IMP, 1 }, { "ADD", &CPU::ADD, &CPU::IMP, 1 },   { "ADD", &CPU::ADD, &CPU::IMP, 1 }, { "ADD", &CPU::ADD, &CPU::IMP, 2 },   { "ADD", &CPU::ADD, &CPU::IMP, 1 },   { "ADC", &CPU::ADC, &CPU::IMP, 1 }, { "ADC", &CPU::ADC, &CPU::IMP, 1 }, { "ADC", &CPU::ADC, &CPU::IMP, 1 }, { "ADC", &CPU::ADC, &CPU::IMP, 1 }, { "ADC", &CPU::ADC, &CPU::IMP, 1 }, { "ADC", &CPU::ADC, &CPU::IMP, 1 }, { "ADC", &CPU::ADC, &CPU::IMP, 2 }, { "ADC", &CPU::ADC, &CPU::IMP, 1 },
		{ "SUB", &CPU::SUB, &CPU::IMP, 1 },   { "SUB", &CPU::SUB, &CPU::IMP, 1 },  { "SUB", &CPU::SUB, &CPU::IMP, 1 }, { "SUB", &CPU::SUB, &CPU::IMP, 1 }, { "SUB", &CPU::SUB, &CPU::IMP, 1 },   { "SUB", &CPU::SUB, &CPU::IMP, 1 }, { "SUB", &CPU::SUB, &CPU::IMP, 2 },   { "SUB", &CPU::SUB, &CPU::IMP, 1 },   { "SBC", &CPU::SBC, &CPU::IMP, 1 }, { "SBC", &CPU::SBC, &CPU::IMP, 1 }, { "SBC", &CPU::SBC, &CPU::IMP, 1 }, { "SBC", &CPU::SBC, &CPU::IMP, 1 }, { "SBC", &CPU::SBC, &CPU::IMP, 1 }, { "SBC", &CPU::SBC, &CPU::IMP, 1 }, { "SBC", &CPU::SBC, &CPU::IMP, 2 }, { "SBC", &CPU::SBC, &CPU::IMP, 1 },
		{ "AND", &CPU::AND, &CPU::IMP, 1 },   { "AND", &CPU::AND, &CPU::IMP, 1 },  { "AND", &CPU::AND, &CPU::IMP, 1 }, { "AND", &CPU::AND, &CPU::IMP, 1 }, { "AND", &CPU::AND, &CPU::IMP, 1 },   { "AND", &CPU::AND, &CPU::IMP, 1 }, { "AND", &CPU::AND, &CPU::IMP, 2 },   { "AND", &CPU::AND, &CPU::IMP, 1 },   { "XOR", &CPU::XOR, &CPU::IMP, 1 }, { "XOR", &CPU::XOR, &CPU::IMP, 1 }, { "XOR", &CPU::XOR, &CPU::IMP, 1 }, { "XOR", &CPU::XOR, &CPU::IMP, 1 }, { "XOR", &CPU::XOR, &CPU::IMP, 1 }, { "XOR", &CPU::XOR, &CPU::IMP, 1 }, { "XOR", &CPU::XOR, &CPU::IMP, 2 }, { "XOR", &CPU::XOR, &CPU::IMP, 1 },
		{ "OR", &CPU::OR, &CPU::IMP, 1 },     { "OR", &CPU::OR, &CPU::IMP, 1 },    { "OR", &CPU::OR, &CPU::IMP, 1 },   { "OR", &CPU::OR, &CPU::IMP, 1 },   { "OR", &CPU::OR, &CPU::IMP, 1 },     { "OR", &CPU::OR, &CPU::IMP, 1 },   { "OR", &CPU::OR, &CPU::IMP, 2 },     { "OR", &CPU::OR, &CPU::IMP, 1 },     { "CP", &CPU::CP, &CPU::IMP, 1 },   { "CP", &CPU::CP, &CPU::IMP, 1 },   { "CP", &CPU::CP, &CPU::IMP, 1 },   { "CP", &CPU::CP, &CPU::IMP, 1 },   { "CP", &CPU::CP, &CPU::IMP, 1 },   { "CP", &CPU::CP, &CPU::IMP, 1 },   { "CP", &CPU::CP, &CPU::IMP, 2 },   { "CP", &CPU::CP, &CPU::IMP, 1 },
		{ "RET", &CPU::RET, &CPU::IMP, 2 },   { "POP", &CPU::POP, &CPU::IMP, 3 },  { "JP", &CPU::JP, &CPU::REG, 3 },   { "JP", &CPU::JP, &CPU::REG, 3 },   { "CALL", &CPU::CALL, &CPU::REG, 3 }, { "PUSH", &CPU::PUSH, &CPU::IMP, 4 },
		{ "RET", &CPU::RET, &CPU::IMP, 2 },   { "POP", &CPU::POP, &CPU::IMP, 3 },  { "JP", &CPU::JP, &CPU::REG, 3 },   { "-" },                            { "CALL", &CPU::CALL, &CPU::REG, 3 }, { "PUSH", &CPU::PUSH, &CPU::IMP, 4 },
		{ "LDH", &CPU::LDH, &CPU::IMM, 3 },   { "POP", &CPU::POP, &CPU::IMP, 3 },  { "LDH", &CPU::LDH, &CPU::IMP, 2 }, { "-" },                            { "-" },                              { "PUSH", &CPU::PUSH, &CPU::IMP, 4 }, {}, {}, {}, {"JP", &CPU::JP, &CPU::REG, 3},
		{ "LDH", &CPU::LDH, &CPU::IMM, 3 },   { "POP", &CPU::POP, &CPU::IMP, 3 },  { "LDH", &CPU::LDH, &CPU::IMP, 2 }, { "DI", &CPU::DI, &CPU::IMP, 1 },   { "-" },                              { "PUSH", &CPU::PUSH, &CPU::IMP, 4 }
	};
}

void CPU::set_registro(uint8_t n, uint8_t val)
{
	switch (n)
	{
	case 0:
		this->registri.a = val;
		break;
	case 1:
		this->registri.b = val;
		break;
	case 2:
		this->registri.c = val;
		break;
	case 3:
		this->registri.d = val;
		break;
	case 4:
		this->registri.e = val;
		break;
	case 5:
		this->registri.f = val;
		break;
	case 6:
		this->registri.h = val;
		break;
	case 7:
		this->registri.l = val;
		break;
	}
}

uint8_t CPU::get_registro(uint8_t n)
{
	switch (n)
	{
	case 0:
		return this->registri.a;
	case 1:
		return this->registri.b;
	case 2:
		return this->registri.c;
	case 3:
		return this->registri.d;
	case 4:
		return this->registri.e;
	case 5:
		return this->registri.f;
	case 6:
		return this->registri.h;
	case 7:
		return this->registri.l;
	}

	return 0x0;
}

// Imposta il valore di un registro "doppio". Se n è uguale a 0 imposta AF, se è 1 imposta BC,
// 2 imposta DE e 3 imposta HL.
void CPU::set_doppio_registro(uint8_t n, uint16_t val)
{
	switch (n)
	{
	case 0:
		this->registri.a = val >> 8;
		this->registri.f = val & 0xF0;
		break;
	case 1:
		this->registri.b = val >> 8;
		this->registri.c = val & 0xFF;
		break;
	case 2:
		this->registri.d = val >> 8;
		this->registri.e = val & 0xFF;
		break;
	case 3:
		this->registri.h = val >> 8;
		this->registri.l = val & 0xFF;
		break;
	}
}

// Restituisce il valore di un registro "doppio". Se n è uguale a 0 legge AF, se è 1 legge BC,
// 2 legge DE e 3 legge HL.
uint16_t CPU::get_doppio_registro(uint8_t n)
{
	switch (n)
	{
	case 0:
		return (this->registri.a << 8) | this->registri.f;
	case 1:
		return (this->registri.b << 8) | this->registri.c;
	case 2:
		return (this->registri.d << 8) | this->registri.e;
	case 3:
		return (this->registri.h << 8) | this->registri.l;
	}

	return 0x0;
}

// Funzioni per modificare le flags.

void CPU::set_carry(bool attivo)
{
	if (attivo)
		this->registri.f |= (1 << 4);
	else
		this->registri.f &= ~(1 << 4);
}

void CPU::set_half_carry(bool attivo)
{
	if (attivo)
		this->registri.f |= (1 << 5);
	else
		this->registri.f &= ~(1 << 5);
}

void CPU::set_subtract(bool attivo)
{
	if (attivo)
		this->registri.f |= (1 << 6);
	else
		this->registri.f &= ~(1 << 6);
}

void CPU::set_zero(bool attivo)
{
	if (attivo)
		this->registri.f |= (1 << 7);
	else
		this->registri.f &= ~(1 << 7);
}

void CPU::write(uint16_t addr, uint8_t data)
{
	bus->write(addr, data);
}

uint8_t CPU::read(uint16_t addr)
{
	return bus->read(addr);
}

// Per ora questa funzione rende l'emulazione non accurata dal punto di vista del clock. Infatti, questo metodo vede quanti cicli di clock sono richiesti
// per la funzione in questione e, ogni volta che viene richiamata, decrementa il contatore dei cicli. Una volta giunti a zero, fa quello che deve fare.
// Idealmente invece dovrebbe eseguire in un ciclo una parte di istruzione e nell'altro l'altra parte e così via...
void CPU::clock()
{
	if (cicli == 0)
	{
		opcode = read(pc);
		std::cout << "Opcode: " << opcode << " - ";

		pc++;

		std::cout << "Nome: " << lookup[opcode].nome << " - ";

		cicli = lookup[opcode].cicli;
		
		std::cout << "Cicli: " << cicli << std::endl;

		// Imposta l'addressing mode richiesta da questa istruzione.
		(this->*lookup[opcode].addrmode)();

		// Esegui l'operazione per questa istruzione.
		(this->*lookup[opcode].operazione)();
	}

	cicli--;
}

// Addressing Modes

// Implied: non sono necessari dati aggiuntivi per questa istruzione. L'istruzione farà qualcosa
// di molto semplice, come impostare un bit di stato. 
// Per ora fetched = registro A
void CPU::IMP()
{
	fetched = get_registro(0);
}

// Immediate: l'istruzione si aspetta che il valore da usare sia nei byte successivi.
void CPU::IMM()
{
	addr_assoluto = pc++;
}

// Register: vengono usati due valori (spesso registri) contenuti nei due byte successivi all'istruzione.
void CPU::REG()
{
	fetched = read(pc++);
	temp = read(pc++);
}

// Questo metodo prende i dati usati dall'istruzione e li memorizza in una variabile uint8_t.
// Per alcune istruzioni il dato è implicito nell'istruzione stessa.
uint8_t CPU::fetch()
{
	if (lookup[opcode].addrmode != &CPU::IMP)
		fetched = read(addr_assoluto);

	return fetched;
}

// OPCODES //
// 
// Riferimenti:
// https://gbdev.io/gb-opcodes/optables/
// https://gekkio.fi/files/gb-docs/gbctr.pdf

void CPU::NOP()
{
	// niente da fare...
}

void CPU::STOP()
{
	//todo...
	std::cout << "\nTODO\n";
}

// Incrementa un doppio registro.
void CPU::IDO()
{
	int registro = static_cast<int>(((opcode & 0b00110000) >> 4) + 1);
	
	// se registro == 4 allora bisogna gestire lo stack pointer

	set_doppio_registro(registro, get_doppio_registro(registro) + 1);
}

// Incrementa un registro (dedotto dai bit centrali dell'istruzione stessa).
void CPU::INC()
{
	int registro = static_cast<int>(((opcode & 0b00111000) >> 3) + 0b00000001);
	if (registro == 5 || registro == 6) registro += 1;
	if (registro == 8) registro = 0;

	set_registro(registro, get_registro(registro) + 1);

	set_zero(get_registro(registro) == 0);
	set_subtract(false);
	set_half_carry(((get_registro(registro) & 0x0F) + 1) & 0x10);
}

// Incrementa il valore in RAM posto all'indirizzo specificato in HL.
void CPU::IHL()
{
	write(get_doppio_registro(3), read(get_doppio_registro(3) + 1));

	set_zero(get_registro(3) == 0);
	set_subtract(false);
	set_half_carry(((read(get_doppio_registro(3)) & 0x0F) + 1) & 0x10);
}

// Decrementa un doppio registro.
void CPU::DDO()
{
	int registro = static_cast<int>(((opcode & 0b00110000) >> 4) + 1);

	// se registro == 4 allora bisogna gestire lo stack pointer

	set_doppio_registro(registro, get_doppio_registro(registro) - 1);
}

// Decrementa un registro (dedotto dai bit centrali dell'istruzione stessa).
void CPU::DEC()
{
	int registro = static_cast<int>(((opcode & 0b00111000) >> 3) + 0b00000001);
	if (registro == 5 || registro == 6) registro += 1;
	if (registro == 8) registro = 0;

	uint8_t vecchio = get_registro(registro);

	set_registro(registro, get_registro(registro) - 1);

	set_zero(get_registro(registro) == 0);
	set_subtract(true);
	set_half_carry((vecchio & 0x0F) == 0x00);
}

// Decrementa il valore in RAM posto all'indirizzo specificato in HL.
void CPU::DHL()
{
	write(get_doppio_registro(3), read(get_doppio_registro(3) - 1));

	set_zero(get_registro(3) == 0);
	set_subtract(false);
	set_half_carry(((read(get_doppio_registro(3)) & 0x0F) + 1) & 0x10);
}

// LD r8, r8 = copia il valore del registro di destra nel registro di sinistra. L'istruzione
// ha questo formato: 0b01xxxyyy dove xxx indica il registro di sinistra e yyy il registro
// di destra.
void CPU::LD()
{
	int a = static_cast<int>((opcode & 0b00111000) >> 3) + 1;
	int b = static_cast<int>(opcode & 0b00000111) + 1;

	if (b == 5 || b == 6) b++;
	else if (b == 7)
	{
		set_registro(a, read(get_registro(b)));
		return;
	}
	else if (b == 8) b = 0;

	if (a == 5 || a == 6) a++;
	else if (a == 7)
	{
		write(get_doppio_registro(3), get_registro(a));
		return;
	}
	else if (a == 8) a = 0;

	set_registro(a, get_registro(b));
}

// Carica un valore immediato in un registro "doppio". Il registro è dedotto dal byte dell'istruzione,
// mentre il valore di 16 bit viene passato attraverso le variabili fetched e temp.
void CPU::LDIM()
{
	int registro = static_cast<int>((opcode & 0b00110000) >> 4) + 1;
	
	// In questo caso va gestito lo stack pointer
	//if (registro == 4)

	uint16_t risultato = (uint16_t(static_cast<int>(fetched)) << 8) | static_cast<int>(temp);

	set_doppio_registro(registro, risultato);
}

// Copia il valore del registro A all'indirizzo di memoria specificato dal doppio registro.
void CPU::LDA()
{
	int registro = static_cast<int>((opcode & 0b00010000) >> 4) + 1;

	write(get_doppio_registro(registro), get_registro(0));

	if (opcode == 0x22)
		set_doppio_registro(3, get_doppio_registro(3) + 1);
	else if (opcode == 0x32)
		set_doppio_registro(3, get_doppio_registro(3) - 1);
}

// TODO
void CPU::HALT()
{
	//todo...
	std::cout << "\nTODO\n";
}

// Ci sono 7 istruzioni di ADD che essenzialmente sommano un registro ad A. In questo emulatore
// tutte le istruzioni ADD invocano questa funzione, e per decidere quale è il secondo registro
// da gestire viene usato l'opcode stesso (i tre bit meno significativi).
void CPU::ADD()
{
	//fetch();

	// Il registro da cui prelevare il valore da sommare in A.
	int registro = static_cast<int>((opcode & 0b00000111) + 0b00000001);
	
	if (registro == 5 || registro == 6) registro++;
	else if (registro == 7)
	{
		uint8_t risultato = get_registro(0) + read(get_doppio_registro(3));
		set_registro(0, risultato);

		set_zero(risultato == 0);
		set_subtract(false);
		set_half_carry((get_registro(0) & 0xf) + (get_registro(registro) & 0xf) > 0xf);
		set_carry((risultato & 0x100) != 0);

		return;
	}
	else if (registro == 8) registro = 0;

	uint8_t risultato = get_registro(registro) + get_registro(0);
	set_registro(0, risultato);

	set_zero(risultato == 0);
	set_subtract(false);
	set_half_carry((get_registro(0) & 0xf) + (get_registro(registro) & 0xf) > 0xf);
	set_carry((risultato & 0x100) != 0);
}

// La somma con riporto. Il valore specificato nel byte dell'istruzione viene sommato al registro A.
void CPU::ADC()
{
	int registro = static_cast<int>(opcode & 0b00000111) + 1;
	
	if (registro == 5 || registro == 6) registro++;
	else if (registro == 7)
	{
		uint8_t risultato = get_registro(0) + read(get_doppio_registro(3)) + ((get_registro(5) & 0b00010000) >> 4);
		set_registro(0, risultato);

		set_zero(risultato == 0);
		set_subtract(false);
		set_half_carry((risultato & 0b00001000) == 0b00001000);
		set_carry((risultato & 0b100000000) == 0b100000000);

		return;
	}
	else if (registro == 8) registro = 0;

	uint8_t risultato = get_registro(0) + get_registro(registro) + ((get_registro(5) & 0b00010000) >> 4);
	set_registro(0, risultato);

	set_zero(risultato == 0);
	set_subtract(false);
	set_half_carry((risultato & 0b00001000) == 0b00001000);
	set_carry((risultato & 0b100000000) == 0b100000000);
}

// Salva nel registro A la differenza tra A e il registro identificato nel primo byte dell'istruzione.
void CPU::SUB()
{
	int registro = static_cast<int>(opcode & 0b00000111) + 1;

	uint8_t vecchio = get_registro(0);
	set_subtract(true);

	if (registro == 5 || registro == 6) registro++;
	else if (registro == 7)
	{
		uint8_t risultato = get_registro(0) - read(get_doppio_registro(3));

		set_registro(0, risultato);

		set_zero(risultato == 0);
		set_half_carry((vecchio & 0x0F) == 0x00);
		set_carry(get_registro(registro) > get_registro(0));

		return;
	}
	else if (registro == 8) registro = 0;

	uint8_t risultato = get_registro(0) - get_registro(registro);
	set_registro(0, risultato);

	set_zero(risultato == 0);
	set_half_carry((vecchio & 0x0F) == 0x00);
	set_carry(get_registro(registro) > get_registro(0));
}

// Sottrae il valore del registro specificato e la carry flag da A.
void CPU::SBC()
{
	int registro = static_cast<int>(opcode & 0b00000111) + 1;

	uint8_t vecchio = get_registro(0);
	set_subtract(true);

	if (registro == 5 || registro == 6) registro++;
	else if (registro == 7)
	{
		uint8_t risultato = get_registro(0) - read(get_doppio_registro(3)) - ((get_registro(5) & 0b00010000) >> 4);

		set_registro(0, risultato);

		set_zero(risultato == 0);
		set_half_carry((vecchio & 0x0F) == 0x00);
		set_carry(get_registro(registro) + ((get_registro(5) & 0b00010000) >> 4) > get_registro(0));

		return;
	}
	else if (registro == 8) registro = 0;

	uint8_t risultato = get_registro(0) - get_registro(registro) - ((get_registro(5) & 0b00010000) >> 4);
	set_registro(0, risultato);

	set_zero(risultato == 0);
	set_half_carry((vecchio & 0x0F) == 0x00);
	set_carry(get_registro(registro) + ((get_registro(5) & 0b00010000) >> 4) > get_registro(0));
}

// Effettua AND bitwise tra il registro specificato e il registro A, e salva il risultato in A.
void CPU::AND()
{
	int registro = static_cast<int>(opcode & 0b00000111) + 1;

	set_subtract(false);
	set_half_carry(true);
	set_carry(false);

	if (registro == 5 || registro == 6) registro++;
	else if (registro == 7)
	{
		uint8_t risultato = get_registro(0) & get_registro(registro);

		set_registro(0, risultato);
		set_zero(risultato == 0);

		return;
	}
	else if (registro == 8) registro = 0;

	uint8_t risultato = get_registro(0) & get_registro(registro);

	set_registro(0, risultato);
	set_zero(risultato == 0);
}

// Effettua lo XOR bitwise tra il registro A e il registro specificato. Il risultato viene salvato in A.
void CPU::XOR()
{
	int registro = static_cast<int>(opcode & 0b00000111) + 1;

	set_subtract(false);
	set_half_carry(false);
	set_carry(false);

	if (registro == 5 || registro == 6) registro++;
	else if (registro == 7)
	{
		uint8_t risultato = get_registro(0) ^ get_registro(registro);

		set_registro(0, risultato);
		set_zero(risultato == 0);

		return;
	}
	else if (registro == 8) registro = 0;

	uint8_t risultato = get_registro(0) ^ get_registro(registro);

	set_registro(0, risultato);
	set_zero(risultato == 0);
}

// Effettua OR bitwise tra il registro A e il registro specificato. Il risultato viene salvato in A.
void CPU::OR()
{
	int registro = static_cast<int>(opcode & 0b00000111) + 1;

	set_subtract(false);
	set_half_carry(false);
	set_carry(false);

	if (registro == 5 || registro == 6) registro++;
	else if (registro == 7)
	{
		uint8_t risultato = get_registro(0) | get_registro(registro);

		set_registro(0, risultato);
		set_zero(risultato == 0);

		return;
	}
	else if (registro == 8) registro = 0;

	uint8_t risultato = get_registro(0) | get_registro(registro);

	set_registro(0, risultato);
	set_zero(risultato == 0);
}

// Confronta il valore in A con il registro specificato. Per effettuare il confronto viene effettuata
// una sottrazione e vengono impostate di conseguenza le flags. Questa istruzione è quindi identica
// alla SUB, ma non aggiorna il registro A.
void CPU::CP()
{
	int registro = static_cast<int>(opcode & 0b00000111) + 1;

	uint8_t vecchio = get_registro(0);
	set_subtract(true);

	if (registro == 5 || registro == 6) registro++;
	else if (registro == 7)
	{
		uint8_t risultato = get_registro(0) - read(get_doppio_registro(3));

		set_zero(risultato == 0);
		set_half_carry((vecchio & 0x0F) == 0x00);
		set_carry(get_registro(registro) > get_registro(0));

		return;
	}
	else if (registro == 8) registro = 0;

	uint8_t risultato = get_registro(0) - get_registro(registro);

	set_zero(risultato == 0);
	set_half_carry((vecchio & 0x0F) == 0x00);
	set_carry(get_registro(registro) > get_registro(0));
}

// Salta all'indirizzo specificato dall'operando a 8 bit.
void CPU::JR()
{
	int8_t offset = (int8_t)read(addr_assoluto);

	switch (opcode)
	{
	case 0x20:
		if ((get_registro(5) & 0b10000000) != 0x0)
			offset = 0;
		break;
	case 0x28:
		if ((get_registro(5) & 0b10000000) == 0x0)
			offset = 0;
	case 0x30:
		if ((get_registro(5) & 0b00010000) != 0x0)
			offset = 0;
		break;
	case 0x38:
		if ((get_registro(5) & 0b00010000) == 0x0)
			offset = 0;
		break;
	}
	
	pc += offset;
}

// LD r8, n8: carica un immediato in un registro/locazione di memoria.
void CPU::LIR()
{
	int registro = static_cast<int>((opcode & 0b00111000) >> 3) + 1;
	uint8_t valore = read(addr_assoluto);

	if (registro == 5 || registro == 6) registro++;
	else if (registro == 7)
	{
		this->write(get_doppio_registro(3), valore);
		return;
	}
	else if (registro == 8) registro = 0;

	set_registro(registro, valore);
}

// Carica in A un valore salvato in una posizione di memoria indicata da un registro doppio.
void CPU::LAR()
{
	switch (opcode)
	{
	case 0x0A:
		set_registro(0, read(get_doppio_registro(1)));
	case 0x1A:
		set_registro(0, read(get_doppio_registro(2)));
	case 0x2A:
		set_registro(0, read(get_doppio_registro(3)));
		set_doppio_registro(3, get_doppio_registro(3) + 1);
	case 0x3A:
		set_registro(0, read(get_doppio_registro(3)));
		set_doppio_registro(3, get_doppio_registro(3) - 1);
	}
}

// Ruota a sinistra il registro A. In pratica effettua uno shift a sinistra, dove il bit più significativo
// viene copiato nel carry flag e diventa il bit meno significativo.
void CPU::RLCA()
{
	uint8_t val = get_registro(0);
	uint8_t ultimo = val & 0b10000000;

	val = val << 1;
	val = ultimo == 0x00 ? val : val | 0b00000001;
	set_registro(0, val);

	set_zero(false);
	set_subtract(false);
	set_half_carry(false);
	set_carry(ultimo == 0x00 ? false : true);
}

// Ruota a sinistra il registro A (includendo il carry flag). Ciascun bit viene spostato a sinistra,
// il bit più significativo passa al carry flag e il valore del carry flag diventa il bit meno significativo.
void CPU::RLA()
{
	uint8_t val = get_registro(0);
	uint8_t ultimo = val & 0b10000000;
	uint8_t cf = get_registro(5) & 0b00010000;

	cf >> 4;
	val = val << 1;
	val = val | cf;

	set_zero(false);
	set_subtract(false);
	set_half_carry(false);
	set_carry(ultimo == 0x00 ? false : true);
}

// Ruota a destra il registro A. In pratica effettua uno shift a destra, dove il bit meno significativo
// viene copiato nel carry flag e diventa il bit più significativo.
void CPU::RRCA()
{
	uint8_t val = get_registro(0);
	uint8_t primo = val & 0b00000001;

	val = val >> 1;
	val = primo == 0x00 ? val : val | 0b10000000;
	set_registro(0, val);

	set_zero(false);
	set_subtract(false);
	set_half_carry(false);
	set_carry(primo == 0x00 ? false : true);
}

// Ruota a destra il registro A (includendo il carry flag). Ciascun bit viene spostato a destra,
// il bit meno significativo passa al carry flag e il valore del carry flag diventa il bit più significativo.
void CPU::RRA()
{
	uint8_t val = get_registro(0);
	uint8_t primo = val & 0b00000001;
	uint8_t cf = get_registro(5) & 0b00010000;

	cf << 3;
	val = val >> 1;
	val = val | cf;

	set_zero(false);
	set_subtract(false);
	set_half_carry(false);
	set_carry(primo == 0x00 ? false : true);
}

// DDA = Decimal Adjust Accumulator. Serve per correggere il contenuto del registro A dopo un'operazione
// aritmetica in BCD (Binary-Coded Decimal) - in pratica si assicura che A rappresenti un numero decimale
// valido.
void CPU::DAA()
{
	bool n = (get_registro(5) & 0b01000000) == 0x00 ? false : true;
	bool h = (get_registro(5) & 0b00100000) == 0x00 ? false : true;
	bool c = (get_registro(5) & 0b00010000) == 0x00 ? false : true;

	uint8_t correzione = 0;

	if (!n)
	{
		if (h || (get_registro(0) & 0x0F) > 9)
			set_registro(0, get_registro(0) + 0x06);

		if (c || get_registro(0) > 0x99)
		{
			set_registro(0, get_registro(0) + 0x60);
			set_carry(true);
		}
		else
			set_carry(false);
	}
	else
	{
		if (h) set_registro(0, get_registro(0) - 0x06);
		if (c) set_registro(0, get_registro(0) - 0x60);
	}

	set_zero(get_registro(0) == 0);
	set_half_carry(false);
}

// Set Carry Flag. Imposta la carry flag, e azzera le flag half carry e subtract/negative.
void CPU::SCF()
{
	set_carry(true);
	set_half_carry(false);
	set_subtract(false);
}

// Somma un doppio registro al registro HL.
void CPU::AHL()
{
	int registro = static_cast<int>((opcode & 0b00110000) >> 4) + 1;

	// TODO: gestire lo stack pointer
	//if (registro == 4)

	uint16_t risultato = get_doppio_registro(registro) + get_doppio_registro(3);

	set_doppio_registro(3, risultato);

	set_carry(risultato > 0xFFFF);
	set_half_carry((get_doppio_registro(3) & 0x0FFF) + (get_doppio_registro(registro) & 0x0FFF) > 0x0FFF);
	set_subtract(false);
}

// Carica dati dallo stack pointer all'indirizzo di memoria specificato dall'operando a 16 bit.
void CPU::LSP()
{
	//TODO...
	std::cout << "\nTODO\n";
}

// Complement Accumulator: inverte tutti i bit del registro A, e cambia le flag
// del subtract e half carry.
void CPU::CPL()
{
	set_registro(0, ~get_registro(0));

	set_subtract(false);
	set_half_carry(false);
}

// Complement Carry Flag: inverte la carry flag e azzera le flag del subtract
// e half carry.
void CPU::CCF()
{
	bool c = (get_registro(5) & 0b00010000) == 0x00 ? false : true;

	set_carry(!c);
	set_half_carry(false);
	set_subtract(false);
}

// Questa funzione viene invocata sia per l'istruzione RET, che per le varie istruzioni
// RET cc - dove cc è una condizione legata alle flags.
void CPU::RET()
{
	if (opcode == 0xC9)
	{
		//...
	}

	//TODO: se una condizione è vera ci voglio 5 cicli (quindi aggiungine tre se la condizione è verificata)
}

// Il risultato del pop viene messo in un registro a 16 bit specificato nell'istruzione.
void CPU::POP()
{
	int registro = static_cast<int>((opcode & 0b00110000) >> 4) + 1;

	if (registro == 4) registro = 0;

	uint8_t basso = read(sp++);
	uint8_t alto = read(sp++);

	set_doppio_registro(registro, (alto << 8) | basso);
}

void CPU::JP()
{
	bool salto = true;
	uint8_t alto = (uint8_t)read(fetched);
	uint8_t basso = (uint8_t)read(temp);

	switch (opcode)
	{
	case 0xC2:
		if ((get_registro(5) & 0b10000000) != 0x0)
			salto = false;
		else cicli++;
		break;
	case 0xCA:
		if ((get_registro(5) & 0b10000000) == 0x0)
			salto = false;
		else cicli++;
		break;
	case 0xD2:
		if ((get_registro(5) & 0b00010000) != 0x0)
			salto = false;
		else cicli++;
		break;
	case 0xDA:
		if ((get_registro(5) & 0b00010000) == 0x0)
			salto = false;
		else cicli++;
		break;
	case 0xE9:
		pc = get_doppio_registro(3);
		return;
	}

	if (salto)
		pc = (uint16_t)(alto << 8) | basso;
}

void CPU::LDH()
{
	switch (opcode)
	{
	case 0xE0:
		this->write(addr_assoluto, get_registro(0));
		break;
	case 0xF0:
		set_registro(0, this->read(addr_assoluto));
		break;
	case 0xE2:
		uint8_t alto = 0xFF;
		uint8_t basso = get_registro(2);
		this->write((uint16_t)(alto << 8) | basso, get_registro(0));
		break;
	case 0xF2:
		uint8_t alto = 0xFF;
		uint8_t basso = get_registro(2);
		set_registro(0, this->read((uint16_t)(alto << 8) | basso));
		break;
	}
}

void CPU::CALL()
{

}

void CPU::PUSH()
{
	int registro = static_cast<int>((opcode & 0b00110000) >> 4) + 1;

	if (registro == 4) registro = 0;

	uint8_t basso = read(sp++);
	uint8_t alto = read(sp++);

	this->write((alto << 8) | basso, get_doppio_registro(registro));
}

void CPU::DI()
{

}

// Funzione farlocca che è in realtà una NOP, ma questa viene usata
// per gli opcode che non indicano alcuna istruzione.
void CPU::XXX()
{

}