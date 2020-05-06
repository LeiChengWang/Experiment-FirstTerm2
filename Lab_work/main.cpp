#include <iostream>
using namespace std;
#include <string.h>
#include <stdlib.h>
#include <windows.h>

/*------------------------�ṹ��start--------------------------*/

//���ڡ��ꡢ�¡��ա�
struct Data
{
	int year; 
	int month;
	int day;
};

//����
struct material
{
	char seri_number[20];      //���
	char name[20];             //����
	float unit_price;          //����

	char in_out[5];            //������¼

	int  in_num;               //�������
	struct Data in_time;       //���ʱ��

	int out_num;               //��������
	struct Data out_time;      //����ʱ��

	char person[20];           //������
	int  store_num;            //�������
	char note[100];            //��ע

	material* next;            //��һ�����ָ��
};


/*--------------------------ö��start---------------------------*/

//���˵�
enum main_menu
{
	add_record=1,    //��Ӽ�¼
	show_record,   //��ʾ��¼
	search_record, //��ѯ��¼
	change_record, //�޸ļ�¼
	write_file	   //д���ļ� 
}main_menu_switch;


//��һ���Ӳ˵�
enum first_menu
{
	add_more=1,                 //��Ӹ���ļ�¼
	first_exit_to_main         //�������˵�
}first_menu_switch;

//��Ӽ�¼ģʽ�˵�
enum add_record_modei_menu
{
	add_one=1,      //���һ����¼
	add_two,        //��Ӷ�����¼
	add_from_file   //���ļ���Ӽ�¼
}add_record_model_menu;

//�ڶ����Ӳ˵�
enum second_menu
{
	show_more=1,     //��ʾ����ļ�¼
	second_exit_to_main  //�������˵�
}second_menu_switch;

//��ʾ��¼ģʽ�˵�
enum show_record_mode_menu
{
	record_List=1,   //��ʾ����¼
	cangku_Item      //��ʾ�ֿ���Ʒ�嵥
}show_record_mode_menu;

//�������Ӳ˵�
enum third_menu
{
	conti_to_search=1,     //����ɸѡ
	anew_search,         //����ɸѡ 
	third_exit_to_main    //�������˵�
}third_menu_switch;

//���ĸ��Ӳ˵�
enum forth_menu
{
	 change_one=1,       //�޸ĵ�������¼
	 change_together   //�����޸�

}forth_menu_switch;

//���ĸ����Ӳ˵�
enum forth_sub_menu
{
	continue_change = 1,     //�����޸ı���¼��������
	change_others,           //�޸���������¼
	show_change_data,        //��ʾ�޸ĺ������
	forth_exit_to_main       //�������˵�
}forth_sub_menu_switch;

//�������Բ˵�
enum material_menu
{
	seri_number=1,  //���
	name,           //����
	unit_price,     //����
	person,         //������	
	in_out_way,      //����ⷽʽ
	record_data,     //��¼������
	note,           //��ע
}sec_sub,forth_sub;


//������Ӳ˵�
enum fifth_menu
{
	save_to_other=1,       //���浽�����ĵط�
	fifth_exit_to_main    //�������˵�
}fifth_menu_switch;


//���Ͽ��ʼ��ģʽ�˵�
enum material_Base_init
{
	file_in=1,   //�ļ�����
	handwrite  //�ֶ�����
}Base_init;



/*--------------------------��������start---------------------*/

//�˵���������
int Main_menu();         //��ʾ���˵�
int First_menu();        //��ʾ��һ���Ӳ˵�    
int Second_menu();       //��ʾ�ڶ����Ӳ˵�    
int Third_menu();        //��ʾ�������Ӳ˵�  
int Forth_menu();        //��ʾ���ĸ��Ӳ˵�
int Forth_sub_menu();    //��ʾ���ĸ��Ӳ˵����Ӳ˵�
int Material_menu();      //��ʾ�������Բ˵�(���Ͳֿ�)
int Fifth_menu();         //��ʾ������Ӳ˵�   
int material_base_menu();  //��ʾ���ϳ�ʼ��ģʽ�˵�
void Add_record_menu();     //��ʾ��Ӽ�¼�˵�
int Add_record_model_menu();  //��ʾ��Ӽ�¼ģʽ�˵�
int Show_record_mode_menu();     //��ʾ��¼ģʽ�˵�


//���ܺ�������



//����صĺ���

