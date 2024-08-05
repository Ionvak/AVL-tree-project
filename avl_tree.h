#ifndef TREE

#define TREE

#include <cmath>

template<typename Key, typename Info>
class AvlTree{
private:
    struct Node{
        Key id;
        Info data;
        int height;
        Node* left;
        Node* right;

        Node(Key label, Info value, int length = 1, Node* lnode = nullptr, Node* rnode = nullptr) :id(label), data(value), height(length), left(lnode), right(rnode){}
    };

    Node* Root = nullptr;
    unsigned int Size = 0;

//Helper methods.

    int SizeAux(Node* element, int& cnt) const{
       if(element) Size2(element->left, ++cnt);
       if(element) Size2(element->right, ++cnt);
       return cnt;
    }

    void GraphAux(const Node* element, const int n) const{
        if(element->right != nullptr) GraphAux(element->right, n+1);
        int i = 0;
        while(i++ < n) std::cout << '\t';
        if(element == Root) std::cout << "Root";
        std::cout << "->(" << element->id << ',' << element->data << ')' << std::endl;
        if(element->left != nullptr) GraphAux(element->left, n+1);
    }

    void AssignAux(Node* element){
        Insert(element->id, element->data);
        if(element->left) AssignAux(element->left);
        if(element->right) AssignAux(element->right);
    }

    void ClearAux(Node*& element){
        if(element->right) ClearAux(element->right);
        if(element->left) ClearAux(element->left);
        delete element;
        element = nullptr;
    }

        void LeftRotate(Node*& pivot){
            Node* temp = pivot;
            pivot = pivot->right;
            temp->right = pivot->left;
            pivot->left = temp;
        }

        void RightRotate(Node*& pivot){
            Node* temp = pivot;
            pivot = pivot->left;
            temp->left = pivot->right;
            pivot->right = temp;
        }

        void LRrotate(Node*& pivot){
            LeftRotate(pivot->left);
            RightRotate(pivot);
        }

        void RLrotate(Node*& pivot){
            RightRotate(pivot->right);
            LeftRotate(pivot);
        }

        void BalanceTree(const Key& target){
            bool found = false;
            BalanceTreeAux(Root,target,found);
        }

        void BalanceTreeAux(Node*& element, const Key& target, bool& found){
            while(!found && element != nullptr){
                if(element->id == target) found = true;
                else if(target > element->id) BalanceTreeAux(element->right,target,found);
                else if(target < element->id) BalanceTreeAux(element->left,target,found);
            }

            if(found && (element->left != nullptr || element->right != nullptr)){
                unsigned int lheight = element->left == nullptr ? 0 : element->left->height;
                unsigned int rheight = element->right == nullptr ? 0 : element->right->height;
                int bf = lheight - rheight;

                if(bf > 1){
                    if(element->left->left) RightRotate(element);
                    else LRrotate(element);
                    this->UpdateHeight();
                }
                else if(bf < -1){
                    if(element->right->right) LeftRotate(element);
                    else RLrotate(element);
                    this->UpdateHeight();
                }
            }
        }

    unsigned int Height(Node* element) const{
        if(element == nullptr) return 0;
        else return 1 + std::max(Height(element->left), Height(element->right));
    }

    void UpdateHeight(){ UpdateHeightAux(Root); }

    void UpdateHeightAux(Node* element){
        element->height = Height(element);
        if(element->left != nullptr) UpdateHeightAux(element->left);
        if(element->right != nullptr) UpdateHeightAux(element->right);
    }


    Node* GetNodeAux(const Key& target) const{
        Node* temp = Root;
        while(temp != nullptr){
            if(target > temp->id) temp = temp->right;
            else if(target < temp->id) temp = temp->left;
            else return temp;
        }
        return nullptr;
    }



public:
//Class methods.
    AvlTree(){}



    AvlTree(const Node* start) : Root(start), Size(Size2(start,0)){}



    ~AvlTree(){ this->Clear(); }



    AvlTree(const AvlTree& src){ *this = src; }



    bool IsEmpty() const{ return Root == nullptr; }



    int GetSize() const{ return this->Size; }



    unsigned int GetHeight() const{
         if(!this->IsEmpty()) return Root->height;
         else return 0;
    }



    int NodeHeight(const Key& node) const{
        Node* temp = GetNode(node);
        if(temp) return temp->height;
        else return 0;
}



    bool Search(const Key& target) const{
        Node* temp = Root;
        while(temp != nullptr){
            if(target > temp->id) temp = temp->right;
            else if(target < temp->id) temp = temp->left;
            else return true;
        }
        return false;
    }



    const Node* GetNode(const Key& target) const{
        Node* temp = Root;
        while(temp != nullptr){
            if(target > temp->id) temp = temp->right;
            else if(target < temp->id) temp = temp->left;
            else return temp;
        }
        return nullptr;
    }



