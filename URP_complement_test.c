#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LEN sizeof(struct CubeList)
#define MAX 50
#define buff_size 5
struct CubeList
{
	char pcn_expression[MAX];
	struct CubeList * next;
};
short int Variable_Count = 0, SOP_Count = 0;
bool Simple_test_flag = false;
char buff[buff_size] = {0};
struct CubeList * function_buff[32];

void Buff_Clear(char buff[])
{
	int i = 0;
	for(;i < buff_size; i++)
		buff[i] = NULL;
}

int Valid_Int_to_Char(int x, char buff[])// x is the value needed conversion
{
	itoa(x, buff, 10);
	int i = 0, count = 0;
	for(;i < buff_size; i++)
	{
		if(buff[i] != 0)
			count++;
	}
	return count;
}

struct CubeList * Dont_Care_Cube()
{
	struct CubeList * p1;
	int i = 0;
	p1 = (struct CubeList *)malloc(LEN);
	for(i = 0;i < Variable_Count; i++)
		{p1 -> pcn_expression[2*i] = '1';p1 -> pcn_expression[2*i + 1] = '1';}
	p1 -> next = NULL;
	return p1;
}

struct CubeList * CubeList_generate(FILE *fo)
{
	int i = 0, j = 0;
	char flag = 0;
	struct CubeList *p1 ,*p2, *head = NULL;
	for(i = 0; i < buff_size; i++)
	{
		flag = fgetc(fo);
		if(flag <= 57 && flag >= 48)
			buff[i] = flag;
		if(flag == '\n')
			break;
	}
	Variable_Count = atoi(buff);
	Buff_Clear(buff);
	for(i = 0; i < buff_size; i++)
	{
		flag = fgetc(fo);
		if(flag <= 57 && flag >= 48)
			buff[i] = flag;
		if(flag == '\n')
			break;
	}
	SOP_Count = atoi(buff);
	Buff_Clear(buff);
	p1 = p2 = Dont_Care_Cube();
	head = p1;
	//////////////////////////////////////////////
	while(!feof(fo))
	{
		if(flag != ' ')          //jump the first num
			flag = fgetc(fo);
		else
		{
			while(flag != '\n')// flag == ' '
			{
				for(i = 0; i < buff_size; i++)
				{
					flag = fgetc(fo);
					if((flag <= 57 && flag >= 48) || flag == '-')
						buff[i] = flag;
					if(flag == ' ' || flag == '\n')
						break;
				}
				if(atoi(buff) > 0)
					p1 -> pcn_expression[2 * (atoi(buff) - 1)] = '0';
				if(atoi(buff) < 0)
					p1 -> pcn_expression[2 * (abs(atoi(buff)) - 1) + 1] = '0';
				Buff_Clear(buff);
			}
			if(j < SOP_Count - 1)
			{
				p1 = Dont_Care_Cube();
				p2 -> next = p1;
				p2 = p1;
			}
			j++;
		}
	}
	return (head);
}

struct CubeList * positiveCofactor(struct CubeList * input, int x)
{
	if(input == NULL)
		return NULL;
	struct CubeList * pos1, * head, * pos2, * tail, * NEW;
	int i;
	pos2 = pos1 = (struct CubeList *)malloc(LEN);
	NEW = tail = head = pos1;
	while(input != NULL)
	{
		for(i = 0;i < MAX; i++)
			pos1 -> pcn_expression[i] = input -> pcn_expression[i];
		if(input -> next != NULL)
		{
			pos1 = (struct CubeList *)malloc(LEN);
			pos2 -> next = pos1;
			pos2 = pos1;
		}
		else pos2 -> next = NULL;
		input = input -> next;
	}
	i = 0;
	while(head != NULL)//cofactor
	{

		if(i == 2)
		{tail = tail -> next;i = 1;}
		if(head -> pcn_expression[2 * (x-1)] == '1' && head -> pcn_expression[2 * (x-1) + 1] == '1')
			{head = head -> next;i++;continue;}
		if(head -> pcn_expression[2 * (x-1)] == '0' && head -> pcn_expression[2 * (x-1) + 1] == '1')
			{head -> pcn_expression[2 * (x-1)] = '1'; head = head -> next; i++; continue;}
		if(head -> pcn_expression[2 * (x-1)] == '1' && head -> pcn_expression[2 * (x-1) + 1] == '0')
		{
			if(head == tail)
			{
				tail = tail -> next; free(head); NEW = head = tail;//if the only cube is freed, tail = head = new = NULL
				continue;
			}
			if(head -> next != NULL)
			{
				tail -> next = head -> next;
				free(head);
				head = tail -> next;
			}
			else
			{
				free(head);
				tail -> next = NULL;
				break;
			}
		}
	}
	return NEW;
}

