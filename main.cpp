/*
一键比对项目相似度
主程序作者：司南Gentoo（GitHub：@SinanGentoo）
本项目使用了scratch-source-copier与scratch-source-comparer，未经许可不得转载，谢谢
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
string link1,link2,fileName[2];
struct executeValue{
	int status;
	string result;
}answer;
executeValue runCMD(string cmd){
	executeValue temp;
	if (cmd.size() == 0){
		temp.status=-1;
		return temp;
	}
	 char buffer[1024] = {0};
 	string result = "";
 	FILE *pin = popen(cmd.c_str(), "r");
	 if (!pin) {
		temp.status=-1;
		return temp;
	}
	while(!feof(pin)) if(fgets(buffer, sizeof(buffer), pin)!=NULL) result += buffer;
	temp.result=result;
	temp.status=pclose(pin);
	return temp;
}
void getProjectFile(string link){
	//为了贯彻落实Alex Cui关于该程序的意见，system函数弃用
	runCMD(string("cd scratch-source-copier && npm start "+link).c_str());
	runCMD("cp -r ./scratch-source-copier/files/ ./tmp/");
	runCMD("rm -rf ./scratch-source-copier/files");
	//runCMD("clear");
}
void parseProjectInfo(){
	int oneLineLength;
	answer=runCMD("cd ./tmp/files && ls");
	for(int i=0;;i++){
		if(answer.result[i] == '\n'){
			oneLineLength=i;
			break;
		}
	}
	for(int i=0;i<oneLineLength;i++) fileName[0]+=answer.result[i];
	for(int i=oneLineLength+1;i<answer.result.length();i++) fileName[1]+=answer.result[i];
}
string checkAndFixDependence(){
	executeValue tmp;
	tmp=runCMD("npm -v");
	if (tmp.result.find("bash:") != string::npos) return "npm not installed";
	tmp=runCMD("ls");
	if (tmp.result.find("scratch-source-copier") == string::npos) return "copier not installed";
	if (tmp.result.find("scratch-source-comparer") == string::npos) return "comparer not installed";
	return "success";
}
int main(int argc, char *argv[]){
	//for (int i = 0; i < argc; ++i) cout << argv[i] << endl;
	cout<<"=============================="<<endl;
	cout<<"Scratch作品一键比对工具"<<endl;
	cout<<"作者：司南Gentoo"<<endl;
	cout<<"版本：1.0.0"<<endl;
	cout<<"=============================="<<endl;
	if(argc<3){
		cout<<"\033[31m[ERR]\033[0m命令有误！使用方法：./soc [原作品] [疑似侵权作品]"<<endl;
		return 0;
	}
	if(checkAndFixDependence()!="success"){
		cout<<"\033[31m[ERR]\033[0m依赖不完整！请检查相应文件是否存在："<<checkAndFixDependence()<<endl;
		return 0;
	}
	link1=argv[1],link2=argv[2];
	cout<<"\033[32m[INFO]\033[0m正在删除缓存..."<<endl;
	runCMD("rm -rf ./tmp/files && cd tmp && mkdir files"); 
	cout<<"\033[32m[INFO]\033[0m正在下载原作品代码..."<<endl;
	getProjectFile(link1);
	cout<<"\033[32m[INFO]\033[0m正在下载疑似侵权作品代码..."<<endl;
	getProjectFile(link2);
	cout<<"\033[32m[INFO]\033[0m正在解析待比对信息..."<<endl;
	parseProjectInfo();
	cout<<"\033[32m[INFO]\033[0m开始比对..."<<endl;
	system(string("cd scratch-source-comparer && npm start \"../tmp/files/"+fileName[0]+"\" \"../tmp/files/"+fileName[1]+"\"").c_str());
	return 0;
}
