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
	ifstream infile;	//创建文件输入流
	ofstream ofile;               //定义输出文件
	ofile.open("H:\\myfile.txt");     //作为输出文件打开
	infile.open(infileName.data());
	string lineStr;
	string input_result;	//临时存储用字符串
	if (!infile.is_open()) {
		cout << "输入文件打开失败！" << endl;
		return;
	}
	int lineCnt = 0;      //行统计
	char* sInputfile = "H:\\EpanetSimulation\\Debug\\data\\ky8.inp";
	char* Reportfile = "H:\\EpanetSimulation\\Debug\\data\\Reportfile.rpt";
	ENopen(sInputfile, Reportfile, "");
	int i, NumNodes;
	float pressure;
	long t;
	ENopenH();
	while (getline(infile, lineStr)) {		//lineStr代表每次模拟的节点需水量数据
		vector<string> vectorString;		//用于存放每次实验迭代的需水量数据
		vector<float> random_pressure;
		ENgetcount(EN_NODECOUNT, &NumNodes);	//获得节点总数
		float* temp=new float[NumNodes];
		stringstream input(lineStr);
		while (input >> input_result) {		//得到每次实验迭代的需水量数据，并放入向量中
			//cout << "input_result:" << input_result << endl;
			vectorString.push_back(input_result);
		}
		/* 设置当前执行的参数 */
		for ( i = 0; i < vectorString.size(); i++)
		{
			ENsetnodevalue(i+1, EN_BASEDEMAND, stringToNum<float>(vectorString[i]));
		}
		/* 初始化水力特性 */
		ENinitH(0);
		/* 单一时段运行 */
		ENrunH(&t);
		cout << "----------------" << "lineCnt=" << lineCnt << "-------------" << endl;
		/* 检索结果并将结果存入数组中 */
		for ( i = 0; i < NumNodes; i++)
		{
			ENgetnodevalue(i + 1, EN_PRESSURE, &pressure);	
			temp[i]= pressure;
			//cout << temp[i] << endl;
		}
		/*将数组中的数据写入文件*/
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
		if (lineCnt == 999)break;	//动态开启
		lineCnt++;
	}
	ENcloseH();
	infile.close();                                     //关闭文件流
	ofile.close();  //关闭文件
}

int main() {

	getPressureFromFile("D:/keyanshuju/Random_demand.txt");
	
	return 0;
}
