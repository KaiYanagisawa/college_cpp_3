f (find_value(subject_point) == value)
    // {
    //     return 1;
    // }
    // else if (find_value(subject_point) != value)
    // {
    //     cerr << "ERROR:key and different value have already been registered:" << find_key(subject_point) << " " << value << " " << find_value(subject_point) << "\n";
    //     exit(EXIT_FAILURE);
    // }
    // else if (subject_point == NULL)
    // {
    //     /*未登録だったらハッシュ値hashvalueにおけるリストの先頭ノードtable[hashvalue]にkeyとvalueを格納した新しいノードを追加*/
    //     int hash_value = get_hashvalue(key);
    //     Node *p = table[hash_value];
    //     // p->key = key;
    //     // p->value = value;
    // }