#include <iostream>
#include <stack>
using namespace std;
template<class T>
struct c_Node{
    T m_data;
    c_Node<T>* m_child[2];

    c_Node(T dato){

        m_data=dato;
        m_child[0]=nullptr;
        m_child[1]=nullptr;
    }
};
template<class T>
struct c_BT_Iterator{
    pair<c_Node<T>*,int> m_pair;
    int m_id;
    pair<int,int> ayuda;
    stack<pair<c_Node<T>*,int> > m_stack;
    c_BT_Iterator<T> operator=(c_BT_Iterator<T> x){
        m_stack=x.m_stack;
        return *this;
    }
    bool operator!=(c_BT_Iterator<T> x){
        return m_stack!=x.m_stack;
    }
    c_BT_Iterator<T> operator++(int){
        m_pair=m_stack.top();
        do{
            m_stack.pop();
            if(m_pair.second==m_id){
                m_stack.push(make_pair(m_pair.first,(m_id+1)%3));
                if(m_pair.first->m_child[ayuda.first]) m_stack.push(make_pair(m_pair.first->m_child[ayuda.first],m_id));
            }
            else if(m_pair.second==(m_id+1)%3){
                m_stack.push(make_pair(m_pair.first,(m_id+2)%3));
                if(m_pair.first->m_child[ayuda.second]) m_stack.push(make_pair(m_pair.first->m_child[ayuda.second],m_id));
            }
            m_pair=m_stack.top();
        }
        while(m_pair.second!=1 and !m_stack.empty());
        return *this;
    }
    T operator*(){
        m_pair=m_stack.top();
        return m_pair.first->m_data;
    }
};
template <class T>
class c_BT_Inorder_Iterator : public c_BT_Iterator<T>{
public:
    c_BT_Inorder_Iterator(){
        this->m_id=0;
        this->ayuda.first=0;
        this->ayuda.second=1;
    }
};

template <class T>
class c_BT_Preorder_Iterator : public c_BT_Iterator<T>{
public:
    c_BT_Preorder_Iterator(){
        this->m_id=1;
        this->ayuda.first=0;
        this->ayuda.second=1;
    }
};

template <class T>
class c_BT_Postorder_Iterator : public c_BT_Iterator<T>{
public:
    c_BT_Postorder_Iterator(){
        this->m_id=2;
        this->ayuda.first=0;
        this->ayuda.second=1;
    }
};
template <class T>
class c_BT_Reverse_Iterator : public c_BT_Iterator<T>{
public:
    c_BT_Reverse_Iterator(){
        this->m_id=0;
        this->ayuda.first=1;
        this->ayuda.second=0;
    }
};
template<class T>
class c_BinTRee{
public:
    typedef c_BT_Inorder_Iterator<T> inorder_iterator;
    typedef c_BT_Postorder_Iterator<T> postorder_iterator;
    typedef c_BT_Preorder_Iterator<T> preorder_iterator;
    typedef c_BT_Reverse_Iterator<T> reverse_iterators;
    c_BinTRee();
    bool busca(T , c_Node<T>**&);
    bool inserta(T);
    bool saca(T);
    void inorden(c_Node<T>*);
    inorder_iterator inbegin();
    inorder_iterator inend();
    postorder_iterator postbegin();
    postorder_iterator postend();
    preorder_iterator prebegin();
    preorder_iterator preend();
    reverse_iterators revbegin();
    reverse_iterators revend();
    c_Node<T>*m_root;
};
template<class T>
c_BinTRee<T>::c_BinTRee(){
    m_root=nullptr;
}
template<class T>
bool c_BinTRee<T>::busca(T x, c_Node<T>**&p)
{
    for(p=&m_root; (*p) && (*p)->m_data!=x; p=&(*p)->m_child[(*p)->m_data<x]);
    return (*p);
}
template<class T>

bool c_BinTRee<T>::inserta(T x)
{
    c_Node<T>**p;

    if(busca(x,p)) return 0;

    *p=new c_Node<T>(x);

    return 1;
}
template<class T>

bool c_BinTRee<T>::saca(T x)
{
    c_Node<T>** p;
    c_Node<T>* temp;

    if(!busca(x,p)) return 0;
    temp=(*p);
    if((*p)->m_child[0] && (*p)->m_child[1]){

        for(p=&((*p)->m_child[0]); (*p)->m_child[1]; p=&((*p)->m_child[1]));
        swap((*p)->m_data,temp->m_data);
    }
    temp=(*p);
    (*p)=(*p)->m_child[!!(*p)->m_child[1]];
    return 1;
}
template<class T>
typename c_BinTRee<T>::inorder_iterator c_BinTRee<T>::inbegin(){
    c_Node<T>* p=m_root;
    inorder_iterator it;
    it.m_stack.push(make_pair(p,0));
    it++;
    return it;
}

template<class T>
typename c_BinTRee<T>::inorder_iterator c_BinTRee<T>::inend(){
    return inorder_iterator();
}

template<class T>
typename c_BinTRee<T>::preorder_iterator c_BinTRee<T>::prebegin()
{
    c_Node<T>* p=m_root;
    preorder_iterator it;
    it.m_stack.push(make_pair(p,1));
    return it;
}

template<class T>
typename c_BinTRee<T>::preorder_iterator c_BinTRee<T>::preend(){
    return preorder_iterator();
}

template<class T>
typename c_BinTRee<T>::postorder_iterator c_BinTRee<T>::postbegin(){
    c_Node<T>* p=m_root;
    postorder_iterator it;
    it.m_stack.push(make_pair(p,2));
    it++;
    return it;
}

template<class T>
typename c_BinTRee<T>::postorder_iterator c_BinTRee<T>::postend(){
    return postorder_iterator();
}
template<class T>
typename c_BinTRee<T>::reverse_iterators c_BinTRee<T>::revbegin(){
    c_Node<T>* p=m_root;
    reverse_iterators it;
    it.m_stack.push(make_pair(p,0));
    it++;
    return it;
}

template<class T>
typename c_BinTRee<T>::reverse_iterators c_BinTRee<T>::revend(){
    return reverse_iterators();
}
int main()
{
    c_BinTRee<int> arbol;
    c_BinTRee<int>::inorder_iterator it;
    c_BinTRee<int>::postorder_iterator post_it;
    c_BinTRee<int>::preorder_iterator pre_it;
    c_BinTRee<int>::reverse_iterators rev;
    arbol.inserta(4);
    arbol.inserta(6);
    arbol.inserta(3);
    arbol.inserta(8);
    arbol.inserta(9);
    arbol.inserta(1);
    cout<<"inorden: ";
    for(it=arbol.inbegin();it!=arbol.inend(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    cout<<"postorden: ";
    for(post_it=arbol.postbegin();post_it!=arbol.postend(); post_it++){

        cout<<*post_it<<" ";
    }
    cout<<endl;
    cout<<"preorden: ";
    for(pre_it=arbol.prebegin();pre_it!=arbol.preend(); pre_it++){

        cout<<*pre_it<<" ";
    }
    cout<<endl;
    cout<<"reverse: ";
    for(rev=arbol.revbegin();rev!=arbol.revend(); rev++){
        cout<<*rev<<" ";
    }
}
