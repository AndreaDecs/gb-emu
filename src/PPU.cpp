#include "PPU.h"
#include "Bus.h"

PPU::PPU()
{
}

void PPU::clock()
{
	uint8_t modalita = 0;			// modalità attuale per la creazione della scanline (MOMENTANEO)

	switch (modalita)
	{
	case 0:
		processaOam();
		break;
	case 1:

		break;
	case 2:

		break;

	case 3:

		break;
	}
}

void PPU::write(uint16_t addr, uint8_t data)
{
	bus->write(addr, data);
}

uint8_t PPU::read(uint16_t addr)
{
	return bus->read(addr);
}

void PPU::processaOam()
{
	uint8_t conta = 0;
	uint16_t offset = 0xFE00;

	//for (size_t i = 0; i < 40; i++)
	//{
	//	uint8_t y = read(offset + i * 4 + 0);
	//	uint8_t x = read(offset + i * 4 + 1);
	//	uint8_t tile = read(offset + i * 4 + 2);
	//	uint8_t flags = read(offset + i * 4 + 3);

	//	uint8_t spriteY = y - 16;

	//	/*if ()
	//	{

	//	}*/
	//}
}

void PPU::processaTransfer()
{
}

void PPU::processaHBlank()
{
}

void PPU::processaVBlank()
{
}
