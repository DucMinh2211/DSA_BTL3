/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list){
        this->copyFrom(list);
    }
    
    void sort(int (*comparator)(T&,T&)=0){
        //TODO: implement this function
        //     - You should implement the merge sort algorithm

        // Lambda để trộn hai nửa danh sách
        auto merge = [&](typename DLinkedList<T>::Node* left, 
                        typename DLinkedList<T>::Node* right) -> typename DLinkedList<T>::Node* {
            typename DLinkedList<T>::Node dummy; // Dummy node cho danh sách tạm
            typename DLinkedList<T>::Node* current = &dummy;

            while (left and right) {
                if (compare(left->data, right->data, comparator) <= 0) {
                    current->next = left;
                    left->prev = current;
                    left = left->next;
                } else {
                    current->next = right;
                    right->prev = current;
                    right = right->next;
                }
                current = current->next;
            }

            // Thêm các nút còn lại
            if (left) {
                current->next = left;
                left->prev = current;
            }
            if (right) {
                current->next = right;
                right->prev = current;
            }

            return dummy.next; // Trả về nút đầu tiên của danh sách tạm
        };

        // Lambda để chia danh sách thành hai nửa
        auto split = [&](typename DLinkedList<T>::Node* head) -> typename DLinkedList<T>::Node* {
            typename DLinkedList<T>::Node* slow = head;
            typename DLinkedList<T>::Node* fast = head;

            while (fast and fast->next) {
                slow = slow->next;
                fast = fast->next->next;
            }

            typename DLinkedList<T>::Node* mid = slow->next;
            slow->next = nullptr;
            if (mid) mid->prev = nullptr;

            return mid;
        };

        // Lambda để thực hiện merge sort
        auto mergeSort = [&](autoand self, typename DLinkedList<T>::Node* head) -> typename DLinkedList<T>::Node* {
            if (!head or !head->next) return head;

            typename DLinkedList<T>::Node* mid = split(head);

            typename DLinkedList<T>::Node* left = self(self, head);
            typename DLinkedList<T>::Node* right = self(self, mid);

            return merge(left, right);
        };

        // Bỏ qua dummy nodes và gọi mergeSort
        typename DLinkedList<T>::Node* firstNode = this->head->next; // Nút thực đầu tiên
        typename DLinkedList<T>::Node* lastNode = this->tail->prev;  // Nút thực cuối cùng

        typename DLinkedList<T>::Node* sortedList = mergeSort(mergeSort, firstNode);

        // Cập nhật lại head và tail
        this->head->next = sortedList;
        sortedList->prev = this->head;

        typename DLinkedList<T>::Node* tail = sortedList;
        while (tail->next) tail = tail->next;

        this->tail->prev = tail;
        tail->next = this->tail;
    };
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */

