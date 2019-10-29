#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<typeinfo>
using namespace std;


vector<string>saveText;


template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
void readFile(string fileName) {
	ifstream infile;
	infile.open(fileName.data());
	string lineStr;  
	string input_result;//临时存储用字符串
	
	if (!infile.is_open()) {
		cout << "文件打开失败！" << endl;
		return;
		
	}
	int lineCnt = 0;                                      //行统计
	while (getline(infile, lineStr)) {
		vector<string> vectorString;
		stringstream input(lineStr);
		//依次输出到input_result中，并存入vectorString中
		
		while (input >> input_result){
			cout <<"input_result:"<< input_result << endl;
			vectorString.push_back(input_result);
		}

		for (int j = 0; j<vectorString.size(); j++) {
			cout <<"第"<<j<<"个"<< stringToNum<float>(vectorString[j])-1<< endl;
		}
		
		if (lineCnt == 0)break;
	}
	
	infile.close();                                     //关闭文件流
	
}


/*
int main()

{

	
	

	readFile("D:/keyanshuju/Random_demand.txt");
	

	return 0;

}
*/