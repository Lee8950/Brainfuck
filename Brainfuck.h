#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ecl {

	class Brainfuckvm {

	private:

		bool SCRIPTMODE;
		int STACKRECORD;
		int VMPOINTER;
		std::vector<int> VMMEM;
		std::vector<std::string> INSTRUCTION;

		bool RECORD(char COMMAND, bool ISRCD) {
			for (int i = STACKRECORD; i < INSTRUCTION.size(); i++) {
				INSTRUCTION[i] += COMMAND;
			}
			return true;
		}

		bool MOV_RGT() {
			if (this->VMPOINTER == this->VMMEM.size() - 1) {
				this->VMMEM.push_back(0);
			}
			this->VMPOINTER++;
			return true;
		}

		bool MOV_LFT() {
			if (this->VMPOINTER == 0) {
				std::cout << "Error 0x02 : Pointer has reached the upper bound of the machine";
				return false;
			}
			this->VMPOINTER--;
			return true;
		}

		bool ADD() {
			VMMEM[VMPOINTER]++;
			return true;
		}

		bool SUB() {
			VMMEM[VMPOINTER]--;
			return true;
		}

		bool READ() {
			VMMEM[VMPOINTER] = std::getchar();
			if (SCRIPTMODE && VMMEM[VMPOINTER] == '\n') {
				VMMEM[VMPOINTER] = 0;
			}
			return true;
		}

		bool PRINT() {
			std::cout << char(VMMEM[VMPOINTER]);
			return true;
		}

		bool BGNSGN(char COMMAND) {
			std::string CODE;
			CODE.clear();
			this->INSTRUCTION.push_back(CODE);
			return true;
		}

		bool BCKSGN() {
			std::string CODE;
			CODE = INSTRUCTION.back();
			this->STACKRECORD++;
			while ((VMMEM[VMPOINTER] != 0)) {
				for (int i = 0; i < CODE.length(); i++) {
					this->read(CODE[i], false);
				}
			}
			this->STACKRECORD--;
			this->INSTRUCTION.pop_back();
			CODE.clear();
			return true;
		}



	public:

		Brainfuckvm() {
			this->SCRIPTMODE = false;
			this->VMMEM.push_back(0);
			this->VMPOINTER = 0;
			this->STACKRECORD = 0;
		}

		void togglemode() {
			if (this->SCRIPTMODE) {
				this->SCRIPTMODE = false;
			}
			else {
				this->SCRIPTMODE = true;
			}
		}

		bool read(char COMMAND, bool ISRCDBTTMLYR = true) {
			//for (int i = 0; i < VMMEM.size(); i++) {
			//	cout << VMMEM[i] << ' ';
			//}
			//cout << endl;
			bool OperateStatus = true;
			switch (COMMAND) {
			case ' ':break;
			case '\n':break;
			case '\t':break;
			case '\0':break;
			case '>':OperateStatus = RECORD(COMMAND, ISRCDBTTMLYR); this->MOV_RGT(); break;
			case '<':OperateStatus = RECORD(COMMAND, ISRCDBTTMLYR); this->MOV_LFT(); break;
			case '+':OperateStatus = RECORD(COMMAND, ISRCDBTTMLYR); this->ADD(); break;
			case '-':OperateStatus = RECORD(COMMAND, ISRCDBTTMLYR); this->SUB(); break;
			case '.':OperateStatus = RECORD(COMMAND, ISRCDBTTMLYR); this->PRINT(); break;
			case ',':OperateStatus = RECORD(COMMAND, ISRCDBTTMLYR); this->READ(); break;
			case '[':OperateStatus = RECORD(COMMAND, ISRCDBTTMLYR); this->BGNSGN(COMMAND); break;
			case ']':OperateStatus = this->BCKSGN(); RECORD(COMMAND, ISRCDBTTMLYR); break;
			default:/*std::cout << "Error 0x01 : Unrecognized character";*/ return false;
			}
			return OperateStatus;
		}

	};

}