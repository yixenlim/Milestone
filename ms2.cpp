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
#include <cstdlib>
#include <cctype>
#include <fstream>
using namespace std;

//declaration of all variable names
string data1,data2,data3,data4,input_choice,drawing,input,rotation,direction,wrap_effect,filename,line = "====================================================================================";
int x,y,speed,board_x,board_y,choice_x,choice_y,ori_choice_x,ori_choice_y,time_step,c_limit,first_print_y,first_print_x,last_print_y,last_print_y2,last_print_x,
starting_counter,counter,counter2,counter3,counter4,starting_c,c,c2,c3,starting_r,r,r2,r3,reserve;
bool token,validation,wrap;
ifstream inFile;

//prototype of all functions
void clear();
void print_line();
void border();

//prototype for input validation functions
string skip_emptyRow(ifstream&,string);
bool is_digit(string);
string lower(string);
void check_optional(ifstream&,string&,string&,int&);

//prototype for display functions
void stationary();
void rot_stationary();
void up();
void rot_up();
void down();
void rot_down();
void left();
void rot_left();
void right();
void rot_right();
void delay();
void print(string,int,int,int);

int main () 
{
	clear();//clear screen function
	
	//loop to read inputs
	do
	{
		cout << "\nDo you have an input file? (y for yes and n for no)" << endl;
		cin >> input_choice;
		
		if (lower(input_choice) != "n" and lower(input_choice) != "y")//if user enter wrong input
		{
			cout << "\nPlease enter a valid choice!" << endl;
			token = false;//invalid choice entered
			cin.clear();
			cin.ignore(1000,'\n');
		}
		else
		{
			token = true;//valid choice entered
			if (lower(input_choice) == "y")//if user has a file to be displayed
			{
				cin.ignore(1000,'\n');
				do
				{
					cout << "\nEnter a filename: ";
					getline(cin,filename);
					inFile.open(filename.c_str());
					
					if (inFile.fail())//if file does not exist
					{
						token = false;
						validation = true;//default of input validation is true
						cout << "The filename is invalid" << endl;
						cin.clear();
					}
					else //if file found
					{
						token = true;
						validation = true;
						
						data1 = skip_emptyRow(inFile,data1);//skip empty rows if there are any and read the first input
						
						if (!is_digit(data1) or stoi(data1) < 1 or stoi(data1) > 10 or data1 == "\0")//if file contains nothing or the first data is not integer for speed or out of given range
						{
							cout << "Invalid input data: Invalid speed" << endl;
							validation = false;//invalid input detected
						}
						else
						{
							speed = stoi(data1);//convert the data into integer to store as speed
							
							inFile.ignore(1000,'\n');
							do //this loop skips empty rows to read input phrase
							{
								getline(inFile,input);
							} while (input == "\0" and !inFile.eof());
							
							if (input.size() > 25 or input == "\0")//if input phrase is larger than 25 characters or no data detected
							{
								cout << "Invalid input data: No input phrase or input phrase exceeds 25 characters" << endl;
								validation = false;
							}
							else if (input.size() <= 25)//if input phrase is valid
							{
								for (int i = 0;i < input.size();i++)//this loop checks if input phrase has any symbols
								{
									if (!(isalnum(input[i]) or input[i] == ' '))
									{
										validation = false;
										cout << "Invalid input data: Input phrase contains symbol" << endl;
										break;
									}
								}
								
								if (validation != false)//if speed and input phrase is valid
								{
									//read in the folowing two data
									data1 = skip_emptyRow(inFile,data1);
									data2 = skip_emptyRow(inFile,data2);
									
									if (!is_digit(data1) or !is_digit(data2) or data1 == "\0" or data2 == "\0")//if no integer or nothing detected for anchor point (required input data)
									{
										cout << "Invalid input data: Invalid anchor point or board size" << endl;
										validation = false;
									}
									else //if the two data are integers (possible for anchor point or board size)
									{
										data3 = skip_emptyRow(inFile,data3);
										
										if (lower(data3) == "lr" or lower(data3) == "rl" or lower(data3) == "ud" or lower(data3) == "du" or lower(data3) == "st")//if third data is direction
										{
											//default value of drawing character and board size
											drawing = '#';
											board_x = 40;
											board_y = 20;
											//the first and second data are anchor point
											ori_choice_x = stoi(data1);
											ori_choice_y = stoi(data2);
											//third data is store as direction
											direction = lower(data3);
											
											check_optional(inFile,rotation,wrap_effect,time_step);//call function to check the data validation of three optional input data
										}
										else if (data3 == "\0")//if nothing detected for direction (required input data)
										{
											cout << "Invalid input data: Invalid direction" << endl;
											validation = false;
										}
										else if (is_digit(data3))//if third data is integer
										{
											data4 = skip_emptyRow(inFile,data4);
											
											if (lower(data4) == "lr" or lower(data4) == "rl" or lower(data4) == "ud" or lower(data4) == "du" or lower(data4) == "st")//if forth data is direction
											{
												//check if third data is for drawing character
												if (data3.size() == 1 or lower(data3) == "inc")
												{
													if (lower(data3) == "inc")
														drawing = lower(data3);
													else
														drawing = data3;
													
													direction = lower(data4);
													board_x = 40;
													board_y = 20;
													ori_choice_x = stoi(data1);
													ori_choice_y = stoi(data2);
													
													check_optional(inFile,rotation,wrap_effect,time_step);
												}
												else
												{
													cout << "Invalid input data: Invalid drawing character" << endl;
													validation = false;
												}
											}
											else if (!is_digit(data4) or data4 == "\0")//if forth data is nothing and not direction and not integer
											{
												cout << "Invalid input data: Invalid board size, anchor point, drawing character or direction" << endl;
												validation = false;
											}
											else //if forth data is integer
											{
												board_x = stoi(data1);
												board_y = stoi(data2);
												ori_choice_x = stoi(data3);
												ori_choice_y = stoi(data4);
												
												data1 = skip_emptyRow(inFile,data1);
												
												//check if the data is direction or drawing character
												if (lower(data1) == "lr" or lower(data1) == "rl" or lower(data1) == "ud" or lower(data1) == "du" or lower(data1) == "st")
												{
													drawing = '#';
													direction = lower(data1);
													check_optional(inFile,rotation,wrap_effect,time_step);
												}
												else if (data1.size() == 1 or lower(data1) == "inc")
												{
													if (lower(data1) == "inc")
														drawing = lower(data3);
													else
														drawing = data1;
													
													inFile >> direction;
													
													if (lower(direction) == "lr" or lower(direction) == "rl" or lower(direction) == "ud" or lower(direction) == "du" or lower(direction) == "st")
													{
														direction = lower(direction);
														check_optional(inFile,rotation,wrap_effect,time_step);
													}
													else
													{
														cout << "Invalid input data: Invalid direction" << endl;
														validation = false;
													}
												}
												else
												{
													cout << "Invalid input data: Invalid direction or drawing character" << endl;
													validation = false;
												}
											}
										}
										else if (data3.size() == 1 or lower(data3) == "inc") //if third data is drawing character
										{
											if (lower(data3) == "inc")
												drawing = lower(data3);
											else
												drawing = data3;
												
											board_x = 40;
											board_y = 20;
											ori_choice_x = stoi(data1);
											ori_choice_y = stoi(data2);
											
											inFile >> direction;
											
											if (lower(direction) == "lr" or lower(direction) == "rl" or lower(direction) == "ud" or lower(direction) == "du" or lower(direction) == "st")
											{	
												direction = lower(direction);
												check_optional(inFile,rotation,wrap_effect,time_step);
												
											}
											else
											{
												cout << "Invalid input data: Invalid direction" << endl;
												validation = false;
											}
										}
										else
										{
											cout << "Invalid input data: Invalid drawing character or direction" << endl;
											validation = false;
										}
									}
								}
							}
						}
					}
				} while (token == false);
				
				if (validation == true)//if all input data is valid
				{
					if (board_x <= 0 or board_y <= 0)//check validation of board size
						cout << "Invalid input data: Invalid board size" << endl;
					else if (ori_choice_x >= board_x or ori_choice_y >= board_y)//check validation of anchor point
						cout << "Invalid input data: Anchor point out of board size" << endl;
					else if (time_step <= 0)//check validation of time step
						cout << "Invalid input data: Invalid time step" << endl;
					else //all input data is correct and display can be shown
					{
						//default settings for all functions
						wrap = false,first_print_y = -1,last_print_y = -1,last_print_x = -1,first_print_x = -1;
						
						//find the starting counter, starting row and starting column to start printing from according to x-coordinate and y-coordinate and rotation chosen
						if (rotation == "none")//if no rotation chosen
						{
							starting_r = 0;
							starting_c = 0;
							starting_counter = 0;
						}
						else if (rotation == "mr")//if mirror rotation chosen
						{
							starting_c = 0;
							starting_counter = 0;
							
							//find y-coordinate and starting row to start printing
							if (ori_choice_y < (board_y - 6))//if y-coordinate entered is enough to print all rows
							{
								starting_r = 6;//set the default value of starting row
								ori_choice_y = ori_choice_y + 6;
							}
							else //if y-coordinate entered is not enough to print all rows
							{
								starting_r = board_y - ori_choice_y - 1;//find the starting row
								ori_choice_y = board_y - 1;
							}
						}
						else if (rotation == "rot90")//if clockwise 90 degree rotation chosen
						{
							starting_c = 0;
							starting_counter = 0;
							
							//find the x-coordinate and starting column to start printing
							if (ori_choice_x > 5)//if x-coordinate entered by user is enough to print all columns of text
							{
								starting_r = 6;//set the default value of starting column
								ori_choice_x = ori_choice_x - 6;
							}
							else //if x-coordinate entered by user is not enough to print all columns of text
							{
								starting_r = ori_choice_x;//find the starting column
								ori_choice_x = 0;
							}
						}
						else if (rotation == "rot-90")//if anticlockwise 90 degree rotation chosen
						{
							starting_r = 0;
							
							//find the starting counter and y-coordinate to start printing based on anchor dot
							for (counter = 0; counter < input.size() and ori_choice_y < board_y; counter++)
							{
								if (counter < input.size() - 1)
									ori_choice_y = ori_choice_y + 6;
								else
									ori_choice_y = ori_choice_y + 4;
								
								starting_counter = counter;
							}
							
							//find the starting row
							if (ori_choice_y >= board_y)//if the first row of the starting character exceeds the upper border
							{
								if (starting_counter < input.size() - 1)
									starting_c = board_y - ori_choice_y + 5;
								else
									starting_c = board_y - ori_choice_y + 3;
								
								ori_choice_y = board_y-1;//start printing from first row of display board
							}
							else //if the top left corner of starting character is the first row of last character
								starting_c = 4;
						}
						
						//call display function
						if (direction == "st")
						{
							//call the stationary function
							if (rotation == "none" or rotation == "mr")
								stationary();
							else if (rotation == "rot90" or rotation == "rot-90")
								rot_stationary();
						}
						else if (direction == "du")
						{
							//call the up function
							if (rotation == "none" or rotation == "mr")
								up();
							else if (rotation == "rot90" or rotation == "rot-90")
								rot_up();
						}
						else if (direction == "ud")
						{
							//call the down function
							if (rotation == "none" or rotation == "mr")
								down();
							else if (rotation == "rot90" or rotation == "rot-90")
								rot_down();
						}
						else if (direction == "lr")
						{
							//call the right function
							if (rotation == "none" or rotation == "mr")
								right();
							else if (rotation == "rot90" or rotation == "rot-90")
								rot_right();
							
						}
						else if (direction == "rl")
						{
							//call the left function
							if (rotation == "none" or rotation == "mr")
								left();
							else if (rotation == "rot90" or rotation == "rot-90")
								rot_left();
						}
						
						token = false;
						inFile.close();
					}
				}
			}
		}
		
	} while(token == false);
	
	return 0;
}

