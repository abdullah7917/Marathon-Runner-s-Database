//Abdullah Ali Khan, cs 163 - in person, 11/30/2025
//This file calls all the inputs
#include "bst.h"

void get_stream_input(stream & s)
{
    char buffer[100];

    cout << "Enter Stream ID: ";
    cin.ignore();
    cin.getline(buffer, 100);
    s.stream_id = new char[strlen(buffer) + 1];
    strcpy(s.stream_id, buffer);

    cout << "Enter Streamer Name: ";
    cin.getline(buffer, 100);
    s.name = new char[strlen(buffer) + 1];
    strcpy(s.name, buffer);

    cout << "Enter Game: ";
    cin.getline(buffer, 100);
    s.game = new char[strlen(buffer) + 1];
    strcpy(s.game, buffer);

    cout << "Enter Number of Viewers: ";
    cin >> s.viewers;

    cout << "Enter Duration (minutes): ";
    cin >> s.duration;
    cin.ignore(); // clear newline

    cout << "Enter Language: ";
    cin.getline(buffer, 100);
    s.language = new char[strlen(buffer) + 1];
    strcpy(s.language, buffer);

    cout << "Enter Region: ";
    cin.getline(buffer, 100);
    s.region = new char[strlen(buffer) + 1];
    strcpy(s.region, buffer);

    cout << "Enter Category: ";
    cin.getline(buffer, 100);
    s.category = new char[strlen(buffer) + 1];
    strcpy(s.category, buffer);

    cout << "Enter Start Time: ";
    cin.getline(buffer, 100);
    s.start_time = new char[strlen(buffer) + 1];
    strcpy(s.start_time, buffer);
}

int main()
{
    table bst;
    int choice = 0;

    while (choice != 7)
    {
        cout << "\nEnter the task number to perform:\n";
        cout << "1 = Insert a Stream\n";
        cout << "2 = Display All Streams\n";
        cout << "3 = Remove a Stream\n";
        cout << "4 = Retrieve a Stream\n";
	cout << "5 = Display an event by game \n";
	cout << "6 = Display height\n";
        cout << "7 = Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 1)
        {
            stream s;
            get_stream_input(s);
            if (bst.insert(s))
                cout << "Stream inserted successfully!\n";
            else
                cout << "Failed to insert stream.\n";
            bst.destroy_stream(s);
        }
        else if (choice == 2)
        {
            bst.display_all();
        }
        else if (choice == 3)
        {
            char name[100], game[100];
            cout << "Enter Streamer Name to remove: ";
            cin.getline(name, 100);
            cout << "Enter Game to remove: ";
            cin.getline(game, 100);

            if (bst.remove(name, game))
                cout << "Stream removed successfully!\n";
            else
                cout << "Stream not found.\n";
        }
        else if (choice == 4)
        {
            char name[100], id[100];
            cout << "Enter Streamer Name to retrieve: ";
            cin.getline(name, 100);
            cout << "Enter Stream ID to retrieve: ";
            cin.getline(id, 100);

            stream found;
            if (bst.retrieve(name, id, found))
            {
                cout << "\nFound Stream:\n";
                cout << "Streamer: "   << found.name << "\n";
                cout << "Stream ID: "  << found.stream_id << "\n";
                cout << "Game: "       << found.game << "\n";
                cout << "Viewers: "    << found.viewers << "\n";
                cout << "Duration: "   << found.duration << "\n";
                cout << "Language: "   << found.language << "\n";
                cout << "Region: "     << found.region << "\n";
                cout << "Category: "   << found.category << "\n";
                cout << "Start time: " << found.start_time << "\n";

                bst.destroy_stream(found);
            }
            else
            {
                cout << "Stream not found.\n";
            }
        }
	
	else if (choice == 5)
	{
	    char game[100];
	    cin.ignore(); 
	    cout << "Enter game: ";
	    cin.getline(game, 100);

	    int count = bst.display_game(game);

	    if (count > 0)
	    {
		cout << "\nDisplayed " << count << " stream(s) for game: " << game << "\n";
	    }
	    else
	    {
		cout << "No streams found for game: " << game << "\n";
	    }
	}

	else if (choice == 6)
	{
		int height = bst.height(); 
		cout<< "The height of the BST is: "<<height<<"\n";
	}

        else if (choice == 7)
        {
            cout << "\nThank you for using my program.\n";
        }
        else
        {
            cout << "Invalid task number. Please enter 1-5.\n";
        }
    }

    return 0;
}
