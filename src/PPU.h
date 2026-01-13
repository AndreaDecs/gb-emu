#pragma once

#include <array>

const uint8_t LARGHEZZA_TILE = 8;
const uint8_t ALTEZZA_TILE = 8;
const uint8_t BYTE_PER_TILE = 2;

// Dichiarazione qui sopra per prevenire inclusioni circolari
class Bus;

class PPU
{
public:
	PPU();

	Bus* bus;									// Un collegamento al bus

	void clock();

	void connettiBus(Bus* indirizzo) { bus = indirizzo; }
	void write(uint16_t addr, uint8_t data);	// Scrive sul bus (e poi direttamente in memoria)
	uint8_t read(uint16_t addr);				// Legge dal bus

private:
	enum Colore
	{
		Zero,
		Uno,
		Due,
		Tre
	};

	/*struct Tile
	{
		std::array<Colore, LARGHEZZA_TILE* ALTEZZA_TILE> buffer;
	};*/

private:
	void processaOam();
	void processaTransfer();
	void processaHBlank();
	void processaVBlank();
};

