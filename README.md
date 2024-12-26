# laba3
Реализованы следующие хранилища для поиска данных **хеш таблица** и **сбалансированное дерево**.
Проверены и протистированы на разраяженных матрицах и векторах
## Btree
 - BTree(int order = 3);
    
 - ~BTree();
    
 - size_t GetCount() const;
    
 - size_t GetCapacity() const;
    
 - TElement Get(const TKey &key) const;
    
 - bool ContainsKey(const TKey &key) const;
    
 - void Add(const TKey &key, const TElement &element);
    
 - void Remove(const TKey &key);
    
 - void Update(const TKey &key, const TElement &element);
    
 - UnqPtr<IDictionaryIterator<TKey, TElement>> GetIterator() const;

## Hash Table
 - HashTable(size_t initialCapacity = 16);

 - ~HashTable();

 - size_t GetCount() const ;

 - size_t GetCapacity() const ;

 - TElement Get(const TKey &key) const ;

 - bool ContainsKey(const TKey &key) const ;

 - void Add(const TKey &key, const TElement &element) ;

 - void Remove(const TKey &key) ;

 - void Update(const TKey &key, const TElement &element) ;

  - UnqPtr<IDictionaryIterator<TKey, TElement>> GetIterator() const ;
