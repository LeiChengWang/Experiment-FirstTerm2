#include <iostream>
using namespace std;
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#pragma warning(disable:4996)

/*------------------------宏定义start--------------------------*/

//用来记录查询模式
#define First_search     1     //首次查询
#define Continue_search  2     //继续筛选
#define Clear_list       3     //清空查询链表


//用于模式跳跃
#define normal          0     
#define jump_to_first   1
#define jump_to_second  2
#define jump_to_third   3
#define jump_to_forth   4
#define jump_to_fifth   5







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
	seri_number=1,   //编号
	name,            //名称
	unit_price,      //单价
	person,          //保管人	
	in_out_way,      //出入库方式
	record_data,     //记录的日期
	note,			 //备注
	num,             //数量
	all,             //全部属性
	in_out_time,     //出入库时间
	change_all,       //修改全部
	in_out_num       //出入库数量
}sec_sub,third_sub,forth_sub;


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
int Search_record_mode();         //显示查询模式菜单     //查询表单记录还是仓库物品
int Search_record_menu();          //显示选择查询表单记录属性的菜单
int Change_record_menu();           //显示修改材料属性菜单


//功能函数声明

void Delay(int i);        //延时函数


//库相关的函数

struct material* Creat_ku();               //建立材料库【创建链表】
void print_ori(struct material* head,int mode);     //输出原始表单
struct material* Creat_Item_List();        //建立物品的仓库(带有一个头结点)  
void Print_ku(struct material* thi_head);  //输出仓库的物品

void Handout_ku_init(struct material* head, struct material* sec_head);   //表单记录处理初始化【仓库物品分类】

//Update 相关的函数
void Join_to_record_List(struct material* new_record, struct material* record_List);  //将某项表单记录更新记录到表单中
void Join_record(struct material* now_record, struct material* sec_head);            //将某项表单记录更新到仓库物品中

//添加记录相关的函数

int Add_one_record(int mode);       //添加单条记录到表单中和仓库中   返回值判断单条记录输入是否结束  0-结束 1-添加完成
void Add_many_record();      //添加多条记录到表单和仓库中


void Show_related_record(enum material_menu link);   //显示相关的表单记录
void Show_Cangku_Item();    //显示仓库物品清单



void Search_related_record(enum material_menu link,int mode);     //查询表单记录  参数说明:link-判断检索条件 mode-判断检索模式 
void Search_ku_item();         //查询仓库记录
  
void Change_record(enum material_menu link, int mode);      //修改单条表单记录功能 
void Update_change_to_record(struct material* Change_record_head, struct material* now_search_head, struct material* base_head);   //将修改的单条查询记录更新到表单记录中
void Change_many_record(enum material_menu link, int mode);   //修改多条表单记录功能



/*---------------------------全局变量、指针start-------------------*/

int all_temp=0;  //用于记录实时选择的各种菜单值
int sum_record=0;       //表单的数量
int sum_item=0;         //仓库物品的数量
int sum_search = 0;     //检索链表中记录的数量
int mode_jump= normal;          //当有特殊需要时，进行不同模式之间的跳转，正常是顺序执行的，这个可以实现跳跃
material* base_head=NULL;       //材料库表单记录的头指针
material* ku_head=NULL;         //仓库物品的头指针
material* Search_head=NULL;     //查询记录时头指针
material* Change_record_head = NULL;     //修改记录位置指针