struct CubeList * negativeCofactor(struct CubeList * input, int x)
{
	if(input == NULL)
		return NULL;
	struct CubeList * pos1, * head, * pos2, * tail, * NEW;
	int i;
	pos2 = pos1 = (struct CubeList *)malloc(LEN);
	NEW = tail = head = pos1;
	while(input != NULL)
	{
		for(i = 0;i < MAX; i++)
			pos1 -> pcn_expression[i] = input -> pcn_expression[i];
		if(input -> next != NULL)
		{
			pos1 = (struct CubeList *)malloc(LEN);
			pos2 -> next = pos1;
			pos2 = pos1;
		}
		else pos2 -> next = NULL;
		input = input -> next;

	}
	i = 0;
	while(head != NULL)//cofactor
	{

		if(i == 2)
		{tail = tail -> next;i = 1;}
		if(head -> pcn_expression[2 * (x-1)] == '1' && head -> pcn_expression[2 * (x-1) + 1] == '1')
			{head = head -> next;i++;continue;}
		if(head -> pcn_expression[2 * (x-1)] == '1' && head -> pcn_expression[2 * (x-1) + 1] == '0')
			{head -> pcn_expression[2 * (x-1) + 1] = '1'; head = head -> next; i++; continue;}
		if(head -> pcn_expression[2 * (x-1)] == '0' && head -> pcn_expression[2 * (x-1) + 1] == '1')
		{
			if(head == tail)
			{
				tail = tail -> next; free(head); NEW = head = tail;
				continue;
			}
			if(head -> next != NULL)
			{
				tail -> next = head -> next;
				free(head);
				head = tail -> next;
			}
			else
			{
				free(head);
				tail -> next = NULL;
				break;
			}
		}
	}
	return NEW;
}

struct CubeList * Half_AND(int x, struct CubeList * input)
{
	if(input == NULL)
		return NULL;
	struct CubeList * head;
	head = input;
	if(x > 0)
	{
		while(input != NULL)
		{
			input -> pcn_expression[2 * (x-1)] = '0';
			input -> pcn_expression[2 * (x-1) + 1] = '1';
			input = input -> next;
		}
	}
	if(x < 0)
	{
		while(input != NULL)
		{
			input -> pcn_expression[2 * ((-x) -1) + 1] = '0';
			input -> pcn_expression[2 * ((-x) -1) ] = '1';
			input = input -> next;
		}
	}

	return head;
}