void clear()//function to clear screen
{
	system("CLS");
}

void print_line()//function to print an entire empty row
{
	for (int counter_line = 0;counter_line < board_x;counter_line++)
	{
		cout << " ";
	}
}

void border()//funtion to print top and bottom border
{
	for (int counter_border = 0;counter_border < board_x+2;counter_border++)
	{
		cout << "=";
	}
}

bool is_digit(string alpha)//check whether the input is digit
{
	bool digit = true;
	
	for (int index = 0;index < alpha.size();index++)
	{
		if (!(isdigit(alpha[index])) and alpha[index] != ' ')//if symbol detected
		{
			digit = false;
			break;
		}
	}
	return digit;
}

string lower(string data)//change the data to lower case
{
	for (int i = 0;i < data.size();i++)
		data[i] = tolower(data[i]);
	
	return data;
}

string skip_emptyRow(ifstream& inFile,string data)//skips empty rows when reading input data file
{
	data.clear();
	while (data == "\0" and !inFile.eof())//this loop read input until found data or reach the end of the input data file
	{
		inFile >> data;
	}
	return data;
}

void check_optional(ifstream& inFile,string& rotation,string& wrap_effect,int& time_step)//function to verify the optional input data
{
	data1 = skip_emptyRow(inFile,data1);
	
	if (data1 == "\0")//if no more data is in the file
	{
		//default value of optional input data
		rotation = "none";
		wrap_effect = "nwr";
		time_step = 1;
	}
	else if (is_digit(data1))//if integer for time step detected
	{
		time_step = stoi(data1);
		data1 = skip_emptyRow(inFile,data1);
		
		//check if next data is wrap-around choice or rotation or nothing or invalid data
		if (lower(data1) == "wr")
		{
			wrap_effect = lower(data1);
			data1 = skip_emptyRow(inFile,data1);
			
			if (data1 == "\0")
				rotation = "none";
			else if (lower(data1) == "rot90" or lower(data1) == "rot-90" or lower(data1) == "mr")
				rotation = lower(data1);
			else
			{
				cout << "Invalid input data: Invalid rotation" << endl;
				validation = false;
			}
		}
		else if (lower(data1) == "rot90" or lower(data1) == "rot-90" or lower(data1) == "mr")
		{
			rotation = lower(data1);
			data1 = skip_emptyRow(inFile,data1);
			
			if (data1 == "\0")
				wrap_effect = "nwr";
			else if(lower(data1) == "wr")
				wrap_effect = lower(data1);
			else
			{
				cout << "Invalid input data: Invalid wrap-around choice" << endl;
				validation = false;
			}	
		}
		else if (data1 == "\0")
		{
			rotation = "none";
			wrap_effect = "nwr";
		}
		else
		{
			cout << "Invalid input data: Invalid rotation or wrap-around choice" << endl;
			validation = false;
		}
	}
	else if (lower(data1) == "wr")//if wrap-around choice detected
	{
		wrap_effect = lower(data1);
		data1 = skip_emptyRow(inFile,data1);
		
		//check if next data is time step or rotation or nothing or invalid data
		if (data1 == "\0")
		{
			rotation = "none";
			time_step = 1;
		}
		else if (is_digit(data1))
		{
			time_step = stoi(data1);
			data1 = skip_emptyRow(inFile,data1);
			
			if (data1 == "\0")
				rotation = "none";
			else if (lower(data1) == "rot90" or lower(data1) == "rot-90" or lower(data1) == "mr")
				rotation = lower(data1);
			else
			{
				cout << "Invalid input data: Invalid rotation" << endl;
				validation = false;
			}
		}
		else if (lower(data1) == "mr" or lower(data1) == "rot90" or lower(data1) == "rot-90")
		{
			rotation = lower(data1);
			data1 = skip_emptyRow(inFile,data1);
			
			if (data1 == "\0")
				time_step = 1;
			else if (is_digit(data1))
				time_step = stoi(data1);
			else
			{
				cout << "Invalid input data: Invalid time step" << endl;
				validation = false;
			}
		}
		else
		{
			cout << "Invalid input data: Invalid time step or rotation" << endl;
			validation = false;
		}
	}
	else if (lower(data1) == "rot90" or lower(data1) == "rot-90" or lower(data1) == "mr")//if rotation detected
	{
		rotation = lower(data1);
		data1 = skip_emptyRow(inFile,data1);
		
		//check if next data is wrap-around choice or wrap-around choice or nothing or invalid data
		if (data1 == "\0")
		{
			wrap_effect = "nwr";
			time_step = 1;
		}
		else if (lower(data1) == "wr")
		{
			wrap_effect = lower(data1);
			data1 = skip_emptyRow(inFile,data1);
			
			if (data1 == "\0")
				time_step = 1;
			else if (is_digit(data1))
				time_step = stoi(data1);
			else
			{
				cout << "Invalid input data: Invalid time step" << endl;
				validation = false;
			}
		}
		else if (is_digit(data1))
		{
			time_step = stoi(data1);
			data1 = skip_emptyRow(inFile,data1);
			
			if (data1 == "\0")
				wrap_effect = "nwr";
			else if (lower(data1) =="wr")
				wrap_effect = lower(data1);
			else
			{
				cout << "Invalid input data: Invalid wrap-around choice" << endl;
				validation = false;
			}
		}
		else
		{
			cout << "Invalid input data: Invalid time step or wrap-around choice" << endl;
			validation = false;
		}
	}
	else
	{
		cout << "Invalid input data: Invalid time step, rotation or wrap-around choice" << endl;
		validation = false;
	}
}

