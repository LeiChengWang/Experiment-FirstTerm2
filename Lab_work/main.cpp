#include <iostream>
using namespace std;
#include <string.h>
#include <stdlib.h>
#include <windows.h>

/*------------------------结构体start--------------------------*/

//日期【年、月、日】
struct Data
{
	int year; 
	int month;
	int day;
};

//材料
struct material
{
	char seri_number[20];      //编号
	char name[20];             //名称
	float unit_price;          //单价

	char in_out[5];            //出入库记录

	int  in_num;               //入库数量
	struct Data in_time;       //入库时间

	int out_num;               //出库数量
	struct Data out_time;      //出库时间

	char person[20];           //保管人
	int  store_num;            //库存数量
	char note[100];            //备注

	material* next;            //下一个结点指针
};


/*--------------------------枚举start---------------------------*/

//主菜单
enum main_menu
{
	add_record=1,    //添加记录
	show_record,   //显示记录
	search_record, //查询记录
	change_record, //修改记录
	write_file	   //写入文件 
}main_menu_switch;


//第一个子菜单
enum first_menu
{
	add_more=1,                 //添加更多的记录
	first_exit_to_main         //返回主菜单
}first_menu_switch;

//添加记录模式菜单
enum add_record_modei_menu
{
	add_one=1,      //添加一条记录
	add_two,        //添加多条记录
	add_from_file   //从文件添加记录
}add_record_model_menu;

//第二个子菜单
enum second_menu
{
	show_more=1,     //显示更多的记录
	second_exit_to_main  //返回主菜单
}second_menu_switch;

//显示记录模式菜单
enum show_record_mode_menu
{
	record_List=1,   //显示表单记录
	cangku_Item      //显示仓库物品清单
}show_record_mode_menu;

//第三个子菜单
enum third_menu
{
	conti_to_search=1,     //继续筛选
	anew_search,         //重新筛选 
	third_exit_to_main    //返回主菜单
}third_menu_switch;

//第四个子菜单
enum forth_menu
{
	 change_one=1,       //修改单个表单记录
	 change_together   //批量修改

}forth_menu_switch;

//第四个子子菜单
enum forth_sub_menu
{
	continue_change = 1,     //继续修改表单记录其他属性
	change_others,           //修改其他表单记录
	show_change_data,        //显示修改后的数据
	forth_exit_to_main       //返回主菜单
}forth_sub_menu_switch;

//材料属性菜单
enum material_menu
{
	seri_number=1,  //编号
	name,           //名称
	unit_price,     //单价
	person,         //保管人	
	in_out_way,      //出入库方式
	record_data,     //记录的日期
	note,           //备注
}sec_sub,forth_sub;


//第五个子菜单
enum fifth_menu
{
	save_to_other=1,       //保存到其他的地方
	fifth_exit_to_main    //返回主菜单
}fifth_menu_switch;


//材料库初始化模式菜单
enum material_Base_init
{
	file_in=1,   //文件读入
	handwrite  //手动输入
}Base_init;



/*--------------------------函数声明start---------------------*/

//菜单函数声明
int Main_menu();         //显示主菜单
int First_menu();        //显示第一个子菜单    
int Second_menu();       //显示第二个子菜单    
int Third_menu();        //显示第三个子菜单  
int Forth_menu();        //显示第四个子菜单
int Forth_sub_menu();    //显示第四个子菜单的子菜单
int Material_menu();      //显示材料属性菜单(表单和仓库)
int Fifth_menu();         //显示第五个子菜单   
int material_base_menu();  //显示材料初始化模式菜单
void Add_record_menu();     //显示添加记录菜单
int Add_record_model_menu();  //显示添加记录模式菜单
int Show_record_mode_menu();     //显示记录模式菜单


//功能函数声明



//库相关的函数

struct material* Creat_ku();               //建立材料库【创建链表】
void print_ori(struct material* head);     //输出原始表单
struct material* Creat_Item_List();        //建立物品的仓库(带有一个头结点)  
void Print_ku(struct material* thi_head);  //输出仓库的物品

void Handout_ku_init(struct material* head, struct material* sec_head);   //表单记录处理初始化【仓库物品分类】

//Update 相关的函数
void Join_to_record_List(struct material* new_record, struct material* record_List);  //将某项表单记录更新记录到表单中
void Join_record(struct material* now_record, struct material* sec_head);            //将某项表单记录更新到仓库物品中

//添加记录相关的函数

