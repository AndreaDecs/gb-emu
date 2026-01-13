#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "Bus.h"

class Demo : public olc::PixelGameEngine
{
public:
	Demo()
	{
		sAppName = "GB Emu";
	}

	Bus gb;

	// questa funzione è temporanea!!!
	std::vector<uint8_t> leggiROM(std::string str)
	{
		std::vector<uint8_t> tokens;
		size_t pos = 0;
		std::uint8_t token;
		while ((pos = str.find(' ')) != std::string::npos)
		{
			token = std::stoul(str.substr(0, pos), nullptr, 16);
			tokens.push_back(token);
			str.erase(0, pos + 1);
		}
		tokens.push_back(std::stoul(str, nullptr, 16));

		return tokens;
	}

	//altra funzione temporanea
	void DrawCPU(int x, int y)
	{
		DrawString(x, y, "PC: $" + hex(gb.cpu.pc, 4));
		DrawString(x, y + 16, "A: " + std::to_string(gb.cpu.get_registro(0)));
		DrawString(x, y + 32, "B: " + std::to_string(gb.cpu.get_registro(1)));
		DrawString(x, y + 48, "C: " + std::to_string(gb.cpu.get_registro(2)));
		DrawString(x, y + 64, "D: " + std::to_string(gb.cpu.get_registro(3)));
		DrawString(x, y + 80, "E: " + std::to_string(gb.cpu.get_registro(4)));
		DrawString(x, y + 96, "F: " + std::to_string(gb.cpu.get_registro(5)));
		DrawString(x, y + 112, "H: " + std::to_string(gb.cpu.get_registro(6)));
		DrawString(x, y + 128, "L: " + std::to_string(gb.cpu.get_registro(7)));
	}

	//altra temporanea
	std::string hex(uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

public:
	bool OnUserCreate() override
	{
		//0xC000 la RAM effettiva inizia da qui
		uint16_t offset = 0xC000;

		//PROVA!!
		////std::stringstream ss;
		//ss << "CD 81 28 31 FF DF AF E0 47 E0 48 E0 49 21 00 80";
		////ss << "00 80 00 00 80";
		/*while (!ss.eof())
		{
			std::string b;
			ss >> b;
			std::cout << std::stoul(b, nullptr, 16) << std::endl;
			//gb.ram[offset] = std::stoul(b, nullptr, 16);
			gb.ram.at(offset) = (uint8_t)std::stoul(b, nullptr, 16);
		}*/

		std::string s = "C1 D1 E1 F1";
		std::vector<uint8_t> tokens = leggiROM(s);

		for (auto& i : tokens)
		{
			gb.write(offset, i);
			offset++;
		}
		
		//gb.stampa();
		gb.cpu.pc = 0xC000;
		std::cout << "Prima istruzione: " << gb.read(gb.cpu.pc) << std::endl;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		/*for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));*/

		Clear(olc::DARK_BLUE);

		if (GetKey(olc::Key::SPACE).bPressed)
		{
			gb.cpu.clock();
		}

		DrawCPU(64, 4);

		return true;
	}
};

int main()
{
	Demo demo;
	if (demo.Construct(160, 144, 4, 4, false, true))
		demo.Start();

	return 0;
}