void stationary()//function to print normal and mirror rotation stationary text
{
	y = board_y - 1,choice_y = ori_choice_y,choice_x = ori_choice_x,r = starting_r;
	
	clear();
	border();//print the top border
	cout << endl;
	
	while (y >= 0)
	{
		cout << "=";//print the left border
		
		if (choice_y != y)//print empty row if the y-coordinate is not match
			print_line();
		else if ( r >= 0 and r <= 6 )//enter once the y-coordinate is found and rows of text have not been printed completely
		{
			x = 0;
			while (x < board_x)
			{
				if (choice_x != x)//print empty column if the x-coordinate is not match
				{
					cout << " ";
					x++;
				}
				else
				{
					c = starting_c;//c will be used in the loop to determine which column to print
					for (counter = starting_counter; counter < input.size() and x < board_x; counter++)//this loop print rows of every character
					{
						while (c < 6 and x < board_x)
						{
							print(input,counter,r,c);//call the print function to print every element
							c++;//increment to next column of text
							x++;//increment to next column of display board
						}
						c = 0;//set to start printing from first column for next character
					}
					
					//change the row of text to be printed at the next row according to rotation chosen
					if (rotation == "none")
						r++;
					else if (rotation == "mr")
						r--;
					
					while (x < board_x)//fill in empty column if there are any
					{
						cout << " ";
						x++;
					}
				}
			}
			choice_y--;//decrement user input of y-coordinate to match the entry condition
		}
		else
			print_line();//print empty row after 7 rows of character
	
		cout << "=" << endl;//print the right border
		y--;//move to the row below
	}
	border();//print the bottom border
	cout << endl;
}

void rot_stationary()//function to print clockwise and anticlockwise 90 degree rotation stationary text (note that in these two rotations, row is column and vice versa)
{
	y = board_y - 1,choice_y = ori_choice_y,choice_x = ori_choice_x,counter = starting_counter,c = starting_c;
	
	clear();
	border();
	cout << endl;
	
	while (y >= 0)
	{
		cout << "=";
		
		if (choice_y != y)
			print_line();
		else if (counter >= 0 and counter < input.size())//this prints each row of each character
		{
			x=0;
			while (x < board_x)
			{
				if (choice_x != x)
				{
					cout << " ";
					x++;
				}
				else
				{
					r = starting_r;//r will be use in the loop to determine which column to print
					while(r >= 0 and r <= 6 and x < board_x)
					{
						print(input,counter,r,c);
						x++;
						
						//find the next column of text to print
						if (rotation == "rot90")
							r--;
						else if (rotation == "rot-90")
							r++;
					}
					
					while (x < board_x)
					{
						cout << " ";
						x++;
					}
				}
			}
			choice_y--;
			
			//change the row of text to be printed at the next row according to rotation chosen
			if (rotation == "rot90")
				c++;
			else if (rotation == "rot-90")
				c--;
		}
		else 
			print_line();

		cout << "=" << endl;
		y--;
		
		if (rotation == "rot90")
		{
			//if the next printing row is row 6 (c = 6) which exceeds the printing row of a character,set row to first row of next character
			if (c > 5)
			{
				counter++;
				c = 0;
			}
		}
		else if (rotation == "rot-90")
		{
			//if the next printing row is row -1 (c = -1) which exceeds the printing row of a character,set row to last row of previous character
			if (c < 0)
			{
				counter--;
				c = 5;
			}
		}
	}
	border();
	cout << endl;
}