struct material* Creat_ku();               //�������Ͽ⡾��������
void print_ori(struct material* head);     //���ԭʼ��
struct material* Creat_Item_List();        //������Ʒ�Ĳֿ�(����һ��ͷ���)  
void Print_ku(struct material* thi_head);  //����ֿ����Ʒ

void Handout_ku_init(struct material* head, struct material* sec_head);   //����¼�����ʼ�����ֿ���Ʒ���ࡿ

//Update ��صĺ���
void Join_to_record_List(struct material* new_record, struct material* record_List);  //��ĳ�����¼���¼�¼������
void Join_record(struct material* now_record, struct material* sec_head);            //��ĳ�����¼���µ��ֿ���Ʒ��

//��Ӽ�¼��صĺ���

int Add_one_record(int mode);       //��ӵ�����¼�����кͲֿ���   ����ֵ�жϵ�����¼�����Ƿ����  0-���� 1-������
void Add_many_record();      //��Ӷ�����¼�����Ͳֿ���


/*---------------------------ȫ�ֱ�����ָ��start-------------------*/

int all_temp;  //���ڼ�¼ʵʱѡ��ĸ��ֲ˵�ֵ
int sum_record;   //��������
int sum_item;     //�ֿ���Ʒ������
material* base_head;    //���Ͽ����¼��ͷָ��
material* ku_head;    //�ֿ���Ʒ��ͷָ��



