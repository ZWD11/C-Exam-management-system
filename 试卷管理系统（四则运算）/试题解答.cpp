#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

int gcd(int a,int b){//求两数公约数 
int t; 
if(a < b){
	int t = a;
	a = b;
	a = t;
}
while (b>0){
    t = a % b;
    a = b;
    b = t;
}
return a;
}

int problem_easy(){
	clock_t start,end;//clock_t(长整型，计时函数，返回值表示该程序从启动到函数调用占用cpu的时间，毫秒为单位） 
	start = clock();
	int sum=0;//初始化做对的题目数量 
	
	FILE *fp, *fp_ans;
	fp = fopen("D:\\试题库\\easy.txt","r");
	fp_ans = fopen("D:\\试题库\\solve_easy.txt","w");
	
	if(fp == NULL){
		printf("文件打开失败!\n");
		exit(0);//正常运行并退出程序 
	}else{
		while(!feof(fp)){ //feof（检测文件结束符的函数，结束非零，否则为零） 
			char buf[20];//定义一个字符数组用字符形式输入题目 
			fgets(buf,20,fp);//从fp文件中读取 
			int len = strlen(buf);
			int a=0,b=0;
			char c;
			for(int i=0;i<len-1;i++)
				printf("%c",buf[i]);
				
			int flag = 0;//判断是否运算符 
			for(int i=0;i<len-1;i++){
				if(flag == 0){
				if(buf[i] >= '0' && buf[i] <='9'){
					a =  buf[i] - '0';//类型转换 
				}
				}
				
				if(buf[i] == '+') flag=1,c='+';
				if(buf[i] == '-') flag=1,c='-';
				
				if(flag == 1){
					if(buf[i] >= '0' && buf[i] <='9'){
						b = b * 10 + buf[i] - '0';
					}			
				}		
			}
			int ans,your_ans;
			if(c == '+'){
				ans = a+b;
				fprintf(fp_ans,"%d",a);
				fputs(" + ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
			}else if(c == '-'){
				ans = a-b;
				fprintf(fp_ans,"%d",a);
				fputs(" - ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
			}

			scanf("%d",&your_ans);
			fprintf(fp_ans,"%d\n",your_ans);
			
			if(your_ans == ans)
			     sum++;	
			
		}	

		end = clock();
		double time = (double)(end-start)/CLK_TCK;	//除以clk_tck把毫秒化为秒	

		printf("你本次答题时间为:%.2lf秒\n",time);
		printf("您的得分为:%d分\n",sum*5);	
		fputs("您本次答题时间为：",fp_ans);
		fprintf(fp_ans,"%.2lf秒",time);
		fputs("\n您的得分为:",fp_ans);
		fprintf(fp_ans,"%d分\n",sum*5);		 
	}
	fclose(fp);
	fclose(fp_ans);	
	//存入新文件并给文件改名
	fp = NULL;
	fp_ans = NULL;
	struct tm *p;//通过此结构体获取时间 
    char name[100];
    time_t timep;//time_t时间类型函数 从1970年开始计算的秒数 
    timep = time(NULL);//获取时间，单位为秒 
    p=localtime(&timep);//获取从1970至今过了多少秒，存入time_t类型的timep中并转换为struct tm 结构 
    strftime( name, 100, "%Y.%m.%d_%H %M %S.txt", p);//strftime可以转换成str字符串的时间格式 
	rename("solve_easy.txt",name);//rename（重命名文件名或目录 成功返回0，否则为-1） 
	return 0;	
	}
//与easy大致一样 
int problem_medium(){
	clock_t start,end;
	start = clock();
	int sum=0;
	
	FILE *fp,*fp_ans;
	fp = fopen("D:\\试题库\\medium.txt","r");
	fp_ans = fopen("D:\\试题库\\solve_medium.txt","w");
	
	if(fp == NULL){
		printf("文件打开失败！\n");
		exit(0);
	}else{
		while(!feof(fp)){
			char buf[20];
			fgets(buf,20,fp);
			int len = strlen(buf);
			int a=0,b=0;
			char c;
			
			for(int i=0;i<len-1;i++)
				printf("%c",buf[i]);	
			int flag = 0;
			for(int i=0;i<len;i++){
				if(flag == 0){
					if(buf[i] >= '0' && buf[i] <='9'){
						a = a * 10 + buf[i] - '0';
					}
				}
				
				if(buf[i] == '+') flag=1,c='+';
				if(buf[i] == '-') flag=1,c='-';
				if(buf[i] == '*') flag=1,c='*';
				if(buf[i] == '/') flag=1,c='/';
								
				if(flag == 1){
					if(buf[i] >= '0' && buf[i] <='9'){
						b = b * 10 + buf[i] - '0';
					}			
				}		
			}			
			int ans,your_ans;

			if(c == '+'){
				ans = a+b;
				fprintf(fp_ans,"%d",a);//
				fputs(" + ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
				scanf("%d",&your_ans);
				fprintf(fp_ans,"%d\n",your_ans);
				if(your_ans == ans)
					sum++;	
			}else if(c == '-'){
				ans = a-b;
				fprintf(fp_ans,"%d",a);
				fputs(" - ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
				scanf("%d",&your_ans);
				fprintf(fp_ans,"%d\n",your_ans);
				if(your_ans == ans)
					sum++;
			}else if(c == '*'){
				ans = a*b;
				fprintf(fp_ans,"%d",a);
				fputs(" * ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
				scanf("%d",&your_ans);
				fprintf(fp_ans,"%d\n",your_ans);
				if(your_ans == ans)
					sum++;				
			}else if(c == '/'){
				fprintf(fp_ans,"%d",a);
				fputs(" / ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
				int ans_fenzi,ans_fenmu,your_fenzi,your_fenmu=0;
				int t = gcd(a,b);
				ans_fenzi = a/t;
				ans_fenmu = b/t;
				if(ans_fenmu == 1){
					char str[10];//以字符串形式输入 
					scanf("%s",str);
					int length = strlen(str);
					int student_ans = 0;
					for(int i=0;i<length;i++){
						if(str[i] >= '0' && str[i] <='9'){
							student_ans = student_ans * 10 + str[i] - '0';
							}
						}		
					fprintf(fp_ans,"%s\n",str);
				if(student_ans == ans_fenzi) //当答案与分子相同时
					sum++;
				}else{
					scanf("%d/%d",&your_fenzi,&your_fenmu);	
					if(your_fenmu != 0)
						fprintf(fp_ans,"%d/%d\n",your_fenzi,your_fenmu);
						else
						fprintf(fp_ans,"%d\n",your_fenzi);
					if((ans_fenzi == your_fenzi) && (ans_fenmu == your_fenmu))
						sum++;
				}
			}	
			
		}
		end = clock();
		double time = (double)(end-start)/CLK_TCK;		
		printf("您本次答题的时间为:%.2lf秒\n",time);
		printf("您的得分为:%d分\n",sum*5);	
		fputs("您本次的答题时间为：",fp_ans);
		fprintf(fp_ans,"%.2lf秒",time);
		fputs("\n您的得分为: ",fp_ans);
		fprintf(fp_ans,"%d分\n",sum*5);		
	}
	fclose(fp);
	fclose(fp_ans);
	//存入新文件并给文件改名
	fp = NULL;
	fp_ans = NULL;
	struct tm *p;
    char name[100];
    time_t timep;
    timep = time(NULL); 
    p=localtime(&timep);
    strftime(name, 100, "%Y.%m.%d_%H %M %S.txt", p);
	rename("solve_medium.txt",name);
	return 0;
}

int problem_difficult(){
	clock_t start,end;
	start = clock();
	int sum=0;
	
	FILE *fp,*fp_ans;
	fp = fopen("D:\\试题库\\difficult.txt","r");
	fp_ans = fopen("D:\\试题库\\solve_difficult.txt","w");
	
	if(fp == NULL){
		printf("文件打开失败！\n");
		exit(0);
	}else{
		while(!feof(fp)){
			char buf[20];
			fgets(buf,20,fp);
			int len = strlen(buf);
			int a=0,b=1,c=0,d=1;//分别存储两个数的分子、分母
			char op;//记录符号
			for(int i=0;i<len-1;i++)
				printf("%c",buf[i]);

			int flag = 0;//用于判断前后两个数字
			a = buf[0] - '0';
			if(buf[1] == '/')
				b = buf[2] - '0';
				else
				b = 1;
				
			if(b == 1)//记录符号
				op = buf[2];
				else
				op = buf[4];
				
			for(int i=3;i<len;i++){
				if(buf[i] >= '0' && buf[i] <= '9' && flag == 0){
					c = buf[i] - '0';
					flag = 1;
					i++;//防止重复记录
				}
				if(flag == 1 && buf[i] >= '0' && buf[i] <= '9'){
					d = buf[i] - '0';
					
				}	
			}
									
			if(op == '+'){
				if(b == 1)	//将试卷写入作答试卷
					fprintf(fp_ans,"%d",a);
					else
					fprintf(fp_ans,"%d/%d",a,b);
				fputs(" + ",fp_ans);
				if(d == 1)
					fprintf(fp_ans,"%d",c);
					else
					fprintf(fp_ans,"%d/%d",c,d);
				fprintf(fp_ans," = ");
				
				int ans_fenzi,ans_fenmu,yourans_fenzi,yourans_fenmu=0;	//计算出案与输入的答案作比较
				int da_fenzi = b * d; 
				int da_fenmu = a*d + b*c;
				int t = gcd(da_fenmu,da_fenzi);
				ans_fenzi = da_fenzi / t;
				ans_fenmu = da_fenmu / t;
				
				if(ans_fenmu == 1){//当答案的分母为1时，输入应为一个整数，防止用户输错，用字符串输入
					char str[10];
					scanf("%s",str);
					int length = strlen(str);
					int student_ans ;
					for(int i=0;i<length;i++){
						if(str[i] >= '0' && str[i] <='9'){
								student_ans = student_ans * 10 + str[i] - '0';
							}
					}		
					fprintf(fp_ans,"%s\n",str);
					if(student_ans == ans_fenzi) //当答案与分子相同时
						sum++;
				}else{
					scanf("%d/%d",&yourans_fenzi,&yourans_fenmu);
					if(yourans_fenmu != 0)		//防止用户乱输入
						fprintf(fp_ans,"%d/%d\n",yourans_fenzi,yourans_fenmu);
						else
						fprintf(fp_ans,"%d\n",yourans_fenzi);
					if((ans_fenzi == yourans_fenzi) && (ans_fenmu == yourans_fenmu))
						sum++;
				}
				
			}else if(op == '-'){		//减法
				if(b == 1)					//将试卷写入作答试卷
					fprintf(fp_ans,"%d",a);
					else
					fprintf(fp_ans,"%d/%d",a,b);
				fputs(" - ",fp_ans);
				if(d == 1)
					fprintf(fp_ans,"%d",c);
					else
					fprintf(fp_ans,"%d/%d",c,d);
				fprintf(fp_ans," = ");
				
				int ans_fenzi,ans_fenmu,yourans_fenzi,yourans_fenmu=0;
				int da_fenmu = b * d;//计算出答案与输入的答案作比较
				int da_fenzi = a*d - b*c;
				int t = gcd(da_fenmu,da_fenzi);
				ans_fenzi = da_fenzi / t;
				ans_fenmu = da_fenmu / t;
				if(ans_fenmu == 1){	//当答案的分母为1时，输入应为一个整数，防止用户输错，用字符串输入
					char str[10];
					scanf("%s",str);
					int	length= strlen(str);
					int stu_ans ;
					for(int i=0;i<length;i++){
						if(str[i] >= '0' && str[i] <='9'){
								stu_ans = stu_ans * 10 + str[i] - '0';
							}
					}		
					fprintf(fp_ans,"%s\n",str);
					if(stu_ans == ans_fenzi) //当答案与分子相同时
						sum++;
				}else{
					scanf("%d/%d",&yourans_fenzi,&yourans_fenmu);
					if(yourans_fenmu != 0)
						fprintf(fp_ans,"%d/%d\n",yourans_fenzi,yourans_fenmu);
					else
						fprintf(fp_ans,"%d\n",yourans_fenzi);
					if((ans_fenzi == yourans_fenzi) && (ans_fenmu == yourans_fenmu))
						sum++;
				}										
			}else if(op == '*'){
				if(b == 1)					//将试卷写入作答试卷
					fprintf(fp_ans,"%d",a);
					else
					fprintf(fp_ans,"%d/%d",a,b);
				fputs(" * ",fp_ans);
				if(d == 1)
					fprintf(fp_ans,"%d",c);
					else
					fprintf(fp_ans,"%d/%d",c,d);
				fprintf(fp_ans," = ");
								
				int ans_fenzi,ans_fenmu,yourans_fenzi,yourans_fenmu=0;
				int da_fenmu = b * d;				//计算出答案与输入的答案作比较
				int da_fenzi = a * c;
				int t = gcd(da_fenmu,da_fenzi);
				ans_fenzi = da_fenzi / t;
				ans_fenmu = da_fenmu / t;
				
				if(ans_fenmu == 1){				//当答案的分母为1时，输入应为一个整数，防止用户输错，用字符串输入 
					char str[10];
					scanf("%s",str);
					int length = strlen(str);
					int stu_ans ;
					for(int i=0;i<length;i++){
						if(str[i] >= '0' && str[i] <='9'){
								stu_ans = stu_ans * 10 + str[i] - '0';
							}
					}
					
					fprintf(fp_ans,"%s\n",str);
					if(stu_ans == ans_fenzi) //当答案与分子相同时
						sum++;		
				}else{
					scanf("%d/%d",&yourans_fenzi,&yourans_fenmu);
					if(yourans_fenmu != 0)
						fprintf(fp_ans,"%d/%d\n",yourans_fenzi,yourans_fenmu);
					else
						fprintf(fp_ans,"%d\n",yourans_fenzi);
					if((ans_fenzi == yourans_fenzi) && (ans_fenmu == yourans_fenmu))
						sum++;
				}								
			}else if(op == '/'){//除法，与乘法相似，乘倒数即可
				if(b == 1)	//将试卷写入作答试卷
					fprintf(fp_ans,"%d",a);
					else
					fprintf(fp_ans,"%d/%d",a,b);
				fputs(" / ",fp_ans);
				if(d == 1)
					fprintf(fp_ans,"%d",c);
					else
					fprintf(fp_ans,"%d/%d",c,d);
				fprintf(fp_ans," = ");
				
				int ans_fenzi,ans_fenmu,yourans_fenzi,yourans_fenmu=0;
				int tempt = c; //借用乘法模板，颠倒一下除数分子分母
				c = d;
				d = tempt;
				
				int da_fenmu = b * d;				//计算出答案与输入的答案作比较
				int da_fenzi = a * c;
				int t = gcd(da_fenmu,da_fenzi);
				ans_fenzi = da_fenzi / t;
				ans_fenmu = da_fenmu / t;
				
				if(ans_fenmu == 1){				//当答案的分母为1时，输入应为一个整数，防止用户输错，用字符串输入
					char str[10];
					scanf("%s",str);
					int length = strlen(str);
					int stu_ans ;
					for(int i=0;i<length;i++){
						if(str[i] >= '0' && str[i] <='9'){
								stu_ans = stu_ans * 10 + str[i] - '0';
							}
					}
					
					fprintf(fp_ans,"%s\n",str);
					if(stu_ans == ans_fenzi) //当答案与分子相同时
						sum++;		
				}else{
					scanf("%d/%d",&yourans_fenzi,&yourans_fenmu);
					if(yourans_fenmu != 0)
						fprintf(fp_ans,"%d/%d\n",yourans_fenzi,yourans_fenmu);
					else
						fprintf(fp_ans,"%d\n",yourans_fenzi);
					if((ans_fenzi == yourans_fenzi) && (ans_fenmu == yourans_fenmu))
						sum++;
				}									
										
			}

		}
		end = clock();
		double time = (double)(end-start)/CLK_TCK;		
		
		printf("您本次答题的时间为:%.2lf秒\n",time);
		printf("您的得分为:%d分\n",sum*5);
		fputs("您的答题时间为：",fp_ans);
		fprintf(fp_ans,"%.2lf秒",time);
		fputs("\n您的得分为:",fp_ans);
		fprintf(fp_ans,"%d分\n",sum*5);		 
	}
	fclose(fp);
	fclose(fp_ans);
	//文件改名 
	fp = NULL;
	fp_ans = NULL;
	struct tm *p;
    char name[100];
    time_t timep;
    timep = time(NULL); 
    p=localtime(&timep);
    strftime( name, 100, "%Y.%m.%d_%H %M %S.txt", p);
	rename("solve_difficult.txt",name);	
	
	return 0;	
}

int main(){
	int nandu;
	printf("请选择难度 E easy M medium D difficult\n");
	        scanf("%c",&nandu);
	if(nandu == 'E'){
		problem_easy();
	}
		else if(nandu == 'M'){ 
			problem_medium();
		}
			else if(nandu == 'D'){
				problem_difficult();
				}
		system("pause");
}