void up()//function to print normal and mirror rotation up-moving text
{
	
	for (int step = 0;step < time_step;step++)//loop according to time step
	{
		if (first_print_y == (board_y - 1))//if text printed at the first row of display board
		{
			wrap = true;//open wrap effect
			reserve = 0;//set the default value of reserve (use for print wrap text at the lower part of display board)
			first_print_y = -1;//reset default value
			r3 = starting_r;//r3 will be used to determine starting row of text to be printed at upper part of display board
		}
		
		y = board_y - 1,choice_x = ori_choice_x,choice_y = ori_choice_y;
		
		clear();//call function to clear screen
		border();
		cout << endl;
		
		if (wrap == false)//if wrap effect is not needed
		{
			first_print_y = choice_y;//save the first row of display board that printed text
			r = starting_r;
			
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if ( r >= 0 and r <= 6 )
				{
					last_print_y = y;//save the last row of display board that printed text
					x = 0;
					while (x < board_x)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							c = starting_c;//c will be used as starting column of first character
							for (counter = starting_counter; counter < input.size() and x < board_x; counter++)
							{	
								while (c < 6 and x < board_x)
								{
									print(input,counter,r,c);
									c++;
									x++;
								}
								c = 0;//set column to the first column for the next character
							}
							
							if (rotation == "none")
								r++;
							else if (rotation == "mr")
								r--;
							
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					choice_y--;
				}
				else
					print_line();
				cout << "=" << endl;
				y--;
			}
		}
		else if (wrap == true)//if wrap effect is needed
		{
			//change the starting row to print text at the upper part of display board and set the starting row to print text at the lower part of display board
			if (rotation == "none")
			{
				r3++;//upper part of display board
				r = 0;//lower part of display board
			}
			else if (rotation == "mr")
			{
				r3--;//upper part of display board
				r = 6;//lower part of display board
			}
			
			r2 = r3;//r2 will be used in loop
			
			if (last_print_y > 0)//if existing text at upper part of display board has suitable distance with the bottom border
				reserve++;//increment reserve to start printing the wrap text at the lower part of the display board
			
			while (y >= 0)
			{
				cout << "=";
				
				x = 0;
				while (x < board_x)
				{
					while (choice_x != x)
					{
						cout << " ";
						x++;
					}
					
					if (r2 >= 0 and r2 <= 6)//this existing print the text at upper part of display board
					{
						c = starting_c;
						for (counter = starting_counter; counter < input.size() and x < board_x; counter++)
						{	
							while (c < 6 and x < board_x)
							{
								print(input,counter,r2,c);
								last_print_y = y;//save the last printed row of existing text
								c++;
								x++;
							}
							c = 0;
						}
						
						if (rotation == "none")
							r2++;//2
						else if (rotation == "mr")
							r2--;
						
						while (x < board_x)
						{
							cout << " ";
							x++;
						}
					}
					else
					{
						if (y >= reserve or wrap_effect != "wr")//print empty rows in between or blank row
						{
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
						else
						{
							if (y == board_y - 2)//if the wrap text is printed at second row of the display board
							{
								wrap = false;//close wrap effect
								ori_choice_y = y;//set y-coordinate be increment later as it has the same output
								
								//set the starting row of text to start printing
								if (rotation == "none")
									starting_r = 0;
								else if (rotation == "mr")
									starting_r = 6;
							}
							
							c = starting_c;
							for (counter = starting_counter; counter < input.size() and x < board_x and r>=0 and r <= 6; counter++)//print the wrap text at the lower part of display board
							{	
								while (c < 6 and x < board_x)
								{
									print(input,counter,r,c);
									c++;
									x++;
								}
								c = 0;
							}
							
							if (rotation == "none")
								r++;
							else if (rotation == "mr")
								r--;
							
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
				}
				cout << "=" << endl;
				y--;
			}
		}
		border();
		cout << endl;
		ori_choice_y++;//increment the y-coordinate entered by user so that it appears moving upwards
		delay();//delay function to control the speed of refresh cycle
	}
}

void rot_up()//function to print clockwise and anticlockwise 90 degree rotation up-moving text (note that in these two rotations, row is column and vice versa)
{
	for (int step = 0;step < time_step;step++)
	{
		if (first_print_y == board_y - 1)//if text is printed at the first row which just below the top border
		{
			wrap = true;//open wrap effect
			reserve = 0;//set the default value of reserve
			first_print_y = -1;//reset default value
			
			//set the starting row and starting character of existing text to be printed at the upper part of the display board
			counter3 = starting_counter;
			c3 = starting_c;
		}
		
		y = board_y - 1,choice_x = ori_choice_x,choice_y = ori_choice_y,r = starting_r;;
		
		clear();
		border();
		cout << endl;

		if (wrap == false)
		{
			first_print_y = choice_y;//save the first row to print the text
			
			//set the starting character and starting row to print
			c = starting_c;
			counter = starting_counter;
			
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if (counter >= 0 and counter < input.size())
				{
					last_print_y = y;//save the last row that printed the text
					x = 0;
					while (x < board_x)
					{
						if (choice_x != x)//print empty column if the x-coordinate is not match
						{
							cout << " ";
							x++;
						}
						else
						{
							r = starting_r;
							while(r >= 0 and r <= 6 and x < board_x)
							{
								print(input,counter,r,c);
								x++;
								
								if (rotation == "rot90")
									r--;
								else if (rotation == "rot-90")
									r++;
							}
							
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					choice_y--;
					
					if (rotation == "rot90")
						c++;
					else if (rotation == "rot-90")
						c--;
				}
				else 
					print_line();
				
				cout << "=" << endl;
				y--;
				
				if (rotation == "rot90")
				{
					if (counter == input.size() - 1)
						c_limit = 4;
					else
						c_limit = 5;
					
					if (c > c_limit)
					{
						counter++;
						c = 0;
					}
				}
				else if (rotation == "rot-90")
				{
					if (c < 0)
					{
						counter--;
						c = 5;
					}
				}
			}
		}
		else if (wrap == true)
		{
			if (rotation == "rot90")
			{
				c3++;//increment the starting row to be printed at the upper part of the display board
				
				//set the starting row and starting character of text to be printed at the lower part of the display board
				c = 0;//first row
				counter = 0;//first character
				
				if (c3 > 5)
				{
					counter3++;
					c3 = 0;
				}
			}
			else if (rotation == "rot-90")
			{
				c3--;//decrement the starting row to be printed at the upper part of the display board
				
				//set the starting row and starting character of text to be printed at the lower part of the display board
				c = 4;//last column of last character
				counter = input.size() - 1;//last character
				
				if (c3 < 0)
				{
					counter3--;
					c3 = 5;
				}
			}
			
			if (last_print_y > 2 or last_print_y2 > 2)//when the last printed row has a suitable distance with the lower border for the wrap text to be printed
				reserve++;//increment the reserved row for wrap text
			
			//counter2 and c2 will be used in the loop
			counter2 = counter3;
			c2 = c3;
			
			while (y >= 0)
			{
				cout << "=";
				
				if (counter2 >= 0 and counter2 < input.size())//print the existing text at the upper part of the display board
				{
					last_print_y2 = 0;
					x = 0;
					while (x < board_x)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							r = starting_r;
							while(r >= 0 and r <= 6 and x < board_x)
							{
								print(input,counter2,r,c2);
								last_print_y = y;
								x++;
								
								if (rotation == "rot90")
									r--;
								else if (rotation == "rot-90")
									r++;
							}
							
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					if (rotation == "rot90")
						c2++;
					else if (rotation == "rot-90")
						c2--;
				}
				else 
				{
					if (y >= reserve or wrap_effect != "wr")//print empty rows in between
						print_line();
					else
					{
						x = 0;
						while (x < board_x)
						{
							if (choice_x != x)
							{
								cout << " ";
								x++;
							}
							else if (counter >= 0 and counter < input.size())//print the wrap text at the lower part of the display board
							{
								r = starting_r;
								while(r >= 0 and r <= 6 and x < board_x)
								{
									print(input,counter,r,c);
									last_print_y2 = y;//save the last printed row of wrapped text
									x++;
									
									if (rotation == "rot90")
										r--;
									else if (rotation == "rot-90")
										r++;
								}
								
								while (x < board_x)
								{
									cout << " ";
									x++;
								}
							}
							else //fill in empty column after the wrap text finish printing
							{
								while (x < board_x)
								{
									cout << " ";
									x++;
								}
							}
						}

						if (rotation == "rot90")
							c++;
						else if (rotation == "rot-90")
							c--;
					}
				}
				cout << "=" << endl;
				y--;
				
				if (rotation == "rot90")
				{
					if (counter2 == input.size() - 1)
						c_limit = 4;
					else
						c_limit = 5;
					
					//set the row to be printed to the first row of next character
					if (c2 > c_limit)//upper part of the display board
					{
						counter2++;
						c2 = 0;
					}
					
					if (c > c_limit)//lower part of the display board
					{
						counter++;
						c = 0;
					}
				}
				else if (rotation == "rot-90")
				{
					//set the row to be printed to the last row of previous character
					if (c2 < 0)//upper part of the display board
					{
						counter2--;
						c2 = 5;
					}
					
					if (c < 0)//lower part of the display board
					{
						counter--;
						c = 5;
					}
				}
			}
			
			if (reserve == board_y and wrap_effect == "wr")//if the wrap text is printed at the first row of display board,restart wrap process
			{
				//reset reserve and last_print_y
				reserve = 0;
				last_print_y = -1;
				
				//set the starting row and starting character to be changed later
				if (rotation == "rot90")
				{
					counter3 = 0;
					c3 = 0;
				}
				else if (rotation == "rot-90")
				{
					counter3 = input.size() - 1;
					c3 = 4;
				}
			}			
		}
		border();
		cout << endl;
		ori_choice_y++;
		delay();
	}
}

void down()//function to print normal and mirror rotation down-moving text
{
	for (int step = 0;step < time_step;step++)
	{
		if (last_print_y == 0)//if the text is printed at last row of display board
		{
			if (first_print_y < (board_y - 2) )//if the last printed row has a suitable distance with the top border
			{
				wrap = true;
				last_print_y = -1;
				reserve = first_print_y;//save the value as reserve that use to print existing text at the lower part of the display board
				
				//set the starting row to be changed later that use to print wrap text at the upper part of the display board
				if (rotation == "none")
					r3 = 7;
				else if (rotation == "mr")
					r3 = -1;
			}
		}
		
		y = board_y - 1,choice_x = ori_choice_x,choice_y = ori_choice_y;
		
		clear();
		border();
		cout << endl;
		
		if (wrap == false)
		{
			if (rotation == "none" or (rotation == "mr" and starting_r == 6))
				first_print_y = choice_y;//save the first row that printed text
			
			r = starting_r;
		
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if ( r >= 0 and r <= 6 )
				{
					if (rotation == "none" or (rotation == "mr" and starting_r == 6))
						last_print_y = y;//save the last row that printed text
					
					x = 0;
					
					while (x < board_x)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							c = starting_c;
							for (counter = starting_counter; (counter < input.size()) and x < board_x; counter++)
							{	
								while (c < 6 and x < board_x)
								{
									print(input,counter,r,c);
									c++;
									x++;
								}
								c = 0;
							}
							
							if (rotation == "none")
								r++;
							else if (rotation == "mr")
								r--;
							
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					choice_y--;
				}
				else
					print_line();
				cout << "=" << endl;
				y--;
			}
			
			if (rotation == "mr" and starting_r < 6)//if the starting row is not the first row or mirror text, enter to enable the saving to last printed row
			{
				ori_choice_y++;
				starting_r++;
			}
		}
		else if (wrap == true)
		{
			if (rotation == "none")
			{
				r3--;//change the starting row to be printed at the upper part of display baord
				r = 0;//starting row to print text at the lower part of display board
			}
			else if (rotation == "mr")
			{
				r3++;//change the starting row to be printed at the upper part of display baord
				r = 6;//starting row to print text at the lower part of display board
			}
			
			reserve--;//decrement the reserved row for printing existing text at the lower part of display board
			
			r2 = r3;//r2 will be used in the loop
			
			while (y >= 0)
			{
				cout << "=";
				x = 0;
				
				while (choice_x != x)
				{
					cout << " ";
					x++;
				}
				
				if (r2 >= 0 and r2 <= 6 and wrap_effect == "wr")//this loop print wrap text at the upper part of display board
				{
					c = starting_c;
					for (counter = starting_counter; counter < input.size() and x < board_x; counter++)
					{	
						while (c < 6 and x < board_x)
						{
							print(input,counter,r2,c);
							c++;
							x++;
							
							//check to close wrap effect if second row of wrap text has been printed out at the upper part of display board
							if ((rotation == "none" and r2 == 1) or (rotation == "mr" and r2 == 5))
							{
								wrap = false;
								ori_choice_y = board_y;//reset y-coordinate to be decrement later as it has the same output
								
								//reset the value of starting row
								if (rotation == "none")
									starting_r = 0;
								else if (rotation == "mr")
									starting_r = 6;
							}
						}
						c = 0;
					}
					
					if (rotation == "none")
						r2++;
					else if (rotation == "mr")
						r2--;
					
					while (x < board_x)
					{
						cout << " ";
						x++;
					}
				}
				else if (y > reserve)//print empty rows in between
				{
					while (x < board_x)
					{
						cout << " ";
						x++;
					}
				}
				else //print the existing text at the lower part of the display board
				{
					c = starting_c;
					for (counter = starting_counter; counter < input.size() and x < board_x; counter++)
					{	
						while (c < 6 and x < board_x)
						{
							print(input,counter,r,c);
							c++;
							x++;
						}
						c = 0;
					}
					
					if (rotation == "none")
						r++;
					else if (rotation == "mr")
						r--;
					
					while (x < board_x)
					{
						cout << " ";
						x++;
					}
				}
				cout << "=" << endl;
				y--;
			}
		}
		border();
		cout << endl;
		ori_choice_y--;//decrement y-coordinate that entered by user so that it appears moving downwards
		delay();
	}
}

void rot_down()//function to print clockwise and anticlockwise 90 degree rotation down-moving text (note that in these two rotations, row is column and vice versa)
{
	for (int step = 0;step < time_step;step++)
	{		
		if (last_print_y == 0)//when the text is printed at the last row
		{
			if (first_print_y < (board_y - 4))//if the text printed has a suitable distance with the top border
			{
				wrap = true;
				last_print_y = -1;
				reserve = first_print_y;//save the value of reserve
				
				//set the starting row and starting character for wrap text to be changed later
				if (rotation == "rot90")
				{
					counter3 = input.size() - 1;
					c3 = 5;
				}
				else if (rotation == "rot-90")
				{
					counter3 = 0;
					c3 = -1;
				}
			}
		}
		
		y = board_y - 1,choice_x = ori_choice_x,choice_y = ori_choice_y;
		
		clear();
		border();
		cout << endl;

		if (wrap == false)
		{
			first_print_y = choice_y;//save the first row that printed text
			
			//set the starting character to print
			c = starting_c;
			counter = starting_counter;
			
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if (counter >= 0 and counter < input.size())
				{
					x = 0;
					while (x < board_x)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							r = starting_r;
							while(r >= 0 and r <= 6 and x < board_x)
							{
								if (rotation == "rot90" or (rotation == "rot-90" and starting_counter == (input.size() - 1) and starting_c == 4))
									last_print_y = y;//save the last printed row if rotation is rot90 or if rotation is rot-90 and last row of last character has been printed out
								
								print(input,counter,r,c);
								x++;
								
								if (rotation == "rot90")
									r--;
								else if (rotation == "rot-90")
									r++;
							}
							
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					choice_y--;
					
					if (rotation == "rot90")
						c++;
					else if (rotation == "rot-90")
						c--;
				}
				else 
					print_line();
				
				cout << "=" << endl;
				y--;
				
				if (rotation == "rot90")
				{
					if (counter == input.size() - 1)
						c_limit = 4;
					else
						c_limit = 5;
					
					if (c > c_limit)
					{
						counter++;
						c=0;
					}
				}
				else if (rotation == "rot-90")
				{
					if (c < 0)
					{
						counter--;
						c=5;
					}
				}
			}
			
			if (rotation == "rot-90" and (starting_counter != (input.size() - 1) or starting_c != 4))//if the starting row of character is not the first row of last character
			{
				starting_c++;
				ori_choice_y++;
				
				if (starting_c > 5)//if the starting row exceeds the row that can be printed,set to the last row of next character
				{
					starting_c = 0;
					starting_counter++;
				}
			}
		}
		else if (wrap == true)
		{
			if (rotation == "rot90")
			{
				c3--;//change starting row of wrap text to be printed at the upper part of the display board
				
				//set the starting row and character of existing text to be printed at the lower part of the display board
				c = 0;
				counter = 0;
				
				if (c3 < 0)//move row to the last row of the previous character for wrap text
				{
					counter3--;
					c3 = 5;
				}
				
				if (counter3 == 0 and c3 == 1 and wrap_effect == "wr")//if the second row of the first character of wrap text is printed out at the upper part of the display board
				{
					wrap = false;//close wrap effect
					ori_choice_y = board_y;//set y-coordinate to be decrement later as it has the same output
				}
			}
			else if (rotation == "rot-90")
			{
				c3++;//change starting row of text to be printed at the upper part of the display board
				
				//set the starting row and character of existing text to be printed at the lower part of the display board
				c = 4;
				counter = input.size() - 1;
				
				if (c3 > 5)//move row to the first row of the next character for wrap text
				{
					counter3++;
					c3 = 0;
				}
				
				if (counter3 == input.size() - 1 and c3 == 3 and wrap_effect == "wr")//if the second row of the last character of wrap text is printed out at the upper part of the display board
				{
					wrap = false;//close wrap effect
					ori_choice_y = board_y;//set y-coordinate to be decrement later as it has the same output 
				}
			}
			
			//counter2 and c2 will be used in the loop
			c2 = c3;
			counter2 = counter3;
			
			reserve--;//decrement reserve rows to print the text at the lower part of the display board
			
			while (y >= 0)
			{
				cout << "=";
				
				if (counter2 >= 0 and counter2 < input.size() and wrap_effect == "wr")//print the wrap text at the upper part of the display board
				{
					x = 0;
					while (x < board_x)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							r = starting_r;
							while(r >= 0 and r <= 6 and x < board_x)
							{
								print(input,counter2,r,c2);
								x++;
								
								if (rotation == "rot90")
									r--;
								else if (rotation == "rot-90")
									r++;
							}
							
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					if (rotation == "rot90")
						c2++;
					else if (rotation == "rot-90")
						c2--;
				}
				else 
				{
					if (y > reserve)//print empty rows in between
						print_line();
					else //print the existing text at the lower part of the display board
					{
						x = 0;
						while (x < board_x)
						{
							if (choice_x != x)
							{
								cout << " ";
								x++;
							}
							else if (counter >=0 and counter < input.size())
							{
								r = starting_r;
								while(r >= 0 and r <= 6 and x < board_x)
								{
									print(input,counter,r,c);
									x++;
									
									if (rotation == "rot90")
										r--;
									else if (rotation == "rot-90")
										r++;
								}
								
								while (x < board_x)
								{
									cout << " ";
									x++;
								}
							}
							else
							{
								while (x < board_x)
								{
									cout << " ";
									x++;
								}
							}
						}

						if (rotation == "rot90")
							c++;
						else if (rotation == "rot-90")
							c--;
					}
				}
				cout << "=" << endl;
				y--;
				
				if (rotation == "rot90")
				{
					if (counter2 == input.size() - 1)
						c_limit = 4;
					else
						c_limit = 5;
					
					if (c2 > c_limit)
					{
						counter2++;
						c2 = 0;
					}
					
					if (c > 5)
					{
						counter++;
						c = 0;
					}
				}
				else if (rotation == "rot-90")
				{
					if (c2 < 0)
					{
						counter2--;
						c2 = 5;
					}
					
					if (c < 0)
					{
						counter--;
						c = 5;
					}
				}
			}
		}
		border();
		cout << endl;
		ori_choice_y--;
		delay();
	}
}

void right()//function to print normal and mirror rotation right-moving text
{
	for (int step = 0;step < time_step;step++)
	{
		if (last_print_x == (board_x - 1))//if the text is printed at the last column in display board
		{
			if (first_print_x > 3)//if the text has a suitable distance with the left border
			{
				last_print_x = -1;//reset last_print_x
				counter2 = input.size() - 1;//set starting character to the last character
				c2 = 5;//set starting column to be decrement later
				wrap = true;//open wrap effect
				reserve = first_print_x;//save the value of reserve to print existing text at the right part of display board
			}
		}

		y = board_y - 1,choice_x = ori_choice_x,choice_y = ori_choice_y,r = starting_r;
		
		clear();
		border();
		cout << endl;
		
		if (wrap == false)
		{
			if (rotation == "none" or (rotation == "mr" and starting_c == 0))
				first_print_x = choice_x;//save the first printed column of display board
		
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if ( r >= 0 and r <= 6 )
				{
					x = 0;
					while (x < board_x)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else 
						{	
							c = starting_c;
							for (counter = starting_counter;counter < input.size() and x < board_x; counter++)
							{
								if (counter == input.size() - 1)
									c_limit = 5;
								else
									c_limit = 6;
								
								while (c < c_limit and x < board_x)
								{
									if (rotation == "none" or (rotation == "mr" and starting_c == 0))
										last_print_x = x;//save the last printed column of display board
									
									print(input,counter,r,c);
									c++;
									x++;
								}
								c = 0;
							}

							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					choice_y--;
					
					if (rotation == "none")
						r++;
					else if (rotation == "mr")
						r--;
				}
				else 
				{
					print_line();
				}
				cout << "=" << endl;
				y--;
			}
			
			if (rotation == "mr" and starting_c > 0)//if the starting column is not 0 yet (means the text is not printed from the very beginning)
			{
				starting_c--;//change the starting column to previous column 
				ori_choice_x--;
			}
		}
		else if (wrap == true)
		{
			c2--;//derement the starting column to be printed
			
			if (c2 < 0)//set the starting column to the last column of previous character
			{
				c2 = 5;
				counter2--;
			}
			
			reserve++;//increment reserve to determine the column to print the wrap text at the right part of display board 
			
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if ( r >= 0 and r <= 6 )
				{
					c = c2;
					x = 0;
					while (x < board_x)
					{
						for (counter = counter2;counter < input.size() and x < board_x and wrap_effect == "wr"; counter++)//this print the wrap text at the left part of the display board
						{
							if (counter == input.size() - 1)
								c_limit = 5;
							else
								c_limit = 6;
							
							while (c < c_limit and x < board_x)
							{
								if (counter == 0 and c == 1)//if second column of first character is wrapped at the left part of display board
								{
									wrap = false;//close the wrap effect
									ori_choice_x = -1;//reset x-coordinate to be increment later as it has the same output
									starting_c = 0;//reset the starting column
								}
								
								print(input,counter,r,c);
								c++;
								x++;
							}
							c = 0;
						}
						
						while (x < reserve and x < board_x)//print empty column after wrap text at left part of display board if there is any
						{
							cout << " ";
							x++;
						}
						
						for (counter = starting_counter;counter < input.size() and x < board_x; counter++)//this loop printing existing text at the right part of display board
						{
							c = 0;
							while (c < 6 and x < board_x)
							{
								print(input,counter,r,c);
								c++;
								x++;
							}
						}
					}
					choice_y--;
					
					if (rotation == "none")
						r++;
					else if (rotation == "mr")
						r--;
				}
				else 
					print_line();
				
				cout << "=" << endl;
				y--;
			}
		}
		border();
		cout << endl;
		ori_choice_x++;//increment the x-coordinate entered by user so that it appears moving to the right
		delay();
	}
}

