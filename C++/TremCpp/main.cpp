#include <iostream>
#include "class/mapatrem.h"
#include "class/threads/thread.h"
#include <vector>
#include <string>
#include "class/threadtest.h"

#define DOWNlockNO 65364
#define DOWNlockYE 1113940

#define UPlockNO 65362
#define UPlockYE 1113938

#define ESClockNO 27
#define ESClockYE 1048603




int main(int argc, char **argv)
{
	// Para compilar em build: cmake .. (somente na 1ª vez)
	// make

	/*
	ThreadTest teste(4);
	Thread::SleepMS(10000);
	return 0;
	*/

	MapaTrem trens;
	trens.Trem1Pos(1, 1);
	trens.Trem1Txt("Mensagem trem 1.");
	trens.Trem2Pos(1, 2);
	trens.Trem2Txt("Mensagem trem 2.");
	trens.Gate(1);

	// Loop geral do sistema
	while(1) {
		//ThreadTest sistema(1);

		// Captura o pressionar de uma tecla do teclado
		int key = trens.GetLastKeyAndEmpty();

		if(key == UPlockNO || key == UPlockYE)
		{
		ThreadTest trem1(1);

			// Trem 1 de Lucerne para Engelberg com avanço direto por Stans
				for (float p = -1; p <= 1; p += 0.01)
				{
					if (p < 0)
						trens.Trem1Pos((-1) * p, 1);
					else
						trens.Trem1Pos(p, 0);
					//trens.Trem1Pos(p.x,p.y);
					Thread::SleepMS(10);

				/*	trens.Trem1Txt("a1=" + to_string((int) trens.A1()) +
								   " a2=" + to_string((int) trens.A2()) +
								   " b1=" + to_string((int) trens.B1()) +
								   " b2=" + to_string((int) trens.B2()) +
								   " c=" + to_string((int) trens.C()));
				*/
				}
				//trens.Trem1Txt("Mensagem trem 1.");

			// Trem 1 de Engelberg avança direto para Lucerne
			for (float p = 1; p >= -1; p -= 0.01)
			{
				if (p > 0)
					trens.Trem1Pos(p, 0);
			    else
					trens.Trem1Pos((-1) * p, 1);
				//trens.Trem1Pos(p.x,p.y);
				Thread::SleepMS(10);

				/*trens.Trem1Txt("a1=" + to_string((int) trens.A1()) +
							   " a2=" + to_string((int) trens.A2()) +
							   " b1=" + to_string((int) trens.B1()) +
							   " b2=" + to_string((int) trens.B2()) +
							   " c=" + to_string((int) trens.C()));
				*/
			}
			//trens.Trem1Txt("Mensagem trem 1.");

		} else if(key == DOWNlockNO || key == DOWNlockYE)
		{
			ThreadTest trem2(1);

			// Trem 2 de Sarnen para Engelberg com avanço direto por Stans
				trens.Gate(0);
				for (float p = -1; p <= 1; p += 0.01)
				{
					if (p < 0)
						trens.Trem2Pos((-1) * p, 2);
					else
						trens.Trem2Pos(p, 0);
					//trens.Trem1Pos(p.x,p.y);
					Thread::SleepMS(10);

					/*trens.Trem2Txt("a1=" + to_string((int) trens.A1()) +
								   " a2=" + to_string((int) trens.A2()) +
								   " b1=" + to_string((int) trens.B1()) +
								   " b2=" + to_string((int) trens.B2()) +
								   " c=" + to_string((int) trens.C()));
					*/
				}
				//trens.Trem2Txt("Mensagem trem 2.");

			// Trem 2 de Engelberg para Sarnen com avanço direto por Stans
				for (float p = 1; p >= -1; p -= 0.01)
				{
					if (p > 0)
						trens.Trem2Pos(p, 0);
					else
						trens.Trem2Pos((-1) * p, 2);
					//trens.Trem1Pos(p.x,p.y);
					Thread::SleepMS(10);

					/*trens.Trem2Txt("a1=" + to_string((int) trens.A1()) +
								   " a2=" + to_string((int) trens.A2()) +
								   " b1=" + to_string((int) trens.B1()) +
								   " b2=" + to_string((int) trens.B2()) +
								   " c=" + to_string((int) trens.C()));
					*/
				}
			//	trens.Trem2Txt("Mensagem trem 2.");

		} else if(key == ESClockNO || key == ESClockYE)
		{
				//exit(1);

				break;
		}

		// 10ms
		Thread::SleepMS(10);
	}//while

	return 0;
}
