#include<iostream>
#include<math.h>
#include<time.h>
#include <chrono>
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	char onOff;
	//Момент инерции двигателя I (кг∙м)
	int inertion = 10;
	//Температура перегрева T перегрева (C 0)
	int maxTemperature = 110;
	//Коэффициент зависимости скорости нагрева от крутящего момента HM
	double hM = 0.01;
	//Коэффициент зависимости скорости нагрева от скорости вращения коленвала HV
	double hV = 0.0001;
	//Коэффициент зависимости скорости охлаждения от температуры двигателя и окружающей	среды C
	double c = 0.1;
	//Кусочно-линейная зависимость крутящего момента M, вырабатываемого двигателем, от
	//скорости вращения коленвала V(крутящий момент в Н∙м, скорость вращения в радиан / сек) : 
	int arrM[] = { 20,75,100,105,75,0 };
	int arrV[] = { 0, 75, 150,200,250,300 };
	int tmp = arrV[0];
	//Температура окружающей среды
	double enviromentTemp = 0;
	//Температура двигателя
	double engineTemp = 0;
	//Скорость охлаждения и нагрева
	float heatingSpeed = 0.0, coolingSpeed = 0.0;
	//Ускорение коленвала
	float acceleration = 0.0;
	//Максимальная температура двигателя
	double engineMaxTemp = 0.0;
	while (true)
	{
		system("cls");
		cout << "Введите температуру окуржающей среды: " << endl;
		cin >> enviromentTemp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else
		{
			std::cin.ignore(32767, '\n');
			break;
		}
	}
	engineTemp = enviromentTemp;
	cout << "Для включения двигателя введите 1 " << endl;
	cout << "Для выхода введите 2 " << endl;
	do
	{
		cin >> onOff;
		if (onOff == '1' || onOff == '2')
		{
			break;
		}
		cout << "Вы ввели неверное выражение, попробуйте еще раз" << endl;
	} while (true);
	switch (onOff)
	{
	case '1':
	{
		cout << "Двигатель запущен" << endl;
		auto begin = std::chrono::steady_clock::now();
		for (int i = 0; i < 5; i++)
		{
			for (;;)
			{
				acceleration = arrM[i] / inertion;
				arrV[i] += acceleration;
				heatingSpeed = arrM[i] * hM * pow(tmp, 2) * hV;
				coolingSpeed = c * (enviromentTemp - engineTemp);
				engineTemp += heatingSpeed;
				engineTemp += coolingSpeed;
				if (engineTemp > 0 && engineTemp < engineMaxTemp)
				{
					cout << "Максимальная достигнутая температура двигателя " << engineMaxTemp << endl;
					break;
				}
				engineMaxTemp = engineTemp;
				if (i < 5)
				{
					if (arrV[i] >= arrV[i + 1])
					{
						tmp = arrV[i + 1];
						i++;
					}
				}
				if (engineTemp >= maxTemperature)
				{
					break;
				}
			}
		}
		auto end = chrono::steady_clock::now();
		auto elapsed_mcrs = chrono::duration_cast<chrono::microseconds>(end - begin);
		cout << "Время превышения температуры " << elapsed_mcrs.count() << " microsec\n";
		break;
	}
	case '2':
	{
		exit(1);
	}
	}
}
