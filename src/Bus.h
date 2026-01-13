#pragma once

#include "CPU.h"
#include "PPU.h"

#include <cstdint>
#include <array>

class Bus
{
public:
	Bus();
	~Bus();
	
public:
	CPU cpu;
	PPU ppu;

	// Work RAM
	std::array<uint8_t, 8191> ram;

	// Video RAM
	std::array<uint8_t, 8191> vram;

	// OAM (Object Attribute Memory)
	std::array<uint8_t, 160> oam;

	// Metodo per scrivere qualcosa nella memoria (qualsiasi parte, tutti gli indirizzi sono accessibili da qui)
	void write(uint16_t addr, uint8_t data);

	// Metodo per leggere qualcosa dalla memoria
	uint8_t read(uint16_t addr);

	// Stampa il contenuto di tutti gli indirizzi (usato per debug)
	void stampa();
};