void rot_right()//function to print clockwise and anticlockwise 90 degree rotation right-moving text (note that in these two rotations, row is column and vice versa)
{
	for (int step = 0;step < time_step;step++)
	{
		if (last_print_x == (board_x - 1))//if the text is printed at the last column of the display board
		{
			if (first_print_x > 0)//if the first column of the text has a suitable distance with the left border
			{
				//set the starting column to be changed later that use to print wrap text at the left part of display baord
				if (rotation == "rot90")
					r3 = -1;
				else if (rotation == "rot-90")
					r3 = 7;
				
				last_print_x = -1;//reset last_print_x
				wrap = true;//open wrap effect
				reserve = first_print_x;//set the value of reserve
			}
		}
		
		y = board_y - 1,choice_y = ori_choice_y,choice_x = ori_choice_x,c = starting_c,counter = starting_counter;
		
		clear();
		border();
		cout << endl;
		
		if (wrap == false)
		{
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if ( counter >= 0 and counter < input.size() )
				{
					x = 0;
					while (x < board_x)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							first_print_x = x; 
							r = starting_r;
							while(r >= 0 and r <= 6 and x < board_x)
							{
								if ((rotation == "rot90" and starting_r == 6) or rotation == "rot-90")
									last_print_x = x;
								
								print(input,counter,r,c);
								x++;
								
								if (rotation == "rot90")
									r--;
								else if (rotation == "rot-90")
									r++;
							}
							
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					choice_y--;
					
					if (rotation == "rot90")
						c++;
					else if (rotation == "rot-90")
						c--;
				}
				else 
					print_line();
				
				cout << "=" << endl;
				y--;
				
				if (rotation == "rot90")
				{
					if (c > 5)
					{
						counter++;
						c=0;
					}
				}
				else if (rotation == "rot-90")
				{
					if (c < 0)
					{
						counter--;
						c=5;
					}
				}
			}
			
			if (rotation == "rot90" and starting_r < 6)//if the starting column is not the first column of text, enter to enable the saving of last printed column
			{
				starting_r++;
				ori_choice_x--;
			}
			
		}
		else if (wrap == true)
		{
			//change the starting column to be printed at the left part of the display board
			if (rotation == "rot90")
				r3++;
			else if (rotation == "rot-90")
				r3--;
			
			reserve++;//increment the first column to print the existing text
			
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if (counter >= 0 and counter < input.size())
				{
					x = 0;
					while (x < board_x)
					{
						r2 = r3;
						while(r2 >= 0 and r2 <= 6 and x < board_x and wrap_effect == "wr")//this loop print text at the left part of the display board
						{
							print(input,counter,r2,c);
							x++;
							
							if ((rotation == "rot90" and r3 > 4) or (rotation == "rot-90" and r3 < 2))//if the the second column of wrap text is printed out at left part of display board
							{
								wrap = false;//close wrap effect
								ori_choice_x = -1;//set the x-coordinate to be increment later as it has the same output
							}
							
							if (rotation == "rot90")
								r2--;
							else if (rotation == "rot-90")
								r2++;
						}
						
						while (x < reserve and x < board_x)//this loop print the empty columns in between according to the value of reserve
						{
							cout << " ";
							x++;
						}
						
						r = starting_r;
						while(r >= 0 and r <= 6 and x < board_x)//this loop print the existing text at the right part of the display board
						{
							print(input,counter,r,c);
							x++;
							
							if (rotation == "rot90")
								r--;
							else if (rotation == "rot-90")
								r++;
						}
					}
					choice_y--;
					
					if (rotation == "rot90")
						c++;
					else if (rotation == "rot-90")
						c--;
				}
				else //fill the display board with empty rows if all text has been printed out
					print_line();

				cout << "=" << endl;
				y--;
				
				if (rotation == "rot90")
				{
					if (c > 5)
					{
						counter++;
						c=0;
					}
				}
				else if (rotation == "rot-90")
				{
					if (c < 0)
					{
						counter--;
						c=5;
					}
				}
			}
		}
		border();
		cout << endl;
		ori_choice_x++;
		delay();
	}
}

