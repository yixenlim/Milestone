/**********|**********|**********|
Program: TT08.1171103542.Lim.Yixen.cpp
Course: Programming Fundamentals
Year: 2019/20 Trimester 1
Name: Lim Yixen
ID: 1171103542
Lecture Section: TC04
Tutorial Section: TT08
Email: 1171103542@student.mmu.edu.my
Phone: 010-8195904
**********|**********|**********/

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <limits>
using namespace std;

string input,border = "==========================================",line = "====================================================================================";
int x,y,i,r,c,counter,choice,choice_x,choice_y,ori_choice_y,ori_choice_x,direction,time_step,excessive_r,current_r,quantity,counter2,counter3,c2,c3,c4,speed,
excessive_r2,counter4,current_column,current_counter,r2,short_c,long_c,reserve,last_printed;
bool token,wrap,long_wrap;

void clear();
void print_line();

string askinput();

int x_coordinate();
int y_coordinate();
int dir();
int timestep();
int askspeed();

void stationary();
void up();
void down();
void left();
void right();

void delay();
void print(string,int,int,int);

int main () 
{
	clear();
	
	cout << line << endl;
	input = askinput();//ask for user input and store as input
	cout << endl;
	
	cout << line << endl;
	cout << "Please enter the coordinate you wish to start" << endl << endl;
	
	ori_choice_x = x_coordinate();//ask user to enter x-coordinate and store as ori_choice_x
	cout << endl;
	
	ori_choice_y = y_coordinate();//ask user to enter y-coordinate and store as ori_choice_y
	cout << endl;
	
	cout << line << endl;
	direction = dir();//ask for direction and store as direction
	cout << endl;

	if (direction != 0)//ask for time step and speed if stationary is not selected
	{
		cout << line << endl;
		time_step = timestep();//call the function to ask for time step and store as time_step
		cout << endl;
		
		cout << line << endl;
		speed = askspeed();//call the function to ask for speed and store as speed
	}

	if (direction == 0)
		stationary();//call the stationary function
	else if (direction == 1)
		up();//call the up function
	else if (direction == 2)
		down();//call the down function
	else if (direction == 3)
		right();//call the right function
	else if (direction == 4)
		left();//call the left function

	return 0;
}

void clear()
{
	system("CLS");
}

void print_line()
{
	cout << "                                        ";
}

string askinput()
{
	do 
	{
		cout << "Please enter the text you wish to display (Up to 25 characters): " ;
		getline(cin, input);
		
		if (input.size() > 25)//if user enters more than 25 characters
		{
			cout << "\n**Your text exceeds 25 characters!**" << endl;
			token = false;
		}
		
		if (input.size() <=25)
		{
			for (int i = 0;i < input.size();i++)
			{
				if (isalnum(input[i]) or input[i] == ' ')//check if user has entered any symbols
				{
					token = true;
				}
				else
				{ 
					token = false;
					cout << "\n**Your text cannot involve any symbols!**" << endl;
					break;
				}
			}
		}
	} while (token == false);
	
	return input;
}

int x_coordinate()
{
	do
	{
		cout << "X-coordinate (0 <= x <= 39): ";
		cin >> ori_choice_x;
		
		if (cin.fail())//if user does not enter integer
		{
			cout << "\n**Please enter a valid number!**" << endl;
			cin.clear();
			cin.ignore(numeric_limits<int>::max(),'\n');
			token = false;
		}
		else if (ori_choice_x < 0 or ori_choice_x > 39)//if user enter integer that out of range
		{
			cout << "\n**Please enter the x-coordinate within the given range!**" << endl;
			token = false;
		}
		else
		{
			token = true;
		}
	} while (token == false);
	
	return ori_choice_x;
}
	
int y_coordinate()
{
	do
	{
		cout << "Y-coordinate (0 <= y <= 19): ";
		cin >> ori_choice_y;
		
		if (cin.fail())//if user does not enter integer
		{
			cout << "\n**Please enter a valid number!**" << endl;
			cin.clear();
			cin.ignore(numeric_limits<int>::max(),'\n');
			token = false;
		}
		else if (ori_choice_y < 0 or ori_choice_y > 19)
		{
			cout << "\n**Please enter the y-coordinate within the given range!**" << endl;//if user enter integer that out of range
			token = false;
		}
		else
		{
			token = true;
		}
	} while (token == false);
	
	return ori_choice_y;
}

