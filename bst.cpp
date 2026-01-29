//Abdullah Ali Khan, cs 163 - in person, 11/30/2025
//This file writes all the fuction

#include "bst.h"
table::table()
{
    root = nullptr;
}

table::~table()
{
    remove_all(root);
}

int table::remove_all(node *& root)
{
    if (!root) return 0;

    remove_all(root->left);
    remove_all(root->right);

    destroy_stream(root->data);
    delete root;
    root = nullptr;

    return 1;
}

void table::copy_stream(stream & data, const stream & to_add)const
{
    data.stream_id = new char[strlen(to_add.stream_id) + 1];
    strcpy(data.stream_id, to_add.stream_id);

    data.name = new char[strlen(to_add.name) + 1];
    strcpy(data.name, to_add.name);

    data.game = new char[strlen(to_add.game) + 1];
    strcpy(data.game, to_add.game);

    data.language = new char[strlen(to_add.language) + 1];
    strcpy(data.language, to_add.language);

    data.region = new char[strlen(to_add.region) + 1];
    strcpy(data.region, to_add.region);

    data.category = new char[strlen(to_add.category) + 1];
    strcpy(data.category, to_add.category);

    data.start_time = new char[strlen(to_add.start_time) + 1];
    strcpy(data.start_time, to_add.start_time);

    data.viewers  = to_add.viewers;
    data.duration = to_add.duration;
}

void table::destroy_stream(stream & data)
{
    delete [] data.stream_id;
    delete [] data.name;
    delete [] data.game;
    delete [] data.language;
    delete [] data.region;
    delete [] data.category;
    delete [] data.start_time;

    data.stream_id = nullptr;
    data.name = nullptr;
    data.game = nullptr;
    data.language = nullptr;
    data.region = nullptr;
    data.category = nullptr;
    data.start_time = nullptr;
}

int table::insert (const stream & to_add)
{
	return insert (root, to_add);
}

int table::insert (node *& root, const stream & to_add)
{
	if (!root)
	{
		root = new node;
		copy_stream(root->data, to_add);
		root->left = root->right = nullptr;
		return 1;
	}

	if (strcmp (to_add.name , root->data.name) <0)
		return insert (root->left, to_add);
	else 
		return insert (root->right, to_add);

}

int table::display_all()const
{
	if (!root)return 0;
	return display_all(root);
}

int table::display_all(node * root)const 
{
	if (!root) return 0;

	display_all(root->left);
	 cout   << "\nStreamer: "   << root->data.name
         	<< "\nStream ID: "  << root->data.stream_id
        	<< "\nGame: "       << root->data.game
         	<< "\nViewers: "    << root->data.viewers
         	<< "\nDuration: "   << root->data.duration
         	<< "\nLanguage: "   << root->data.language
         	<< "\nRegion: "     << root->data.region
         	<< "\nCategory: "   << root->data.category
         	<< "\nStart time: " << root->data.start_time
         	<< "\n---------------------------\n";
	 
	 display_all(root->right);

	 return 1;
}

int table::remove(const char * streamer_name, const char * game)
{
    return remove(root, streamer_name, game);
}

int table::remove( node *& root,const char*name, const char* game )
{
	if (!root)return 0;

	int compare = strcmp (name, root->data.name);

	if (compare < 0)
		return remove(root->left, name, game);
	
	if (compare >0)
		return remove(root->right, name, game);
	//same name 
	if (strcmp (game , root->data.game )!=0)
	{
		if (remove (root->left, name, game)) return 1;
		return (remove (root->right, name, game));
	}

	// no children 
	if (!root->left && !root->right)
	{
		destroy_stream(root->data);
		delete root;
		root = nullptr;
		return 1;
	}

	//right child only 
	if (!root->left)
	{
		node * temp = root->right;
		destroy_stream (root->data);
		delete root;
		root = temp;
		return 1;
	}
	
	//left child only
	if (!root->right)
	{
		node * temp = root->left;
		destroy_stream (root->data);
                delete root;
                root = temp;
                return 1;

	}

	// 2 children -> replace with IOS
	node * ios = root->right;
	while (ios->left)
		ios = ios->left;

	destroy_stream (root->data);
	copy_stream(root->data, ios->data);

	return remove(root->right, ios->data.name, ios->data.game);
	

}

int table::retrieve(const char * streamer_name, const char * stream_id, stream & found) const
{
    return retrieve(root, streamer_name, stream_id, found);
}

int table::retrieve(node* root, const char * name, const char * stream_id, stream & found)const
{
	if (!root)return 0;

	int compare = strcmp(name, root->data.name);

	if (compare <0)
		return retrieve(root->left, name, stream_id, found);

	if (compare >0)
		return retrieve(root->right, name, stream_id, found);

	if (strcmp (stream_id, root->data.stream_id) == 0)
	{
		copy_stream(found, root->data);
        	return 1;
	}
	
	if (retrieve(root->left, name, stream_id, found)) return 1;
	return retrieve(root->right, name, stream_id, found);


}

int table::display_game(const char * game) const
{
    return display_game(root, game);
}


int table::display_game(node * root, const char * game) const
{
	if (!root)return 0;

	int count = 0;

	count += display_game(root->left, game );

	if (strcmp (root->data.game , game )== 0)
	{
		cout   << "\nStreamer: "   << root->data.name
		       << "\nStream ID: "  << root->data.stream_id
		       << "\nGame: "       << root->data.game
		       << "\nViewers: "    << root->data.viewers
		       << "\nDuration: "   << root->data.duration
		       << "\nLanguage: "   << root->data.language
		       << "\nRegion: "     << root->data.region
		       << "\nCategory: "   << root->data.category
		       << "\nStart time: " << root->data.start_time
		       << "\n---------------------------\n";

       
		++count;
	}

	count += display_game(root->right, game );

	return count;
}

int table::height() const
{
    return height(root);
}

int table::height(node* root) const
{
    if (!root)
        return 0;

    int left_height = height(root->left);
    int right_height = height(root->right);

    if (left_height > right_height)
        return 1 + left_height;
    else
        return 1 + right_height;
}