int main()
{
	//���Ͽ��ʼ������
	sum_record = 0;
	sum_item = 0;

	//������  
	base_head=Creat_ku();

	//print_ori(base_head);     //���ԭʼ�ı���¼

	//�����ֿ�
	ku_head=Creat_Item_List();

	Handout_ku_init(base_head, ku_head);     //���ոս����ı���¼���µ��ֿ����Ʒ�嵥�У���ʼ��������

	//Print_ku(ku_head);            //����ֿ����Ʒ�嵥


	//����ֿ��ʵʱ���Ϲ���ϵͳ
	while (1)
	{
		all_temp=Main_menu();  //�õ����˵���ѡ��ֵ

		main_menu_switch = (main_menu)all_temp;  //ö�����͵�ת��

		//ִ����Ӽ�¼����1
		if (main_menu_switch == add_record)
		{
			while (1)
			{
				//��Ӽ�¼��صĹ���
				all_temp=Add_record_model_menu();   //��ʾ��Ӽ�¼ģʽ�˵�
				add_record_model_menu = (add_record_modei_menu)all_temp;
				if (add_record_model_menu == add_one)
				{
					Add_record_menu();         //��ʾ��Ӽ�¼�˵�

					//��ӵ�����¼����
					Add_one_record(1);
				}
				else if (add_record_model_menu == add_two)
				{
					Add_record_menu();         //��ʾ��Ӽ�¼�˵�

					//��Ӷ�����¼�Ĺ���
					Add_many_record();
				}
				else if (add_record_model_menu == add_from_file)
				{
					Add_record_menu();         //��ʾ��Ӽ�¼�˵�

					//���ļ���Ӽ�¼�Ĺ���

				}
				

				//������¼
				all_temp = First_menu();
				first_menu_switch = (first_menu)all_temp;
				//������Ӽ�¼
				if (first_menu_switch == add_more)   continue;
				//�ص����˵�
				else if (first_menu_switch == first_exit_to_main)  break;			
			}
		}

		//ִ����ʾ��¼����2
		else if (main_menu_switch == show_record)
		{
			while (1)
			{
				//��ʾ��¼��صĹ���

				 //��ʾ��¼ģʽ�˵�
				all_temp=Show_record_mode_menu();    
				show_record_mode_menu = (enum show_record_mode_menu)all_temp;
				
				//����¼�������ʾ
				if(show_record_mode_menu== record_List)
				{
					//ѡ����ʾ����¼������
					all_temp = Material_menu();
					sec_sub = (material_menu)all_temp;
				}


				//�ֿ��嵥�������ʾ
				else if (show_record_mode_menu == cangku_Item)
				{

				}



				
				


				//��ʾ���¼
				all_temp = Second_menu();
				second_menu_switch = (second_menu)all_temp;
				//������Ӽ�¼
				if (second_menu_switch == show_more)   continue;
				//��ʾ���˵�
				else if (second_menu_switch == second_exit_to_main)  break;
			}
		}
		
		//ִ�в�ѯ��¼����3
		else if (main_menu_switch == search_record)
		{
			while (1)
			{
				//��ѯ��¼��صĹ���

				//��ѯ���¼
				all_temp = Third_menu();
				third_menu_switch = (third_menu)all_temp;
				//����ɸѡ
				if (third_menu_switch == conti_to_search)
				{

				}
				//���²�ѯ
				else if (third_menu_switch == anew_search)  continue;
				//�ص����˵�
				else if (third_menu_switch == third_exit_to_main)  break;

			}
		}

		//ִ���޸ļ�¼����4
		else if (main_menu_switch == change_record)
		{
			int change_flag = 1;  //�޸ı�־λ
			while (1)
			{

				//ѡ���޸�ģʽ
				all_temp = Forth_menu();
				forth_menu_switch = (forth_menu)all_temp;
				if (forth_menu_switch == change_one)
				{
					while (1)
					{
						//��һ���޸ĵ�������¼
						if (change_flag == 1)
						{
								//ѡ��Ҫ�޸ĵĲ�������ֵ	
								all_temp = Material_menu();
								forth_sub = (material_menu)all_temp;

								//ִ�е�һ���޸Ĺ���


						}

						//�����޸ĸñ���¼
						else if (change_flag == 2)
						{
								//ѡ�����Ҫ�޸ĵĲ�������ֵ	
								all_temp = Material_menu();
								forth_sub = (material_menu)all_temp;

								//����ִ���޸Ĺ���
						}
						else if (change_flag == 3)
						{
							//ִ���޸ĺ�������ʾ�Ĺ���

						}



						//�޸���ɺ�
						all_temp = Forth_sub_menu();
						forth_sub_menu_switch = (forth_sub_menu)all_temp;
						if (forth_sub_menu_switch == continue_change)
						{
								change_flag = 2;
						}
						if (forth_sub_menu_switch == change_others)
						{
								change_flag = 1;
						}
						if (forth_sub_menu_switch == show_change_data)
						{
								change_flag = 3;
						}
						if (forth_sub_menu_switch == forth_exit_to_main)
						{
								break;    //�˳��޸�ģʽ
						}
					}

				}
				
				if (forth_menu_switch == change_together)
				{
					while (1)
					{
						//�����޸ı���¼
						//ѡ��Ҫ�޸ĵĲ�������ֵ	
						all_temp = Material_menu();
						forth_sub = (material_menu)all_temp;


						//��һ���޸ĵ�������¼
						if (change_flag == 1)
						{
							//ѡ��Ҫ�޸ĵĲ�������ֵ	
							all_temp = Material_menu();
							forth_sub = (material_menu)all_temp;

							//ִ�е�һ���޸Ĺ���


						}

						//�����޸ĸñ���¼
						else if (change_flag == 2)
						{
							//ѡ�����Ҫ�޸ĵĲ�������ֵ	
							all_temp = Material_menu();
							forth_sub = (material_menu)all_temp;

							//����ִ���޸Ĺ���
						}

						else if (change_flag == 3)
						{
							//ִ���޸ĺ�������ʾ�Ĺ���

						}


						//�޸���ɺ�
						all_temp = Forth_sub_menu();
						forth_sub_menu_switch = (forth_sub_menu)all_temp;
						if (forth_sub_menu_switch == continue_change)
						{
							change_flag = 2;
						}
						if (forth_sub_menu_switch == change_others)
						{
							change_flag = 1;
						}
						if (forth_sub_menu_switch == show_change_data)
						{
							change_flag = 3;
						}
						if (forth_sub_menu_switch == forth_exit_to_main)
						{
							break;  //�˳��޸�ģʽ
						}
					}
				}
				
				break;  //�˻������˵�
			}
		}

		//ִ��д���ļ�����5
		else if (main_menu_switch == write_file)
		{
			while (1)
			{
				//д���ļ���صĹ���


				//д����ɺ�
				all_temp = Fifth_menu();
				fifth_menu_switch = (fifth_menu)all_temp;
				
				//�ļ����Ϊ����λ��
				if (fifth_menu_switch == save_to_other)  continue;
				//�ص����˵�
				else if (fifth_menu_switch == fifth_exit_to_main)  break;

			}
		}

	}
	return 0;
}


/*-----------------------�˵�����---------------------------*/

