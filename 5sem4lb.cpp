#include "Notations.h"

int main() 
{
    setlocale(0, "");
    
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