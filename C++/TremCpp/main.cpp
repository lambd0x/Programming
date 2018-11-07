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

using namespace std;

int main(int argc, char **argv)
{
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
		//int key = trens.GetLastKey();
		//cout << "LastKey = " << key << endl;
		
		
		// ESC quando o Num Lock está ou não pressionado
/*		if (key == 27 || key == 1048603){
			cout << "Apertasse o ESC" << endl;
			break;
		}
		else if (key == 65362 || key == 1113938)
			cout << "Apertasse o UP" << endl;
		else if (key == 65364 || key == 1113940)
			cout << "Apertasse o DOWN" << endl;
	*/	
		
		// 1s
		//Thread::SleepMS(1000);
		
		// Captures key strock
		int key = trens.GetLastKey();
		
		switch(key){
		
			case UPlockNO:
			case UPlockYE:
			// Trem 1 de Lucerne para Engelberg com avanço direto por Stans
				for (float p = -1; p <= 1; p += 0.01)
				{
					if (p < 0)
						trens.Trem1Pos((-1) * p, 1);
					else
						trens.Trem1Pos(p, 0);
					//trens.Trem1Pos(p.x,p.y);
					Thread::SleepMS(10);

					trens.Trem1Txt("a1=" + to_string((int) trens.A1()) +
								   " a2=" + to_string((int) trens.A2()) +
								   " b1=" + to_string((int) trens.B1()) +
								   " b2=" + to_string((int) trens.B2()) +
								   " c=" + to_string((int) trens.C()));
				}
				trens.Trem1Txt("Mensagem trem 1.");
				break;
		
			case DOWNlockNO:
			case DOWNlockYE:
			
				trens.Gate(0);
				for (float p = -1; p <= 1; p += 0.01)
				{
					if (p < 0)
						trens.Trem2Pos((-1) * p, 2);
					else
						trens.Trem2Pos(p, 0);
					//trens.Trem1Pos(p.x,p.y);
					Thread::SleepMS(10);

					trens.Trem2Txt("a1=" + to_string((int) trens.A1()) +
								   " a2=" + to_string((int) trens.A2()) +
								   " b1=" + to_string((int) trens.B1()) +
								   " b2=" + to_string((int) trens.B2()) +
								   " c=" + to_string((int) trens.C()));
				
				}
				trens.Trem2Txt("Mensagem trem 2.");
				break;
			
			case ESClockNO:
			case ESClockYE:
				exit(1);
				break;
			}// switch
			
			// 10ms
			Thread::SleepMS(10);
			
	}//while
	
	return 0;
}
