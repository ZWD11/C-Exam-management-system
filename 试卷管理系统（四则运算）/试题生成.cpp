#include<stdio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h> 

//求两数最小公约数 
    int gcd(int a,int b){
    int t; 
    while (b>0){
    t = a % b;
    a = b;
    b = t;
    }
    return a;
    }

//简单型试卷生成 
void problem_easy(){ 
	srand(time(NULL));//以时间为种子，使产生的题随机 
	FILE *fp,*fp_ans;
	fp = fopen("D:\\试题库\\easy.txt","w");
	fp_ans = fopen("D:\\试题库\\answer_easy.txt","w");
	int a,b;
	char c;	
	for(int i=0;i<20;i++){
		a = rand() % 11;//使a在十以内 （包括十） 
		b = rand() % 11;//使b在十以内 （包括十）
		c = rand() % 4 + 42;
		while(c != 43 && c != 45)//使运算符只能为加和减 
			c = rand()%4 + 42;
		while(c == 45 && b > a){//使不为负数 
			a = rand() % 11;
		}
			int ans;
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

		fprintf(fp,"%d %c %d = \n",a,c,b);
		fprintf(fp_ans,"%d\n",ans);
	}
	fclose(fp);
	fclose(fp_ans);
}

//medium型试卷生成 
void problem_medium(){
	srand(time(NULL));
	FILE *fp,*fp_ans;
	fp = fopen("D:\\试题库\\medium.txt","w");
	fp_ans = fopen("D:\\试题库\\answer_medium.txt","w");
	int a,b;
	char c;
	for(int i=0;i<20;i++){
		a = rand() % 101;//使每个数都在100以内（包括100） 
		b = rand() % 101;
		c = rand() % 6 + 42;
		while(c != 43 && c != 45 && c != 42 && c!= 47)//控制运算符为加减乘除 
			c = rand()%6 + 42;
		if(c == 45 && b > a)
			c = 43;
		if(c == 47 && b == 0)
			c = 42;
		while((c == 43 && a + b>100) || (c == 42 && a*b > 100)){//使操作数和结果均100内 
			a = rand() % 101;	
     	}
     	
			if(c == '+'){
				int ans;
				ans = a+b;
				fprintf(fp_ans,"%d",a);//
				fputs(" + ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
				fprintf(fp_ans,"%d\n",ans);
		}else if(c == '-'){
			    int ans;
				ans = a-b;
				fprintf(fp_ans,"%d",a);
				fputs(" - ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
				fprintf(fp_ans,"%d\n",ans);
		}else if(c == '*'){
			    int ans;
				ans = a*b;
				fprintf(fp_ans,"%d",a);
				fputs(" * ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
				fprintf(fp_ans,"%d\n",ans);		
		}else if(c == '/'){
				fprintf(fp_ans,"%d",a);
				fputs(" / ",fp_ans);
				fprintf(fp_ans,"%d",b);
				fputs(" = ",fp_ans);
				int ans_fenzi,ans_fenmu;
				int t = gcd(a,b);
				ans_fenzi = a/t;
				ans_fenmu = b/t;
				if(ans_fenmu == 1){
		           fprintf(fp_ans,"%d\n",ans_fenzi);
				}else{
					fprintf(fp_ans,"%d/%d\n",ans_fenzi,ans_fenmu);
				}
			}
			fprintf(fp,"%d %c %d = \n",a,c,b);
	}
	fclose(fp);
	fclose(fp_ans);		
}

//困难型试卷生成 
void problem_difficult(){
	srand(time(NULL));
	FILE *fp,*fp_ans;
	fp = fopen("D:\\试题库\\difficult.txt","w");
	fp_ans = fopen("D:\\试题库\\answer_difficult.txt","w");
	int a,b=1,d,e=1;
	char c;
	int flag1=0,flag2=0;//flag1为判断前面的那个是否为分式，flag2为后面那个 
	
	for(int i=0;i<20;i++){
		a = rand() % 9 +1;//使每个数都在1到九 
		b = rand() % 9 +1;
		c = rand()%6 + 42;//使c随机在42到47间 
		d = rand() % 9 +1;
		e = rand()%9 + 1;
		
		while(c != 43 && c != 45 && c != 42 && c != 47)//控制运算符为加减乘除 
			c = rand()%6 + 42;

		while( (double)a/b < (double)d/e && c == 45)//使结果不为负数 
			c = 43;
		
		if(a >= b && a % b==0){
			flag1 = 1;
			a = a/b;//使其为最简式 
		}
		if(d >= e && d % e == 0){
			flag2 = 1;
			d = d/e;
		}
		if(a < b && b % a ==0){
			int m = gcd(b,a);
			a=a/m;//使分式化简 
			b=b/m;
		}
		if(d < e && e % d ==0){
			int m = gcd(e,d);
			d=d/m;
			e=e/m;
		}					
			if(c == '+'){
				if(b == 1){
					fprintf(fp_ans,"%d",a);
					fprintf(fp,"%d",a);
				}
					else{
					fprintf(fp_ans,"%d/%d",a,b);
					fprintf(fp,"%d/%d",a,b);
					}
				fputs(" + ",fp_ans);
				fputs(" + ",fp);
				if(e == 1){
				
					fprintf(fp_ans,"%d",d);
					fprintf(fp,"%d",d);
				}
					else{
					
					 fprintf(fp_ans,"%d/%d",d,e);
					 	fprintf(fp,"%d/%d",d,e);
						 }
				fputs(" = ",fp_ans);
				fputs(" = \n",fp);
				
				int ans_fenzi,ans_fenmu;
				int da_fenmu = b * e;
				int da_fenzi = a*e + b*d;
				int t = gcd(da_fenmu,da_fenzi);
				ans_fenzi = da_fenzi / t;
				ans_fenmu = da_fenmu / t;
				if(ans_fenmu == 1){
					fprintf(fp_ans,"%d\n",ans_fenzi);
				}else{
					fprintf(fp_ans,"%d/%d\n",ans_fenzi,ans_fenmu);
				}
			}else if(c == '-'){				
				if(b == 1){
							
					fprintf(fp_ans,"%d",a);
					fprintf(fp,"%d",a);}
					else{
					
					fprintf(fp_ans,"%d/%d",a,b);
					fprintf(fp,"%d/%d",a,b);
				}
				fputs(" - ",fp_ans);
					fputs(" - ",fp);
				if(e == 1){
				
					fprintf(fp_ans,"%d",d);
					fprintf(fp,"%d",d);
				}
					else{
					
					fprintf(fp_ans,"%d/%d",d,e);
					fprintf(fp,"%d/%d",d,e);
				}
				fputs(" = ",fp_ans);
				fputs(" = \n",fp);
				
				int ans_fenzi,ans_fenmu;
				int da_fenmu = b * e;
				int da_fenzi = a*e - b*d;
				int t = gcd(da_fenmu,da_fenzi);
				ans_fenzi = da_fenzi / t;
				ans_fenmu = da_fenmu / t;
			if(ans_fenmu == 1){
					fprintf(fp_ans,"%d\n",ans_fenzi);
				}else{
					fprintf(fp_ans,"%d/%d\n",ans_fenzi,ans_fenmu);
				}
			}else if(c == '*'){
				if(b == 1){
			
					fprintf(fp_ans,"%d",a);
					fprintf(fp,"%d",a);
					}
					else{
					
					fprintf(fp_ans,"%d/%d",a,b);
					fprintf(fp,"%d/%d",a,b);
				}
				fputs(" * ",fp_ans);
				fputs(" * ",fp);
				if(e == 1){
				
					fprintf(fp_ans,"%d",d);
					fprintf(fp,"%d",d);}
					else{
					
					fprintf(fp_ans,"%d/%d",d,e);
					fprintf(fp,"%d/%d",d,e);}
				fputs(" = ",fp_ans);
				fputs(" = \n",fp);
								
				int ans_fenzi,ans_fenmu,yourans_fenzi,yourans_fenmu=0;
				int da_fenmu = b * e;			
				int da_fenzi = a * d;
				int t = gcd(da_fenmu,da_fenzi);
				ans_fenzi = da_fenzi / t;
				ans_fenmu = da_fenmu / t;
					if(ans_fenmu == 1){
					fprintf(fp_ans,"%d\n",ans_fenzi);
				}else{
					fprintf(fp_ans,"%d/%d\n",ans_fenzi,ans_fenmu);
				}
			}else if(c == '/'){//除法，与乘法相似，乘倒数即可
				if(b == 1){
				
					fprintf(fp_ans,"%d",a);
					fprintf(fp,"%d",a);}
					else{
					
					fprintf(fp_ans,"%d/%d",a,b);
					fprintf(fp,"%d/%d",a,b);}
				fputs(" / ",fp_ans);
				fputs(" / ",fp);
				if(e == 1){
				
					fprintf(fp_ans,"%d",d);
					fprintf(fp,"%d",d);}	
					else{
					
					fprintf(fp_ans,"%d/%d",d,e);
					fprintf(fp,"%d/%d",d,e);
				}
				fputs(" = ",fp_ans);
				fputs(" = \n",fp);
				
				int ans_fenzi,ans_fenmu,yourans_fenzi,yourans_fenmu=0;
				int tempt = d; //借用乘法模板，颠倒一下除数分子分母
				d = e;
				e = tempt;
				
				int da_fenmu = b * e;				//计算出答案与输入的答案作比较
				int da_fenzi = a * d;
				int t = gcd(da_fenmu,da_fenzi);
				ans_fenzi = da_fenzi / t;
				ans_fenmu = da_fenmu / t;
					if(ans_fenmu == 1){
					fprintf(fp_ans,"%d\n",ans_fenzi);
				}else{
					fprintf(fp_ans,"%d/%d\n",ans_fenzi,ans_fenmu);
				}
			}
	}
	fclose(fp);
	fclose(fp_ans);		
}

int main(){
	problem_easy();
	problem_medium();
	problem_difficult();
	printf("\n试卷与答案已生成！\n\n");	
	system("pause");
}