int askspeed()
{
	do
	{
		cout << "Please select the speed you want(1-10): ";
		cin >> speed;
		
		if (cin.fail())//if user does not enter integer
		{
			cout << "\n**Please enter a valid number!**" << endl;
			cin.clear();
			cin.ignore(numeric_limits<int>::max(),'\n');
			token = false;
		}
		else if (speed < 0 or speed > 10)//if user enter integer that out of range
		{
			cout << "\n**Please enter the speed within the given range!**" << endl;
			token = false;
		}
		else
		{
			token = true;
		}
	} while (token == false);
	
	return speed;
}

int dir()
{
	cout << "0 - Stationary" << endl;
	cout << "1 - Scrolling up" << endl;
	cout << "2 - Scrolling down" << endl;
	cout << "3 - Moving from left to right" << endl;
	cout << "4 - Moving from right to left\n" << endl;
	
	do 
	{
		cout << "Direction to display your text: ";
		cin >> direction;
		
		if (cin.fail())//if user does not enter integer
		{
			cout << "\n**Please enter a valid choice!**" << endl;
			cin.clear();
			cin.ignore(numeric_limits<int>::max(),'\n');
			token = false;
		}
		else if (direction < 0 or direction > 4)//if user enter integer that out of range
		{
			cout << "\n**Please select a valid choice!**" << endl;
			token = false;
		}
		else
		{
			token = true;
		}
	} while (token == false);
	
	return direction;
}

int timestep()
{
	do
	{
		cout << "Please enter your time step: ";
		cin >> time_step;
		
		if (cin.fail())//if user does not enter integer
		{
			cout << "\n**Please enter a valid number!**" << endl;
			cin.clear();
			cin.ignore(numeric_limits<int>::max(),'\n');
			token = false;
		}
		else if (time_step < 0)//if user enter negative integer
		{
			cout << "\n**Please enter a positive number!**" << endl;
			token = false;
		}
		else
		{
			token = true;
		}
	} while (token == false);
	
	return time_step;
}

void stationary()
{
	y=19,r=0,choice_y=ori_choice_y,choice_x = ori_choice_x;
	
	cout << border << endl;//print the upper border
	
	while (y>=0)
	{
		cout << "=";
		
		if (choice_y != y)//print empty row if the y-coordinate is not match
		{
			print_line();
		}
		else if ( r >= 0 and r <= 6 )//enter once the y-coordinate is found and rows of text have not been printed completely
		{
			x = 0;
			while (x<=39)
			{
				if (choice_x != x)//print empty column if the x-coordinate is not match
				{
					cout << " ";
					x++;
				}
				else
				{
					for (counter = 0; counter < input.size(); counter++)//start to print the text
					{
						c = 0;//set to start printing from column=0
						while (c < 6)
						{
							print(input,counter,r,c);//call the print function to print every element
							
							c++;//increase to next column
							x++;
							
							if (x == 40)//check if the printing process reaches the right border
								break;
						}
						
						if (x == 40)
							break;
					}
					r++;
					
					while (x<=39)//fill in empty column if there are any
					{
						cout << " ";
						x++;
					}
				}
			}
			choice_y--;//decrement user input of y-coordinate to match the entry condition
		}
		else
		{
			print_line();//print empty row after 7 rows of character
		}
		cout << "=" << endl;
		y--;//move to the row below
	}
	cout << border << endl;//print the lower border and here end one time step
}

