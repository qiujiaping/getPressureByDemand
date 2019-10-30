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
	ofile.open("E:\\pythonStudy\\resoures\\randomPressure.txt");     //��Ϊ����ļ���
	infile.open(infileName.data());
	string lineStr;
	string input_result;	//��ʱ�洢���ַ���
	if (!infile.is_open()) {
		cout << "�����ļ���ʧ�ܣ�" << endl;
		return;
	}
	int lineCnt = 0;      //��ͳ��?��ģ��Ĵ�����1000�Σ�
	char* sInputfile = "D:\\keyanshuju\\2019-10-29\\Net3.inp";
	char* Reportfile = "E:\\pythonStudy\\resoures\\Reportfile.rpt";
	ENopen(sInputfile, Reportfile, "");
	int i, NumNodes;
	float pressure;
	//float DEMAND;
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
		//cout << "----------------" << "lineCnt=" << lineCnt << "-------------" << endl;
		/* ������������������������ */
		for ( i = 0; i < NumNodes; i++)
		{
			ENgetnodevalue(i + 1, EN_PRESSURE, &pressure);	
			temp[i]= pressure;
			//ENgetnodevalue(i + 1, EN_DEMAND, &DEMAND);
			//cout <<"----"<<i+1<<"�ڵ����ˮ����------"<<DEMAND << endl;
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
		//if (lineCnt == 999)break;	//��̬����
		//lineCnt++;
	}
	ENcloseH();
	infile.close();                                     //�ر��ļ���
	ofile.close();  //�ر��ļ�
}

int main() {

	getPressureFromFile("E:\\pythonStudy\\resoures\\random_demand.txt");

	return 0;
}
