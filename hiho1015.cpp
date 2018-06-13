#include<iostream>
#include<string>
#include<vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::endl;

int main(){
	int N, countArray[20];
	cin>>N;
	for(int i = 0; i < N; i ++){
		string str_origin, str_pattern;
		cin>>str_pattern;
		
		// 构造NEXT矩阵 
		vector<int> NEXT;
		NEXT.push_back(-1); // 初始化NEXT矩阵 
		for(int j = 1, k = -1; j < str_pattern.length(); j ++){
			while(k > -1 && str_pattern[k + 1] != str_pattern[j]){
				k = NEXT[k];
			}
			if(str_pattern[k+1] == str_pattern[j]){
				k ++;
			}
			NEXT.push_back(k);
		}
		
		cin>>str_origin;
		
		// 统计匹配的字符串数目 
		int j, k = -1, count = 0;
		for(j = 0; j < str_origin.length(); j ++){
			while(k > -1 && str_pattern[k + 1] != str_origin[j]){
				k = NEXT[k];
			}
			if(str_pattern[k + 1] == str_origin[j]){
				k ++;
			}
			if(k == str_pattern.length() - 1){
				count ++;
				k = NEXT[k];
			}
		} 
		countArray[i] = count;
	}
	
	for(int i = 0; i < N; i ++){
		cout<<countArray[i];
		if(i != N -1){
			cout<<endl;
		}
	}
	return 0;
}