void up()
{
	for (int step = 0;step < time_step;step++)//loop according to time step
	{
		clear();
		y=19,r=0,choice_x = ori_choice_x,choice_y = ori_choice_y;
		
		cout << border << endl;
		
		while (y>=0 and choice_y < 20)//print like normal
		{
			cout << "=";
			
			if (choice_y != y)
			{
				print_line();
			}
			else if ( r >= 0 and r <= 6 )
			{
				x = 0;
				while (x<=39)
				{
					if (choice_x != x)
					{
						cout << " ";
						x++;
					}
					else
					{
						for (counter = 0; counter < input.size(); counter++)
						{	
							c = 0;
							while (c < 6)
							{
								print(input,counter,r,c);
								
								c++;
								x++;
								
								if (x == 40)
									break;
							}
							
							if (x == 40)
								break;
						}
						r++;
						
						while (x<=39)
						{
							cout << " ";
							x++;
						}
					}
				}
				choice_y--;
			}
			else
			{
				print_line();
			}
			cout << "=" << endl;
			y--;
		}
		
		if (choice_y >= 20)//if the text move out of the upper border and start wrap effect
		{
			y=19,excessive_r=0;
			if (choice_y == 40)//when text reach the upper border again
			{
				choice_y = 20;//reset choice_y and ori_choice_y to 20 since it has the same effect
				ori_choice_y = 20;
			}
			r = choice_y - 19;//indicate the row of text to start printing at te upper part
			current_r = r;//reserve r-value of row at the lower part of the display board
			
			while (y >= current_r)
			{
				cout << "=";
				if (r < 7)//enter to print the whole upper part
				{
					x=0;
					while (x<=39)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							for (counter = 0; counter < input.size(); counter++)
							{	
								c = 0;
								while (c < 6)
								{
									print(input,counter,r,c);
									
									c++;
									x++;
									
									if (x == 40)
										break;
								}
								
								if (x == 40)
									break;
							}
							r++;
							
							while (x<=39)
							{
								cout << " ";
								x++;
							}
							
							cout << "=" << endl;
						}
					}
					y--;
				}
				else//print the empty rows in between
				{
					print_line();
					cout << "=" << endl;
					y--;
				}
			}

			while (y >= 0)
			{
				cout << "=";
				x=0;
				
				while (x<=39)
				{
					if (choice_x != x and excessive_r <= 6)//locate x-coordinate
					{
						cout << " ";
						x++;
					}
					else if (excessive_r <= 6)
					{
						for (counter = 0; counter < input.size(); counter++)//print out text at the lower part of display board
						{	
							c = 0;
							while (c < 6)
							{
								print(input,counter,excessive_r,c);//call function to start printing starting from excessive_r value row
								
								c++;
								x++;
								
								if (x == 40)
									break;
							}
							
							if (x == 40)
								break;
						}
						excessive_r++;
						
						while (x<=39)
						{
							cout << " ";
							x++;
						}
						
						cout << "=" << endl;
					}
					else 
					{
						print_line();
						cout << "=" << endl;
						break;
					}
				}
				y--;
			}
		}
		cout << border << endl;
		ori_choice_y++;//increment the original choice_y of user so that it appears moving upwards
		
		delay();//funtion called to delay the process of showing by using speed chose by user
	}
}

void down()
{
	wrap = false;//wrap effect is close at first
	
	for (int step = 0;step < time_step;step++)
	{
		clear();
		
		y=19,r=0,choice_x = ori_choice_x,choice_y = ori_choice_y;
		
		cout << border << endl;
		
		if (wrap == false)//when wrap effect is not needed, print like normal
		{
			while (y>=0)
			{
				cout << "=";
				
				if (choice_y != y)
				{
					print_line();
				}
				else if ( r >= 0 and r <= 6 )
				{
					x = 0;
					while (x<=39)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							for (counter = 0; counter < input.size(); counter++)
							{	
								c = 0;
								while (c < 6)
								{
									print(input,counter,r,c);
									
									c++;
									x++;
									
									if (x == 40)
										break;
								}
								
								if (x == 40)
									break;
							}
							
							if (y == 0 and r == 6)//text will out of lower border in next time step
							{
								wrap = true;//open the wrap effect
								excessive_r = 7;
							}
							
							r++;
							
							while (x<=39)
							{
								cout << " ";
								x++;
							}
						}
					}
					choice_y--;
				}
				else
				{
					print_line();
				}
				cout << "=" << endl;
				y--;
			}
		}
		else if (wrap == true)//enter if wrap effect is needed
		{
			excessive_r--;//decrement the strting row at upper part of display board
			excessive_r2 = excessive_r;//excessive_r2 will be changed and used to print text
			
			if (excessive_r2 == 1)//reset the y-coordinate to 19 for the next time step as it has the same effect
			{
				wrap = false;//close the wrap effect for next time step
				ori_choice_y = 20;
				excessive_r = 7;
				r = 7;
			}
			
			while (excessive_r2 < 7)//this loop prints text at the upper part of display board
			{
				cout << "=";
				x=0;
				
				while (x<=39)
				{
					if (choice_x != x)
					{
						cout << " ";
						x++;
					}
					else
					{
						for (counter = 0; counter < input.size(); counter++)//print out text by using excessive_r2 value as starting row value
						{	
							c = 0;
							while (c < 6)
							{
								print(input,counter,excessive_r2,c);
								
								c++;
								x++;
								
								if (x == 40)
									break;
							}
							
							if (x == 40)
								break;
						}
						excessive_r2++;
						
						while (x<=39)
						{
							cout << " ";
							x++;
						}
						
						cout << "=" << endl;
					}
				}
				y--;
			}
				
			r2 = 0;
			while (y >= 0)//this loop print empty rows in between and text at the lower part of the display board
			{
				cout << "=";
				
				if (y > choice_y)//print empty rows until found choice_y
				{
					print_line();
					cout << "=" << endl;
				}
				else
				{
					x=0;
					while (x<=39)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							for (counter = 0; counter < input.size(); counter++)//start to print text starting from row=0
							{	
								c = 0;
								while (c < 6)
								{
									print(input,counter,r2,c);
									
									c++;
									x++;
									
									if (x == 40)
										break;
								}
								
								if (x == 40)
									break;
							}
							r2++;
							
							while (x<=39)
							{
								cout << " ";
								x++;
							}
							cout << "=" << endl;
						}
					}
				}
				y--;
			}
		}
		cout << border << endl;
		ori_choice_y--;//decrement original choice_y of user so that it appears moving downwards

		if (r != 7 and wrap == false)//check if text is not fully shown in the first time step
		{
			wrap = true;
			excessive_r = 7;
		}
		delay();
	}
}

