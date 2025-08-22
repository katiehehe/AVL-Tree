#include <iostream>
#include <sstream>
#include <iomanip>
#include "AVL.h"

using namespace std;

int main(){
    // read in the number of commands
    int n;
    cin >> n;
    cin.ignore();

    AVLTree tree;

    for(int i = 0; i < n; ++i)
    {
        string fullLine;
        getline(cin, fullLine);
        istringstream newCin(fullLine);

        string function, name, id;
        // get the function name
        newCin >> function;
        if(function == "insert")
        {
            // std::quoted removes quotes from the string (https://en.cppreference.com/w/cpp/io/manip/quoted)
            newCin >> quoted(name);
            newCin >> id;
            // if the tree successfully inserted the name and id
            if(tree.insert(name, id))
                cout << "successful" << endl;
            else
                cout << "unsuccessful" << endl;
        }
        else if(function == "remove")
        {
            newCin >> id;
            // if the tree successfully removed the id
            if(tree.remove(id))
                cout << "successful" << endl;
            else
                cout << "unsuccessful" << endl;
        }
        else if(function == "search")
        {
            newCin >> quoted(name); // string name could be a name or an id
            string s = tree.searchId(name);
            if(s != "0") // s = 0 when "name" is not a valid id
            {
                if(s == "1") // "name" is a valid id but it was not found
                {
                    cout << "unsuccessful" << endl;
                }
                else
                {
                    cout << s << endl;
                }
            }
            else
            {
                // call the search function to look for the name
                string m = tree.searchName(name);
                if(m == "0" || m == "1")
                {
                    cout << "unsuccessful" << endl;
                }
                else
                {
                    cout << m << endl;
                }
            }
        }
        else if(function == "printInorder")
        {
            vector<string> print = {};
            tree.printInorder(print);
            for(int j = 0; j < print.size() - 1; ++j)
            {
                cout << print[j] << ", ";
            }
            if(!print.empty())
            {
                cout << print[print.size() - 1] << endl;
            }
        }
        else if(function == "printPreorder")
        {
            vector<string> print = {};
            tree.printPreorder(print);
            for(int j = 0; j < print.size() - 1; ++j)
            {
                cout << print[j] << ", ";
            }
            if(!print.empty())
            {
                cout << print[print.size() - 1] << endl;
            }
        }
        else if(function == "printPostorder")
        {
            vector<string> print = {};
            tree.printPostorder(print);
            for(int j = 0; j < print.size() - 1; ++j)
            {
                cout << print[j] << ", ";
            }
            if(!print.empty())
            {
                cout << print[print.size() - 1] << endl;
            }
        }
        else if(function == "printLevelCount")
        {
            cout << tree.printLevelCount() << endl;
        }
        else if(function == "removeInorder")
        {
            int m;
            newCin >> m;
            // if the mth node is successfully removed
            if(tree.removeInorder(m))
                cout << "successful" << endl;
            else
                cout << "unsuccessful" << endl;
        }
        // the command is invalid
        else
        {
            cout << "unsuccessful" << endl;
        }
    }
	return 0;
}
