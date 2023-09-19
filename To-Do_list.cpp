#include<iomanip>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
void displayMenu();
class task
{
	public:
		static int taskId;
		string taskName;
		string completed = "Not Completed";
		string dueDate;
		char priority;
		task(string tName, string tDueDate, char tpriority, int taskId);
		void markAsCompleted();
		void displayTask();
		int displayTaskId();	
		task();
};
int task::taskId = 0;
void storeTasksFromFile(vector <task> &v, int &maxId);
void displayVec(vector<task> &v);
int stringToStr(string &str);
void updateFile(vector<task> &vec);
int main()
{
	ofstream output("task.txt" , ios::app);
	ifstream input("task.txt");
	cout<<"Welcome To Your Own To-Do List.\nManage Your Tasks Effectively\n";	
	int menuChoice, maxId;
	vector<task> toDoList;
	toDoList.clear();
	storeTasksFromFile(toDoList, maxId = 0);
	char choice;
	do 
	{
		displayMenu();
		int taskId = ++maxId;
		std::cin>>menuChoice;
		switch(menuChoice)
		{
			case 1:
			{
				string tName, tDueDate;
				char tPriority;
				cout<<"Enter Task Name: ";
				std::cin.ignore();
				getline(std::cin,tName);
				cout<<"Enter Due Date: ";
				getline(std::cin,tDueDate);
				cout<<"Set Priority For the Task 'H' for high, 'M' for Medium and 'L' for Low: ";
				std::cin>>tPriority;
				tPriority = tolower(tPriority);
				std::cin.ignore();
				task newTask(tName, tDueDate, tPriority,taskId);
				toDoList.push_back(newTask);
				if(output.is_open())
				{
					output << newTask.taskId << "," << newTask.taskName << "," << newTask.dueDate  << "," << newTask.completed << "," << newTask.priority << endl;
					cout<<"Task Has Been Saved With Id: "<<newTask.displayTaskId()<<endl;
					output.close();
				}
				if(output.fail())
				{
					cout<<"Your Task was not able to be saved in the file. Please try again by running the program again\n";
				}
				break;
			}
			case 2:
			{
				cout<<"\tTasks in the List\n";
				displayVec(toDoList);
				break;
			}
			case 3:
			{
				int mark;
				bool isfound = false;
				displayVec(toDoList);
				cout<<"Enter a Task by its Id To Mark it as Completed\n";
				std::cin>>mark;
				for(task &task1 : toDoList)
				{
					if(task1.taskId == mark)
					{
						task1.markAsCompleted();
						updateFile(toDoList);
						isfound = true ;
						cout << "Task has been successfully marked as completed\n";
						break;
					}
					if (!isfound)
					{
						cout<<"Task with Id "<< mark << " not found\n";
					}
				}
				break;
			}
			case 4:
				{
					int choice; 
					cout<<"1. Search by Priority\t2. Search by Task ID\n";
					std::cin>>choice;
					switch (choice)
					{
					case 1:
						{
							char pchoice;
							cout<<"Press Follwing to continue:\n1. 'H' for high\t\t2.'M' for Medium\t3.'L' For low\n";
							std::cin>>pchoice;
							bool found = false; 
							pchoice = tolower(pchoice);
					 		cout << "Tasks with priority " << pchoice << ":" << endl;
							if(toDoList.empty())
							{
								cout<<"No Tasks To Display\n";
							}
							else 
							{
								for(task &task1 : toDoList )
								{
									if(task1.priority == pchoice)
									{
										task1.displayTask();
										found = true;
									}
														
								}
								if(!found)
								{
									cout<<"Task not found\n";
								}
							}
							break;
						}				
					case 2:
					{
						int searchId;
						cout<<"Enter an Id to continue\n";
						std::cin>>searchId;
						bool found = false;
						if(toDoList.empty())
						{
							cout<<"No Tasks To Display\n";
						}
						else 
						{	
							for (task &task1 : toDoList)
							{
								cout << "Task ID in vector: " << task1.taskId << ", Search ID: " << searchId << endl; 
								if(task1.taskId == searchId)
								{
									task1.displayTask();
									found = true;
									break;
								}
							}
							if(!found)
							{
								cout<<"Task not found\n";
							}
						}	
						break;
					}	
						default:
							cout<<"Invalid Choice \n";
							break;
					}
					break;
				}
			case 5:
				choice = 'n';
				break;
			default:
				cout<<"\nWarning: Invalid Choice\n\n";
				break;
		}
			cout<<"Do You Want to Continue(y/n)\n";
			std::cin>>choice;
			tolower(choice);
	}while(choice == 'y');
	return 0;
}
void task::markAsCompleted()
{
	completed = "Completed";
}
void task::displayTask()
{
    cout << left << setw(10) << taskId;
    cout << setw(30) << taskName;
    cout << setw(25) << dueDate;
    cout << setw(20) << priority;
    cout << setw(25) << completed << endl;
}
task::task(string tName, string tDueDate, char tpriority, int taskId)
{
	taskName = tName;
	dueDate = tDueDate;
	priority = tpriority;
	taskId = taskId;
}
task::task()
{ 
	taskName = "";
	dueDate = "" ; 
	priority = ' '; 
	// this-> taskId = taskId;
	completed = "Not Completed";
}
void displayMenu()
{
	cout<<"Menu:\n";
	cout<<"1. Add New Task\t\t\t2. Display Tasks\n3. Mark A Task As Completed\t4. Search Tasks\n5. Exit"<<endl;
	cout<<"Select One To Continue: ";
}
int task::displayTaskId(){
	return taskId;
}
void displayVec(vector<task> &vec)
{
    ifstream input("task.txt");

    if (input.is_open())
    {
        vec.clear();
        string line;
     	cout << left << setw(10) << "Task ID" << setw(30) << "Name" << setw(25) << "Due Date" << setw(20) << "Priority" << setw(25) << "State" << endl;
    	cout << setfill('-') << setw(110) << "" << setfill(' ') << endl;
        while (getline(input, line))
        {
            istringstream iss(line);
            string taskIdStr, taskName, dueDate, completed, priority;

            if (getline(iss, taskIdStr, ',') && getline(iss, taskName, ',') &&
                getline(iss, dueDate, ',') && getline(iss, completed, ',') &&
                getline(iss, priority, ','))
            {
                int num = stringToStr(taskIdStr);
                task newTask(taskName, dueDate, priority[0], num);
                vec.push_back(newTask);
                newTask.displayTask();
			}
        }
        input.close();
        if (vec.empty())
        {
            cout << "\nNo Tasks in the List To Display\n\n";
        }
    }
}
int stringToStr(string &str)
{
	int result = 0;
	istringstream iss(str);
	iss >> result;
	return result;
}
void updateFile(vector <task> &vec)
{
	ofstream output("task.txt" , ios::trunc);
	if (output.is_open())
	{
		for(task& task1 : vec)
		{
			output<<task1.taskId<<","<<task1.taskName<<","<<task1.dueDate<<","<<task1.completed<<","<<task1.priority<<"\n";
		}
		output.close();
	}
	else 
	{
		cout<<"Unable to Mark the task as Completed. Please Try Again\n";
	}
}
void storeTasksFromFile(vector <task> &v , int &maxId)
{
	if(v.empty()){
		string input;
		ifstream storeData("task.txt");
		while(getline(storeData, input))
		{	        
			istringstream iss(input);
			string taskIdStr, taskName, dueDate, completed, priority;
			if (getline(iss, taskIdStr, ',') && getline(iss, taskName, ',') &&
			getline(iss, dueDate, ',') && getline(iss, completed, ',') &&
			getline(iss, priority, '\n'))
			{
				int num = stringToStr(taskIdStr);
				if(num > maxId)
				{
					maxId = num;
				}
				task newTask(taskName, dueDate, priority[0], num);
				newTask.completed = completed; 
				v.push_back(newTask);	
			}
		}
		storeData.close();
	}
}


/*
Validate Inputs:

// Function to validate a single character input
char validateCharacter() {
    char input;
    bool validInput = false;

    do {
        std::cout << "Enter a single character: ";

        if (std::std::cin >> input) {
            if (std::std::cin.peek() == '\n') {
                validInput = true;
            } else {
                std::cout << "Invalid input. Please enter only a single character." << std::endl;
                std::std::cin.clear();
                std::std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else {
            std::cout << "Invalid input. Please enter a single character." << std::endl;
            std::std::cin.clear();
            std::std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!validInput);

    return input;
}

// Function to validate an integer input
int validateInteger() {
    int input;
    bool validInput = false;

    do {
        std::cout << "Enter an integer: ";

        if (std::std::cin >> input) {
            if (std::std::cin.peek() == '\n') {
                validInput = true;
            } else {
                std::cout << "Invalid input. Please enter only an integer." << std::endl;
                std::std::cin.clear();
                std::std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::std::cin.clear();
            std::std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!validInput);

    return input;
}
*/