void right()
{
	quantity=input.size(),wrap=false,counter=0,c=0,choice=choice_x,counter2=quantity-1,c2=6;
	
	for (int step = 0;step < time_step;step++)
	{
		clear();
		choice++;
	
		y=19,r=0,choice_x=ori_choice_x,choice_y=ori_choice_y;
		
		cout << border << endl;
		
		while (y>=0)
		{
			cout << "=";
			
			if (choice_y != y)
			{
				print_line();
			}
			else if ( r >= 0 and r <= 6 )
			{
				x = 0;
				while (x<=39)
				{
					if (wrap == false)//enter if no wrap effect needed, print like normal
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else 
						{	
							choice = x;//save the choice_x value as choice
							for (counter = 0; counter < input.size(); counter++)
							{
								c = 0;
								while (c < 6)
								{
									last_printed = x;//save the last printed x-coordinate value
									print(input,counter,r,c);
									
									c++;
									x++;
									
									if (x == 40)
										break;
								}
								if (x == 40)
									break;
							}

							while (x<=39)
							{
								cout << " ";
								x++;
							}
						}
					}
					else if (wrap == true)//enter if wrap effect needed
					{
						if (c2 == -1)//reset column value to last column and to previous character
						{
							c2 = 5;
							counter2--;
						}
						
						c3 = c2;
						
						for (counter3 = counter2; counter3 < input.size(); counter3++)//start printing the text accroding to the value of counter2 and c2 at the left part of display board
						{
							while (c3 < 6)
							{
								print(input,counter3,r,c3);
								
								c3++;
								x++;
								
								if (x == 40)
								{
									break;
								}
							}
							
							c3=0;//set c3=0 for the character afterwards

							if (x == 40)
							{
								break;
							} 
						}
							
						while (x <= 39)
						{
							if (choice != x)//print empty column until the changing x-coordinate by using the value of choice
							{
								cout << " ";
								x++;
							}
							else 
							{	
								for (counter = 0; counter < input.size(); counter++)//start printing text at the right part of display board
								{
									c = 0;
									while (c < 6)
									{
										print(input,counter,r,c);
										
										c++;
										x++;
										
										if (x == 40)
										{
											break;
										}
									}
									
									if (x == 40)
									{
										break;
									} 
								}
							}
						}
					}
				}
				r++;
				choice_y--;
			}
			else
			{
				print_line();
			}
			cout << "=" << endl;
			y--;
		}
		cout << border << endl;
		ori_choice_x++;//increment the original choice_x of user so that it appears moving to the right
		
		if (last_printed == 39 and counter == quantity - 1 and c == 6)//when last column of last character is printed at x=39
		{
			last_printed = 0;
			wrap = true;//open the wrap effect
			c2--;//change the starting column to be printed at the left part of display board
		}
		else if (counter2 == 0 and c2 == 1)//if the second column of first character has been printed out at x=0 after the wrap effect takes place
		{
			wrap = false;//close the wrap effect
			ori_choice_x = 0;//set the ori_choice_x to 0 as it has the same output as next time step
			counter2 = quantity - 1;//reset the default value of counter2 and c2
			c2=6;
		}
		else if (wrap == true)//if wrap effect takes place
		{
			c2--;//change the starting column to be printed at the left part of display board
		}
		else if (wrap == false and counter != quantity and c != 6)//enter when not all text are displayed
		{
			wrap = true;//start wrap effect
			c2--;//change the starting column to be printed at the left part of display board
		}
		
		delay();
	}
}

