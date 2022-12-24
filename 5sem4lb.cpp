#include "Notations.h"

int main() 
{
    setlocale(0, "");
    //25 61 59 81 26 50 77 19 60 80 2 93 6 70 27
    Tree bst;
    bst.insert(25);
    bst.insert(61);
    bst.insert(59);
    bst.insert(81);
    bst.insert(26);
    bst.insert(50);
    bst.insert(77);
    bst.insert(19);
    bst.insert(60);
    bst.insert(80);
    bst.insert(2);
    bst.insert(93);
    bst.insert(6);
    bst.insert(70);
    bst.insert(27);

    bst.min_elem();
    bst.max_elem();
    bst.Preorder();
    bst.Inorder();
    bst.Postorder();
    bst.search(77);
    bst.next_elem(80);
    bst.prev_elem(59);
    bst.remove(2);
    bst.Widthorder();
    bst.Print_tree_as_tree();



    Btree tree;
    /* 
    post = 98 654 * 5 / 7 1 1 + ^ /
    inf = (((98*654)/5)/(7^(1+1)))
    pref = / / * 98 654 5 ^ 7 + 1 1
    */
    cout << "Выберите тип вводимой записи:\n";
    cout << "0. Префиксная\n";
    cout << "1. Инфиксная\n";
    cout << "2. Постфиксная\n";
    int type;
    cin >> type;
    cout << "Введите запись: ";
    string str;
    cin.clear();
    cin.ignore(32756,'\n');
    getline(cin, str);
    switch (type)
    {
    case 0:
        tree.pre_to_post(str);
        break;
    case 1:
        tree.inf_to_post(str);
        break;
    case 2:
        tree.post_to_post(str);
        break;
    default:
        cout << "неверно введён тип записи\n";
        break;
    }
    tree.creat_tree();

    cout << endl << "Prefix: "; tree.Preorder();
    cout << endl << "Postfix: "; tree.Postorder();
    cout << endl << "Infix: "; tree.Inorder();

    system("pause");
}