int Add_one_record(int mode);       //添加单条记录到表单中和仓库中   返回值判断单条记录输入是否结束  0-结束 1-添加完成
void Add_many_record();      //添加多条记录到表单和仓库中


/*---------------------------全局变量、指针start-------------------*/

int all_temp;  //用于记录实时选择的各种菜单值
int sum_record;   //表单的数量
int sum_item;     //仓库物品的数量
material* base_head;    //材料库表单记录的头指针
material* ku_head;    //仓库物品的头指针



int main()
{
	//材料库初始化工作
	sum_record = 0;
	sum_item = 0;

	//建立表单  
	base_head=Creat_ku();

	//print_ori(base_head);     //输出原始的表单记录

	//建立仓库
	ku_head=Creat_Item_List();

	Handout_ku_init(base_head, ku_head);     //将刚刚建立的表单记录更新到仓库的物品清单中（初始化工作）

	//Print_ku(ku_head);            //输出仓库的物品清单


	//进入仓库的实时材料管理系统
	while (1)
	{
		all_temp=Main_menu();  //得到主菜单的选择值

		main_menu_switch = (main_menu)all_temp;  //枚举类型的转换

		//执行添加记录功能1
		if (main_menu_switch == add_record)
		{
			while (1)
			{
				//添加记录相关的功能
				all_temp=Add_record_model_menu();   //显示添加记录模式菜单
				add_record_model_menu = (add_record_modei_menu)all_temp;
				if (add_record_model_menu == add_one)
				{
					Add_record_menu();         //显示添加记录菜单

					//添加单条记录功能
					Add_one_record(1);
				}
				else if (add_record_model_menu == add_two)
				{
					Add_record_menu();         //显示添加记录菜单

					//添加多条记录的功能
					Add_many_record();
				}
				else if (add_record_model_menu == add_from_file)
				{
					Add_record_menu();         //显示添加记录菜单

					//从文件添加记录的功能

				}
				

				//添加完记录
				all_temp = First_menu();
				first_menu_switch = (first_menu)all_temp;
				//继续添加记录
				if (first_menu_switch == add_more)   continue;
				//回到主菜单
				else if (first_menu_switch == first_exit_to_main)  break;			
			}
		}

		//执行显示记录功能2
		else if (main_menu_switch == show_record)
		{
			while (1)
			{
				//显示记录相关的功能

				 //显示记录模式菜单
				all_temp=Show_record_mode_menu();    
				show_record_mode_menu = (enum show_record_mode_menu)all_temp;
				
				//表单记录的相关显示
				if(show_record_mode_menu== record_List)
				{
					//选择显示表单记录的属性
					all_temp = Material_menu();
					sec_sub = (material_menu)all_temp;
				}


				//仓库清单的相关显示
				else if (show_record_mode_menu == cangku_Item)
				{

				}



				
				


				//显示完记录
				all_temp = Second_menu();
				second_menu_switch = (second_menu)all_temp;
				//继续添加记录
				if (second_menu_switch == show_more)   continue;
				//显示主菜单
				else if (second_menu_switch == second_exit_to_main)  break;
			}
		}
		
		//执行查询记录功能3
		else if (main_menu_switch == search_record)
		{
			while (1)
			{
				//查询记录相关的功能

				//查询完记录
				all_temp = Third_menu();
				third_menu_switch = (third_menu)all_temp;
				//继续筛选
				if (third_menu_switch == conti_to_search)
				{

				}
				//重新查询
				else if (third_menu_switch == anew_search)  continue;
				//回到主菜单
				else if (third_menu_switch == third_exit_to_main)  break;

			}
		}

		//执行修改记录功能4
		else if (main_menu_switch == change_record)
		{
			int change_flag = 1;  //修改标志位
			while (1)
			{

				//选择修改模式
				all_temp = Forth_menu();
				forth_menu_switch = (forth_menu)all_temp;
				if (forth_menu_switch == change_one)
				{
					while (1)
					{
						//第一次修改单个表单记录
						if (change_flag == 1)
						{
								//选择要修改的材料属性值	
								all_temp = Material_menu();
								forth_sub = (material_menu)all_temp;

								//执行第一次修改功能


						}

						//继续修改该表单记录
						else if (change_flag == 2)
						{
								//选择继续要修改的材料属性值	
								all_temp = Material_menu();
								forth_sub = (material_menu)all_temp;

								//继续执行修改功能
						}
						else if (change_flag == 3)
						{
							//执行修改后数据显示的功能

						}



						//修改完成后
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
								break;    //退出修改模式
						}
					}

				}
				
				if (forth_menu_switch == change_together)
				{
					while (1)
					{
						//批量修改表单记录
						//选择要修改的材料属性值	
						all_temp = Material_menu();
						forth_sub = (material_menu)all_temp;


						//第一次修改单个表单记录
						if (change_flag == 1)
						{
							//选择要修改的材料属性值	
							all_temp = Material_menu();
							forth_sub = (material_menu)all_temp;

							//执行第一次修改功能


						}

						//继续修改该表单记录
						else if (change_flag == 2)
						{
							//选择继续要修改的材料属性值	
							all_temp = Material_menu();
							forth_sub = (material_menu)all_temp;

							//继续执行修改功能
						}

						else if (change_flag == 3)
						{
							//执行修改后数据显示的功能

						}


						//修改完成后
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
							break;  //退出修改模式
						}
					}
				}
				
				break;  //退回至主菜单
			}
		}

		//执行写入文件功能5
		else if (main_menu_switch == write_file)
		{
			while (1)
			{
				//写入文件相关的功能


				//写入完成后
				all_temp = Fifth_menu();
				fifth_menu_switch = (fifth_menu)all_temp;
				
				//文件另存为其他位置
				if (fifth_menu_switch == save_to_other)  continue;
				//回到主菜单
				else if (fifth_menu_switch == fifth_exit_to_main)  break;

			}
		}

	}
	return 0;
}