void left()
{
	wrap=false,quantity=input.size(),counter=0,c=0,reserve=40,short_c=0,counter2=0,long_c=0,long_wrap=false;
	
	for (int step = 0;step < time_step;step++)
	{
		clear();
		
		if (choice == 1)//if the long text start at x=1 in the last time step
		{
			ori_choice_x = 0;//reset x-coordinate to 0 as it has the same output
			choice = 2;
			long_wrap = false;//close the wrap effect
			counter2 = 0;//reset value of counter2 and long_c
			long_c = 0;
		}
		else if (wrap == true)//enter if short text is detected and wrap effect need to take place
		{
			short_c++;//change the starting column of text to be printed at the left part of display board
			reserve--;//to reserve empty column at the right part of display board for wrap effect
		}
		else if (long_wrap == true)//enter if long text being detected in the first time step
		{
			long_c++;//change the starting column of text to be printed at the left part of display board
		}
		
		y=19,r=0,choice_x = ori_choice_x,choice_y=ori_choice_y;
		
		cout << border << endl;
		
		while (y>=0)
		{
			cout << "=";
			
			if (choice_y != y)
			{
				print_line();
			}
			else if ( r >= 0 and r <= 6 )
			{
				x = 0;
				while (x<=39)
				{
					if (long_wrap == true)//enter if a long text being detected
					{
						if (long_c == 6)//reset starting column to be printed to the first column of the next character
						{
							long_c = 0;
							counter2++;
						}
						
						c3 = long_c;
						
						for (counter3 = counter2; counter3 < input.size(); counter3++)//start printing at the left part of display board according to counter2 and c3
						{
							while (c3 < 6)
							{
								print(input,counter3,r,c3);
								current_counter=counter3;//save the latest printed character
								current_column=c3;//save the latest printed column
								
								c3++;
								x++;
								
								if (x == 40)
									break;
							}
							
							c3 = 0;
							
							if (x == 40)
								break;
						}
						
						if (current_counter == quantity-1 and current_column == 5)//if the last column of last character has been printed out
						{
							while (x <= 39)
							{
								if (x == 1)
									choice = x;//save the x-value if text starts printing at x=1
								
								for (counter4 = 0; counter4 < input.size(); counter4++)//start the wrap effect as printing the first character out
								{
									c4 = 0;
									while (c4 < 6)
									{
										print(input,counter4,r,c4);
										
										c4++;
										x++;
										
										if (x == 40)
											break;
									}
									if (x == 40)
										break;
								}
							}
						}
					}
					else if (wrap == false)//enter if text does not exceed the left border or for the first time step
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else 
						{	
							for (counter = 0; counter < input.size(); counter++)
							{
								c = 0;
								while (c < 6)
								{
									print(input,counter,r,c);
									
									c++;
									x++;
									
									if (x == 40)
										break;
								}
								if (x == 40)
									break;
							}

							while (x<=39)
							{
								cout << " ";
								x++;
							}
						}
					}
					else if (wrap == true)//enter if a short text detected and need to start wrap effect
					{
						if (short_c == 6)//reset the column to be printed at left part to 0 for the next character
						{
							short_c = 0;
							counter2++;
						}
						
						c3 = short_c;
						
						for (counter3 = counter2;counter3 < input.size();counter3++)//start printing accroding to the value of counter2 at left part of display board
						{
							while (c3 < 6)
							{
								print(input,counter3,r,c3);
								
								c3++;
								x++;
							}
							c3 = 0;
						}

						while (x < reserve)//print out the empty column in between
						{
							cout << " ";
							x++;
						}
						
						for (counter4 = 0; counter4 < input.size(); counter4++)//print the wrap effect part at the right part of display board
						{
							c4 = 0;
							while (c4 < 6)
							{
								print(input,counter4,r,c4);
								
								c4++;
								x++;
								
								if (x == 40)
									break;
							}
							
							if (x == 40)
								break;
						}
						
						while (x != 40)
						{
							cout << " ";
							x++;
						}
					}
				}
				r++;
				choice_y--;
			}
			else
			{
				print_line();
			}
			cout << "=" << endl;
			y--;
		}
		cout << border << endl;
		ori_choice_x--;//decrement the original choice_x of user so that it appears moving to the left

		if (counter == quantity and c == 6 and wrap == false and ori_choice_x < 0)//if a short text being detected
		{
			wrap = true;//start the wrap effect
		}
		else if (reserve == 1)//the short text is all printed strating from x=1 when wrap effect is opened
		{
			wrap = false;//close the wrap effect
			ori_choice_x = 0;//reset the ori_choice_x to 0 as it has the same output as the next time step
			reserve=40;//reset the value of reserve,short_c and counter2
			short_c=0;
			counter2=0;
		}
		else if (ori_choice_x < 0 and wrap == false and counter != quantity and c != 6 )//if a long text being detected
		{
			ori_choice_x = 0;
			long_wrap = true;//start the wrap effect
		}
		
		delay();
	}
}