void left()//function to print normal and mirror rotation left-moving text
{
	for (int step = 0;step < time_step;step++)
	{
		if (first_print_x == 0)//if text id pritned at the first column of display board
		{
			first_print_x = -1;//reset first_print_x
			wrap = true;//open wrap effect
			c2 = starting_c;//set starting column to start printing text at the left part of display board to be increment later
			counter2 = 0;//set starting character to start printing at the left part of display board
			reserve = board_x;//set the value of reserve
		}
		
		y = board_y - 1,choice_x = ori_choice_x,choice_y = ori_choice_y,r = starting_r;
		
		clear();
		border();
		cout << endl;
		
		if (wrap == false)
		{
			first_print_x = choice_x;
		
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if ( r >= 0 and r <= 6 )
				{
					x = 0;
					while (x < board_x)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else 
						{
							c = starting_c;
							for (counter = starting_counter;counter < input.size() and x < board_x; counter++)
							{
								if (counter == input.size() - 1)
									c_limit = 5;
								else
									c_limit = 6;
								
								while (c < c_limit and x < board_x)
								{
									print(input,counter,r,c);
									last_print_x = x;//save the last printed column
									c++;
									x++;
								}
								c = 0;
							}

							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					choice_y--;
					
					if (rotation == "none")
						r++;
					else if (rotation == "mr")
						r--;
				}
				else 
					print_line();
				
				cout << "=" << endl;
				y--;
			}
		}
		else if (wrap == true)
		{
			c2++;//increment the starting column to be printed at the right part of display board
			
			if (c2 > 5)//move the starting column to the first column of the next character
			{
				c2 = 0;
				counter2++;
			}
			
			if (last_print_x < (board_x - 4) and wrap_effect == "wr")//if the text has suitable distance with the right border
				reserve--;//decrement the column to wrap text if allowed
			
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if ( r >= 0 and r <= 6 )
				{
					c = c2;
					x = 0;
					while (x < board_x)
					{
						for (counter = counter2;counter < input.size() and x < board_x; counter++)//this loop print the existing text at left part of display board
						{
							if (counter == input.size() - 1)
								c_limit = 5;
							else
								c_limit = 6;
							
							while (c < c_limit and x < board_x)
							{
								print(input,counter,r,c);
								last_print_x = x;
								c++;
								x++;
							}
							c=0;
						}
						
						while (x < reserve and x < board_x)//this loop print empty column in between
						{
							cout << " ";
							x++;
						}
						
						for (counter = starting_counter;counter < input.size() and x < board_x; counter++)//this loop print the wrap text at the right part of display board
						{
							if (x == 1)//enter if the wrap text starts at second column of display board
							{
								wrap = false;//close the wrap effect
								ori_choice_x = 1;//set x-coordinate to be decrement later as it has the same output
								starting_c = 0;//set the starting column
							}
							
							c = 0;
							while (c < 6 and x < board_x)
							{
								print(input,counter,r,c);
								c++;
								x++;
							}
						}
						
						while (x < board_x)//this loop print empty column if there are space after wrap text finish printing 
						{
							cout << " ";
							x++;
						}
					}
					choice_y--;
					
					if (rotation == "none")
						r++;
					else if (rotation == "mr")
						r--;
				}
				else 
					print_line();
				
				cout << "=" << endl;
				y--;
			}
		}
		border();
		cout << endl;
		ori_choice_x--;//decrement the x-coordinate entered by user so that it appears moving to the left
		delay();
	}
}