//��ʾ���˵�  //����ֵ��ѡ��Ĳ˵�ֵ
int Main_menu()
{
	cout << "/*---------���˵�------------*/" << endl;
	cout << "1.��Ӽ�¼" << endl;
	cout << "2.��ʾ��¼" << endl;
	cout << "3.��ѯ��¼" << endl;
	cout << "4.�޸ļ�¼" << endl;
	cout << "5.д���ļ�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ��һ���Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int First_menu()
{
	cout << "/*---------�Ӳ˵�1------------*/" << endl;
	cout << "1.��Ӹ����¼"<< endl;
	cout << "2.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ��Ӽ�¼ģʽ�˵�
int Add_record_model_menu()
{
	cout << "1.��ӵ�����¼" << endl;
	cout << "2.��Ӷ�����¼" << endl;
	cout << "3.���ļ���Ӽ�¼" << endl;
	cout << "��ѡ����Ӽ�¼��ģʽ��" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;

}

//��ʾ��Ӽ�¼�˵�
void Add_record_menu()
{
	cout << "�밴�����µĸ�ʽ�������¼������" << endl;
	cout << "��/���|���|����|����|��/�����|��/���ʱ�䡾��.��.�ա�|������|��ע" << endl;
}


//��ʾ�ڶ����Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int Second_menu()
{
	cout << "/*---------�Ӳ˵�2------------*/" << endl;
	cout << "1.��ʾ����ļ�¼" << endl;
	cout << "2.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ��¼ģʽ�˵�
int Show_record_mode_menu()
{
	cout << "1.��ʾ����¼" << endl;
	cout << "2.��ʾ�ֿ��嵥" << endl;
	cout << "������Ҫ��ʾ��¼�����ͣ�";
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ�������Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int Third_menu()
{
	cout << "/*---------�Ӳ˵�3------------*/" << endl;
	cout << "1.����ɸѡ" << endl;
	cout << "2.����ɸѡ" << endl;
	cout << "3.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}



//��ʾ���ĸ��Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int Forth_menu()
{
	cout << "/*---------�Ӳ˵�4------------*/" << endl;
	cout << "1.�޸ĵ�������¼" << endl;
	cout << "2.�����޸ı���¼" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�е��޸�ģʽ��" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}


//��ʾ�������Բ˵�(���Ͳֿ�)    //����ֵ��ѡ��Ĳ˵�ֵ
int Material_menu(int mode)
{
	int temp;
	if (mode == 1)
	{
		cout << "/*---------����¼���ϵ����Բ˵�------------*/" << endl;
		cout << "1.��/���" << endl;
		cout << "2.����" << endl;
		cout << "3.����" << endl;
		cout << "4.������" << endl;
		cout << "5." << endl;
		cout << "��������Ҫѡ��Ĳ��ϵ�����:" << endl;
		cin >> temp;
		switch (temp)
		{
			case 1:
				temp = 5; break;
			case 2:
				temp = 1; break;
			case 3:
				temp = 2; break;
			case 4:
				temp = 3; break;
			case 5:
				temp = 6; break;
			case 6:
				temp = 4; break;
		}
	}
	else if (mode == 2)
	{
		cout << "/*---------�ֿ���Ʒ�����Բ˵�------------*/" << endl;		
		cout << "1.���" << endl;
		cout << "2.����" << endl;
		cout << "��������Ҫѡ��Ĳֿ���Ʒ������:" << endl;
		
		cin >> temp;
	}
	system("cls");
	return temp;
}


//��ʾ���ĸ��Ӳ˵����Ӳ˵�      //����ֵ��ѡ��Ĳ˵�ֵ
int Forth_sub_menu()
{
	cout << "/*---------���Ӳ˵�2------------*/" << endl;
	cout << "1.�����޸ı���¼��������" << endl;
	cout << "2.�޸���������¼" << endl;
	cout << "3.��ʾ�޸ĺ������" << endl;
	cout << "4.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ������Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int Fifth_menu()
{
	cout << "/*---------�Ӳ˵�5------------*/" << endl;
	cout << "1.���浽�����ĵط�" << endl;
	cout << "2.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ���ϳ�ʼ��ģʽ�˵�      //����ֵ��ѡ��Ĳ˵�ֵ
int material_base_menu()
{
	cout << "/*---------����ʼ��ģʽ�˵�------------*/" << endl;
	cout << "1.�ļ�����" << endl;
	cout << "2.�ֶ�����" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "������Ҫѡ���ı���ʼ��ģʽ��" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}


/*-----------------------�⺯��---------------------------*/

//��������¼����������  ����ͷ��㣩
struct material* Creat_ku()  
{
	int flag = 0;  //�����ͱ�־
	int n = 0;     //�����жϽ����
	struct material* head = NULL;  //ͷָ��
	struct material* p1 = NULL;    //���ڲ��ϵش����µĽ��
	struct material* p2 = NULL;    //����ָ�����������һ�����
	head = (struct material*)malloc(sizeof(material));
	head->next = NULL;
	cout << "�Ƿ����յı�?����--1/��--0��"<<endl;
	cin >> flag;
	system("cls");
	//�����յı�
	if (flag == 1)
	{
		sum_record = 0;
		return head;
	}

	//�����еļ�¼�����
	else if (flag == 0)
	{
		all_temp=material_base_menu();
		Base_init = (material_Base_init)all_temp;

		//�ļ������ʼ����
		if (Base_init == file_in)
		{

		}

		//�ֶ������ʼ����
		else if (Base_init == handwrite)
		{
			
			cout << "���������¼��" << endl;
			cout << "��/���|���|����|����|��/�����|��/���ʱ�䡾��.��.�ա�|������|��ע"<<endl;
			cout << "**����ok��������¼�����**"<<endl;


			for (int i = 0;; i++)    //���ص�
			{
				p1 = (struct material*)malloc(sizeof(material));
				cin >> p1->in_out;
				if (strcmp(p1->in_out, "ok") == 0)
				{
					system("cls");
					break;
				}
					
				//����¼
				if (strcmp(p1->in_out, "���") == 0)
				{
					cin >> p1->seri_number >> p1->name >> p1->unit_price >> p1->in_num >> p1->in_time.year >> p1->in_time.month >> p1->in_time.day >> p1->person >> p1->note;
				}
				//�����¼
				else
				{
					cin >> p1->seri_number >> p1->name >> p1->unit_price >> p1->out_num >> p1->out_time.year >> p1->out_time.month >> p1->out_time.day >> p1->person >> p1->note;
				}									
				n++;
				sum_record++;
				if (n == 1)
				{
					head = p1;
				}
				else
				{
					p2->next = p1;
				}
				p2 = p1;
			}
			if (sum_record != 0)
				p2->next = NULL;
			return head;
		}
	}

	
}


//�������¼
void print_ori(struct material* head)
{
	struct material* pp = head;
	//������ı�����
	cout << "��/���|���|����|����|��/�����|��/���ʱ�䡾��.��.�ա�|������|��ע" << endl;

	for (int i = 0; i < sum_record; i++)
	{
		//��ν������������Ű�����???

		if (strcmp(pp->in_out,"���") == 0)
		{
			cout << pp->in_out << " " << pp->seri_number << " " << pp->name << " " << pp->unit_price << " " << pp->in_num << " "
				<< pp->in_time.year << "��" << pp->in_time.month << "��" << pp->in_time.day << "��"<<" "
				<< pp->person<<" " << pp->note << endl;
		}

		if (strcmp(pp->in_out, "����") == 0)
		{
			cout << pp->in_out << " " << pp->seri_number << " " << pp->name << " " << pp->unit_price << " " << pp->out_num << " "
				<< pp->out_time.year << "��" << pp->out_time.month << "��" << pp->out_time.day << "��"<<" "
				<< pp->person<<" " << pp->note << endl;
		
		}

		pp = pp->next;
	}
}


//������Ʒ�Ĳֿ�(����һ��ͷ���)
struct material* Creat_Item_List()
{
	struct material* sec_head = NULL;  //�ֿ��ͷָ��
	struct material* p1 = NULL; 
	sec_head = (struct material*)malloc(sizeof(material));
	sec_head->next = NULL;
	sum_item = 0;
	return sec_head;
}


//����ֿ����Ʒ
void Print_ku(struct material* thi_head)
{
	struct material* pp = thi_head->next;
	for (int i = 0; i < sum_item; i++)
	{
		cout << pp->seri_number << " " << pp->name << " " << pp->store_num << " "<<endl;
		pp = pp->next;
	}
}


/*-----------------------���ܺ���---------------------------*/


//����¼�����ʼ�����ֿ���Ʒ���ࡿ
void Handout_ku_init(struct material* head, struct material* sec_head)
{
	struct material* record_head = head;
	struct material* cangku_head = sec_head;

	for (int i = 0; i < sum_record; i++)
	{
		

		//���ñ���¼�����ݷ���ֿ���Ʒ��
		Join_record(record_head,sec_head);

		record_head = record_head->next;   //��һ���ı���¼
	}
}

//��ĳ�����¼���¼�¼������
void Join_to_record_List(struct material* new_record,struct material* record_List)
{
	struct material* record_head_temp = record_List;
	//�ҵ��������һ����¼
	for (int i = 0; i < sum_record; i++)
	{
		record_head_temp = record_head_temp->next;
	}

	//���ü�¼��ӵ�����
	record_head_temp->next = new_record;
	new_record->next = NULL;

	//����¼����һ
	sum_record++;	
}

//��ĳ�����¼���µ��ֿ���Ʒ��
void Join_record(struct material* now_record, struct material* sec_head)
{
	struct material* cangku_head = sec_head;
	int flag = 0;      //�ֿ�����Ʒ�ı�־λ
	for (int i = 0; i < sum_item;i++)
	{
		cangku_head = cangku_head->next;  //�����ֿ��е���Ʒ

		//�ñ���¼�ǲֿ������е���Ʒ
		if (strcmp(cangku_head->seri_number,now_record->seri_number) == 0)
		{
			//��Ʒ�������
			if (strcmp(now_record->in_out, "���") == 0)
			{
				cangku_head->store_num += now_record->in_num;
			}
			//��Ʒ���г���
			else
			{
				cangku_head->store_num -= now_record->out_num;
			}

			flag = 1;
			break;
		}
	}
	//���û�ҵ�����Ʒ���½���Ʒ
	if (flag == 0)
	{
		
		cangku_head = sec_head;
		
		//�ҵ�β���
		for (int i = 0; i < sum_item; i++)
		{
			if(sum_item!=0)
			cangku_head = cangku_head->next;
		}

		struct material* p0;
		p0 = (struct material*)malloc(sizeof(material));
		strcpy(p0->seri_number, now_record->seri_number); //��Ÿ�ֵ
		strcpy(p0->name,now_record->name);                //���Ƹ�ֵ

		//��Ʒ�������
		if (strcmp(now_record->in_out, "���") == 0)
		{
			p0->store_num = now_record->in_num;
		}
		//��Ʒ���г���
		else
		{
			p0->store_num = -now_record->out_num;
		}

		cangku_head->next = p0;
		p0->next = NULL;
		sum_item++;
	}
}


//��ӵ�����¼�����кͲֿ���   ����ֵ�жϵ�����¼�����Ƿ����  0-���� 1-������
int Add_one_record(int mode)
{
	if (mode == 1)
	{
		struct material* new_one;
		new_one = (struct material*)malloc(sizeof(material));
		cin >> new_one->in_out;

		//����¼
		if (strcmp(new_one->in_out,"���") == 0)
		{
			cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->in_num >> new_one->in_time.year >> new_one->in_time.month >> new_one->in_time.day >> new_one->person >> new_one->note;
		}
		//�����¼
		else
		{
			cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->out_num >> new_one->out_time.year >> new_one->out_time.month >> new_one->out_time.day >> new_one->person >> new_one->note;
		}

		//���ü�¼��ӵ�����
		Join_to_record_List(new_one, base_head);

		//���ü�¼���µ��ֿ���
		Join_record(new_one, ku_head);

		
		cout << "������¼�����ɣ�����";
		Sleep(1500);
		system("cls");
		
		return 1;
	}
	else if (mode == 2)
	{
		for (int i=0;;i++)
		{
			struct material* new_one;
			new_one = (struct material*)malloc(sizeof(material));
			cin >> new_one->in_out;

			if (strcmp(new_one->in_out,"ok") == 0)
			{
				break;
			}	
			//����¼
			else if (strcmp(new_one->in_out,"���") == 0)
			{
				cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->in_num >> new_one->in_time.year >> new_one->in_time.month >> new_one->in_time.day >> new_one->person >> new_one->note;
			}
			//�����¼
			else 
			{
				cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->out_num >> new_one->out_time.year >> new_one->out_time.month >> new_one->out_time.day >> new_one->person >> new_one->note;
			}

			//���ü�¼��ӵ�����
			Join_to_record_List(new_one, base_head);

			//���ü�¼���µ��ֿ���
			Join_record(new_one, ku_head);
		}
		return 2;
	}
	return 0;   //�����¼ʧ�ܣ�
}

//��Ӷ�����¼�����Ͳֿ���
void Add_many_record()
{
	int end_flag;
	end_flag=Add_one_record(2);
	if (end_flag == 2)
	{
		cout << "������¼�����ɣ�����";
		Sleep(1500);
		system("cls");
	}
}

//��ʱ����
void Delay(int i)
{
}