    void Insert(const Key& label, const Info& value){
        if(this->IsEmpty()){
            Root = new Node(label,value,1);
            Size++;
        }

        if(!Search(label)){
            Node* temp = Root;
            while(temp != nullptr){
                if(label > temp->id){
                    if(temp->right == nullptr){
                        temp->right = new Node(label,value);
                        Size++;
                        break;
                    }
                    temp = temp->right;
                }
                else if(label < temp->id){
                    if(temp->left == nullptr){
                        temp->left = new Node(label,value);
                        Size++;
                        break;
                    }
                    temp = temp->left;
                }
            }

       this->UpdateHeight();
       this->BalanceTree(label);
        }
    }



    void Remove(const Key& label){
        if(!this->IsEmpty() && Root->id == label){
            if(Root->right == nullptr && Root->left == nullptr){
                delete Root;
                Root = nullptr;
                Size--;
            }
            else if(Root->right != nullptr && Root->left == nullptr){
                Node* temp = Root;
                Root = Root->right;
                delete temp;
                Size--;
            }
            else if(Root->right == nullptr && Root->left != nullptr){
                Node* temp = Root;
                Root = Root->left;
                delete temp;
                Size--;
                Root->height = 1;
            }
            else if(Root->right != nullptr && Root->left != nullptr){
                if(Root->right->left == nullptr){
                    Node* temp = Root;
                    Root->right->left = Root->left;
                    Root = Root->right;
                    delete temp;
                    Size--;
                    Root->height = 1;
                }
                else{
                    Node* temp = Root;
                    temp = temp->right;
                    while(temp->left->left != nullptr) temp = temp->left;
                    Root->id = temp->left->id;
                    Root->data = temp->left->data;
                    delete temp->left;
                    temp->left = nullptr;
                    Size--;
                    this->UpdateHeight();
                    this->BalanceTree(Root->id);
                }
            }
        }

        if(Search(label)){
            Node* curr = Root;
            Node* prev = Root;
            while(curr->id != label){
                prev = curr;
                if(label > curr->id) curr = curr->right;
                else if(label < curr->id) curr = curr->left;
            }

            if(curr->left == nullptr && curr->right == nullptr){
                if(label > prev->id){
                    prev->right = nullptr;
                    delete curr;
                    Size--;
                }
                else{
                    prev->left = nullptr;
                    delete curr;
                    Size--;
                }
            }

            else if(curr->right != nullptr && curr->left == nullptr){
                if(label > prev->id){
                    prev->right = prev->right->right;
                    delete curr;
                    Size--;
                }
                else{
                    prev->left = prev->left->right;
                    delete curr;
                    Size--;
                }
            }

            else if(curr->right == nullptr && curr->left != nullptr){
                if(label > prev->id){
                    prev->right = prev->right->left;
                    delete curr;
                    Size--;
                }
                else{
                    prev->left = prev->left->left;
                    delete curr;
                    Size--;
                }
            }

            else if(curr->right != nullptr && curr->left != nullptr){

                if(curr->right->left == nullptr){
                    if(label > prev->id){
                        curr->right->left = curr->left;
                        prev->right = prev->right->right;
                        delete curr;
                        Size--;
                    }
                    else{
                        curr->right->left = curr->left;
                        prev->left = prev->left->right;
                        delete curr;
                        Size--;
                    }
                }

                else{
                    if(label > prev->id) prev = prev->right;
                    else prev = prev->left;
                    curr = curr->right;
                    while(curr->left->left != nullptr) curr = curr->left;
                    prev->id = curr->left->id;
                    prev->data = curr->left->data;
                    delete curr->left;
                    curr->left = nullptr;
                    Size--;
                }

            }
            this->UpdateHeight();
            this->BalanceTree(prev->id);
        }
    }



    void Graph() const{ Graph(Root); }



    void Graph(const Node* subtree) const{
        if(subtree != nullptr) GraphAux(subtree,0);
        else std::cout << "Root->";
        std::cout << "\n\n";
    }



    void Clear(){
       if(!this->IsEmpty()){
        ClearAux(Root);
        Size = 0;
       }
    }



//Defined class operators.

    AvlTree& operator=(const AvlTree& src){
        this->Clear();
        if(!src.IsEmpty()) AssignAux(src.Root);
        return *this;
    }



    Info& operator[](const Key& key){
        if(this->Search(key)) return GetNodeAux(key)->data;
        else{
            this->Insert(key,Info());
            return GetNodeAux(key)->data;
        }
    }



    const Info& operator[](const Key& key) const{
        if(this->Search(key)) return GetNode(key)->data;
        else{
            this->Insert(key,Info());
            return GetNode(key)->data;
        }
    }


};



#endif // TREE