void rot_left()//function to print clockwise and anticlockwise 90 degree rotation left-moving text (note that in these two rotations, row is column and vice versa)
{
	for (int step = 0;step < time_step;step++)
	{
		if (first_print_x == 0)//if any column of the text is printed at the first column of the display board
		{
			r3 = starting_r;
			wrap = true;//open wrap effect
			first_print_x = 1;//reset last_print_x
			reserve = board_x;//set default value of reserve
		}
		
		y = board_y - 1,choice_y = ori_choice_y,choice_x = ori_choice_x,c = starting_c,counter = starting_counter;
		
		clear();
		border();
		cout << endl;
		
		if (wrap == false)
		{
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if (counter >= 0 and counter < input.size())
				{
					x = 0;
					while (x < board_x)
					{
						if (choice_x != x)
						{
							cout << " ";
							x++;
						}
						else
						{
							first_print_x = x;
							r = starting_r;
							while(r >= 0 and r <= 6 and x < board_x)
							{
								print(input,counter,r,c);
								last_print_x = x;
								x++;
								
								if (rotation == "rot90")
									r--;
								else if (rotation == "rot-90")
									r++;
							}
							
							while (x < board_x)
							{
								cout << " ";
								x++;
							}
						}
					}
					choice_y--;
					
					if (rotation == "rot90")
						c++;
					else if (rotation == "rot-90")
						c--;
				}
				else 
				{
					print_line();
				}
				cout << "=" << endl;
				y--;
				
				if (rotation == "rot90")
				{
					if (c > 5)
					{
						counter++;
						c=0;
					}
				}
				else if (rotation == "rot-90")
				{
					if (c < 0)
					{
						counter--;
						c=5;
					}
				}
			}
			
		}
		else if (wrap == true)
		{
			//change the starting column to be printed at the left part of the display board
			if (rotation == "rot90")
				r3--;
			else if (rotation == "rot-90")
				r3++;
			
			if (last_print_x < (board_x - 1) and wrap_effect == "wr")//if the last column of the existing text is too close to the right border
				reserve--;//change the starting column to print text at the right part of the display board
			
			while (y >= 0)
			{
				cout << "=";
				
				if (choice_y != y)
					print_line();
				else if (counter >= 0 and counter < input.size())
				{
					x = 0;
					while (x < board_x)
					{
						r2 = r3;//r2 will be used in the loop
						
						//this loop print existing text at the left part of the display board
						while(r2 >= 0 and r2 <= 6 and x < board_x)
						{
							print(input,counter,r2,c);
							last_print_x = x;
							x++;
							
							if (rotation == "rot90")
								r2--;
							else if (rotation == "rot-90")
								r2++;
						}
						
						//this loop print the empty columns in between or when last column of existing text at the left part of display board is too close to the right border
						while (x < reserve and x < board_x)
						{
							cout << " ";
							x++;
						}

						if (rotation == "rot90")
							r=6;
						else if (rotation == "rot-90")
							r=0;
						
						//this loop print the wrap text at the right part of the display board
						while(r >= 0 and r <= 6 and x < board_x)
						{
							if (x == 0)//if the wrap text is printed at the first column, restart wrap process
							{
								//prepare the starting column of the text to decrement later
								if (rotation == "rot90")
									r3 = 6;
								else if (rotation == "rot-90")
									r3 = 0;
								
								reserve = board_x;//reset reserve
							}
						
							print(input,counter,r,c);
							x++;

							if (rotation == "rot90")
								r--;
							else if (rotation == "rot-90")
								r++;
						}
						
						//this loop print empty column after wrapped text if there are any
						while (x < board_x)
						{
							cout << " ";
							x++;
						}
					}
					choice_y--;
					
					if (rotation == "rot90")
						c++;
					else if (rotation == "rot-90")
						c--;
				}
				else //fill the display board with empty rows if all text has been printed out
					print_line();
				
				cout << "=" << endl;
				y--;
				
				if (rotation == "rot90")
				{
					if (c > 5)
					{
						counter++;
						c=0;
					}
				}
				else if (rotation == "rot-90")
				{
					if (c < 0)
					{
						counter--;
						c=5;
					}
				}
			}
		}
		border();
		cout << endl;
		ori_choice_x--;
		delay();
	}
}

