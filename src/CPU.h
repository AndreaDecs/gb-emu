#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

// Dichiarazione qui sopra per prevenire inclusioni circolari
class Bus;

class CPU
{
public:
	CPU();

	Bus* bus;									// Un collegamento al bus

	// Metodi utili vari
	void connettiBus(Bus* indirizzo) { bus = indirizzo; }

public:
	struct Registri
	{
		uint8_t a = 0x0;
		uint8_t b = 0x0;
		uint8_t c = 0x0;
		uint8_t d = 0x0;
		uint8_t e = 0x0;
		uint8_t f = 0x0;
		uint8_t h = 0x0;
		uint8_t l = 0x0;
	} registri;

	// Altri registri (special-purpose)
	uint16_t pc;								// Program Counter
	uint8_t sp = 0xFFFE;						// Stack Pointer

	// Le flags vengono memorizzate nella parte alta del registro f (il registro delle flags, per l'appunto). I 4 bit più bassi sono sempre impostati a 0.
	// IMPORTANTE: in origine anche questa struttura dati era una struct; per semplicità ora è una enum, però non si esclude un possibile ritorno ad una struct.
	enum Flags
	{
		carry = 4,
		half_carry,
		subtract,
		zero
	};

	// Metodi utili a manipolare registri/CPU
	void set_registro(uint8_t n, uint8_t val);
	uint8_t get_registro(uint8_t n);

	void set_doppio_registro(uint8_t n, uint16_t val);
	uint16_t get_doppio_registro(uint8_t n);

	void set_carry(bool attivo);
	void set_half_carry(bool attivo);
	void set_subtract(bool attivo);
	void set_zero(bool attivo);

	void write(uint16_t addr, uint8_t data);	// Scrive sul bus (e poi direttamente in memoria)
	uint8_t read(uint16_t addr);				// Legge dal bus

	uint8_t opcode = 0x00;						// L'opcode dell'istruzione attualmente in esecuzione
	int cicli = 0;								// I cicli di clock rimanenti per l'esecuzione di questa istruzione

	// Metodi per i segnali
	void clock();
	void reset();
	void irq();									// Interrupt Request

	// Struct rappresentante un'istruzione - include il nome e il numero di cicli richiesto.
	struct Istruzione
	{
		std::string nome = "";
		//std::function<void()> operazione;
		void		(CPU::* operazione)(void) = nullptr;
		void		(CPU::* addrmode)(void) = nullptr;
		uint8_t		cicli = 0;
	};

	// Una lookup table contenente tutte le istruzioni.
	std::vector<Istruzione> lookup;

	// Addressing Modes 
	
	void IMP();									// Implied
	void IMM();									// Immediate
	void REG();									// Register (vengono usati due registri non specificati nel primo byte dell'istruzione)
	void ABS();									// Absolute


private:
	// Ottiene la sorgente dei dati da gestire: potrebbe essere necessario leggere due registri, un indirizzo di memoria
	// o il dato potrebbe essere implicito nell'istruzione. Questo metodo decide in base alla modalità di indirizzamento
	// usata.
	uint8_t fetch();

	uint8_t fetched;							// Il valore da elaborare nell'ALU
	uint8_t temp;								// Una variabile usata quando l'istruzione richiede 3 bytes
	uint16_t addr_assoluto;						// Indirizzo da memoria assoluto da visitare

private:
	// Dichiarazione di tutte le istruzioni supportate dalla CPU. Alcune funzioni qui sotto hanno
	// dei nomi inventati, per rispettare la convenzione (rispettata dalla maggior parte delle istruzioni)
	// delle tre lettere. Alcune, come per esempio IDO e IHL non sono vere istruzioni, ma solo delle
	// funzioni scritte qui per convenienza, e vengono in realtà associate all'istruzione INC.
	// PERO' alcune funzioni devono avere nomi a 4 lettere, altrimenti non si capisce più niente :(
	void NOP();
	void STOP();
	void IDO();									// Questa istruzione rappresenta INC ma con un doppio registro
	void INC();
	void IHL();									// Questa sarebbe sempre INC [HL]
	void DDO();									// Questa decrementa un doppio registro
	void DEC();
	void DHL();									// Questa sarebbe DEC [HL]
	void LD();
	void LDIM();								// LD r16, imm16
	void LDA();									// LD [BC/DE/HL+/HL-], A
	void HALT();
	void ADD();
	void ADC();
	void SUB();
	void SBC();
	void AND();
	void XOR();
	void OR();
	void CP();
	void JR();
	void LIR();									// LD r8, n8 -- carica un immediato in un registro/locazione di memoria
	void LAR();									// LD A, [doppio_registro]
	void RLCA();
	void RLA();
	void RRCA();
	void RRA();
	void DAA();
	void SCF();
	void AHL();									// ADD HL, rr
	void LSP();									// LD [a16], SP
	void CPL();
	void CCF();
	void RET();
	void POP();
	void JP();
	void LDH();
	void CALL();
	void PUSH();
	void DI();
	void XXX();
};