int main()
{
	//材料库初始化工作
	sum_record = 0;
	sum_item = 0;

	//建立表单  
	base_head=Creat_ku();

	//print_ori(base_head,1);     //输出原始的表单记录

	//建立仓库
	ku_head=Creat_Item_List();

	Handout_ku_init(base_head, ku_head);     //将刚刚建立的表单记录更新到仓库的物品清单中（初始化工作）

	//Print_ku(ku_head);            //输出仓库的物品清单


	//进入仓库的实时材料管理系统
	while (1)
	{
		//跳跃模式关闭  进入正常模式（用户自己进行选择）
		if (mode_jump == normal)
		{
			all_temp = Main_menu();  //得到主菜单的选择值

			main_menu_switch = (main_menu)all_temp;  //枚举类型的转换
		}

		//开启跳跃模式
		if (mode_jump == jump_to_third)
		{
			main_menu_switch = search_record;
		}

		

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
					//显示单价
					if (sec_sub == unit_price)
					{
						Show_related_record(sec_sub);
					}
					//显示数量
					else if (sec_sub == num)
					{
						Show_related_record(sec_sub);
					}
					//显示保管人
					else if (sec_sub == person)
					{
						Show_related_record(sec_sub);
					}
					//显示备注
					else if (sec_sub == note)
					{
						Show_related_record(sec_sub);
					}
					//显示全部的记录
					else if (sec_sub == all)
					{
						Show_related_record(sec_sub);
					}

					
				}


				//仓库清单的相关显示
				else if (show_record_mode_menu == cangku_Item)
				{
					//显示仓库的全部物品清单
					Show_Cangku_Item();

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
			int search_mode = 0;  //记录查询模式 第一次、继续、重新
			while (1)
			{
				if (mode_jump == normal)
				{
					//查询记录相关的功能
					if (search_mode == 0)
					{
						//选择查询模式
						all_temp = Search_record_mode();

					}
				}

				//由修改模式跳转至此，进行表单记录的查询
				else if (mode_jump == jump_to_third)
				{
					all_temp = 1;
				}
				
				
				//查询表单记录
				if (all_temp == 1)
				{
					//选择查询的表单记录的属性
					all_temp=Search_record_menu();
					third_sub = (enum material_menu)all_temp;


					//查询表单记录功能
					if (search_mode == 0)
					{
						search_mode = First_search;
					}
					//按照编号进行检索
					if (third_sub == seri_number)
					{
						Search_related_record(third_sub, search_mode);
					}

					//按照名称进行检索
					if (third_sub == name)
					{
						Search_related_record(third_sub, search_mode);
					}

					//按照日期进行检索
					if (third_sub == record_data)
					{
						Search_related_record(third_sub, search_mode);
					}

					//按照保管人进行检索
					if (third_sub == person)
					{
						Search_related_record(third_sub, search_mode);
					}

					//按照备注进行检索
					if (third_sub == note)
					{
						Search_related_record(third_sub, search_mode);
					}

					

				}

				//查询仓库物品记录
				else if (all_temp == 2)
				{
					//查询仓库物品记录功能
					Search_ku_item();

				}



				//查询完记录
				all_temp = Third_menu();
				third_menu_switch = (third_menu)all_temp;
				
				//继续筛选
				if (third_menu_switch == conti_to_search)
				{
					if (all_temp == 1)
					{
						search_mode = Continue_search;
					}
					
				}
				
				//重新查询
				else if (third_menu_switch == anew_search)
				{
					if (all_temp == 1)
					{
						search_mode = 0;
						Search_related_record(third_sub, Clear_list);   //清空查询链表
					}
					else if (all_temp == 2)
					{
						search_mode = 0;
					}
			
				}
				
				//回到主菜单
				else if (third_menu_switch == third_exit_to_main)
				{
					//开启跳跃模式
					if (mode_jump == jump_to_third)
					{
						main_menu_switch = change_record;
						mode_jump = jump_to_forth;
					}
					break;
				}

			}
		}

		//执行修改记录功能4
		else if (main_menu_switch == change_record)
		{
			int change_flag = 1;  //修改标志位
			while (1)
			{
				//首次进入修改模式，进行模式选择
				if (mode_jump == normal)
				{
					//选择修改模式
					all_temp = Forth_menu();
					forth_menu_switch = (forth_menu)all_temp;
				}

				//由跳跃模式从查询跳到这里就不用重新选择修改模式
				else if (mode_jump!=normal)
				{
					forth_menu_switch = forth_menu_switch;  
				}
			
				if (forth_menu_switch == change_one)
				{
					while (1)
					{
						//已经从查询模式回来，恢复正常模式
						if (mode_jump == jump_to_forth)
						{
							mode_jump = normal;
						}
						//询问用户想要修改的具体的表单记录  执行跳跃模式
						else if (mode_jump != jump_to_third&& change_flag!=2&& change_flag!=3)
						{
							mode_jump = jump_to_third;
							break;
						}
						

						//第一次修改单个表单记录
						if (change_flag == 1)
						{
								//将经由查询模式得到的表单记录定位到表单库中的具体位置
							     
								//函数函数....................................
								
								cout << "已找到想要修改的表单记录" << endl;

								//选择要修改的材料属性值	
								all_temp = Change_record_menu();
								forth_sub = (material_menu)all_temp;

								system("cls");

								//执行第一次修改功能
								Change_record(forth_sub,1);

						}

						//继续修改该表单记录
						else if (change_flag == 2)
						{
								//选择继续要修改的材料属性值	
								all_temp = Change_record_menu();
								forth_sub = (material_menu)all_temp;
								Change_record(forth_sub,2);

								//继续执行修改功能
						}

						else if (change_flag == 3)
						{
							//执行修改后数据显示的功能
							Change_record(forth_sub, 3);
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

						//已经从查询模式回来，恢复正常模式
						if (mode_jump == jump_to_forth)
						{
							mode_jump = normal;
						}
						//询问用户想要修改的具体的表单记录  执行跳跃模式
						else if (mode_jump != jump_to_third && change_flag != 2 && change_flag != 3)
						{
							mode_jump = jump_to_third;
							break;
						}

						//第一次修改单个表单记录
						if (change_flag == 1)
						{
							//选择要修改的材料属性值	
							all_temp = Change_record_menu();
							forth_sub = (material_menu)all_temp;

							//执行第一次修改功能

							Change_many_record(forth_sub,1);
						}

						//继续修改该表单记录
						else if (change_flag == 2)
						{
							//选择继续要修改的材料属性值	
							all_temp = Material_menu();
							forth_sub = (material_menu)all_temp;

							//继续执行修改功能
							Change_many_record(forth_sub,2);
						}

						else if (change_flag == 3)
						{
							//执行修改后数据显示的功能
							Change_many_record(forth_sub,3);

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
	cout << "请输入要显示记录的类型：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//显示第三个子菜单    //返回值是选择的菜单值
int Third_menu()
{
	cout << "/*---------子菜单3------------*/" << endl;
	cout << "1.继续筛选(提示:仅查询表单记录可以使用该功能！)" << endl;
	cout << "2.重新查询" << endl;
	cout << "3.返回主菜单" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "请输入想要执行的功能：" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//显示查询模式菜单  //查询表单记录还是仓库物品
int Search_record_mode()
{
	cout << "1.查询表单记录" << endl;
	cout << "2.查询仓库物品" <<endl;
	cout << "请选择查询模式: " << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//显示选择查询表单记录属性的菜单
int Search_record_menu()
{
	cout << "1.编号" << endl;
	cout << "2.名称" << endl;
	cout << "3.日期" << endl;
	cout << "4.保管人" << endl;
	cout << "5.备注"<<endl;
	cout << "请输入筛选条件: " << endl;
	int temp;
	cin >> temp;
	switch (temp)
	{
		case 1:
			temp = 1; break;
		case 2:
			temp = 2; break;
		case 3:
			temp = 6; break;
		case 4:
			temp = 4; break;
		case 5:
			temp = 7; break;
	}
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


//显示材料属性菜单(表单)    //返回值是选择的菜单值
int Material_menu()
{
	int temp;

		cout << "/*---------表单记录材料的属性菜单------------*/" << endl;
		cout << "1.单价" << endl;
		cout << "2.数量" << endl;
		cout << "3.保管人" << endl;
		cout << "4.备注" << endl;
		cout << "5.全部显示" << endl;
		cout << "请输入想要选择的材料的属性:" << endl;
		cin >> temp;
		switch (temp)
		{
			case 1:
				temp = 3; break;
			case 2:
				temp = 8; break;
			case 3:
				temp = 4; break;
			case 4:
				temp = 7; break;
			case 5:
				temp = 9; break;
		
		}
	system("cls");
	return temp;
}

//显示修改材料属性菜单
int Change_record_menu()
{
	cout << "请选择想要修改的表单记录的属性：" << endl;
	cout << "1.编号" << endl;
	cout << "2.名称" << endl;
	cout << "3.单价" << endl;
	cout << "4.出入库记录" << endl;
	cout << "5.入库数/出库数" << endl;
	cout << "6.入库/出库时间" << endl;
	cout << "7.保管人" << endl;
	cout << "8.备注" << endl;
	cout << "9.全部修改" << endl;
	int temp;
	cin >> temp;
	switch (temp)
	{
	case 1:
		temp = 1; break;
	case 2:
		temp = 2; break;
	case 3:
		temp = 3; break;
	case 4:
		temp = 5; break;
	case 5:
		temp = 12; break;
	case 6:
		temp = 6; break;
	case 7:
		temp = 4; break;
	case 8:
		temp = 7; break;
	case 9:
		temp = 11; break;
	}
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
			bool error=0;  //显示当前表单是否有错误

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


					//检测表单数据的有效性
					if (strcmp(p1->in_out, "入库") != 0 && strcmp(p1->in_out, "出库") != 0)
					{
						cout << "Error::	**未标明出入库方式**  该条表单记录添加无效！！！" << endl;
						cout << "请继续输入有效表单记录 或 输入ok结束" << endl;
						error = 1;
					}
					else if (strcmp(p1->in_out, "入库") == 0)
					{
						if (p1->in_time.year < 0
							|| p1->in_time.month < 0
							|| p1->in_time.month>12
							|| p1->in_time.day < 1
							|| p1->in_time.day>31)
						{
							cout << "Error::	*日期格式有误**  该条表单记录添加无效！！！" << endl;
							cout << "请继续输入有效表单记录 或 输入ok结束" << endl;
							error = 1;
						}

						if (p1->in_num < 0)
						{
							cout << "Error::	*材料的数量不能为负值**  该条表单记录添加无效！！！" << endl;
							cout << "请继续输入有效表单记录 或 输入ok结束" << endl;
							error = 1;
						}


						if (p1->unit_price < 0)
						{
							cout << "Error::	*材料的单价不能为负值**  该条表单记录添加无效！！！" << endl;
							cout << "请继续输入有效表单记录 或 输入ok结束" << endl;
							error = 1;
						}


					}
					else if (strcmp(p1->in_out, "出库") == 0)
					{
						if (p1->out_time.year < 0
							|| p1->out_time.month < 0
							|| p1->out_time.month>12
							|| p1->out_time.day < 1
							|| p1->out_time.day>31)
						{
							cout << "Error::	*日期格式有误**  该条表单记录添加无效！！！" << endl;
							cout << "请继续输入有效表单记录 或 输入ok结束" << endl;
							error = 1;
						}

						if (p1->out_num < 0)
						{
							cout << "Error::	*材料的数量不能为负值**  该条表单记录添加无效！！！" << endl;
							cout << "请继续输入有效表单记录 或 输入ok结束" << endl;
							error = 1;
						}


						if (p1->unit_price < 0)
						{
							cout << "Error::	*材料的单价不能为负值**  该条表单记录添加无效！！！" << endl;
							cout << "请继续输入有效表单记录 或 输入ok结束" << endl;
							error = 1;
						}

					}


					//如果数据有错误，输出提示信息
					if (error == 1)
					{
						Delay(2000);
						
					}


					//将该记录存储到表单中
					if (error == 0)
					{
						n++;
						sum_record++;
						if (n == 1)
						{
							head->next = p1;
						}
						else
						{
							p2->next = p1;
						}
						p2 = p1;
					}
				error = 0;
			}
			if (sum_record != 0)
				p2->next = NULL;

			
			return head;
		}
	}

	
}


//输出表单记录   参数说明： mode—用于设置模式 1-输出原始表单 2-输出查询链表记录
void print_ori(struct material* head,int mode)
{
	int number = 0;
	struct material* pp = head->next;
	//输出表单的标题栏
	cout << "出/入库|编号|名称|单价|出/入库数|出/入库时间【年.月.日】|保管人|备注" << endl;

	if (mode == 1)         //显示原始的表单记录
	{
		number = sum_record;
	}
	else if (mode == 2)    //显示查询链表
	{
		number = sum_search;
	}


	for (int i = 0; i < number; i++)
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

//结点与结点相互赋值  将p2赋值给p1
void Copy_node_to_node(struct material* p1, struct material* p2);


/*-----------------------功能函数---------------------------*/


//表单记录处理初始化【仓库物品分类】
void Handout_ku_init(struct material* head, struct material* sec_head)
{
	struct material* record_head = head;
	struct material* cangku_head = sec_head;

	for (int i = 0; i < sum_record; i++)
	{
		record_head = record_head->next;   //下一个的表单记录

		//将该表单记录的内容放入仓库物品中
		Join_record(record_head,sec_head);

		
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

			//物品进行出库  **需要考虑该物品的数量是否够出库的
			else
			{
				//如果仓库中该物品不够的话
				if (cangku_head->store_num < now_record->out_num)
				{
					cout << "Error::该条表单记录在更新到仓库时出错" << endl;
					cout << "仓库中" << cangku_head->name << "不够出库" << "   ";
					cout << "仓库中" << cangku_head->name <<"剩余数量: "<< cangku_head->store_num << endl;
					cout << "请选择 作废该记录(1)-或-减少出库数(2)" << endl;
					int temp;
					cin >> temp;
					
					//作废该记录
					if (temp == 1)
					{
						now_record->out_num = 0;
						cout << "记录已作废!!!";
						Delay(1500);
						system("cls");
					}
					//重新输入出库数
					if (temp == 2)
					{
						cin >> now_record->out_num;
						cangku_head->store_num -= now_record->out_num;
						cout << "更改后的表单记录添加完成!!!" << endl;
						Delay(1500);
						system("cls");
					}				
				}
				else
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

		//物品进行出库--不可能
		else if (strcmp(now_record->in_out, "出库") == 0)
		{
			cout << "Error::该条表单记录在更新到仓库时出错" << endl;
			cout << "仓库中没有" << now_record->name << "这一物品" << endl;
			cout << "请选择 作废该记录(1)或更改该条记录(2)" << endl;

			int temp;
			cin >> temp;

			//作废该记录
			if (temp == 1)
			{
				now_record->out_num = 0;
				cout << "记录已作废!!!";
				Delay(1500);
				system("cls");
			}
			//重新输入出库数
			if (temp == 2)
			{
				
				cin >> now_record->in_out;
				//入库记录
				if (strcmp(now_record->in_out, "入库") == 0)
				{
					cin >> now_record->seri_number >> now_record->name >> now_record->unit_price 
						>> now_record->in_num >> now_record->in_time.year >> now_record->in_time.month 
						>> now_record->in_time.day>> now_record->person >> now_record->note;
					p0->store_num = now_record->in_num;
				}
				

				cout << "更改后的表单记录添加完成!!!" << endl;
				Delay(1500);
				system("cls");
			}
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
		int error = 0;
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

		//记录格式检查
		if (strcmp(new_one->in_out, "入库") != 0 && strcmp(new_one->in_out, "出库") != 0)
		{
			cout << "Error::	**未标明出入库方式**  该条表单记录添加无效！！！" << endl;
			error = 1;
		}
		else if (strcmp(new_one->in_out, "入库") == 0)
		{
			if (new_one->in_time.year < 0
				|| new_one->in_time.month < 0
				|| new_one->in_time.month>12
				|| new_one->in_time.day < 1
				|| new_one->in_time.day>31)
			{
				cout << "Error::	*日期格式有误**  该条表单记录添加无效！！！" << endl;
				error = 1;
			}

			if (new_one->in_num < 0)
			{
				cout << "Error::	*材料的数量不能为负值**  该条表单记录添加无效！！！" << endl;
				error = 1;
			}


			if (new_one->unit_price < 0)
			{
				cout << "Error::	*材料的单价不能为负值**  该条表单记录添加无效！！！" << endl;
				error = 1;
			}


		}
		else if (strcmp(new_one->in_out, "出库") == 0)
		{
			if (new_one->out_time.year < 0
				|| new_one->out_time.month < 0
				|| new_one->out_time.month>12
				|| new_one->out_time.day < 1
				|| new_one->out_time.day>31)
			{
				cout << "Error::	*日期格式有误**  该条表单记录添加无效！！！" << endl;
				error = 1;
			}

			if (new_one->out_num < 0)
			{
				cout << "Error::	*材料的数量不能为负值**  该条表单记录添加无效！！！" << endl;
				error = 1;
			}


			if (new_one->unit_price < 0)
			{
				cout << "Error::	*材料的单价不能为负值**  该条表单记录添加无效！！！" << endl;
				error = 1;
			}

		}


		//如果数据有错误，输出提示信息
		if (error == 1)
		{
			Delay(3500);
			system("cls");
		}

		

		if (error == 0)
		{
			//将该记录添加到表单中
			Join_to_record_List(new_one, base_head);

			//将该记录更新到仓库中
			Join_record(new_one, ku_head);

			cout << "单条记录添加完成！！！";
			Sleep(1500);
			system("cls");
		}
		
		
		return 1;
	}
	else if (mode == 2)
	{
		
		for (int i=0;;i++)
		{
			int error = 0;
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
			//记录格式检查
			if (strcmp(new_one->in_out, "入库") != 0 && strcmp(new_one->in_out, "出库") != 0)
			{
				cout << "Error::	**未标明出入库方式**  该条表单记录添加无效！！！" << endl;
				error = 1;
			}
			else if (strcmp(new_one->in_out, "入库") == 0)
			{
				if (new_one->in_time.year < 0
					|| new_one->in_time.month < 0
					|| new_one->in_time.month>12
					|| new_one->in_time.day < 1
					|| new_one->in_time.day>31)
				{
					cout << "Error::	*日期格式有误**  该条表单记录添加无效！！！" << endl;
					error = 1;
				}

				if (new_one->in_num < 0)
				{
					cout << "Error::	*材料的数量不能为负值**  该条表单记录添加无效！！！" << endl;
					error = 1;
				}


				if (new_one->unit_price < 0)
				{
					cout << "Error::	*材料的单价不能为负值**  该条表单记录添加无效！！！" << endl;
					error = 1;
				}


			}
			else if (strcmp(new_one->in_out, "出库") == 0)
			{
				if (new_one->out_time.year < 0
					|| new_one->out_time.month < 0
					|| new_one->out_time.month>12
					|| new_one->out_time.day < 1
					|| new_one->out_time.day>31)
				{
					cout << "Error::	*日期格式有误**  该条表单记录添加无效！！！" << endl;
					error = 1;
				}

				if (new_one->out_num < 0)
				{
					cout << "Error::	*材料的数量不能为负值**  该条表单记录添加无效！！！" << endl;
					error = 1;
				}


				if (new_one->unit_price < 0)
				{
					cout << "Error::	*材料的单价不能为负值**  该条表单记录添加无效！！！" << endl;
					error = 1;
				}

			}
			if (error == 1)
			{
				cout << endl;
			}
			else if (error == 0)
			{
				//将该记录添加到表单中
				Join_to_record_List(new_one, base_head);

				//将该记录更新到仓库中
				Join_record(new_one, ku_head);
			}
			
		}
		cout << "多条记录添加完成!!!";
		Delay(2000);
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
	Sleep(i);
}

//显示相关的表单记录
void Show_related_record(enum material_menu link)
{
	material* pp = base_head;
	if (link == unit_price)
	{
		
		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << " " << pp->name << " ";
			if (strcmp(pp->in_out,"入库") == 0)
			{
				cout << pp->in_time.year << " " << pp->in_time.month << " " << pp->in_time.day << " ";
			}
			else if (strcmp(pp->in_out, "出库") == 0)
			{
				cout << pp->out_time.year<< " " << pp->out_time.month << " " << pp->out_time.day << " ";
			}
			cout << pp->in_out << " " << pp->unit_price << endl;
		}

	}
	else if (link == num)
	{
		
		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << " " << pp->name << " ";
			if (strcmp(pp->in_out, "入库") == 0)
			{
				cout << pp->in_time.year << " " << pp->in_time.month << " " << pp->in_time.day << " ";
				cout << pp->in_out << " " << pp->in_num << endl;
			}
			else if (strcmp(pp->in_out, "出库") == 0)
			{
				cout << pp->out_time.year << " " << pp->out_time.month << " " << pp->out_time.day << " ";
				cout << pp->in_out << " " << pp->out_num << endl;
			}
			
		}
	}
	else if (link == person)
	{
		
		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << " " << pp->name << " ";
			if (strcmp(pp->in_out, "入库") == 0)
			{
				cout << pp->in_time.year << " " << pp->in_time.month << " " << pp->in_time.day << " ";
			}
			else if (strcmp(pp->in_out, "出库") == 0)
			{
				cout << pp->out_time.year << " " << pp->out_time.month << " " << pp->out_time.day << " ";
			}
			cout << pp->in_out << " " << pp->person << endl;
		}
	}
	else if (link == note)
	{
		
		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << " " << pp->name << " ";
			if (strcmp(pp->in_out, "入库") == 0)
			{
				cout << pp->in_time.year << " " << pp->in_time.month << " " << pp->in_time.day << " ";
			}
			else if (strcmp(pp->in_out, "出库") == 0)
			{
				cout << pp->out_time.year << " " << pp->out_time.month << " " << pp->out_time.day << " ";
			}
			cout << pp->in_out << " " << pp->note << endl;
		}
	
	}
	else if (link == all)
	{

		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << " " << pp->name << " ";
			if (strcmp(pp->in_out, "入库") == 0)
			{
				cout << pp->in_time.year << " " << pp->in_time.month << " " << pp->in_time.day << " ";
				cout << pp->in_out << " " << pp->unit_price << " " << pp->in_num << " " << pp->person << " " << pp->note << endl;
			}
			else if (strcmp(pp->in_out, "出库") == 0)
			{
				cout << pp->out_time.year << " " << pp->out_time.month << " " << pp->out_time.day << " ";
				cout << pp->in_out << " " << pp->unit_price << " " << pp->out_num << " " << pp->person << " " << pp->note << endl;
			}
			
		}
	}
}

//显示仓库物品清单
void Show_Cangku_Item()
{
	material* pp= ku_head;
	for (int i = 0; i < sum_item; i++)
	{
		pp = pp->next;
		cout << pp->seri_number << " " << pp->name<<" " << pp->store_num<<endl;
	}
}


//查询表单记录  参数说明:link-判断检索条件 mode-判断检索模式 
void Search_related_record(enum material_menu link,int mode)
{
	material search;  //记录检索的属性
	int flag = 0;  //用来判断当前记录是否符合条件
	int n = 0;
	//第一次检索
	if (mode == First_search)
	{
		
		
		sum_search = 0;

		Search_head = (material *)malloc(sizeof(material));
		material *p1=NULL, *p2=NULL;
		material* biao_dan = base_head;

		
		//按照编号进行检索
		if (link == seri_number)
		{
			cout << "请输入想要检索的材料的编号: " << endl;
			cin >> search.seri_number;
		}

		//按照名称进行检索
		if (link == name)
		{
			cout << "请输入想要检索的材料的名称: " << endl;
			cin >> search.name;
		}

		//按照日期进行检索
		if (link == record_data)
		{
			cout << "请输入想要检索的材料出库或入库日期:" << endl;
			cin >> search.in_time.year>> search.in_time.month>> search.in_time.day;  //此处将检索的日期放到入库日期中
		}

		//按照保管人进行检索
		if (link == person)
		{
			cout << "请输入想要检索的材料的保管人: " << endl;
			cin >> search.person;
		}

		//按照备注进行检索
		if (link == note)
		{
			cout << "请输入想要检索的材料的备注: " << endl;
			cin >> search.note;
		}

		system("cls");

		//已完成检索内容的输入，接下来就要进行检索
		for (int i = 0; i < sum_record; i++)
		{
			biao_dan = biao_dan->next;

			//按照编号进行检索
			if (link == seri_number)
			{
				if (strcmp(search.seri_number, biao_dan->seri_number) == 0)
				{
					flag = 1;
				}
			}

			//按照名称进行检索
			if (link == name)
			{
				if (strcmp(search.name, biao_dan->name) == 0)
				{
					flag = 1;
				}
			}

			//按照日期进行检索
			if (link == record_data)
			{
				//如果是入库记录
				if (strcmp(biao_dan->in_out, "入库") == 0)
				{
					if (search.in_time.year == biao_dan->in_time.year
						&& search.in_time.month == biao_dan->in_time.month
						&& search.in_time.day == biao_dan->in_time.day)
					{
						flag = 1;
					}
				}
				//如果是出库记录
				else if (strcmp(biao_dan->in_out,"出库") == 0)
				{
					if (search.out_time.year == biao_dan->out_time.year
						&& search.out_time.month == biao_dan->out_time.month
						&& search.out_time.day == biao_dan->out_time.day)
					{
						flag = 1;
					}
				}
				
			}

			//按照保管人进行检索
			if (link == person)
			{
				if (strcmp(search.person, biao_dan->person) == 0)
				{
					flag = 1;
				}
			}

			//按照备注进行检索
			if (link == note)
			{
				if (strcmp(search.note, biao_dan->note) == 0)
				{
					flag = 1;
				}
			}


			//如果该记录符合检索记录的话，就将该记录加到检索链表中
			if (flag == 1)
			{
				n++;
				//记录赋值
				p1 = (material*)malloc(sizeof(material));

				strcpy(p1->seri_number,biao_dan->seri_number);
				strcpy(p1->name, biao_dan->name);
				p1->unit_price = biao_dan->unit_price;
				strcpy(p1->in_out, biao_dan->in_out);
				if (strcmp(biao_dan->in_out, "入库") == 0)
				{
					p1->in_num=biao_dan->in_num;
					p1->in_time.year = biao_dan->in_time.year;
					p1->in_time.month = biao_dan->in_time.month;
					p1->in_time.day = biao_dan->in_time.day;
				}
				else if (strcmp(biao_dan->in_out, "出库") == 0)
				{
					p1->out_num = biao_dan->out_num;
					p1->out_time.year = biao_dan->out_time.year;
					p1->out_time.month = biao_dan->out_time.month;
					p1->out_time.day = biao_dan->out_time.day;
				}
				strcpy(p1->person, biao_dan->person);
				strcpy(p1->note, biao_dan->note);

				//新结点添加到检索链表中
				if (n == 1)
				{
					Search_head->next = p1;
				}
				else
				{
					p2->next = p1;
				}
				p2 = p1;
			
				flag = 0;  //清除符合检索标志位
				sum_search++;  //记录符合检索的记录数量
			}

			
		}

		p2->next = NULL;
	}

	//继续检索
	else if (mode == Continue_search)
	{
		int sum_search_temp = sum_search;
		material* p1 = NULL, * p2 = NULL;
		material* biao_dan = Search_head;
		material* temp_head = (material*)malloc(sizeof(material));
		//按照编号进行检索
		if (link == seri_number)
		{
			cout << "请输入想要检索的材料的编号: " << endl;
			cin >> search.seri_number;
		}

		//按照名称进行检索
		if (link == name)
		{
			cout << "请输入想要检索的材料的名称: " << endl;
			cin >> search.name;
		}

		//按照日期进行检索
		if (link == record_data)
		{
			cout << "请输入想要检索的材料出库或入库日期:" << endl;
			cin >> search.in_time.year >> search.in_time.month >> search.in_time.day;  //此处将检索的日期放到入库日期中
		}

		//按照保管人进行检索
		if (link == person)
		{
			cout << "请输入想要检索的材料的保管人: " << endl;
			cin >> search.person;
		}

		//按照备注进行检索
		if (link == note)
		{
			cout << "请输入想要检索的材料的备注: " << endl;
			cin >> search.note;
		}

		system("cls");

		//已完成再次筛选内容的输入，接下来就要从查询链表中重新检索
		for (int i = 0; i < sum_search_temp; i++)
		{
			biao_dan = biao_dan->next;

			//按照编号进行检索
			if (link == seri_number)
			{
				if (strcmp(search.seri_number, biao_dan->seri_number) == 0)
				{
					flag = 1;
				}
			}

			//按照名称进行检索
			if (link == name)
			{
				if (strcmp(search.name, biao_dan->name) == 0)
				{
					flag = 1;
				}
			}

			//按照日期进行检索
			if (link == record_data)
			{
				//如果是入库记录
				if (strcmp(biao_dan->in_out, "入库") == 0)
				{
					if (search.in_time.year == biao_dan->in_time.year
						&& search.in_time.month == biao_dan->in_time.month
						&& search.in_time.day == biao_dan->in_time.day)
					{
						flag = 1;
					}
				}
				//如果是出库记录
				else if (strcmp(biao_dan->in_out, "出库") == 0)
				{
					if (search.out_time.year == biao_dan->out_time.year
						&& search.out_time.month == biao_dan->out_time.month
						&& search.out_time.day == biao_dan->out_time.day)
					{
						flag = 1;
					}
				}

			}

			//按照保管人进行检索
			if (link == person)
			{
				if (strcmp(search.person, biao_dan->person) == 0)
				{
					flag = 1;
				}
			}

			//按照备注进行检索
			if (link == note)
			{
				if (strcmp(search.note, biao_dan->note) == 0)
				{
					flag = 1;
				}
			}


			//如果该记录符合检索记录的话，就将该记录加到检索链表中
			if (flag == 1)
			{
				n++;
				//记录赋值
				p1 = (material*)malloc(sizeof(material));

				strcpy(p1->seri_number, biao_dan->seri_number);
				strcpy(p1->name, biao_dan->name);
				p1->unit_price = biao_dan->unit_price;
				strcpy(p1->in_out, biao_dan->in_out);
				if (strcmp(biao_dan->in_out, "入库") == 0)
				{
					p1->in_num = biao_dan->in_num;
					p1->in_time.year = biao_dan->in_time.year;
					p1->in_time.month = biao_dan->in_time.month;
					p1->in_time.day = biao_dan->in_time.day;
				}
				else if (strcmp(biao_dan->in_out, "出库") == 0)
				{
					p1->out_num = biao_dan->out_num;
					p1->out_time.year = biao_dan->out_time.year;
					p1->out_time.month = biao_dan->out_time.month;
					p1->out_time.day = biao_dan->out_time.day;
				}
				strcpy(p1->person, biao_dan->person);
				strcpy(p1->note, biao_dan->note);

				//新结点添加到检索链表中
				if (n == 1)
				{
					temp_head->next = p1;
				}
				else
				{
					p2->next = p1;
				}
				p2 = p1;

				flag = 0;  //清除符合检索标志位
				sum_search++;  //记录符合检索的记录数量
			}

			if(flag==0)
			{
				sum_search--;
			}

		}

		p2->next = NULL;

		Search_head = temp_head;
		
	}

	if (mode == First_search || mode == Continue_search)
	{
		print_ori(Search_head, 2);
	}

		//清空检索链表
	else if (mode == Clear_list)
	{
		
		material* temp_head_behind = Search_head->next;
		material* temp_head_front= Search_head->next;
		for (int i = 0; i < sum_search; i++)
		{
			temp_head_front = temp_head_front->next;
			free(temp_head_behind);
			temp_head_behind = temp_head_front;

		}
		system("cls");
	}
	

	
}


//查询仓库记录			
void Search_ku_item()
{
	material* temp_head = ku_head;
	material* search = (material*)malloc(sizeof(material));
	material* p1 = NULL, * p2 = NULL;

	cout << "请输入想要查询仓库物品的名称: "<<endl;
	cin >> search->name;

	system("cls");
	for (int i = 0; i < sum_item; i++)
	{
		
		temp_head = temp_head->next;

		if (strcmp(temp_head->name, search->name) == 0)
		{
			cout << temp_head->seri_number << " " << temp_head->name << " " << temp_head->store_num << endl;
		}
	}
	
}


//将经由查询模式得到的表单记录定位到表单库中的具体位置


//修改单条表单记录功能   参数说明 link: 修改的表单记录属性  mode:修改模式 1-首次修改 2-继续修改 3-显示记录
void Change_record(enum material_menu link,int mode)
{
	struct material* temp_data = (material*)malloc(sizeof(material));  //临时数据存储
	int mode_change_all = 0;
	if (link == all)  mode_change_all = 1;  //如果修改全部的属性 就要把所有的if执行一遍
	struct material* one_record;  //用于保存查询到的单条原始表单记录


	//首次修改
	if (mode == 1||mode==2)
	{

		//找到要修改的表单记录
		one_record = Search_head->next;

		//将原始的结点值赋给临时数据存储结点
		Copy_node_to_node(temp_data, one_record);
		

		//修改某一属性
		
		//修改编号
		if (link == seri_number|| mode_change_all==1)
		{
			cout << "请输入修改后的编号" << endl;
			cin >> temp_data->seri_number;
		}
		//修改名字
		if (link == name || mode_change_all == 1)
		{
			cout << "请输入修改后的姓名" << endl;
			cin >> temp_data->name;
		}
		//修改单价
		if (link == unit_price || mode_change_all == 1)
		{
			cout << "请输入修改后的单价" << endl;
			cin >> temp_data->unit_price;
		}
		//修改出入库记录
		if (link == in_out_way || mode_change_all == 1)
		{
			cout << "请输入修改后的出入库记录" << endl;
			cin >> temp_data->in_out;
		}
		//修改出入库数量
		if (link == in_out_num || mode_change_all == 1)
		{
			cout << "请输入修改后的出入库数量" << endl;
			if (strcmp(temp_data->in_out, "入库") == 0)
			{
				cin >> temp_data->in_num;
			}
			else if (strcmp(temp_data->in_out, "出库") == 0)
			{
				cin >> temp_data->out_num;
			}
		}

		//修改出入库时间
		if (link == in_out_time || mode_change_all == 1)
		{
			cout << "请输入修改后的出入库时间" << endl;
			if (strcmp(temp_data->in_out, "入库") == 0)
			{
				cin >> temp_data->in_time.year >> temp_data->in_time.month >> temp_data->in_time.day;

			}
			else if (strcmp(temp_data->in_out, "出库") == 0)
			{
				cin >> temp_data->out_time.year >> temp_data->out_time.month >> temp_data->out_time.day;
			}
		}
		//修改保管人
		if (link==person || mode_change_all == 1)
		{
			cout << "请输入修改后的保管人";
			cin >> temp_data->person;
		}
		//修改备注
		if (link == note || mode_change_all == 1)
		{
			cout << "请输入修改后的备注" << endl;
			cin >> temp_data->note;
		}
		//全部修改
		if (link == all)
		{
			cout <<"已经全部修改完成";
		}
		

		//到这里仅仅是将查询的表单记录修改完

		//将修改的查询记录更新到表单记录中
		Update_change_to_record(temp_data, one_record,base_head);

		//将表单记录更新到仓库中
		ku_head->next = NULL;  //先将仓库的物品清空
		sum_item = 0;    //仓库物品清零
		Handout_ku_init(base_head,ku_head);

		//将修改完的临时结点重新赋值给查询链表中的结点,以便于下一次修改
		Copy_node_to_node(one_record, temp_data);
	}


	//显示记录
	if (mode == 3)
	{
		temp_data = Search_head->next;
		if (strcmp(temp_data->in_out, "入库") == 0)
		{
			cout << temp_data->in_out << " " << temp_data->seri_number << " " << temp_data->name << " " << temp_data->unit_price << " " << temp_data->in_num << " "
				<< temp_data->in_time.year << "年" << temp_data->in_time.month << "月" << temp_data->in_time.day << "日" << " "
				<< temp_data->person << " " << temp_data->note << endl;
		}

		if (strcmp(temp_data->in_out, "出库") == 0)
		{
			cout << temp_data->in_out << " " << temp_data->seri_number << " " << temp_data->name << " " << temp_data->unit_price << " " << temp_data->out_num << " "
				<< temp_data->out_time.year << "年" << temp_data->out_time.month << "月" << temp_data->out_time.day << "日" << " "
				<< temp_data->person << " " << temp_data->note << endl;

		}
	}
}


//将修改的单条查询记录更新到表单记录中  参数说明： 第一个是修改后结点数据   第二个是相应的查询链表原始结点数据  第三个是表单记录头指针
void Update_change_to_record(struct material* Change_record_head, struct material* now_search_head, struct material* base_head)
{
	int find_flag = 0;  //搜索标志位 0-没找到 1-找到

	struct material* now_base_record = base_head->next;  //用于遍历链表的指针


	//搜索表单记录,找到当前的查询记录对应的表单记录的位置，将已修改的结点赋值给搜索到的结点
	for (int i = 0; i < sum_record; i++)
	{
		if (strcmp(now_base_record->seri_number, now_search_head->seri_number) == 0)
		{
			if (strcmp(now_base_record->name, now_search_head->name) == 0)
			{
				if (now_base_record->unit_price == now_search_head->unit_price)
				{
					if (strcmp(now_base_record->in_out, now_search_head->in_out) == 0)
					{
						if (strcmp(now_base_record->in_out, "入库") == 0)
						{
							if (now_base_record->in_num == now_search_head->in_num)
							{
								if (now_base_record->in_time.year == now_search_head->in_time.year
									&& now_base_record->in_time.month == now_search_head->in_time.month
									&& now_base_record->in_time.day == now_search_head->in_time.day)
								{
									if (strcmp(now_base_record->person, now_search_head->person) == 0)
									{
										if (strcmp(now_base_record->note, now_search_head->note) == 0)
										{
											//执行到这里，就找到一样的结点了
											//进行赋值
											Copy_node_to_node(now_base_record, Change_record_head);
											break;
										}
									}
								}
							}

						}
						else if (strcmp(now_base_record->in_out, "出库") == 0)
						{
							if (now_base_record->out_num == now_search_head->out_num)
							{
								if (now_base_record->out_time.year == now_search_head->out_time.year
									&& now_base_record->out_time.month == now_search_head->out_time.month
									&& now_base_record->out_time.day == now_search_head->out_time.day)
								{
									if (strcmp(now_base_record->person, now_search_head->person) == 0)
									{
										if (strcmp(now_base_record->note, now_search_head->note) == 0)
										{
											//执行到这里，就找到一样的结点了
											//进行赋值
											Copy_node_to_node(now_base_record, Change_record_head);
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		now_base_record = now_base_record->next;
	}

}


//结点与结点相互赋值  将p2赋值给p1
void Copy_node_to_node(struct material* p1, struct material* p2)
{
	strcpy(p1->seri_number, p2->seri_number);
	strcpy(p1->name, p2->name);
	p1->unit_price = p2->unit_price;
	strcpy(p1->in_out, p2->in_out);
	if (strcmp(p1->in_out, "入库") == 0)
	{
		p1->in_num = p2->in_num;
		p1->in_time.year = p2->in_time.year;
		p1->in_time.month = p2->in_time.month;
		p1->in_time.day = p2->in_time.day;

	}
	else if (strcmp(p1->in_out, "出库") == 0)
	{
		p1->out_num = p2->out_num;
		p1->out_time.year = p2->out_time.year;
		p1->out_time.month = p2->out_time.month;
		p1->out_time.day = p2->out_time.day;
	}
	strcpy(p1->person, p2->person);
	strcpy(p1->note, p2->note);
}

//修改多条表单记录功能
void Change_many_record(enum material_menu link, int mode)
{
	struct material* temp_data = (material*)malloc(sizeof(material));  //临时数据存储
	int mode_change_all = 0;
	if (link == all)  mode_change_all = 1;  //如果修改全部的属性 就要把所有的if执行一遍
	struct material* one_record;  //用于遍历查询到的多条原始表单记录
	struct material* Copy_search_head = NULL;   //查询链表的复制链表（有头结点） 
	struct material* one_copy_record;         //用于遍历复制链表

	//首次修改
	if (mode == 1 || mode == 2)
	{
		//找到要修改的表单记录
		one_record = Search_head->next;
		Copy_node_to_node(temp_data,one_record);  //初始化临时数据结点

		//将查询链表复制一份，得到Copy_search_list,修改复制链表的数据，原始的查询链表不可以动
		//准备工作
		int n = 0;
		Copy_search_head = (struct material*)malloc(sizeof(material));
		struct material* p1 = NULL;    //用于不断地创建新的结点
		struct material* p2 = NULL;    //用于指向链表的最后的一个结点
		Copy_search_head->next = NULL;

		//开始复制
		for (int i = 0; i < sum_search; i++)
		{
			n++;
			p1= (struct material*)malloc(sizeof(material));
			Copy_node_to_node(p1, one_record);
			if (n == 1)
			{
				Copy_search_head->next = p1;
			}
			else if (n > 1)
			{
				p2->next = p1;
			}
			p2 = p1;

			one_record = one_record->next;   //查询链表的下一个结点
			

		}
		p2->next = NULL;

		//修改某一属性 修改的值赋给临时结点
		//修改编号
		if (link == seri_number || mode_change_all == 1)
		{
			cout << "请输入修改后的编号" << endl;
			cin >> temp_data->seri_number;
		}
		//修改名字
		if (link == name || mode_change_all == 1)
		{
			cout << "请输入修改后的姓名" << endl;
			cin >> temp_data->name;
		}
		//修改单价
		if (link == unit_price || mode_change_all == 1)
		{
			cout << "请输入修改后的单价" << endl;
			cin >> temp_data->unit_price;
		}
		//修改出入库记录
		if (link == in_out_way || mode_change_all == 1)
		{
			cout << "请输入修改后的出入库记录" << endl;
			cin >> temp_data->in_out;
		}
		//修改出入库数量
		if (link == in_out_num || mode_change_all == 1)
		{
			cout << "请选择想要修改入库数还是出库数??  输入<入库> or <出库>"<<endl;
			cin >> temp_data->in_out;
			cout << "请输入修改后的出入库数量" << endl;
			if (strcmp(temp_data->in_out, "入库") == 0)
			{
				cin >> temp_data->in_num;
			}
			else if (strcmp(temp_data->in_out, "出库") == 0)
			{
				cin >> temp_data->out_num;
			}
		}

		//修改出入库时间
		if (link == in_out_time || mode_change_all == 1)
		{
			cout << "请选择想要修改入库时间还是出库时间??  输入<入库> or <出库>" << endl;
			cin >> temp_data->in_out;
			cout << "请输入修改后的出入库时间" << endl;
			if (strcmp(temp_data->in_out, "入库") == 0)
			{
				cin >> temp_data->in_time.year >> temp_data->in_time.month >> temp_data->in_time.day;

			}
			else if (strcmp(temp_data->in_out, "出库") == 0)
			{
				cin >> temp_data->out_time.year >> temp_data->out_time.month >> temp_data->out_time.day;
			}
		}
		//修改保管人
		if (link == person || mode_change_all == 1)
		{
			cout << "请输入修改后的保管人";
			cin >> temp_data->person;
		}
		//修改备注
		if (link == note || mode_change_all == 1)
		{
			cout << "请输入修改后的备注" << endl;
			cin >> temp_data->note;
		}
		//全部修改
		if (link == all)
		{
			cout << "已经全部修改完成";
		}
		
		one_record = Search_head->next;               //重新指向查询链表的第一个结点
		one_copy_record = Copy_search_head->next;     //指向赋值链表的第一个结点

		//将复制链表中的结点一个一个的修改  单一属性的修改或者全部属性的修改
		for (int i = 0; i < sum_search; i++)
		{
			if (link == seri_number)
			{
				strcpy(one_copy_record->seri_number,temp_data->seri_number);
			}
			//修改名字
			if (link == name)
			{
				strcpy(one_copy_record->name, temp_data->name);
			}
			//修改单价
			if (link == unit_price)
			{
				one_copy_record->unit_price= temp_data->unit_price;
			}
			//修改出入库记录
			if (link == in_out_way)
			{
				strcpy(one_copy_record->in_out,temp_data->in_out);
			}
			//修改出入库数量
			if (link == in_out_num)
			{
				cout << "请输入修改后的出入库数量" << endl;
				if (strcmp(temp_data->in_out, "入库") == 0)
				{
					one_copy_record->in_num= temp_data->in_num;
				}
				else if (strcmp(temp_data->in_out, "出库") == 0)
				{
					one_copy_record->out_num=temp_data->out_num;
				}
			}

			//修改出入库时间
			if (link == in_out_time)
			{
				cout << "请输入修改后的出入库时间" << endl;
				if (strcmp(temp_data->in_out, "入库") == 0)
				{
					one_copy_record->in_time.year= temp_data->in_time.year;
					one_copy_record->in_time.month = temp_data->in_time.month;
					one_copy_record->in_time.day = temp_data->in_time.day;

				}
				else if (strcmp(temp_data->in_out, "出库") == 0)
				{
					one_copy_record->out_time.year = temp_data->out_time.year;
					one_copy_record->out_time.month = temp_data->out_time.month;
					one_copy_record->out_time.day = temp_data->out_time.day;
				}
			}
			//修改保管人
			if (link == person)
			{
				strcpy(one_copy_record->person,temp_data->person);
			}
			//修改备注
			if (link == note)
			{
				strcpy(one_copy_record->note, temp_data->note);
			}
			//全部修改
			if (link == all)
			{
				Copy_node_to_node(one_copy_record, temp_data);
			}

			
			one_copy_record = one_copy_record->next;     //换复制链表中的下一个结点
		} 

		one_record = Search_head->next;               //重新指向查询链表的第一个结点
		one_copy_record = Copy_search_head->next;     //指向赋值链表的第一个结点

		//到这里仅仅是将查询链表的结点修改完

		//将修改的查询记录更新到表单记录中
		for (int i = 0; i < sum_search; i++)
		{
			Update_change_to_record(one_copy_record, one_record, base_head);
			one_record = one_record->next;
			one_copy_record = one_copy_record->next;
		}
		

		//将表单记录更新到仓库中
		ku_head->next = NULL;  //先将仓库的物品清空
		sum_item = 0;    //仓库物品清零
		Handout_ku_init(base_head, ku_head);

		one_record = Search_head->next;               //重新指向查询链表的第一个结点
		one_copy_record = Copy_search_head->next;     //指向赋值链表的第一个结点

		//将修改完的临时结点重新赋值给查询链表中的结点,以便于下一次修改
		for (int i = 0; i < sum_search; i++)
		{
			Copy_node_to_node(one_record, one_copy_record);
			one_record = one_record->next;
			one_copy_record = one_copy_record->next;
		}
		
		
	}


	//显示记录
	if (mode == 3)
	{
		print_ori(Search_head,2);
	}
}