void delay()//function to define different speed
{
	if (speed == 1)
		i = 10000000;
	else if (speed == 2)
		i = 20000000;
	else if (speed == 3)
		i = 30000000;
	else if (speed == 4)
		i = 40000000;
	else if (speed == 5)
		i = 50000000;
	else if (speed == 6)
		i = 60000000;
	else if (speed == 7)
		i = 70000000;
	else if (speed == 8)
		i = 80000000;
	else if (speed == 9)
		i = 90000000;
	else if (speed == 10)
		i = 100000000;
	
	for (;i < 100000000;i++)//smaller value takes longer time to finish this process which means slower
	{	}
}

void print(string input,int counter,int r,int c)//function to be called to print one element only at one time
{
	//2d-array of 37 characters
	char space[7][6] = { {' ',' ',' ',' ',' ',' '},
						 {' ',' ',' ',' ',' ',' '},
						 {' ',' ',' ',' ',' ',' '},
						 {' ',' ',' ',' ',' ',' '},
						 {' ',' ',' ',' ',' ',' '},
						 {' ',' ',' ',' ',' ',' '},
						 {' ',' ',' ',' ',' ',' '} };

	char A[7][6] = { {' ',' ','#',' ',' ',' '}, 
					 {' ','#',' ','#',' ',' '}, 
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#','#','#','#','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '} };
			 
	char B[7][6] = { {'#','#','#','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#','#','#','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#','#','#','#',' ',' '} }; 
				   
	char C[7][6] = { {' ','#','#','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {' ','#','#','#',' ',' '} };
					 
	char D[7][6] = { {'#','#','#','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#','#','#','#',' ',' '} };
					 
	char E[7][6] = { {'#','#','#','#','#',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#','#','#','#',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#','#','#','#','#',' '} };
					 
	char F[7][6] = { {'#','#','#','#','#',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#','#','#','#',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '} };
					 
	char G[7][6] = { {' ','#','#','#','#',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ','#','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {' ','#','#','#','#',' '} };
					 
	char H[7][6] = { {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#','#','#','#','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '} };
					 
	char I[7][6] = { {' ','#','#','#',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ','#','#','#',' ',' '} };
					 
	char J[7][6] = { {'#','#','#','#','#',' '},
					 {' ',' ',' ',' ','#',' '},
					 {' ',' ',' ',' ','#',' '},
					 {' ',' ',' ',' ','#',' '},
					 {' ',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {' ','#','#','#',' ',' '} };
					 
	char K[7][6] = { {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ','#',' ',' '},
					 {'#',' ','#',' ',' ',' '},
					 {'#','#',' ',' ',' ',' '},
					 {'#',' ','#',' ',' ',' '},
					 {'#',' ',' ','#',' ',' '},
					 {'#',' ',' ',' ','#',' '} };
					 
	char L[7][6] = { {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#','#','#','#','#',' '} };
					 
	char M[7][6] = { {'#',' ',' ',' ','#',' '},
					 {'#','#',' ','#','#',' '},
					 {'#',' ','#',' ','#',' '},
					 {'#',' ','#',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '} };
					 
	char N[7][6] = { {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#','#',' ',' ','#',' '},
					 {'#',' ','#',' ','#',' '},
					 {'#',' ',' ','#','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '} };
					 
	char O[7][6] = { {' ','#','#','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {' ','#','#','#',' ',' '} };
					 
	char P[7][6] = { {'#','#','#','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#','#','#','#',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '} }; 

	char Q[7][6] = { {' ','#','#','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ','#',' ','#',' '},
					 {'#',' ',' ','#',' ',' '},
					 {' ','#','#',' ','#',' '} };
					 
	char R[7][6] = { {'#','#','#','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#','#','#','#',' ',' '},
					 {'#',' ','#',' ',' ',' '},
					 {'#',' ',' ','#',' ',' '},
					 {'#',' ',' ',' ','#',' '} };

	char S[7][6] = { {' ','#','#','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {' ','#','#','#',' ',' '},
					 {' ',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {' ','#','#','#',' ',' '} }; 

	char T[7][6] = { {'#','#','#','#','#',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '} };

	char U[7][6] = { {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {' ','#','#','#',' ',' '} };

	char V[7][6] = { {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {' ','#',' ','#',' ',' '},
					 {' ',' ','#',' ',' ',' '} };
					 
	char W[7][6] = { {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ','#',' ','#',' '},
					 {'#',' ','#',' ','#',' '},
					 {'#','#',' ','#','#',' '},
					 {'#',' ',' ',' ','#',' '} };

	char X[7][6] = { {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {' ','#',' ','#',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ','#',' ','#',' ',' '},
					 {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '} };

	char Y[7][6] = { {'#',' ',' ',' ','#',' '},
					 {'#',' ',' ',' ','#',' '},
					 {' ','#',' ','#',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ',' ','#',' ',' ',' '} };

	char Z[7][6] = { {'#','#','#','#','#',' '},
					 {' ',' ',' ',' ','#',' '},
					 {' ',' ',' ','#',' ',' '},
					 {' ',' ','#',' ',' ',' '},
					 {' ','#',' ',' ',' ',' '},
					 {'#',' ',' ',' ',' ',' '},
					 {'#','#','#','#','#',' '} };
					   
	char zero[7][6] = { {' ','#','#','#',' ',' '},
		                {'#',' ',' ',' ','#',' '},
				        {'#',' ',' ','#','#',' '},
				        {'#',' ','#',' ','#',' '},
				        {'#','#',' ',' ','#',' '},
				        {'#',' ',' ',' ','#',' '},
				        {' ','#','#','#',' ',' '} };

	char one[7][6] = { {' ',' ','#',' ',' ',' '},
					   {' ','#','#',' ',' ',' '},
					   {' ',' ','#',' ',' ',' '},
					   {' ',' ','#',' ',' ',' '},
					   {' ',' ','#',' ',' ',' '},
					   {' ',' ','#',' ',' ',' '},
					   {' ','#','#','#',' ',' '} };
					   
	char two[7][6] = { {' ','#','#','#',' ',' '},
					   {'#',' ',' ',' ','#',' '},
					   {' ',' ',' ',' ','#',' '},
					   {' ',' ','#','#',' ',' '},
					   {' ','#',' ',' ',' ',' '},
					   {'#',' ',' ',' ',' ',' '},
					   {'#','#','#','#','#',' '} };
					   
	char three[7][6] = { {'#','#','#','#','#',' '},
					     {' ',' ',' ',' ','#',' '},
					     {' ',' ',' ','#',' ',' '},
					     {' ',' ','#','#',' ',' '},
					     {' ',' ',' ',' ','#',' '},
					     {'#',' ',' ',' ','#',' '},
					     {' ','#','#','#',' ',' '} };

	char four[7][6] = { {' ',' ',' ','#',' ',' '},
					    {' ',' ','#','#',' ',' '},
					    {' ','#',' ','#',' ',' '},
					    {'#',' ',' ','#',' ',' '},
					    {'#','#','#','#','#',' '},
					    {' ',' ',' ','#',' ',' '},
					    {' ',' ',' ','#',' ',' '} };

	char five[7][6] = { {'#','#','#','#','#',' '},
					    {'#',' ',' ',' ',' ',' '},
					    {'#','#','#','#',' ',' '},
					    {' ',' ',' ',' ','#',' '},
					    {' ',' ',' ',' ','#',' '},
					    {'#',' ',' ',' ','#',' '},
					    {' ','#','#','#',' ',' '} };

	char six[7][6] = { {' ',' ','#','#',' ',' '},
					   {' ','#',' ',' ',' ',' '},
					   {'#',' ',' ',' ',' ',' '},
					   {'#','#','#','#',' ',' '},
					   {'#',' ',' ',' ','#',' '},
					   {'#',' ',' ',' ','#',' '},
					   {' ','#','#','#',' ',' '} };

	char seven[7][6] = { {'#','#','#','#','#',' '},
					     {' ',' ',' ',' ','#',' '},
					     {' ',' ',' ','#',' ',' '},
					     {' ',' ','#',' ',' ',' '},
					     {' ','#',' ',' ',' ',' '},
					     {' ','#',' ',' ',' ',' '},
					     {' ','#',' ',' ',' ',' '} };
						 
	char eight[7][6] = { {' ','#','#','#',' ',' '},
					     {'#',' ',' ',' ','#',' '},
					     {'#',' ',' ',' ','#',' '},
					     {' ','#','#','#',' ',' '},
					     {'#',' ',' ',' ','#',' '},
					     {'#',' ',' ',' ','#',' '},
					     {' ','#','#','#',' ',' '} };
						 
	char nine[7][6] = { {' ','#','#','#',' ',' '},
					    {'#',' ',' ',' ','#',' '},
					    {'#',' ',' ',' ','#',' '},
					    {' ','#','#','#','#',' '},
					    {' ',' ',' ',' ','#',' '},
					    {' ',' ',' ','#',' ',' '},
					    {' ','#','#',' ',' ',' '} };		
						 
	if (input[counter] == 'A' or input[counter] == 'a')
		cout << A[r][c];
	else if (input[counter] == 'B' or input[counter] == 'b')
		cout << B[r][c];
	else if (input[counter] == 'C' or input[counter] == 'c')
		cout << C[r][c];
	else if (input[counter] == 'D' or input[counter] == 'd')
		cout << D[r][c];
	else if (input[counter] == 'E' or input[counter] == 'e')
		cout << E[r][c];
	else if (input[counter] == 'F' or input[counter] == 'f')
		cout << F[r][c];
	else if (input[counter] == 'G' or input[counter] == 'g')
		cout << G[r][c];
	else if (input[counter] == 'H' or input[counter] == 'h')
		cout << H[r][c];
	else if (input[counter] == 'I' or input[counter] == 'i')
		cout << I[r][c];
	else if (input[counter] == 'J' or input[counter] == 'j')
		cout << J[r][c];
	else if (input[counter] == 'K' or input[counter] == 'k')
		cout << K[r][c];
	else if (input[counter] == 'L' or input[counter] == 'l')
		cout << L[r][c];
	else if (input[counter] == 'M' or input[counter] == 'm')
		cout << M[r][c];
	else if (input[counter] == 'N' or input[counter] == 'n')
		cout << N[r][c];
	else if (input[counter] == 'O' or input[counter] == 'o')
		cout << O[r][c];
	else if (input[counter] == 'P' or input[counter] == 'p')
		cout << P[r][c];
	else if (input[counter] == 'Q' or input[counter] == 'q')
		cout << Q[r][c];
	else if (input[counter] == 'R' or input[counter] == 'r')
		cout << R[r][c];
	else if (input[counter] == 'S' or input[counter] == 's')
		cout << S[r][c];
	else if (input[counter] == 'T' or input[counter] == 't')
		cout << T[r][c];
	else if (input[counter] == 'U' or input[counter] == 'u')
		cout << U[r][c];
	else if (input[counter] == 'V' or input[counter] == 'v')
		cout << V[r][c];
	else if (input[counter] == 'W' or input[counter] == 'w')
		cout << W[r][c];
	else if (input[counter] == 'X' or input[counter] == 'x')
		cout << X[r][c];
	else if (input[counter] == 'Y' or input[counter] == 'y')
		cout << Y[r][c];
	else if (input[counter] == 'Z' or input[counter] == 'z')
		cout << Z[r][c];
	else if (input[counter] == ' ')
		cout << space[r][c];
	else if (input[counter] == '1')
		cout << one[r][c];
	else if (input[counter] == '2')
		cout << two[r][c];
	else if (input[counter] == '3')
		cout << three[r][c];
	else if (input[counter] == '4')
		cout << four[r][c];
	else if (input[counter] == '5')
		cout << five[r][c];
	else if (input[counter] == '6')
		cout << six[r][c];
	else if (input[counter] == '7')
		cout << seven[r][c];
	else if (input[counter] == '8')
		cout << eight[r][c];
	else if (input[counter] == '9')
		cout << nine[r][c];
	else if (input[counter] == '0')
		cout << zero[r][c];
}