#include "Bus.h"

#include <iostream>

Bus::Bus()
{
    // Tramite questa chiamata, la CPU può riferirsi al bus (tra l'altro "padre" della cpu) e il bus può riferirsi alla CPU quando vuole (avendola istanziata il bus stesso)
    cpu.connettiBus(this);

    // Stesso collegamento effettuato con la CPU, ma stavolta per la PPU
    ppu.connettiBus(this);

    for (auto& i : ram)
        i = 0x00;
}

Bus::~Bus()
{
}

void Bus::write(uint16_t addr, uint8_t data)
{
    if (addr >= 0xC000 && addr <= 0xDFFF)
        ram[addr - 0xC000] = data;
    else if (addr >= 0x8000 && addr <= 0x9FFF)
        vram[addr - 0x8000] = data;
    else if (addr >= 0xFE00 && addr <= 0xFE9F)
        oam[addr - 0xFE00] = data;
}

uint8_t Bus::read(uint16_t addr)
{
    if (addr >= 0xC000 && addr <= 0xDFFF)
        return ram[addr - 0xC000];
    else if (addr >= 0x8000 && addr <= 0x9FFF)
        return vram[addr - 0x8000];
    else if (addr >= 0xFE00 && addr <= 0xFE9F)
        return oam[addr - 0xFe00];

    return 0x00;
}

void Bus::stampa()
{
    for (auto& i : ram)
        std::cout << i << std::endl;
}