/*-----------------------菜单函数---------------------------*/

//显示主菜单  //返回值是选择的菜单值
int Main_menu()
{
	cout << "/*---------主菜单------------*/" << endl;
	cout << "1.添加记录" << endl;
	cout << "2.显示记录" << endl;
	cout << "3.查询记录" << endl;
	cout << "4.修改记录" << endl;
	cout << "5.写入文件" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "请输入想要执行的功能：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//显示第一个子菜单    //返回值是选择的菜单值
int First_menu()
{
	cout << "/*---------子菜单1------------*/" << endl;
	cout << "1.添加更多记录"<< endl;
	cout << "2.返回主菜单" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "请输入想要执行的功能：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//显示添加记录模式菜单
int Add_record_model_menu()
{
	cout << "1.添加单条记录" << endl;
	cout << "2.添加多条记录" << endl;
	cout << "3.从文件添加记录" << endl;
	cout << "请选择添加记录的模式：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;

}

//显示添加记录菜单
void Add_record_menu()
{
	cout << "请按照以下的格式输入表单记录的详情" << endl;
	cout << "出/入库|编号|名称|单价|出/入库数|出/入库时间【年.月.日】|保管人|备注" << endl;
}


//显示第二个子菜单    //返回值是选择的菜单值
int Second_menu()
{
	cout << "/*---------子菜单2------------*/" << endl;
	cout << "1.显示更多的记录" << endl;
	cout << "2.返回主菜单" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "请输入想要执行的功能：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//显示记录模式菜单
int Show_record_mode_menu()
{
	cout << "1.显示表单记录" << endl;
	cout << "2.显示仓库清单" << endl;
	cout << "请输入要显示记录的类型：";
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//显示第三个子菜单    //返回值是选择的菜单值
int Third_menu()
{
	cout << "/*---------子菜单3------------*/" << endl;
	cout << "1.继续筛选" << endl;
	cout << "2.重新筛选" << endl;
	cout << "3.返回主菜单" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "请输入想要执行的功能：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}



//显示第四个子菜单    //返回值是选择的菜单值
int Forth_menu()
{
	cout << "/*---------子菜单4------------*/" << endl;
	cout << "1.修改单个表单记录" << endl;
	cout << "2.批量修改表单记录" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "请输入想要执行的修改模式：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}


//显示材料属性菜单(表单和仓库)    //返回值是选择的菜单值
int Material_menu(int mode)
{
	int temp;
	if (mode == 1)
	{
		cout << "/*---------表单记录材料的属性菜单------------*/" << endl;
		cout << "1.出/入库" << endl;
		cout << "2.单价" << endl;
		cout << "3.日期" << endl;
		cout << "4.保管人" << endl;
		cout << "5." << endl;
		cout << "请输入想要选择的材料的属性:" << endl;
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
		cout << "/*---------仓库物品的属性菜单------------*/" << endl;		
		cout << "1.编号" << endl;
		cout << "2.名称" << endl;
		cout << "请输入想要选择的仓库物品的属性:" << endl;
		
		cin >> temp;
	}
	system("cls");
	return temp;
}


//显示第四个子菜单的子菜单      //返回值是选择的菜单值
int Forth_sub_menu()
{
	cout << "/*---------子子菜单2------------*/" << endl;
	cout << "1.继续修改表单记录其他属性" << endl;
	cout << "2.修改其他表单记录" << endl;
	cout << "3.显示修改后的数据" << endl;
	cout << "4.返回主菜单" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "请输入想要执行的功能：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//显示第五个子菜单    //返回值是选择的菜单值
int Fifth_menu()
{
	cout << "/*---------子菜单5------------*/" << endl;
	cout << "1.保存到其他的地方" << endl;
	cout << "2.返回主菜单" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "请输入想要执行的功能：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//显示材料初始化模式菜单      //返回值是选择的菜单值
int material_base_menu()
{
	cout << "/*---------表单初始化模式菜单------------*/" << endl;
	cout << "1.文件读入" << endl;
	cout << "2.手动输入" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "请输入要选定的表单初始化模式：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}


/*-----------------------库函数---------------------------*/

//建立表单记录【创建链表】  （有头结点）
struct material* Creat_ku()  
{
	int flag = 0;  //库类型标志
	int n = 0;     //用于判断结点数
	struct material* head = NULL;  //头指针
	struct material* p1 = NULL;    //用于不断地创建新的结点
	struct material* p2 = NULL;    //用于指向链表的最后的一个结点
	head = (struct material*)malloc(sizeof(material));
	head->next = NULL;
	cout << "是否建立空的表单?【是--1/否--0】"<<endl;
	cin >> flag;
	system("cls");
	//建立空的表单
	if (flag == 1)
	{
		sum_record = 0;
		return head;
	}

	//将已有的记录存入表单
	else if (flag == 0)
	{
		all_temp=material_base_menu();
		Base_init = (material_Base_init)all_temp;

		//文件读入初始化表单
		if (Base_init == file_in)
		{

		}

		//手动输入初始化表单
		else if (Base_init == handwrite)
		{
			
			cout << "请输入表单记录：" << endl;
			cout << "出/入库|编号|名称|单价|出/入库数|出/入库时间【年.月.日】|保管人|备注"<<endl;
			cout << "**输入ok结束表单记录的添加**"<<endl;


			for (int i = 0;; i++)    //划重点
			{
				p1 = (struct material*)malloc(sizeof(material));
				cin >> p1->in_out;
				if (strcmp(p1->in_out, "ok") == 0)
				{
					system("cls");
					break;
				}
					
				//入库记录
				if (strcmp(p1->in_out, "入库") == 0)
				{
					cin >> p1->seri_number >> p1->name >> p1->unit_price >> p1->in_num >> p1->in_time.year >> p1->in_time.month >> p1->in_time.day >> p1->person >> p1->note;
				}
				//出库记录
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


//输出表单记录
void print_ori(struct material* head)
{
	struct material* pp = head;
	//输出表单的标题栏
	cout << "出/入库|编号|名称|单价|出/入库数|出/入库时间【年.月.日】|保管人|备注" << endl;

	for (int i = 0; i < sum_record; i++)
	{
		//如何解决数据输出的排版问题???

		if (strcmp(pp->in_out,"入库") == 0)
		{
			cout << pp->in_out << " " << pp->seri_number << " " << pp->name << " " << pp->unit_price << " " << pp->in_num << " "
				<< pp->in_time.year << "年" << pp->in_time.month << "月" << pp->in_time.day << "日"<<" "
				<< pp->person<<" " << pp->note << endl;
		}

		if (strcmp(pp->in_out, "出库") == 0)
		{
			cout << pp->in_out << " " << pp->seri_number << " " << pp->name << " " << pp->unit_price << " " << pp->out_num << " "
				<< pp->out_time.year << "年" << pp->out_time.month << "月" << pp->out_time.day << "日"<<" "
				<< pp->person<<" " << pp->note << endl;
		
		}

		pp = pp->next;
	}
}


//建立物品的仓库(带有一个头结点)
struct material* Creat_Item_List()
{
	struct material* sec_head = NULL;  //仓库的头指针
	struct material* p1 = NULL; 
	sec_head = (struct material*)malloc(sizeof(material));
	sec_head->next = NULL;
	sum_item = 0;
	return sec_head;
}


//输出仓库的物品
void Print_ku(struct material* thi_head)
{
	struct material* pp = thi_head->next;
	for (int i = 0; i < sum_item; i++)
	{
		cout << pp->seri_number << " " << pp->name << " " << pp->store_num << " "<<endl;
		pp = pp->next;
	}
}


/*-----------------------功能函数---------------------------*/


//表单记录处理初始化【仓库物品分类】
void Handout_ku_init(struct material* head, struct material* sec_head)
{
	struct material* record_head = head;
	struct material* cangku_head = sec_head;

	for (int i = 0; i < sum_record; i++)
	{
		

		//将该表单记录的内容放入仓库物品中
		Join_record(record_head,sec_head);

		record_head = record_head->next;   //下一个的表单记录
	}
}

//将某项表单记录更新记录到表单中
void Join_to_record_List(struct material* new_record,struct material* record_List)
{
	struct material* record_head_temp = record_List;
	//找到表单的最后一个记录
	for (int i = 0; i < sum_record; i++)
	{
		record_head_temp = record_head_temp->next;
	}

	//将该记录添加到表单中
	record_head_temp->next = new_record;
	new_record->next = NULL;

	//表单记录数加一
	sum_record++;	
}

//将某项表单记录更新到仓库物品中
void Join_record(struct material* now_record, struct material* sec_head)
{
	struct material* cangku_head = sec_head;
	int flag = 0;      //仓库中物品的标志位
	for (int i = 0; i < sum_item;i++)
	{
		cangku_head = cangku_head->next;  //遍历仓库中的物品

		//该表单记录是仓库中已有的物品
		if (strcmp(cangku_head->seri_number,now_record->seri_number) == 0)
		{
			//物品进行入库
			if (strcmp(now_record->in_out, "入库") == 0)
			{
				cangku_head->store_num += now_record->in_num;
			}
			//物品进行出库
			else
			{
				cangku_head->store_num -= now_record->out_num;
			}

			flag = 1;
			break;
		}
	}
	//如果没找到该物品，新建物品
	if (flag == 0)
	{
		
		cangku_head = sec_head;
		
		//找到尾结点
		for (int i = 0; i < sum_item; i++)
		{
			if(sum_item!=0)
			cangku_head = cangku_head->next;
		}

		struct material* p0;
		p0 = (struct material*)malloc(sizeof(material));
		strcpy(p0->seri_number, now_record->seri_number); //编号赋值
		strcpy(p0->name,now_record->name);                //名称赋值

		//物品进行入库
		if (strcmp(now_record->in_out, "入库") == 0)
		{
			p0->store_num = now_record->in_num;
		}
		//物品进行出库
		else
		{
			p0->store_num = -now_record->out_num;
		}

		cangku_head->next = p0;
		p0->next = NULL;
		sum_item++;
	}
}


//添加单条记录到表单中和仓库中   返回值判断单条记录输入是否结束  0-结束 1-添加完成
int Add_one_record(int mode)
{
	if (mode == 1)
	{
		struct material* new_one;
		new_one = (struct material*)malloc(sizeof(material));
		cin >> new_one->in_out;

		//入库记录
		if (strcmp(new_one->in_out,"入库") == 0)
		{
			cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->in_num >> new_one->in_time.year >> new_one->in_time.month >> new_one->in_time.day >> new_one->person >> new_one->note;
		}
		//出库记录
		else
		{
			cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->out_num >> new_one->out_time.year >> new_one->out_time.month >> new_one->out_time.day >> new_one->person >> new_one->note;
		}

		//将该记录添加到表单中
		Join_to_record_List(new_one, base_head);

		//将该记录更新到仓库中
		Join_record(new_one, ku_head);

		
		cout << "单条记录添加完成！！！";
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
			//入库记录
			else if (strcmp(new_one->in_out,"入库") == 0)
			{
				cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->in_num >> new_one->in_time.year >> new_one->in_time.month >> new_one->in_time.day >> new_one->person >> new_one->note;
			}
			//出库记录
			else 
			{
				cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->out_num >> new_one->out_time.year >> new_one->out_time.month >> new_one->out_time.day >> new_one->person >> new_one->note;
			}

			//将该记录添加到表单中
			Join_to_record_List(new_one, base_head);

			//将该记录更新到仓库中
			Join_record(new_one, ku_head);
		}
		return 2;
	}
	return 0;   //加入记录失败！
}

//添加多条记录到表单和仓库中
void Add_many_record()
{
	int end_flag;
	end_flag=Add_one_record(2);
	if (end_flag == 2)
	{
		cout << "多条记录添加完成！！！";
		Sleep(1500);
		system("cls");
	}
}

//延时函数
void Delay(int i)
{
}