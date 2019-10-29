#include "epanet2.h"
#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<typeinfo>
#include<iomanip>
#define PI acos(-1)
using namespace std;


template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

void getPressureFromFile(string infileName) {
	ifstream infile;	//�����ļ�������
	ofstream ofile;               //��������ļ�
	ofile.open("H:\\myfile.txt");     //��Ϊ����ļ���
	infile.open(infileName.data());
	string lineStr;
	string input_result;	//��ʱ�洢���ַ���
	if (!infile.is_open()) {
		cout << "�����ļ���ʧ�ܣ�" << endl;
		return;
	}
	int lineCnt = 0;      //��ͳ��
	char* sInputfile = "H:\\EpanetSimulation\\Debug\\data\\ky8.inp";
	char* Reportfile = "H:\\EpanetSimulation\\Debug\\data\\Reportfile.rpt";
	ENopen(sInputfile, Reportfile, "");
	int i, NumNodes;
	float pressure;
	long t;
	ENopenH();
	while (getline(infile, lineStr)) {		//lineStr����ÿ��ģ��Ľڵ���ˮ������
		vector<string> vectorString;		//���ڴ��ÿ��ʵ���������ˮ������
		vector<float> random_pressure;
		ENgetcount(EN_NODECOUNT, &NumNodes);	//��ýڵ�����
		float* temp=new float[NumNodes];
		stringstream input(lineStr);
		while (input >> input_result) {		//�õ�ÿ��ʵ���������ˮ�����ݣ�������������
			//cout << "input_result:" << input_result << endl;
			vectorString.push_back(input_result);
		}
		/* ���õ�ǰִ�еĲ��� */
		for ( i = 0; i < vectorString.size(); i++)
		{
			ENsetnodevalue(i+1, EN_BASEDEMAND, stringToNum<float>(vectorString[i]));
		}
		/* ��ʼ��ˮ������ */
		ENinitH(0);
		/* ��һʱ������ */
		ENrunH(&t);
		cout << "----------------" << "lineCnt=" << lineCnt << "-------------" << endl;
		/* ������������������������ */
		for ( i = 0; i < NumNodes; i++)
		{
			ENgetnodevalue(i + 1, EN_PRESSURE, &pressure);	
			temp[i]= pressure;
			//cout << temp[i] << endl;
		}
		/*�������е�����д���ļ�*/
		for (int i = 0; i < NumNodes; i++)
		{
			if (i < NumNodes-1) {
				ofile << temp[i] << " ";
			}
			else
			{
				ofile << temp[i];
			}
		}
		ofile << endl;
		if (lineCnt == 999)break;	//��̬����
		lineCnt++;
	}
	ENcloseH();
	infile.close();                                     //�ر��ļ���
	ofile.close();  //�ر��ļ�
}

int main() {

	getPressureFromFile("D:/keyanshuju/Random_demand.txt");
	
	return 0;
}
