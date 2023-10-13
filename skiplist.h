#include <string>
#include <iostream>
#include <climits>
#include <cstdlib>
#include <random>


bool flipCoin() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1);

    return distribution(gen) == 0;
}
template<typename K, typename V>
class Node{
    public:
        Node *next;
        Node *above;
        Node *prev;
        Node *below;
        Node(const K k, const V v){
            this->key = k;
            this->value = v;
            this->next = NULL;
            this->above = NULL;
            this->prev = NULL;
            this->below = NULL;
        }
        Node(const K k){
            this->key = k;
            this->next = NULL;
            this->above = NULL;
            this->prev = NULL;
            this->below = NULL;
        }
        K key;
        V value;

};
template<typename K, typename V>
class SkipList{      
    private:
        Node<K, V>* head;
        Node<K, V>* tail;

        const int neg_infinity = INT_MIN;
        const int pos_infinity = INT_MAX;

        int HeightSkipList = 0;
        
        void CanIncreaseLevel(int level){
            if(level >= HeightSkipList){
                HeightSkipList++;
                AddEmptyLevel();
            }
        }

        void AddEmptyLevel(){
            Node<K, V>* newHeadNode = new Node<K,V>(neg_infinity);
            Node<K, V>* newTailNode = new Node<K,V>(pos_infinity);

            newHeadNode->next = newTailNode;
            newHeadNode->below = head;
            newTailNode->prev = newHeadNode;
            newTailNode->below = tail;
            head->above = newHeadNode;
            tail->above = newTailNode;

            head = newHeadNode;
            tail = newTailNode;
        }

        Node<K, V>* InsertAfterAbove(Node<K, V>* AbovePosition, Node<K, V>* OriginalPosition, K Key){
            Node<K, V>* newNode = new Node<K, V>(Key);
            Node<K, V>* NodeBeforeNewNode = AbovePosition->below->below;

            setBeforeAndAfterReferences(OriginalPosition, newNode);
            setAboveAndBelowReferences(AbovePosition, Key, newNode, NodeBeforeNewNode);

            return newNode;
        }
        
        void setBeforeAndAfterReferences(Node<K, V>* OriginalPosition, Node<K, V>* newNode){
            OriginalPosition->next->prev = newNode;
            newNode->prev = OriginalPosition;
            newNode->next = OriginalPosition->next;
            OriginalPosition->next = newNode;
            
        }
        
        void setAboveAndBelowReferences(Node<K, V>* AbovePosition, K Key, Node<K, V>* newNode, Node<K, V>* NodeBeforeNewNode){
            if(NodeBeforeNewNode != NULL){
                while(true){
                    if(NodeBeforeNewNode->next->key != Key){
                        NodeBeforeNewNode = NodeBeforeNewNode->next;
                    }else
                        break;
                }

                newNode->below = NodeBeforeNewNode->next;
                NodeBeforeNewNode->next->above = newNode;
            }

            if(AbovePosition != NULL){
                if(AbovePosition->next->key == Key){
                    newNode->above = AbovePosition->next;
                }
            }
        }
        
        void RemoveReferencesToNode(Node<K, V>* NodeToBeRemoved){
            Node<K, V>* AfterNodeToBeRemoved = NodeToBeRemoved->next;
            Node<K, V>* BeforeNodeToBeRemoved = NodeToBeRemoved->prev;

            BeforeNodeToBeRemoved->next = AfterNodeToBeRemoved;
            AfterNodeToBeRemoved->prev = BeforeNodeToBeRemoved;

        }
    
    
    public:
        
        SkipList(const int k, const V v){
            head = new Node<K, V>(neg_infinity, v);
            tail = new Node<K, V>(pos_infinity, v);
            head->next = tail;
            tail->prev = head;
        }

        
        Node<K, V>* SearchElement(K SearchKey){
            Node<K, V>* cur = head;
            while(cur->below != NULL){
                cur = cur->below;
                while(SearchKey >= cur->next->key){
                    cur = cur->next;
                }
            }

            return cur;
        }

        
        Node<K, V>* InsertElement(K InsertKey){
            Node<K, V>* position = SearchElement(InsertKey);
            Node<K, V>* originpos;

            if(position->key == InsertKey){
                return position;
            }

            int level = -1;
            int NumOfHead = -1;
            
            do{
                NumOfHead++;
                level++;
                CanIncreaseLevel(level);

                originpos = position;

                while(position->above == NULL){
                    position = position->prev;
                }
                position = position->above;
                
                originpos = InsertAfterAbove(position, originpos, InsertKey);

            } while(flipCoin() == true);
        }
        
        Node<K, V>* DeleteElement(K DeleteKey){
            Node<K, V>* NodeToBeRemoved = SearchElement(DeleteKey);
            
            if(NodeToBeRemoved->key != DeleteKey){
                return NULL;
            }

            RemoveReferencesToNode(NodeToBeRemoved);

            while(NodeToBeRemoved != NULL){
                RemoveReferencesToNode(NodeToBeRemoved);

                if(NodeToBeRemoved->above != NULL){
                    NodeToBeRemoved = NodeToBeRemoved->above;
                }else{
                    break;
                }
            }
            return NodeToBeRemoved;

        }

        void DisplaySkipList() {
            Node<K, V>* currentLevelNode = head;
            int level = HeightSkipList;

            while (currentLevelNode) {
                Node<K, V>* currentNode = currentLevelNode;

                std::cout << "Level " << level << ": " << std::endl; 

                while (currentNode) {
                    std::cout << "   " <<  currentNode->key << currentNode->value << "   ";

                    currentNode = currentNode->next;
                }

                std::cout << std::endl;

                currentLevelNode = currentLevelNode->below;
                level--;
        }
}
};  