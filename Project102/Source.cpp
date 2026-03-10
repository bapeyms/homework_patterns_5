#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class iDevice abstract
{
protected:
	string description;
public:
	string getDescription() 
	{
		return description;
	};
	virtual ~iDevice() = default;
};
class VideoCard : public iDevice
{
public:
	VideoCard()
	{
		description = "RX 7800 XT | VRAM: 16GB GDDR6 | Core Clock : 2124 MHz | Boost : 2430 MHz | Memory Bus : 256 - bit";
	}
};
class CPU : public iDevice
{
public:
	CPU()
	{
		description = "Ryzen 7 7700X | Cores: 8 | Threads : 16 | Base Clock : 4.5 GHz | Boost Clock : 5.4 GHz | Cache : 40MB";
	}
};
class HDD : public iDevice
{
public:
	HDD()
	{
		description = "Seagate Barracuda 2TB | Capacity: 2TB | Speed : 7200 RPM | Cache : 256MB | Interface : SATA III 6Gb / s";
	}
};

class Report
{
protected:
	iDevice* device;
public:
	iDevice* getDevice()
	{
		return device;
	}
	void setDevice(iDevice* device)
	{
		this->device = device;
	}
	virtual ~Report() = default;
	virtual void showReport() = 0;
};

class ConsoleReport : public Report
{
public:
	void showReport() override
	{
		cout << "- CONSOLE REPORT -" << endl;
		cout << device->getDescription() << endl << endl;
	}
};
class FileReport : public Report
{
public:
	void showReport() override
	{
		cout << "- FILE REPORT - " << endl;
		ofstream file("reportFile.txt", ios::trunc);
		if (file.is_open())
		{
			file << "- FILE REPORT -" << endl;
			file << device->getDescription() << endl << endl;
			file.close();
			cout << "The report is written to a file" << endl;
		}
		else
		{
			cout << "ERROR!" << endl;
		}
	}
};

void Client(iDevice* device, Report* report)
{
	report->setDevice(device);
	report->showReport();
}

int main()
{
	iDevice* device = new VideoCard();
	Report* report = new ConsoleReport();

	Client(device, report);
	delete device;
	delete report;

	device = new HDD();
	report = new FileReport();
	Client(device, report);
	delete device;
	delete report;
	return 0;
}