void delay()//function to define different speed
{
	int i;
	i = speed * 10000000;
	
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
						 
	if (input[counter] == 'A' or input[counter] == 'a')//if the current character is found
	{
		if (A[r][c] == ' ')//print empty column according to the map of 2d array
			cout << A[r][c];
		else if (drawing != "inc")//print drawing character if inception is not wanted
			cout << drawing;
		else //print the character of its own if inception is wanted
			cout << input[counter];
	}
	else if (input[counter] == 'B' or input[counter] == 'b')
	{
		if (B[r][c] == ' ')
			cout << B[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'C' or input[counter] == 'c')
	{
		if (C[r][c] == ' ')
			cout << C[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'D' or input[counter] == 'd')
	{
		if (D[r][c] == ' ')
			cout << D[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'E' or input[counter] == 'e')
	{
		if (E[r][c] == ' ')
			cout << E[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'F' or input[counter] == 'f')
	{
		if (F[r][c] == ' ')
			cout << F[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'G' or input[counter] == 'g')
	{
		if (G[r][c] == ' ')
			cout << G[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'H' or input[counter] == 'h')
	{
		if (H[r][c] == ' ')
			cout << H[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'I' or input[counter] == 'i')
	{
		if (I[r][c] == ' ')
			cout << I[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'J' or input[counter] == 'j')
	{
		if (J[r][c] == ' ')
			cout << J[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'K' or input[counter] == 'k')
	{
		if (K[r][c] == ' ')
			cout << K[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'L' or input[counter] == 'l')
	{
		if (L[r][c] == ' ')
			cout << L[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'M' or input[counter] == 'm')
	{
		if (M[r][c] == ' ')
			cout << M[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'N' or input[counter] == 'n')
	{
		if (N[r][c] == ' ')
			cout << N[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'O' or input[counter] == 'o')
	{
		if (O[r][c] == ' ')
			cout << O[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'P' or input[counter] == 'p')
	{
		if (P[r][c] == ' ')
			cout << P[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'Q' or input[counter] == 'q')
	{
		if (Q[r][c] == ' ')
			cout << Q[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'R' or input[counter] == 'r')
	{
		if (R[r][c] == ' ')
			cout << R[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'S' or input[counter] == 's')
	{
		if (S[r][c] == ' ')
			cout << S[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'T' or input[counter] == 't')
	{
		if (T[r][c] == ' ')
			cout << T[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'U' or input[counter] == 'u')
	{
		if (U[r][c] == ' ')
			cout << U[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'V' or input[counter] == 'v')
	{
		if (V[r][c] == ' ')
			cout << V[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'W' or input[counter] == 'w')
	{
		if (W[r][c] == ' ')
			cout << W[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'X' or input[counter] == 'x')
	{
		if (X[r][c] == ' ')
			cout << X[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'Y' or input[counter] == 'y')
	{
		if (Y[r][c] == ' ')
			cout << Y[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == 'Z' or input[counter] == 'z')
	{
		if (Z[r][c] == ' ')
			cout << Z[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == ' ')
	{
		cout << space[r][c];
	}
	else if (input[counter] == '1')
	{
		if (one[r][c] == ' ')
			cout << one[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == '2')
	{
		if (two[r][c] == ' ')
			cout << two[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == '3')
	{
		if (three[r][c] == ' ')
			cout << three[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == '4')
	{
		if (four[r][c] == ' ')
			cout << four[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == '5')
	{
		if (five[r][c] == ' ')
			cout << five[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == '6')
	{
		if (six[r][c] == ' ')
			cout << six[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == '7')
	{
		if (seven[r][c] == ' ')
			cout << seven[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == '8')
	{
		if (eight[r][c] == ' ')
			cout << eight[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == '9')
	{
		if (nine[r][c] == ' ')
			cout << nine[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
	else if (input[counter] == '0')
	{
		if (zero[r][c] == ' ')
			cout << zero[r][c];
		else if (drawing != "inc")
			cout << drawing;
		else
			cout << input[counter];
	}
}