#include "epanet2.h"
#include <iostream>
using namespace std;
#define PI acos(-1)

//正常工况下水力计算，得到节点和管段的信息
void normalHydrau(char* inputFile,char*report) {

	char* sOutputfile = "";

	ENopen(inputFile, report, sOutputfile);

	ENsolveH();			    	    //进行平差计算
	ENsaveH();                      //将水力文件转换成输出文件
	ENsetreport("NODES ALL");       //报告中将节点信息显示
	ENreport();						//将格式化的文本报告写入到报告文件
	ENclose();
}

//漏损模拟
void leakSimulation(char* sInputfile,char*pRportAfterLeak,double sFlow,int nodeIndex) {
	
	char* sOutputfile = "";
	//开始正常
	ENopen(sInputfile, pRportAfterLeak, sOutputfile);
	ENsolveH();							    
	ENsaveH();                              
	ENsetreport("NODES ALL");       
	ENreport();

	float fEmitterCoeff;
	
	float pressure;
	int typecode;
	ENgetnodetype(nodeIndex, &typecode);
	ENgetnodevalue(nodeIndex, EN_PRESSURE, &pressure);
	ENclose();

	//开始泄露
	
	if (typecode == 0)
	{
		fEmitterCoeff = (sFlow / 0.063) / pow(pressure, 0.5);
		ENopen(sInputfile, pRportAfterLeak, sOutputfile);
		ENsetnodevalue(nodeIndex, EN_EMITTER, fEmitterCoeff);
		ENsolveH();							   
		ENsaveH();  //保存水力文件（非格式化二进制）                            
		ENsetreport("NODES ALL");    
		ENreport();//保存到报告文件（格式化文本）
		ENclose();

	}

	
}
//单个节点进行漏损模拟
/*

int main(int argc, char* argv[]) {
	int choose= atoi(argv[1]);


	cout << "开始水力模拟" << endl;
    //选择进行正常工况水力计算
	
	if (choose == 1) {   
		char* sInputfile = argv[2];			
		char* pReportAfterLeak = argv[3];
		normalHydrau(sInputfile, pReportAfterLeak);	
	}
	//选择进行漏损模拟
	else if (choose == 2) {
		char* sInputfile = argv[2];			
		char* pReportAfterLeak = argv[3];   
		double sFlow = atof(argv[4]);    //使用atof将char内的数转为double型--设置漏损射流系数
		int nodeIndex = atoi(argv[5]);   //使用atoi将char类型的数据转换为int  在第nodeIndex个模拟漏损
		leakSimulation(sInputfile, pReportAfterLeak, sFlow, nodeIndex);
	}
	
	return 0;

}
*/