struct CubeList * OR(struct CubeList * p1, struct CubeList * p2)
{
    struct CubeList * head1, * head2, * pos1, * pos2, * pos3, * pos4, * head, * head3, * head4;
    int i = 0;
    head1 = p1;
    head2 = p2;
    if(p1 != NULL)
    	head3 = pos1 = pos2 = (struct CubeList *)malloc(LEN);
    else
        pos1 = NULL;
    if(p2 != NULL)
    	head4 = pos3 = pos4 = (struct CubeList *)malloc(LEN);
    else
        pos3 = NULL;
    while(p1 != NULL)
	{
		for(i = 0;i < MAX; i++)
			pos1 -> pcn_expression[i] = p1 -> pcn_expression[i];
		if(p1 -> next != NULL)
		{
			pos1 = (struct CubeList *)malloc(LEN);
			pos2 -> next = pos1;
			pos2 = pos1;
		}
		else
            {pos2 -> next = NULL; pos1 = head3;}
		p1 = p1 -> next;
	}
	p1 = head1;
	while(p2 != NULL)
	{
		for(i = 0;i < MAX; i++)
			pos3 -> pcn_expression[i] = p2 -> pcn_expression[i];
		if(p2 -> next != NULL)
		{
			pos3 = (struct CubeList *)malloc(LEN);
			pos4 -> next = pos3;
			pos4 = pos3;
		}
		else
            {pos4 -> next = NULL; pos3 = head4;}
		p2 = p2 -> next;
	}

	p2 = head2;
	if(pos1 == NULL && pos3 != NULL)
		return pos3;
	if(pos1 != NULL && pos3 == NULL)
		return pos1;
	if(pos1 == NULL && pos3 == NULL)
		return NULL;

	head = pos1;
	while(pos1 -> next != NULL)
		pos1 = pos1 -> next;
	pos1 -> next = pos3;
	return head;
}

bool Complememnt_Simple_test(struct CubeList * input)
{
	int i = 0;
	if(input == NULL || input -> next == NULL)
		{return true;}
	while(input != NULL)
	{

		for(i = 0;i < Variable_Count;i++)
		{
			if(input -> pcn_expression[2*i] != '1' || input -> pcn_expression[2*i + 1] != '1')
				break;
		}
		if(i == Variable_Count)
		{Simple_test_flag = true; return true;}
		input = input -> next;
	}
	return false;
}

struct CubeList * Complememnt_Simple(struct CubeList * input)
{
	struct CubeList * p1, * p2, * head, * ini;
	int i = 0;
    if(Simple_test_flag) // dont cares in a cube with more than 2 lines
		{Simple_test_flag = false; return NULL;}
	ini = Dont_Care_Cube();
	if(input == NULL) // input is 0
		return ini;
	p1 =  (struct CubeList *)malloc(LEN);
	p1 -> next = ini;
	// dont cares in a cube with 1 line
	for(i = 0; i < Variable_Count; i++)
	{
		if(input -> pcn_expression[2*i] != '1' || input ->pcn_expression[2*i + 1] != '1')
			break;
	}
	if(i == Variable_Count)
		return NULL;
	// cube has 1 line and it is not a dont care
	for(i = 0; i < Variable_Count; i++)
	{
		if(input -> pcn_expression[2*i] == '1' && input -> pcn_expression[2*i + 1] == '1')
			continue;
		if(input -> pcn_expression[2*i] == '0' && input -> pcn_expression[2*i + 1] == '1')
		{
			if(p1 -> next != NULL)
				{head = p2 = p1 = Dont_Care_Cube();}
			else
			{
				p1 = Dont_Care_Cube();
				p2 -> next = p1;
				p2 = p1;
			}
			p1 -> pcn_expression[2*i + 1] = '0';
		}
		if(input -> pcn_expression[2*i] == '1' && input -> pcn_expression[2*i + 1] == '0')
		{
			if(p1 -> next != NULL)
				{head = p2 = p1 = Dont_Care_Cube();}
			else
			{
				p1 = Dont_Care_Cube();
				p2 -> next = p1;
				p2 = p1;
			}
			p1 -> pcn_expression[2*i] = '0';
		}
	}
	return head;

}

int Most_Binate(struct CubeList * input)
{
	int T[MAX] = {0}, C[MAX] = {0}, sum = 0, flag = 0;
	int i = 0, index[MAX] = {0}, delta[MAX] = {0};
	while(input != NULL)
	{
		for(i = 0; i < Variable_Count; i++)
		{
			if(input -> pcn_expression[2*i] == '1' && input -> pcn_expression[2*i + 1] == '1')
				continue;
			if(input -> pcn_expression[2*i] == '0' && input -> pcn_expression[2*i + 1] == '1')
				T[i] = T[i] + 1;
			if(input -> pcn_expression[2*i] == '1' && input -> pcn_expression[2*i + 1] == '0')
				C[i] = C[i] + 1;
		}
		input = input -> next;
	}
	for(i = 0; i < Variable_Count; i++)
	{
		if(sum < T[i] + C[i] && T[i] != 0 && C[i] != 0)
			sum = T[i] + C[i];
	}
	if(sum != 0)
	{
		for(i = 0; i < Variable_Count; i++)
		{
			if(sum == T[i] + C[i] && T[i] != 0 && C[i] != 0)
			{
				index[i] = 1;
				delta[i] = abs(T[i] - C[i]);
			}
		}
		for(i = 0, sum = SOP_Count; i < MAX; i++)
		{
			if(index[i])
				if(delta[i] < sum)
					{sum = delta[i]; flag = i;}
		}
		return flag+1;
	}
	else
	{
		for(i = 0; i < Variable_Count; i++)
		{
			if(sum < T[i] + C[i])
				{sum = T[i] + C[i]; flag = i;}
		}
		return flag+1;
	}

}

struct CubeList * Complememnt(struct CubeList * input)
{
	bool flag = false;
	struct CubeList * P, * N, * head;
	int x = 0;
	head = input;
	flag = Complememnt_Simple_test(input);
	input = head;
	printf("a\n");
	if(flag)
		{printf("b\n");return Complememnt_Simple(input);}
	x = Most_Binate(input);
	printf("%d\n", x);
	input = head;
	P = Complememnt(positiveCofactor(input, x));
	input = head;
	N = Complememnt(negativeCofactor(input, x));
	input = head;
	P = Half_AND(x, P);
	N = Half_AND(-x, N);
	return OR(P, N);
}

struct CubeList * AND(struct CubeList * p1, struct CubeList * p2)
{
	return Complememnt(OR(Complememnt(p1), Complememnt(p2)));
}

void Write_to_File(struct CubeList * input, FILE * fw)
{
	int count = 0;
	int i = 0;
	int valid_size = 0;
	struct CubeList * head;
	head = input;
	while(input != NULL)
	{
		count++;
		input = input -> next;
	}
	valid_size = Valid_Int_to_Char(Variable_Count, buff); //write Variable_Count into the buffer as a decimal number
	fwrite(buff, valid_size, 1, fw);// buff, size, count, fw
	fputc('\n', fw);
	Buff_Clear(buff);
	valid_size = Valid_Int_to_Char(count, buff);
	fwrite(buff, valid_size, 1, fw);
	fputc('\n', fw);
	Buff_Clear(buff);
	count = 0;
	////////////////////////////////////////
	//write actual cube
	while(head != NULL)
	{
		for(i = 0; i < Variable_Count; i++)
		{
			if(head -> pcn_expression[2*i] == '1' && head -> pcn_expression[2*i + 1] == '1')
				continue;
			count++;
		}
		Buff_Clear(buff);
		valid_size = Valid_Int_to_Char(count, buff);
		fwrite(buff, valid_size, 1, fw);// starter of every line
		count = 0;
		for(i = 0; i < Variable_Count; i++)
		{
			if(head -> pcn_expression[2*i] == '1' && head -> pcn_expression[2*i + 1] == '1')
				continue;
			if(head -> pcn_expression[2*i] == '1' && head -> pcn_expression[2*i + 1] == '0')
			{
                fputc(' ', fw);
				Buff_Clear(buff);
				valid_size = Valid_Int_to_Char(-(i + 1), buff);
				fwrite(buff, valid_size, 1, fw);
				continue;
			}
			if(head -> pcn_expression[2*i] == '0' && head -> pcn_expression[2*i + 1] == '1')
			{
                fputc(' ', fw);
				Buff_Clear(buff);
				valid_size = Valid_Int_to_Char(i + 1, buff);
				fwrite(buff, valid_size, 1, fw);
				continue;
			}
		}
		head = head -> next;
		fputc('\n', fw);
	}
}


void Parse_the_Command(FILE * fo)
{
	char flag = 0;
	char file_name[150] = "E:/VLSI EDA/programming/C/URP_Complement/BooleanCalculatorEngine/";
	char file_name_copy[150] = "E:/VLSI EDA/programming/C/URP_Complement/BooleanCalculatorEngine/";
	int i = 0, op1 = 0, op2 = 0, op3 = 0;
	FILE *fp1 ,*fw1;
	while(flag != 'q')
	{
		flag = fgetc(fo);// parse the first letter
		if(flag == 'r')
		{
			Buff_Clear(buff);
			flag = fgetc(fo);//avoid the first space
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48))
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			strcat(file_name, buff);
			strcat(file_name, ".pcn");//complete the file direction
			if((fp1 = fopen(file_name, "r")) == NULL)
			{
				printf("cannot open this file2!\n");
				exit(0);
			}//open file
			function_buff[atoi(buff)] = CubeList_generate(fp1);//generate
			fclose(fp1);
			for(i = 0; i < 150; i++)
                file_name[i] = file_name_copy[i];
		}
		if(flag == '!')
		{
			Buff_Clear(buff);
			flag = fgetc(fo);//avoid the first space
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48) || flag == '-')
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			op1 = atoi(buff);
			Buff_Clear(buff);
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48) || flag == '-')
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			op2 = atoi(buff);// extract the two opcodes
			function_buff[op1] = Complememnt(function_buff[op2]);
			op1 = op2 = op3 = 0;
		}
		if(flag == '&')
		{
			Buff_Clear(buff);
			flag = fgetc(fo);//avoid the first space
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48) || flag == '-')
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			op1 = atoi(buff);
			Buff_Clear(buff);
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48) || flag == '-')
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			op2 = atoi(buff);// extract the second opcodes
			Buff_Clear(buff);
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48) || flag == '-')
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			op3 = atoi(buff);// extract the third opcodes
			function_buff[op1] = AND(function_buff[op2], function_buff[op3]);
			op1 = op2 = op3 = 0;
		}
		if(flag == '+')
		{
			Buff_Clear(buff);
			flag = fgetc(fo);//avoid the first space
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48) || flag == '-')
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			op1 = atoi(buff);
			Buff_Clear(buff);
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48) || flag == '-')
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			op2 = atoi(buff);// extract the second opcodes
			Buff_Clear(buff);
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48) || flag == '-')
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			op3 = atoi(buff);// extract the third opcodes
			function_buff[op1] = OR(function_buff[op2], function_buff[op3]);
			op1 = op2 = op3 = 0;
		}
		if(flag == 'p')
		{
			Buff_Clear(buff);
			flag = fgetc(fo);//avoid the first space
			for(i = 0; i < buff_size; i++)
			{
				flag = fgetc(fo);
				if((flag <= 57 && flag >= 48) || flag == '-')
					buff[i] = flag;
				if(flag == ' ' || flag == '\n')
					break;
			}
			strcat(file_name, buff);
			strcat(file_name, ".pcn");
			if((fw1=fopen(file_name,"w")) == NULL)
			{
				printf("cannot open this file3!\n");
				exit(0);
			}
			Write_to_File(function_buff[atoi(buff)], fw1);
			fclose(fw1);
		}
		if(flag == 'q')
			continue;
	}
}

int main(){
	FILE *fp;

	if((fp=fopen("E:/VLSI EDA/programming/C/URP_Complement/BooleanCalculatorEngine/cmd6.txt","r")) == NULL)
	{
		printf("cannot open this file1!\n");
		exit(0);
	}
	Parse_the_Command(fp);
	return 0;
}
